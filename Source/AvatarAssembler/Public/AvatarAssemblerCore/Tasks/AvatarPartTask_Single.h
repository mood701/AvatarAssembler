// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AvatarAssemblerCore/AvatarPartTaskBase.h"
#include "AvatarPartTask_Single.generated.h"

class USkeletalMesh;
struct FAvatarHandleBase;
UCLASS()
class AVATARASSEMBLER_API UAvatarPartTask_Single : public UAvatarPartTaskBase
{
	GENERATED_BODY()

public:
	// getter and setter
	UFUNCTION(BlueprintCallable, Category = AvatarPartTask)
	void SetMeshPath(TSoftObjectPtr<USkeletalMesh> InMeshPath) { MeshPath = InMeshPath; }
	UFUNCTION(BlueprintCallable, Category = AvatarPartTask, BlueprintPure)
	TSoftObjectPtr<USkeletalMesh> GetMeshPath() const { return MeshPath; }

	//

	// IAvatarSoftCollector
	virtual void CollectSoftObjects(TArray<FSoftObjectPath>& Paths) const;
	// IAvatarSoftCollector

protected:

	// override functions
	virtual void OnPreStart() override;
	virtual void OnCancel() override;
	virtual void OnStartResourceLoad() override;
	virtual void OnResourceLoaded() override;
	virtual void OnApplyModifiersBegin() override;
	virtual void OnApplyModifiersEnd() override;
	virtual void OnTaskDone() override;
	//

	UPROPERTY(VisibleAnywhere, SkipSerialization)
	TSoftObjectPtr<USkeletalMesh> MeshPath;

	UPROPERTY(VisibleAnywhere, SkipSerialization)
	USkeletalMesh* Mesh;

	TSharedPtr<FAvatarHandleBase> ResourceHandle;
};
