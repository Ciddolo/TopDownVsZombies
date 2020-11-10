#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "NavigationSystem.h"
#include "CPP_Enemy.h"
#include "CPP_Character.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "CPP_Controller_Enemy.generated.h"

UCLASS()
class TOPDOWNVSZOMBIES_API ACPP_Controller_Enemy : public APlayerController
{
	GENERATED_BODY()
	
public:
	const float IDLE_TIME = 3.0f;
	float IdleTime = IDLE_TIME;
	const float FREEZE_TIME = 1.5f;
	float FreezeTime = FREEZE_TIME;
	bool Patroling;
	FVector Destination;

public:
	virtual void Tick(float DeltaTime) override;

	void Idle(float DeltaTime);
	void Freeze(float DeltaTime);
	void Patrol();
	void Chase();
};
