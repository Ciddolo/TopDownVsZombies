#include "CPP_Controller.h"

#define CHARACTER Cast<ACPP_Character>(GetPawn())
#define DT GetWorld()->DeltaTimeSeconds
#define PRINT GEngine->AddOnScreenDebugMessage(-1, 0.0f, FColor::Yellow,
#define PRINT_ONE GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Yellow,

void ACPP_Controller::SetupInputComponent()
{
	Super::SetupInputComponent();

	InputComponent->BindAction("Shoot", EInputEvent::IE_Pressed, this, &ACPP_Controller::StartShoot);
	InputComponent->BindAction("Shoot", IE_Released, this, &ACPP_Controller::StopShoot);

	InputComponent->BindAxis("LeftStickY", this, &ACPP_Controller::MoveY);
	InputComponent->BindAxis("LeftStickX", this, &ACPP_Controller::MoveX);
	InputComponent->BindAxis("RightStickY", this, &ACPP_Controller::TurnY);
	InputComponent->BindAxis("RightStickX", this, &ACPP_Controller::TurnX);
}

void ACPP_Controller::MoveY(float AxisValue)
{
	MoveYValue = AxisValue;

	MoveYVector = FRotationMatrix(GetControlRotation()).GetScaledAxis(EAxis::X);

	if (CHARACTER)
		CHARACTER->AddMovementInput(MoveYVector * CHARACTER->MovementSpeed * DT, AxisValue);
}

void ACPP_Controller::MoveX(float AxisValue)
{
	MoveXValue = AxisValue;

	MoveXVector = FRotationMatrix(GetControlRotation()).GetScaledAxis(EAxis::Y);

	if (CHARACTER)
		CHARACTER->AddMovementInput(MoveXVector * CHARACTER->MovementSpeed * DT, AxisValue);
}

void ACPP_Controller::TurnY(float AxisValue)
{
	TurnYValue = AxisValue;

	if (CHARACTER)
		CHARACTER->SetActorRotation(FRotator(0.0f, FMath::RadiansToDegrees(FMath::Atan2(TurnXValue, TurnYValue)), 0.0f));
}

void ACPP_Controller::TurnX(float AxisValue)
{
	TurnXValue = AxisValue;
}

void ACPP_Controller::SetCamera(AActor* Camera, float BlendTime)
{
	SetViewTargetWithBlend(Camera, BlendTime);
}

void ACPP_Controller::StartShoot()
{
	if (CHARACTER)
		CHARACTER->IsShooting = true;
}

void ACPP_Controller::StopShoot()
{
	if (CHARACTER)
		CHARACTER->IsShooting = false;
}