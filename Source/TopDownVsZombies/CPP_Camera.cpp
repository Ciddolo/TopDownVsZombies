#include "CPP_Camera.h"

#define CHARACTER Cast<ACPP_Character>(GetPawn())
#define DT GetWorld()->DeltaTimeSeconds
#define PRINT GEngine->AddOnScreenDebugMessage(-1, 0.0f, FColor::Yellow,
#define PRINT_ONE GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Yellow,

ACPP_Camera::ACPP_Camera()
{
	PrimaryActorTick.bCanEverTick = true;

	SpringArm = CreateDefaultSubobject<USpringArmComponent>("SpringArm");
	SpringArm->AttachTo(RootComponent);
	SpringArm->SetUsingAbsoluteRotation(true); // Don't want arm to rotate when character does
	SpringArm->TargetArmLength = 1000.0f;
	SpringArm->SetRelativeRotation(FRotator(-60.f, 0.f, 0.f));
	SpringArm->bDoCollisionTest = false; // Don't want to pull camera in when it collides with level

	Camera = CreateDefaultSubobject<UCameraComponent>("Camera");
	Camera->AttachTo(SpringArm);
}

void ACPP_Camera::BeginPlay()
{
	Super::BeginPlay();
}

void ACPP_Camera::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//PRINT TEXT("CURRENT PLAYER [" + FString::FromInt(Characters.Num()) + "]"));

	SetActorLocation(CalculateLocation());
}

FVector ACPP_Camera::CalculateLocation()
{
	FVector MiddlePoint = FVector::ZeroVector + FVector(0.0f, 0.0f, CameraHeightMin);



	switch (Characters.Num())
	{
	default:
		break;

	case 1:
		MiddlePoint = BehaviourOnePlayer();
		break;

	case 2:
		MiddlePoint = BehaviourTwoPlayer();
		break;

	case 3:
		MiddlePoint = BehaviourThreePlayer();
		break;

	case 4:
		MiddlePoint = BehaviourFourPlayer();
		break;
	}

	return MiddlePoint;
}

void ACPP_Camera::SetCharactersArray(TArray<ACPP_Character*> NewCharacters)
{
	Characters = NewCharacters;
}

FVector ACPP_Camera::BehaviourOnePlayer()
{
	CameraHeight = CameraHeightMin;
	SpringArm->TargetArmLength = CameraHeight;

	return FVector(Characters[0]->GetActorLocation().X, Characters[0]->GetActorLocation().Y, 0.0f);
}

FVector ACPP_Camera::BehaviourTwoPlayer()
{
	float XDiff = FMath::Abs(Characters[0]->GetActorLocation().X - Characters[1]->GetActorLocation().X);
	float YDiff = FMath::Abs(Characters[0]->GetActorLocation().Y - Characters[1]->GetActorLocation().Y);

	if (XDiff >= 700.0f || YDiff >= 1400.0f)
	{
		CameraHeight = CameraHeightMin + FMath::Max(XDiff - 750.0f, YDiff - 1450.0f) * 1.5f;
		CameraHeight = FMath::Clamp(CameraHeight, CameraHeightMin, CameraHeightMax);
	}
	else
		CameraHeight = CameraHeightMin;

	SpringArm->TargetArmLength = CameraHeight;

	FVector TempVector = FMath::Lerp(Characters[0]->GetActorLocation(), Characters[1]->GetActorLocation(), 0.5f);

	return FVector(TempVector.X, TempVector.Y, 0.0f);
}

FVector ACPP_Camera::BehaviourThreePlayer()
{
	float XDiff = FMath::Abs(Characters[0]->GetActorLocation().X - Characters[1]->GetActorLocation().X);
	float YDiff = FMath::Abs(Characters[0]->GetActorLocation().Y - Characters[1]->GetActorLocation().Y);

	if (XDiff >= 700.0f || YDiff >= 1400.0f)
	{
		CameraHeight = CameraHeightMin + FMath::Max(XDiff - 750.0f, YDiff - 1450.0f) * 1.5f;
		CameraHeight = FMath::Clamp(CameraHeight, CameraHeightMin, CameraHeightMax);
	}
	else
		CameraHeight = CameraHeightMin;

	SpringArm->TargetArmLength = CameraHeight;

	FVector TempVector = FMath::Lerp(Characters[0]->GetActorLocation(), Characters[1]->GetActorLocation(), 0.5f);

	return FVector(TempVector.X, TempVector.Y, 0.0f);
}

FVector ACPP_Camera::BehaviourFourPlayer()
{
	float XDiff = FMath::Abs(Characters[0]->GetActorLocation().X - Characters[1]->GetActorLocation().X);
	float YDiff = FMath::Abs(Characters[0]->GetActorLocation().Y - Characters[1]->GetActorLocation().Y);

	if (XDiff >= 700.0f || YDiff >= 1400.0f)
	{
		CameraHeight = CameraHeightMin + FMath::Max(XDiff - 750.0f, YDiff - 1450.0f) * 1.5f;
		CameraHeight = FMath::Clamp(CameraHeight, CameraHeightMin, CameraHeightMax);
	}
	else
		CameraHeight = CameraHeightMin;

	SpringArm->TargetArmLength = CameraHeight;

	FVector TempVector = FMath::Lerp(Characters[0]->GetActorLocation(), Characters[1]->GetActorLocation(), 0.5f);

	return FVector(TempVector.X, TempVector.Y, 0.0f);
}