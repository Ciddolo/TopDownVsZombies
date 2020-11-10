#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Kismet/KismetMathLibrary.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "Components/CapsuleComponent.h"
#include "Perception/PawnSensingComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "CPP_Enemy.generated.h"

UENUM(BlueprintType)
enum class EnemyBehaviour : uint8 { Idle, Patrol, Chase, Investigate, Attack };

UCLASS()
class TOPDOWNVSZOMBIES_API ACPP_Enemy : public ACharacter
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "EnemySense")
		UPawnSensingComponent* Sensing;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "EnemyStat")
		float MaxHP = 100.0f;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "EnemyStat")
		float CurrentHP = MaxHP;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "EnemyStat")
		float ChaseTime = 5.0f;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "EnemyStat")
		float WalkSpeed = 50.0f;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "EnemyStat")
		float InvestigateSpeed = 100.0f;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "EnemyStat")
		float RunSpeed = 250.0f;
	UPROPERTY(BlueprintReadOnly, Category = "EnemyStat")
		bool IsAlive = true;

	UPROPERTY(BlueprintReadWrite, Category = "EnemyStat")
		EnemyBehaviour CurrentBehaviour = EnemyBehaviour::Idle;

	float LostTargetTime = ChaseTime;
	bool bLostTarget;
	APawn* Target;
	FVector NoiseLocation;
	bool FollowHighNoise;

public:
	ACPP_Enemy();

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UFUNCTION(BlueprintCallable, Category = "EnemyFunctions")
		void OnSeePlayer(APawn* Pawn);
	UFUNCTION(BlueprintCallable, Category = "EnemyFunctions")
		void OnSeeEnemy(APawn* Pawn);
	UFUNCTION(BlueprintCallable, Category = "EnemyFunctions")
		void OnHearPlayer(APawn* Pawn, const FVector &Location, float Volume);

	void Die(FVector Direction, float Power);
	bool TakeDamage(float Damage, FVector Direction, float Power);
	void GoToLocation(AController* CurrentController, FVector Destination);
	void RotateToVelocity();
	void LostTarget(float DeltaTime);
	void SetSpeed(float Speed);
};
