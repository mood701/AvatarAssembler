// Copyright (c) 2022 mood701

#pragma once

#include "CoreMinimal.h"
#include "AvatarAssemblerCore/Loader/AvatarLoaderBase.h"
#include "AvatarAssemblerCore/AvatarHandleBase.h"
#include "AvatarCommonLoader.generated.h"

struct FStreamableHandle;
class IAvatarSoftCollector;

USTRUCT()
struct AVATARASSEMBLER_API FAvatarCommonLoaderHandle : public FAvatarHandleBase
{
	GENERATED_BODY()
public:
	virtual void CancelHandle() override;
	virtual bool IsValid() const override;
	void SetHandle(TSharedPtr<FStreamableHandle> RealHandle) { OwnerHandle = RealHandle; }
private:
	TSharedPtr<FStreamableHandle> OwnerHandle;
};

UCLASS()
class AVATARASSEMBLER_API UAvatarCommonLoader : public UAvatarLoaderBase
{
	GENERATED_BODY()

public:
	virtual TSharedPtr<FAvatarHandleBase> LoadObjects(const TArray<FSoftObjectPath>& ObjPaths, EAvatarLoadType LoadType, FSimpleDelegate Callback) override;
};
