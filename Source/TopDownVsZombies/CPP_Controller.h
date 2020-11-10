#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "CPP_Character.h"
#include "DrawDebugHelpers.h"
#include "CPP_Controller.generated.h"

UCLASS()
class TOPDOWNVSZOMBIES_API ACPP_Controller : public APlayerController
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadOnly)
		float MoveYValue;
	UPROPERTY(BlueprintReadOnly)
		float MoveXValue;
	UPROPERTY(BlueprintReadOnly)
		FVector MoveYVector;
	UPROPERTY(BlueprintReadOnly)
		FVector MoveXVector;
	UPROPERTY(BlueprintReadOnly)
		float TurnYValue;
	UPROPERTY(BlueprintReadOnly)
		float TurnXValue;

public:
	virtual void SetupInputComponent() override;

	void MoveY(float AxisValue);
	void MoveX(float AxisValue);
	void TurnY(float AxisValue);
	void TurnX(float AxisValue);

	void StartShoot();
	void StopShoot();

	void SetCamera(AActor* Camera, float BlendTime = 0.0f);
};
