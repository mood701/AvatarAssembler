// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AvatarAssemblerCore/AvatarPartModifierBase.h"
#include "AvatarPartModifier_AttachTo.generated.h"

class USkeletalMeshComponent;

UCLASS()
class AVATARASSEMBLER_API UAvatarPartModifier_AttachTo : public UAvatarPartModifierBase
{
	GENERATED_BODY()
public:
	virtual void ModifyAvatarPart(UAvatarPartTaskBase* PartTask) const override;
	void Init(USkeletalMeshComponent* InMasterComp, bool bIsSetMaster=true);
	void SetSokect(const FName& InSocket, const FTransform& InTransform);
protected:
	TWeakObjectPtr<USkeletalMeshComponent> MasterComponent;
	UPROPERTY(VisibleAnywhere, SkipSerialization)
	bool IsSetMaster = true;
	UPROPERTY(VisibleAnywhere, SkipSerialization)
	FName Socket;
	UPROPERTY(VisibleAnywhere, SkipSerialization)
	FTransform Transform;
};
