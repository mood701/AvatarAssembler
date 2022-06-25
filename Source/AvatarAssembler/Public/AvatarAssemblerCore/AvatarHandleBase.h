// Copyright (c) 2022 mood701

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "AvatarHandleBase.generated.h"

/**
 * 
 */
USTRUCT()
struct AVATARASSEMBLER_API FAvatarHandleBase
{
	GENERATED_BODY()
public:
	virtual void CancelHandle() {}
	virtual bool IsValid() const { return false; }
};
