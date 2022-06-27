// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

UENUM(BlueprintType)
enum class EAvatarPartState : uint8
{
	NONE,
	PRE_START,
	RESOURCE_LOADING,
	RESOURCE_LOADED,
	APPLY_MODIFIERS_BEGIN,
	APPLY_MODIFIERS_END,
	DONE,
};

UENUM()
enum class EAvatarLoadType : uint8
{
	NONE,
	SYNC,
	ASYNC,
	ANY,
};

UENUM()
enum class EAvatarWorkType : uint8
{
	NONE,
	SYNC,
	FRAME,
	ASYNC,
	ANY,
};

namespace AvatarHelper
{
	template<class ENUM_TYPE>
	ENUM_TYPE EnumAdd(ENUM_TYPE CurValue, uint8 AddValue)
	{
		return (ENUM_TYPE)((uint8) CurValue + AddValue);
	}
}
