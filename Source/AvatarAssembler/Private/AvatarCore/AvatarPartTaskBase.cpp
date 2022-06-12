// Fill out your copyright notice in the Description page of Project Settings.


#include "AvatarAssemblerCore/AvatarPartTaskBase.h"
#include "AvatarAssemblerCore/AvatarPartModifierBase.h"
#include "AvatarUtils/AvatarMacros.h"

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
		SetState(EAvatarPartState::NONE);
	}

	AVATAR_CHECKF(CurState == EAvatarPartState::NONE, "Cancel() this task before restart.");
	SetState(EAvatarPartState::PRE_START);
}

void UAvatarPartTaskBase::Cancel()
{
	SetState(EAvatarPartState::NONE);
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

void UAvatarPartTaskBase::MoveToNextState()
{
	AVATAR_CHECK(CurState < EAvatarPartState::DONE);
	
	SetState(AvatarHelper::EnumAdd(CurState, 1));
}

void UAvatarPartTaskBase::ResetState()
{
	SetState(EAvatarPartState::NONE);
}

void UAvatarPartTaskBase::SetState(EAvatarPartState InState)
{
	if(CurState != InState)
	{
		EAvatarPartState PreState = CurState;
		CurState = InState;

		if(OnAvatarPartStateChanged.IsBound())
		{
			OnAvatarPartStateChanged.Broadcast(this, PreState, CurState);
		}
	}
}

void UAvatarPartTaskBase::StartResourceLoad()
{
	AVATAR_CHECK(CurState == EAvatarPartState::PRE_START);
	MoveToNextState();
	// @Todo : Start resource load job
	// -> callback OnResourceLoaded();
}

void UAvatarPartTaskBase::OnResourceLoaded()
{
	AVATAR_CHECK(CurState == EAvatarPartState::RESOURCE_LOADING);
	MoveToNextState();
	ApplyModifiers();
}

void UAvatarPartTaskBase::ApplyModifiers()
{
	AVATAR_CHECK(CurState == EAvatarPartState::APPLY_MODIFIERS);
	MoveToNextState();
	for (const UAvatarPartModifierBase* Modifier : Modifiers)
	{
		AVATAR_CHECK(Modifier);
		Modifier->ModifyAvatarPart(this);
	}
	TaskDone();
}

void UAvatarPartTaskBase::TaskDone()
{
	AVATAR_CHECK(CurState == EAvatarPartState::RESOURCE_LOADED);
	MoveToNextState();
}

#endif
