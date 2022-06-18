// Fill out your copyright notice in the Description page of Project Settings.


#include "AvatarAssemblerCore/Modifiers/AvatarPartModifier_AttachTo.h"
#include "AvatarAssemblerCore/AvatarPartTaskBase.h"
#include "AvatarUtils/AvatarMacros.h"

void UAvatarPartModifier_AttachTo::ModifyAvatarPart(UAvatarPartTaskBase* PartTask) const
{
	AVATAR_CHECK(MasterComponent.IsValid());
	AVATAR_CHECK(PartTask);
	if(MasterComponent == nullptr || PartTask == nullptr)
	{
		return;
	}

	USkeletalMeshComponent* PartMeshComp = PartTask->GetTargetMeshComponent();
	AVATAR_CHECK(PartMeshComp);
	if(PartMeshComp)
	{
		if(IsSetMaster)
		{
			PartMeshComp->AttachToComponent(MasterComponent.Get(), FAttachmentTransformRules::SnapToTargetIncludingScale);
			PartMeshComp->SetMasterPoseComponent(MasterComponent.Get());
		}
		else
		{
			PartMeshComp->AttachToComponent(MasterComponent.Get(), FAttachmentTransformRules::SnapToTargetIncludingScale, Socket);
			PartMeshComp->SetRelativeTransform(Transform);
		}
		if(!PartMeshComp->IsRegistered())
		{
			PartMeshComp->RegisterComponent();
		}
		PartMeshComp->bComponentUseFixedSkelBounds = true;
	}
}

void UAvatarPartModifier_AttachTo::Init(USkeletalMeshComponent* InMasterComp, bool bIsSetMaster)
{
	MasterComponent = InMasterComp;
	IsSetMaster = bIsSetMaster;
}

void UAvatarPartModifier_AttachTo::SetSokect(const FName& InSocket, const FTransform& InTransform)
{
	Socket = InSocket;
	Transform = InTransform;
}
