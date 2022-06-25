// Copyright (c) 2022 mood701


#include "AvatarAssemblerCore/Loader/AvatarCommonLoader.h"
#include "AvatarAssemblerCore/AvatarCommonDefine.h"
#include "AvatarAssemblerCore/AvatarHandleBase.h"
#include "AvatarAssemblerInterface/AvatarSoftCollector.h"
#include "Engine/StreamableManager.h"
#include "Engine/AssetManager.h"

void FAvatarCommonLoaderHandle::CancelHandle()
{
	if(OwnerHandle.IsValid())
	{
		OwnerHandle->CancelHandle();
		OwnerHandle.Reset();
	}
}

bool FAvatarCommonLoaderHandle::IsValid() const
{
	return OwnerHandle.IsValid();
}

TSharedPtr<FAvatarHandleBase> UAvatarCommonLoader::LoadObjects(const TArray<FSoftObjectPath>& ObjPaths, EAvatarLoadType LoadType, FSimpleDelegate Callback)
{
	FStreamableManager& Streamable = UAssetManager::GetStreamableManager();
	if(LoadType == EAvatarLoadType::ANY || LoadType == EAvatarLoadType::ASYNC)
	{
		auto Handle = Streamable.RequestAsyncLoad(ObjPaths, Callback);
		TSharedPtr<FAvatarCommonLoaderHandle> CommonLoaderHandle = MakeShareable(new FAvatarCommonLoaderHandle());
		CommonLoaderHandle->SetHandle(Handle);
		return CommonLoaderHandle;
	}
	else if(LoadType == EAvatarLoadType::SYNC)
	{
		Streamable.RequestSyncLoad(ObjPaths);
		Callback.ExecuteIfBound();
		return nullptr;
	}
	return nullptr;
}
