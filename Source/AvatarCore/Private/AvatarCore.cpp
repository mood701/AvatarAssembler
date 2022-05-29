// Copyright Epic Games, Inc. All Rights Reserved.

#include "AvatarCore.h"
#include "AvatarUtils/AvatarMacros.h"

#define LOCTEXT_NAMESPACE "FAvatarCoreModule"

void FAvatarCoreModule::StartupModule()
{
	// AVATAR_LOG_ADV(" with [{0} {1}] ForTest", *AVATAR_FUNCNAME, *AVATAR_LINE)
	// AVATAR_WRN_ADV(" with [{0} {1}] ForTest", *AVATAR_FUNCNAME, *AVATAR_LINE)
	// AVATAR_ERR_ADV(" with [{0} {1}] ForTest", *AVATAR_FUNCNAME, *AVATAR_LINE)
	// This code will execute after your module is loaded into memory; the exact timing is specified in the .uplugin file per-module
}

void FAvatarCoreModule::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FAvatarCoreModule, AvatarCore)