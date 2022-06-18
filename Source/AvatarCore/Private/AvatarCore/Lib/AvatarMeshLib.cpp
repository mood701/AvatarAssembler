// Fill out your copyright notice in the Description page of Project Settings.


#include "AvatarCore/Lib/AvatarMeshLib.h"

void FAvatarMeshLib::ClearAnimInstanceSafe(USkeletalMeshComponent* MeshComponent)
{
	if(MeshComponent)
	{
		// @TODO : Call UninitializeAnimation() for linked animinstance and postprocess animinstance if need.
		UAnimInstance* Inst = MeshComponent->GetAnimInstance();
		if(Inst)
		{			
			Inst->UninitializeAnimation();
			MeshComponent->ClearAnimScriptInstance();
		}
	}
}
