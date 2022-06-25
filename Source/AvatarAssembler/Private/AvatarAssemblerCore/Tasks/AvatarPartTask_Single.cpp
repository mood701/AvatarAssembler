// Fill out your copyright notice in the Description page of Project Settings.
#include "AvatarAssemblerCore/Tasks/AvatarPartTask_Single.h"
#include "AvatarAssemblerCore/AvatarHandleBase.h"
#include "AvatarAssemblerCore/Loader/AvatarLoaderBase.h"
#include "AvatarUtils/AvatarMacros.h"

void UAvatarPartTask_Single::CollectSoftObjects(TArray<FSoftObjectPath>& Paths) const
{
	Super::CollectSoftObjects(Paths);
	Paths.Add(MeshPath.ToSoftObjectPath());
}

void UAvatarPartTask_Single::OnPreStart()
{
	AVATAR_LOG("[%s_%s]", *AVATAR_FUNCNAME, *AVATAR_LINE);
	StartResourceLoad();
}

void UAvatarPartTask_Single::OnCancel()
{
	AVATAR_LOG("[%s_%s]", *AVATAR_FUNCNAME, *AVATAR_LINE);
	ResourceHandle->CancelHandle();
}

void UAvatarPartTask_Single::OnStartResourceLoad()
{
	AVATAR_LOG("[%s_%s]", *AVATAR_FUNCNAME, *AVATAR_LINE);
	UAvatarLoaderBase* Loader = GetLoader();
	AVATAR_CHECK(Loader);

	TArray<FSoftObjectPath> SoftPaths = GetSoftPaths();
	Loader->LoadObjects(SoftPaths, EAvatarLoadType::ASYNC, FSimpleDelegate::CreateUObject(this, &UAvatarPartTask_Single::ResourceLoaded));
}

void UAvatarPartTask_Single::OnResourceLoaded()
{
	AVATAR_LOG("[%s_%s]", *AVATAR_FUNCNAME, *AVATAR_LINE);
	Mesh = MeshPath.LoadSynchronous();
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
