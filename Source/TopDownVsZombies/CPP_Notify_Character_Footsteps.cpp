#include "CPP_Notify_Character_Footsteps.h"
#include <iostream>

#define PRINT GEngine->AddOnScreenDebugMessage(-1, 0.0f, FColor::Yellow,
#define PRINT_ONE GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Yellow,

void UCPP_Notify_Character_Footsteps::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	Super::Notify(MeshComp, Animation);

	ACPP_Character* Character = Cast<ACPP_Character>(MeshComp->GetOwner());
	if (!Character)
		return;

	Character->MakeNoise(Character->FootstepLoud);
}