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

void UAvatarCommonLoader::LoadObjects(const TArray<FSoftObjectPath>& ObjPaths, EAvatarLoadType LoadType, TSharedPtr<FAvatarHandleBase>& TargetHandle, FSimpleDelegate Callback)
{
	FStreamableManager& Streamable = UAssetManager::GetStreamableManager();
	if(LoadType == EAvatarLoadType::ANY || LoadType == EAvatarLoadType::ASYNC)
	{
		auto Handle = Streamable.RequestAsyncLoad(ObjPaths, Callback);
		TSharedPtr<FAvatarCommonLoaderHandle> CommonLoaderHandle = MakeShareable(new FAvatarCommonLoaderHandle());
		CommonLoaderHandle->SetHandle(Handle);
		TargetHandle = CommonLoaderHandle;
	}
	else if(LoadType == EAvatarLoadType::SYNC)
	{
		// make sure Handle set before call callback
		// to avoid change handle in Callback
		Streamable.RequestSyncLoad(ObjPaths);
		TargetHandle.Reset();
		Callback.ExecuteIfBound();
	}
	else
	{
		TargetHandle.Reset();
	}
}
