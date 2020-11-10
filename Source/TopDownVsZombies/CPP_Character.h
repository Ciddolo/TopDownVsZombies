#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Components/CapsuleComponent.h"
#include "CPP_Enemy.h"
#include "Components/PawnNoiseEmitterComponent.h"
#include "CPP_Character.generated.h"

UCLASS()
class TOPDOWNVSZOMBIES_API ACPP_Character : public ACharacter
{
	GENERATED_BODY()

public:
	FVector Start;
	FVector End;
	bool IsShooting;
	float AttackCD;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "PlayerStat")
		UPawnNoiseEmitterComponent* NoiseEmitter;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "PlayerStat")
		float MaxHP = 100.0f;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "PlayerStat")
		float CurrentHP = MaxHP;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "PlayerStat")
		float AttackSpeed = 1.0f;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "PlayerStat")
		float MovementSpeed = 1000.0f;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "PlayerStat")
		float FootstepLoud = 1.0f;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "PlayerStat")
		float ShootLoud = 3.0f;
	UPROPERTY(BlueprintReadOnly, Category = "PlayerStat")
		bool IsAlive = true;
public:
	ACPP_Character();

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void DrawShot();

	void Shoot();

	void MakeNoise(float Loudness);
};
