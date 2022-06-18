// Fill out your copyright notice in the Description page of Project Settings.
#include "AvatarAssemblerCore/Tasks/AvatarPartTask_Single.h"
#include "AvatarUtils/AvatarMacros.h"

void UAvatarPartTask_Single::OnPreStart()
{
	AVATAR_LOG("[%s_%s]", *AVATAR_FUNCNAME, *AVATAR_LINE);
	StartResourceLoad();
}

void UAvatarPartTask_Single::OnCancel()
{
	AVATAR_LOG("[%s_%s]", *AVATAR_FUNCNAME, *AVATAR_LINE);
}

void UAvatarPartTask_Single::OnStartResourceLoad()
{
	AVATAR_LOG("[%s_%s]", *AVATAR_FUNCNAME, *AVATAR_LINE);
	Mesh = MeshPath.LoadSynchronous();
	AVATAR_CHECK(Mesh);
	ResourceLoaded();
}

void UAvatarPartTask_Single::OnResourceLoaded()
{
	AVATAR_LOG("[%s_%s]", *AVATAR_FUNCNAME, *AVATAR_LINE);
	ApplyModifiersBegin();
}

void UAvatarPartTask_Single::OnApplyModifiersBegin()
{
	AVATAR_LOG("[%s_%s]", *AVATAR_FUNCNAME, *AVATAR_LINE);
	ExecuteModifiers();
	ApplyModifiersEnd();
}

void UAvatarPartTask_Single::OnApplyModifiersEnd()
{
	AVATAR_LOG("[%s_%s]", *AVATAR_FUNCNAME, *AVATAR_LINE);
	TaskDone();
}

void UAvatarPartTask_Single::OnTaskDone()
{
	USkeletalMeshComponent* TargetComp = GetTargetMeshComponent();
	AVATAR_CHECK(TargetComp);
	if(TargetComp)
	{
		TargetComp->SetSkeletalMesh(Mesh);
	}
	AVATAR_LOG("[%s_%s]", *AVATAR_FUNCNAME, *AVATAR_LINE);
}
