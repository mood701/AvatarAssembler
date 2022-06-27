// Fill out your copyright notice in the Description page of Project Settings.
#include "AvatarAssemblerCore/Tasks/AvatarPartTask_Single.h"
#include "AvatarAssemblerCore/AvatarHandleBase.h"
#include "AvatarAssemblerCore/Loader/AvatarLoaderBase.h"
#include "AvatarAssemblerCore/Dispatcher/AvatarCommonDispatcher.h"
#include "AvatarUtils/AvatarMacros.h"

void UAvatarPartTask_Single::CollectSoftObjects(TArray<FSoftObjectPath>& Paths) const
{
	Super::CollectSoftObjects(Paths);
	Paths.Add(MeshPath.ToSoftObjectPath());
}

void UAvatarPartTask_Single::OnPreStart()
{
	AVATAR_LOG("[%s_%s]", *AVATAR_FUNCNAME, *AVATAR_LINE);
	NextModifierID = 0;
	StartResourceLoad();
}

void UAvatarPartTask_Single::OnCancel()
{
	AVATAR_LOG("[%s_%s]", *AVATAR_FUNCNAME, *AVATAR_LINE);
	ResourceHandle->CancelHandle();
	ModifierHandle->CancelHandle();
}

void UAvatarPartTask_Single::OnStartResourceLoad()
{
	AVATAR_LOG("[%s_%s]", *AVATAR_FUNCNAME, *AVATAR_LINE);
	UAvatarLoaderBase* Loader = GetLoader();
	AVATAR_CHECK(Loader);

	TArray<FSoftObjectPath> SoftPaths = GetSoftPaths();
	Loader->LoadObjects(SoftPaths, EAvatarLoadType::ASYNC, ResourceHandle, AVATAR_SIMLPE_UOBJECT_EVENT(UAvatarPartTask_Single::ResourceLoaded));
}

void UAvatarPartTask_Single::OnResourceLoaded()
{
	AVATAR_LOG("[%s_%s]", *AVATAR_FUNCNAME, *AVATAR_LINE);
	Mesh = MeshPath.Get();
	ApplyModifiersBegin();
}

void UAvatarPartTask_Single::OnApplyModifiersBegin()
{
	AVATAR_LOG("[%s_%s]", *AVATAR_FUNCNAME, *AVATAR_LINE);
	ReqExecuteNextModifier();
	//ApplyModifiersEnd();
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

void UAvatarPartTask_Single::ReqExecuteNextModifier()
{
	AVATAR_CHECK(GetCurState() == EAvatarPartState::APPLY_MODIFIERS_BEGIN);
	UAvatarDispatcherBase* Dispatcher = GetDispatcher();
	AVATAR_CHECK(Dispatcher);
	if(Dispatcher == nullptr)
	{
		return;
	}

	if (NextModifierID < Modifiers.Num())
	{
		UAvatarPartModifierBase* Modifier = Modifiers[NextModifierID];
		AVATAR_CHECK(Modifier);
		++NextModifierID;
		Dispatcher->AddOrExecuteWork(
			EAvatarWorkType::FRAME, 
			FSimpleDelegate::CreateLambda([
				ModifierPtr = TWeakObjectPtr<UAvatarPartModifierBase> (Modifier),
				TaskPtr = TWeakObjectPtr<UAvatarPartTaskBase>(this)]()
				{
					if(TaskPtr.IsValid() && ModifierPtr.IsValid())
					{
						ModifierPtr->ModifyAvatarPart(TaskPtr.Get());
					}
				}),
			ModifierHandle,
			AVATAR_SIMLPE_UOBJECT_EVENT(UAvatarPartTask_Single::ReqExecuteNextModifier));
	}
	else
	{
		ApplyModifiersEnd();
	}
}
