#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "CPP_Character.h"
#include "CPP_Camera.generated.h"

UCLASS()
class TOPDOWNVSZOMBIES_API ACPP_Camera : public AActor
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere)
		USpringArmComponent* SpringArm;

	UPROPERTY(EditAnywhere)
		UCameraComponent* Camera;

	UPROPERTY()
		TArray<ACPP_Character*> Characters;

	UPROPERTY(EditAnywhere)
		float CameraHeight = 1000.0f;

	UPROPERTY(EditAnywhere)
		float CameraHeightMin = 1000.0f;

	UPROPERTY(EditAnywhere)
		float CameraHeightMax = 1300.0f;
	
public:	
	ACPP_Camera();

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;

	FVector CalculateLocation();

public:
	void SetCharactersArray(TArray<ACPP_Character*> NewCharacters);
	FVector BehaviourOnePlayer();
	FVector BehaviourTwoPlayer();
	FVector BehaviourThreePlayer();
	FVector BehaviourFourPlayer();
};
