#include "CPP_Controller_AI_Enemy.h"

#define ENEMY Cast<ACPP_Enemy>(GetPawn())
#define PRINT GEngine->AddOnScreenDebugMessage(-1, 0.0f, FColor::Yellow,
#define PRINT_ONE GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Yellow,
#define PRINT_FIVE GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow,

void ACPP_Controller_AI_Enemy::Tick(float DeltaTime)
{
	switch (ENEMY->CurrentBehaviour)
	{
	case EnemyBehaviour::Idle:
		Idle(DeltaTime);
		break;

	case EnemyBehaviour::Patrol:
		Freeze(DeltaTime);
		Patrol();
		break;

	case EnemyBehaviour::Chase:
		Chase();
		break;

	case EnemyBehaviour::Investigate:
		Freeze(DeltaTime);
		Investigate();
		break;

	case EnemyBehaviour::Attack:
		break;
	}
}

void ACPP_Controller_AI_Enemy::Idle(float DeltaTime)
{
	if (!ENEMY->IsAlive)
		return;

	PRINT TEXT("IDLE"));
	StopMovement();

	IdleTime -= DeltaTime;

	if (IdleTime <= 0.0f)
	{
		IdleTime = IDLE_TIME;
		ENEMY->CurrentBehaviour = EnemyBehaviour::Patrol;
	}
}

void ACPP_Controller_AI_Enemy::Freeze(float DeltaTime)
{
	if (!ENEMY->IsAlive)
		return;

	if (ENEMY->GetVelocity().Size() <= 50.0f)
	{
		//PRINT TEXT("FREEZE"));
		FreezeTime -= DeltaTime;

		if (FreezeTime <= 0.0f)
			Patroling = false;
	}
	else
		FreezeTime = FREEZE_TIME;
}

void ACPP_Controller_AI_Enemy::Patrol()
{
	if (!ENEMY->IsAlive)
		return;

	PRINT TEXT("PATROL"));
	ENEMY->SetSpeed(ENEMY->WalkSpeed);

	if (!Patroling)
	{
		Destination = UNavigationSystemV1::GetRandomReachablePointInRadius(GetWorld(), ENEMY->GetActorLocation(), 5000.0f);
		Patroling = true;
	}
	else
	{
		float Distance = (FVector(ENEMY->GetActorLocation().X, ENEMY->GetActorLocation().Y, 0.0f) - FVector(Destination.X, Destination.Y, 0.0f)).Size();
		if (Distance <= 50.0f)
		{
			Patroling = false;
			ENEMY->CurrentBehaviour = EnemyBehaviour::Idle;
		}
	}

	UAIBlueprintHelperLibrary::SimpleMoveToLocation(this, Destination);
	ENEMY->RotateToVelocity();
}

void ACPP_Controller_AI_Enemy::Chase()
{
	if (!ENEMY->IsAlive)
		return;

	PRINT TEXT("CHASE"));
	ENEMY->SetSpeed(ENEMY->RunSpeed);

	Destination = FVector(ENEMY->Target->GetActorLocation().X, ENEMY->Target->GetActorLocation().Y, 0.0f);

	float Distance = (FVector(ENEMY->GetActorLocation().X, ENEMY->GetActorLocation().Y, 0.0f) - Destination).Size();
	//if (Distance <= 100.0f)
	//	PRINT_FIVE TEXT("ATTACK"));

	UAIBlueprintHelperLibrary::SimpleMoveToLocation(this, Destination);
	ENEMY->RotateToVelocity();
}

void ACPP_Controller_AI_Enemy::Investigate()
{
	if (!ENEMY->IsAlive)
		return;

	PRINT TEXT("INVESTIGATE"));
	Destination = ENEMY->NoiseLocation;
	float Distance = (FVector(ENEMY->GetActorLocation().X, ENEMY->GetActorLocation().Y, 0.0f) - Destination).Size();
	if (Distance <= 200.0f)
	{
		ENEMY->CurrentBehaviour = EnemyBehaviour::Idle;
		ENEMY->FollowHighNoise = false;
	}

	UAIBlueprintHelperLibrary::SimpleMoveToLocation(this, Destination);
	ENEMY->RotateToVelocity();
}