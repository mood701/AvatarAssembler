// Fill out your copyright notice in the Description page of Project Settings.


#include "AvatarAssemblerCore/AvatarPartTaskBase.h"
#include "AvatarAssemblerCore/AvatarPartModifierBase.h"
#include "AvatarUtils/AvatarMacros.h"
#include "Components/SkeletalMeshComponent.h"

#define TASK_SIMPLE_EVENT(FUNC_NAME) AVATAR_SIMLPE_UOBJECT_EVENT(UAvatarPartTaskBase::##FUNC_NAME)

void UAvatarPartTaskBase::AddModifier(UAvatarPartModifierBase* Modifier)
{
	AVATAR_CHECK(CurState <= EAvatarPartState::PRE_START);
	if(Modifier)
	{
		UAvatarPartModifierBase* ExistingModifier = GetModifierOfClass(Modifier->GetClass());
		if (ExistingModifier != nullptr)
		{
			Modifiers.Remove(ExistingModifier);
		}
		Modifiers.Add(Modifier);
	}
}

void UAvatarPartTaskBase::RemoveModifierOfClass(TSubclassOf<UAvatarPartModifierBase> InModifierClass)
{
	AVATAR_CHECK(CurState <= EAvatarPartState::PRE_START);
	for (int32 DataIdx = 0; DataIdx < Modifiers.Num(); DataIdx++)
	{
		UAvatarPartModifierBase* Modifier = Modifiers[DataIdx];
		if (Modifier != nullptr && Modifier->IsA(InModifierClass))
		{
			Modifiers.RemoveAt(DataIdx);
			return;
		}
	}
}

UAvatarPartModifierBase* UAvatarPartTaskBase::GetModifierOfClass(TSubclassOf<UAvatarPartModifierBase> InModifierClass)
{
	for (int32 DataIdx = 0; DataIdx < Modifiers.Num(); DataIdx++)
	{
		UAvatarPartModifierBase* Modifier = Modifiers[DataIdx];
		if (Modifier != nullptr && Modifier->IsA(InModifierClass))
		{
			return Modifier;
		}
	}
	return nullptr;
}

USkeletalMeshComponent* UAvatarPartTaskBase::ResetTargetMeshComponent()
{
	USkeletalMeshComponent* PrevComp = GetTargetMeshComponent();
	TargetMeshComp = nullptr;
	return PrevComp;
}

void UAvatarPartTaskBase::SetTargetMeshComponent(USkeletalMeshComponent* MeshComp)
{
	AVATAR_CHECKF(MeshComp, "Use ResetTargetMeshComponent if you want clear.");
	AVATAR_CHECK(CurState <= EAvatarPartState::PRE_START);
	TargetMeshComp = MeshComp;
}

TArray<FSoftObjectPath> UAvatarPartTaskBase::CollectSoftObjects_Implement() const
{
	TArray<FSoftObjectPath> SoftPaths;
	for (int32 DataIdx = 0; DataIdx < Modifiers.Num(); DataIdx++)
	{
		UAvatarPartModifierBase* Modifier = Modifiers[DataIdx];
		if (Modifier != nullptr)
		{
			SoftPaths.Append(IAvatarSoftCollector::Execute_CollectSoftObjects(Modifier));
		}
	}

	return SoftPaths;
}

void UAvatarPartTaskBase::Start()
{
	if(CurState == EAvatarPartState::DONE)
	{
		Cancel();
	}

	AVATAR_CHECKF(CurState == EAvatarPartState::NONE, "Cancel() this task before restart.");
	SetState(EAvatarPartState::PRE_START, TASK_SIMPLE_EVENT(OnPreStart));
}

void UAvatarPartTaskBase::Cancel()
{
	ResetState(TASK_SIMPLE_EVENT(OnCancel));
}

void UAvatarPartTaskBase::AddAssetUserData(UAssetUserData* InUserData)
{
	if (InUserData != nullptr)
	{
		UAssetUserData* ExistingData = GetAssetUserDataOfClass(InUserData->GetClass());
		if (ExistingData != nullptr)
		{
			AssetUserData.Remove(ExistingData);
		}
		AssetUserData.Add(InUserData);
	}
}

