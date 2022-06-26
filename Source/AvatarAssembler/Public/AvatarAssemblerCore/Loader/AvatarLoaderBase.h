// Copyright (c) 2022 mood701

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "AvatarLoaderBase.generated.h"

enum class EAvatarLoadType : uint8;
struct FAvatarHandleBase;

UCLASS()
class AVATARASSEMBLER_API UAvatarLoaderBase : public UObject
{
	GENERATED_BODY()

public:
	virtual void LoadObjects(const TArray<FSoftObjectPath>& ObjPaths, EAvatarLoadType LoadType, TSharedPtr<FAvatarHandleBase>& TargetHandle, FSimpleDelegate Callback = nullptr)
		PURE_VIRTUAL(UAvatarLoaderBase::LoadObjects, return;);
};
