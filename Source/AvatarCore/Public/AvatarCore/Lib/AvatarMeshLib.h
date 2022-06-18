// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

class USkeletalMeshComponent;
class AVATARCORE_API FAvatarMeshLib
{
public:
	static void ClearAnimInstanceSafe(USkeletalMeshComponent* MeshComponent);
};
