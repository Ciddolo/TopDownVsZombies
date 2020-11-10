#include "CPP_Enemy.h"

#define DT GetWorld()->DeltaTimeSeconds
#define PRINT GEngine->AddOnScreenDebugMessage(-1, 0.0f, FColor::Yellow,
#define PRINT_ONE GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Yellow,
#define PRINT_FIVE GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow,

ACPP_Enemy::ACPP_Enemy()
{
	PrimaryActorTick.bCanEverTick = true;

	Sensing = CreateDefaultSubobject<UPawnSensingComponent>("SensingComponent");
	Sensing->HearingThreshold = 600.0f;
	Sensing->LOSHearingThreshold = 1200.0f;
	Sensing->SightRadius = 800.0f;
	Sensing->SensingInterval = 0.2f;
	Sensing->HearingMaxSoundAge = 1.0f;
	Sensing->bOnlySensePlayers = false;
	Sensing->SetPeripheralVisionAngle(45.0f);

	GetCapsuleComponent()->SetCollisionProfileName("Enemy");
}

void ACPP_Enemy::BeginPlay()
{
	Super::BeginPlay();

	Sensing->OnSeePawn.AddDynamic(this, &ACPP_Enemy::OnSeePlayer);
	Sensing->OnSeePawn.AddDynamic(this, &ACPP_Enemy::OnSeeEnemy);
	Sensing->OnHearNoise.AddDynamic(this, &ACPP_Enemy::OnHearPlayer);
}

void ACPP_Enemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (IsAlive)
	{
		if (CurrentBehaviour == EnemyBehaviour::Chase)
			LostTarget(DeltaTime);
	}
}

void ACPP_Enemy::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

void ACPP_Enemy::OnSeePlayer(APawn* Pawn)
{
	if (!IsAlive)
		return;

	if (!Cast<ACPP_Enemy>(Pawn))
	{
		//PRINT_ONE TEXT("SEE PLAYER"));
		Target = Pawn;
		LostTargetTime = ChaseTime;
		CurrentBehaviour = EnemyBehaviour::Chase;
	}
}

void ACPP_Enemy::OnSeeEnemy(APawn* Pawn)
{
	if (!IsAlive)
		return;

	ACPP_Enemy* Zombie = Cast<ACPP_Enemy>(Pawn);
	if (Zombie)
	{
		if (Zombie->IsAlive && Zombie->Target)
		{
			//PRINT_ONE TEXT("SEE ENEMY"));
			Target = Zombie->Target;
			LostTargetTime = Zombie->LostTargetTime;
			CurrentBehaviour = EnemyBehaviour::Chase;
		}
	}
}

void ACPP_Enemy::OnHearPlayer(APawn * Pawn, const FVector &Location, float Volume)
{
	if (CurrentBehaviour == EnemyBehaviour::Chase || CurrentBehaviour == EnemyBehaviour::Attack)
		return;

	if (Volume <= 1.0f)
	{
		if (FollowHighNoise)
			return;

		//PRINT_ONE TEXT("HEAR SOMETHING LOW"));
		SetSpeed(InvestigateSpeed);
	}
	else
	{
		//PRINT_ONE TEXT("HEAR SOMETHING HIGH"));
		SetSpeed(RunSpeed);
		FollowHighNoise = true;
	}

	CurrentBehaviour = EnemyBehaviour::Investigate;
	NoiseLocation = Location;
}

void ACPP_Enemy::Die(FVector Direction, float Power)
{
	PrimaryActorTick.bCanEverTick = false;

	GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	//RAGDOLL
	GetMesh()->SetCollisionEnabled(ECollisionEnabled::PhysicsOnly);
	GetMesh()->SetSimulatePhysics(true);
	//GetMesh()->SetAllBodiesSimulatePhysics(true);
	//GetMesh()->WakeAllRigidBodies();
	//GetMesh()->bBlendPhysics = true;

	GetMesh()->AddForce(Direction * GetMesh()->GetBodyInstance()->GetBodyMass() * Power);
}

bool ACPP_Enemy::TakeDamage(float Damage, FVector Direction, float Power)
{
	CurrentHP -= Damage;

	IsAlive = CurrentHP > 0.0f;

	FString DebugString;

	if (!IsAlive)
	{
		DebugString = GetName() + "\nMAX HP = [" + FString::FromInt(MaxHP) + "]\nCURRENT HP = [" + FString::FromInt(CurrentHP) + "]\nDEAD";

		Die(Direction, Power);
	}
	else
		DebugString = GetName() + "\nMAX HP = [" + FString::FromInt(MaxHP) + "]\nCURRENT HP = [" + FString::FromInt(CurrentHP) + "]\nALIVE";

	//PRINT_FIVE DebugString);

	return IsAlive;
}

void ACPP_Enemy::GoToLocation(AController* CurrentController, FVector Destination)
{
	UAIBlueprintHelperLibrary::SimpleMoveToLocation(CurrentController, Destination);
}

void ACPP_Enemy::RotateToVelocity()
{
	SetActorRotation(UKismetMathLibrary::MakeRotFromX(GetVelocity()));
}

void ACPP_Enemy::LostTarget(float DeltaTime)
{
	//PRINT FString::SanitizeFloat(LostTargetTime));
	LostTargetTime -= DeltaTime;

	if (LostTargetTime <= 0.0f)
	{
		Target = nullptr;
		CurrentBehaviour = EnemyBehaviour::Patrol;
		LostTargetTime = ChaseTime;
	}
}

void ACPP_Enemy::SetSpeed(float Speed)
{
	GetCharacterMovement()->MaxWalkSpeed = Speed;
}