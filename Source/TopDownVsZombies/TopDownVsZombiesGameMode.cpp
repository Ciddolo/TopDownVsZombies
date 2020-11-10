#include "TopDownVsZombiesGameMode.h"

#define DT GetWorld()->DeltaTimeSeconds
#define PRINT GEngine->AddOnScreenDebugMessage(-1, 0.0f, FColor::Yellow,
#define PRINT_ONE GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Yellow,

ATopDownVsZombiesGameMode::ATopDownVsZombiesGameMode()
{
	DefaultPawnClass = ACPP_Character::StaticClass();
	PlayerControllerClass = ACPP_Controller::StaticClass();
}

void ATopDownVsZombiesGameMode::BeginPlay()
{
	Super::BeginPlay();

	Init();
}

void ATopDownVsZombiesGameMode::Init()
{
	UGameplayStatics::SetForceDisableSplitscreen(GetWorld(), true);

	Camera = GetWorld()->SpawnActor<ACPP_Camera>();
	Camera->SetActorLocation(FVector(0.0f, 0.0f, 500.0f));

	ACPP_Controller* Controller_0 = Cast<ACPP_Controller>(UGameplayStatics::GetPlayerControllerFromID(GetWorld(), 0));
	SpawnPlayer(Controller_0, FVector(0.0f, 0.0f, 500.0f));

	//ACPP_Controller* Controller_1 = Cast<ACPP_Controller>(UGameplayStatics::CreatePlayer(GetWorld(), 1, true));
	//SpawnPlayer(Controller_1, FVector(0.0f, 0.0f, 500.0f));

	//ACPP_Controller* Controller_2 = Cast<ACPP_Controller>(UGameplayStatics::CreatePlayer(GetWorld(), 2, true));
	//SpawnPlayer(Controller_2, FVector(0.0f, 0.0f, 500.0f));

	//ACPP_Controller* Controller_3 = Cast<ACPP_Controller>(UGameplayStatics::CreatePlayer(GetWorld(), 3, true));
	//SpawnPlayer(Controller_3, FVector(0.0f, 0.0f, 500.0f));
}

void ATopDownVsZombiesGameMode::AddUniqueCharacter(ACPP_Character* NewCharacter)
{
	Characters.AddUnique(NewCharacter);
	if (Camera)
		Camera->SetCharactersArray(Characters);
}

void ATopDownVsZombiesGameMode::SpawnPlayer(ACPP_Controller* Controller, FVector Location, FRotator Rotation)
{
	UWorld* World = GetWorld();

	FActorSpawnParameters SpawnParameters;
	SpawnParameters.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;

	ACPP_Character* NewPlayer = World->SpawnActor<ACPP_Character>(Player, Location, Rotation, SpawnParameters);
	AddUniqueCharacter(NewPlayer);

	Controller->Possess(NewPlayer);
	Controller->SetCamera(Camera);
}

void ATopDownVsZombiesGameMode::SpawnEnemy(FVector Location, FRotator Rotation)
{
}
