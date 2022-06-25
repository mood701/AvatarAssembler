// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AvatarAssemblerInterface/AvatarSoftCollector.h"
#include "AvatarPartModifierBase.generated.h"

class USkeletalMeshComponent;
class UAvatarPartTaskBase;

UCLASS(Abstract, EditInlineNew)
class AVATARASSEMBLER_API UAvatarPartModifierBase : public UObject, public IAvatarSoftCollector
{
	GENERATED_BODY()

public:
	virtual void ModifyAvatarPart(UAvatarPartTaskBase* PartTask) const PURE_VIRTUAL(UAvatarPartModifierBase::ModifyAvatarPart, );

	virtual void CollectSoftObjects(TArray<FSoftObjectPath>& Paths) const override {  }

	UFUNCTION(BlueprintCallable)
	int GetPriority() const { return Priority; }
	UFUNCTION(BlueprintCallable)
	void SetPriority(int InPriority) { Priority = InPriority; }

private:
	UPROPERTY(EditAnywhere)
	int Priority = 0;
};
