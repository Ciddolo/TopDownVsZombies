#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "CPP_Camera.h"
#include "CPP_Controller.h"
#include "CPP_Character.h"
#include "CPP_Enemy.h"
#include "UObject/ConstructorHelpers.h"
#include "Kismet/GameplayStatics.h"
#include "TopDownVsZombiesGameMode.generated.h"

UCLASS(minimalapi)
class ATopDownVsZombiesGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "CameraManager")
		ACPP_Camera* Camera;

	UPROPERTY(EditAnywhere, Category = "ActorManager")
		TSubclassOf<class ACPP_Character> Player;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "ActorManager")
		TArray<ACPP_Character*> Characters;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "ActorManager")
		TArray<ACPP_Enemy*> Enemies;

	UFUNCTION(BlueprintCallable, Category = "ActorManager")
		void AddUniqueCharacter(ACPP_Character* NewCharacter);

	UFUNCTION(BlueprintCallable, Category = "ActorManager")
		void SpawnPlayer(ACPP_Controller* Controller, FVector Location = FVector::ZeroVector, FRotator Rotation = FRotator::ZeroRotator);

	UFUNCTION(BlueprintCallable, Category = "ActorManager")
		void SpawnEnemy(FVector Location = FVector::ZeroVector, FRotator Rotation = FRotator::ZeroRotator);

public:
	ATopDownVsZombiesGameMode();

protected:
	virtual void BeginPlay() override;

public:
	void Init();
};