void UAvatarPartTaskBase::RemoveUserDataOfClass(TSubclassOf<UAssetUserData> InUserDataClass)
{
	for (int32 DataIdx = 0; DataIdx < AssetUserData.Num(); DataIdx++)
	{
		UAssetUserData* Datum = AssetUserData[DataIdx];
		if (Datum != nullptr && Datum->IsA(InUserDataClass))
		{
			AssetUserData.RemoveAt(DataIdx);
			return;
		}
	}
}

UAssetUserData* UAvatarPartTaskBase::GetAssetUserDataOfClass(TSubclassOf<UAssetUserData> InUserDataClass)
{
	for (int32 DataIdx = 0; DataIdx < AssetUserData.Num(); DataIdx++)
	{
		UAssetUserData* Datum = AssetUserData[DataIdx];
		if (Datum != nullptr && Datum->IsA(InUserDataClass))
		{
			return Datum;
		}
	}
	return nullptr;
}

const TArray<UAssetUserData*>* UAvatarPartTaskBase::GetAssetUserDataArray() const
{
	return &AssetUserData;
}

#if WITH_EDITOR
void UAvatarPartTaskBase::PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent)
{
	for (UAssetUserData* Datum : AssetUserData)
	{
		if (Datum != nullptr)
		{
			Datum->PostEditChangeOwner();
		}
	}

	Super::PostEditChangeProperty(PropertyChangedEvent);
}

#endif

void UAvatarPartTaskBase::MoveToNextState(FSimpleDelegate EventBeforePost)
{
	AVATAR_CHECK(CurState < EAvatarPartState::DONE);
	SetState(AvatarHelper::EnumAdd(CurState, 1), EventBeforePost);
}

void UAvatarPartTaskBase::ResetState(FSimpleDelegate EventBeforePost)
{
	SetState(EAvatarPartState::NONE, EventBeforePost);
}

void UAvatarPartTaskBase::SetState(EAvatarPartState InState, FSimpleDelegate EventBeforePost)
{
	if(CurState != InState)
	{
		EAvatarPartState PreState = CurState;
		CurState = InState;

		// Handle Event after change state and before Post state changed
		EventBeforePost.ExecuteIfBound();

		if(OnAvatarPartStateChanged.IsBound())
		{
			OnAvatarPartStateChanged.Broadcast(this, PreState, CurState);
		}
	}
}

void UAvatarPartTaskBase::StartResourceLoad()
{
	AVATAR_CHECK(CurState == EAvatarPartState::PRE_START);
	MoveToNextState(TASK_SIMPLE_EVENT(OnStartResourceLoad));
}

void UAvatarPartTaskBase::ResourceLoaded()
{
	AVATAR_CHECK(CurState == EAvatarPartState::RESOURCE_LOADING);
	MoveToNextState(TASK_SIMPLE_EVENT(OnResourceLoaded));
}

void UAvatarPartTaskBase::ApplyModifiersBegin()
{
	AVATAR_CHECK(CurState == EAvatarPartState::RESOURCE_LOADED);
	MoveToNextState(TASK_SIMPLE_EVENT(OnApplyModifiersBegin));
}

void UAvatarPartTaskBase::ApplyModifiersEnd()
{
	AVATAR_CHECK(CurState == EAvatarPartState::APPLY_MODIFIERS_BEGIN);
	MoveToNextState(TASK_SIMPLE_EVENT(OnApplyModifiersEnd));
}

void UAvatarPartTaskBase::TaskDone()
{
	AVATAR_CHECK(CurState == EAvatarPartState::APPLY_MODIFIERS_END);
	MoveToNextState(TASK_SIMPLE_EVENT(OnTaskDone));
}

void UAvatarPartTaskBase::ExecuteModifiers()
{
	AVATAR_CHECK(CurState == EAvatarPartState::APPLY_MODIFIERS_BEGIN);
	for (const UAvatarPartModifierBase* Modifier : Modifiers)
	{
		AVATAR_CHECK(Modifier);
		if(Modifier)
		{
			Modifier->ModifyAvatarPart(this);
		}
	}
}
