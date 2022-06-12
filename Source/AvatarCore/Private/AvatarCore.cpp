// Copyright Epic Games, Inc. All Rights Reserved.

#include "AvatarCore.h"
#include "AvatarUtils/AvatarMacros.h"
#include "ISettingsModule.h"
#include "AvatarCore/AvatarConfig.h"

#define LOCTEXT_NAMESPACE "FAvatarCoreModule"

void FAvatarCoreModule::StartupModule()
{
	// This code will execute after your module is loaded into memory; the exact timing is specified in the .uplugin file per-module
	AVATAR_LOG_ADV(" with [%s %s] ForTest", *AVATAR_FUNCNAME, *AVATAR_LINE)
	AVATAR_WRN_ADV(" with [%s %s] ForTest", *AVATAR_FUNCNAME, *AVATAR_LINE)
	AVATAR_ERR_ADV(" with [%s %s] ForTest", *AVATAR_FUNCNAME, *AVATAR_LINE)
	RegisterSettings();
}

void FAvatarCoreModule::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.
	UnregisterSettings();
}

void FAvatarCoreModule::RegisterSettings()
{
	ISettingsModule* SettingModule = FModuleManager::GetModulePtr<ISettingsModule>("Settings");
	if (SettingModule)
	{
		SettingModule->RegisterSettings("Project", "Plugins", "AvatarAssembler",
			LOCTEXT("AvatarAssemblerSettings", "Avatar Assembler"),
			LOCTEXT("AvatarAssemblerSettingsSection", "Configure avatar assembler settings."),
			GetMutableDefault<UAvatarConfig>());
	}
}

void FAvatarCoreModule::UnregisterSettings()
{
	ISettingsModule* SettingModule = FModuleManager::GetModulePtr<ISettingsModule>("Settings");
	if (SettingModule)
	{
		SettingModule->UnregisterSettings("Project", "Plugins", "AvatarAssembler");
	}
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FAvatarCoreModule, AvatarCore)