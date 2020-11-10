#include "CPP_Character.h"
#include "DrawDebugHelpers.h"

#define DT GetWorld()->DeltaTimeSeconds
#define PRINT GEngine->AddOnScreenDebugMessage(-1, 0.0f, FColor::Yellow,
#define PRINT_ONE GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Yellow,
#define PRINT_FIVE GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow,

ACPP_Character::ACPP_Character()
{
	PrimaryActorTick.bCanEverTick = true;

	bUseControllerRotationYaw = false;

	NoiseEmitter = CreateDefaultSubobject< UPawnNoiseEmitterComponent>("NoiseEmitter");
}

void ACPP_Character::BeginPlay()
{
	Super::BeginPlay();
}

void ACPP_Character::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	Start = GetActorLocation() + GetActorUpVector() * 50.0f;
	End = Start + GetActorForwardVector() * 5000.0f;

	DrawShot();

	if (AttackCD > 0.0f)
		AttackCD -= AttackSpeed * DT;
	if (IsShooting && AttackCD <= 0.0f)
		Shoot();
}

void ACPP_Character::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

void ACPP_Character::DrawShot()
{
	FHitResult HitInfo;
	FCollisionQueryParams TraceParams;
	TraceParams.AddIgnoredActor(this);

	if (GetWorld()->LineTraceSingleByChannel(HitInfo, Start, End, ECC_Visibility, TraceParams))
	{
		if (Cast<ACPP_Enemy>(HitInfo.GetActor()))
			DrawDebugLine(GetWorld(), Start, HitInfo.ImpactPoint, FColor::Yellow, false, 0.0f, 0, 10.0f);
		else
			DrawDebugLine(GetWorld(), Start, HitInfo.ImpactPoint, FColor::Red, false, 0.0f, 0, 10.0f);
	}
	else
		DrawDebugLine(GetWorld(), Start, End, FColor::Red, false, 0.0f, 0, 10.0f);
}

void ACPP_Character::Shoot()
{
	AttackCD = 1.0f;

	FHitResult HitInfo;
	FCollisionQueryParams TraceParams;
	TraceParams.AddIgnoredActor(this);

	if (GetWorld()->LineTraceSingleByChannel(HitInfo, Start, End, ECC_Visibility, TraceParams))
	{
		if (Cast<ACPP_Enemy>(HitInfo.GetActor()))
		{
			FVector Direction = HitInfo.GetActor()->GetActorLocation() - GetActorLocation();
			Cast<ACPP_Enemy>(HitInfo.GetActor())->TakeDamage(10.0f, Direction.GetSafeNormal(), 350000.0f);
		}
		//else
		//	PRINT_ONE HitInfo.GetActor()->GetName());
	}

	MakeNoise(ShootLoud);
}

void ACPP_Character::MakeNoise(float Loudness)
{
	//PRINT_ONE TEXT("NOISE"));
	NoiseEmitter->MakeNoise(this, Loudness, FVector(GetActorLocation().X, GetActorLocation().Y, 0.0f));
}