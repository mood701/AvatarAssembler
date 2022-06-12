// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "AvatarConfig.generated.h"

/**
 * 
 */
UCLASS(config = Game, defaultconfig)
class AVATARCORE_API UAvatarConfig : public UObject
{
	GENERATED_BODY()
public:

	UPROPERTY(Config, EditDefaultsOnly, Category = AvatarConfig)
	int TestValue;

	const UAvatarConfig* Get() { return GetDefault<UAvatarConfig>(); }
};
