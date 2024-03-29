// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "AvatarSoftCollector.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI, BlueprintType)
class UAvatarSoftCollector : public UInterface
{
	GENERATED_BODY()
};

class AVATARASSEMBLER_API IAvatarSoftCollector
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	virtual void CollectSoftObjects(TArray<FSoftObjectPath>& Paths) const = 0;
};
