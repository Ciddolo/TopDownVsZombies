#pragma once

#include "CoreMinimal.h"
#include "CPP_Character.h"
#include "Animation/AnimNotifies/AnimNotify_PlaySound.h"
#include "CPP_Notify_Character_Footsteps.generated.h"

UCLASS()
class TOPDOWNVSZOMBIES_API UCPP_Notify_Character_Footsteps : public UAnimNotify_PlaySound
{
	GENERATED_BODY()	

public:
	virtual void Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation) override;
};
