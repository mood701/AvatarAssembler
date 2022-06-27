// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Interfaces/Interface_AssetUserData.h"
#include "AvatarAssemblerInterface/AvatarSoftCollector.h"
#include "AvatarAssemblerCore/AvatarCommonDefine.h"
#include "AvatarPartTaskBase.generated.h"

class UAvatarPartModifierBase;
class USkeletalMeshComponent;
class UAvatarLoaderBase;
class UAvatarDispatcherBase;
DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FOnAvatarPartStateChanged, UAvatarPartTaskBase*, PartTask, EAvatarPartState, PreState, EAvatarPartState, CurState);

UCLASS(BlueprintType)
class AVATARASSEMBLER_API UAvatarPartTaskBase : public UObject, public IInterface_AssetUserData, public IAvatarSoftCollector
{
	GENERATED_BODY()
	
public:

	// modifier
	UFUNCTION(BlueprintCallable, Category = AvatarPartTask)
	void AddModifier(UAvatarPartModifierBase* Modifier);
	UFUNCTION(BlueprintCallable, Category = AvatarPartTask)
	void RemoveModifierOfClass(TSubclassOf<UAvatarPartModifierBase> InModifierClass);
	UFUNCTION(BlueprintCallable, Category = AvatarPartTask)
	UAvatarPartModifierBase* GetModifierOfClass(TSubclassOf<UAvatarPartModifierBase> InModifierClass);
	// modifier

	// getter and setter
	UFUNCTION(BlueprintCallable, Category = AvatarPartTask, BlueprintPure)
	FName GetPartName() const { return PartName; }
	UFUNCTION(BlueprintCallable, Category = AvatarPartTask)
	void SetPartName(const FName& InPartName) { PartName = InPartName; }

	UFUNCTION(BlueprintCallable, Category = AvatarPartTask, BlueprintPure)
	EAvatarPartState GetCurState() const { return CurState; }

	UFUNCTION(BlueprintCallable, Category = AvatarPartTask, BlueprintPure)
	USkeletalMeshComponent* GetTargetMeshComponent() const { return TargetMeshComp; }
	UFUNCTION(BlueprintCallable, Category = AvatarPartTask)
	USkeletalMeshComponent* ResetTargetMeshComponent();
	UFUNCTION(BlueprintCallable, Category = AvatarPartTask)
	void SetTargetMeshComponent(USkeletalMeshComponent* MeshComp);

	void SetLoader(UAvatarLoaderBase* InLoader) { OwnLoader = InLoader; }
	UAvatarLoaderBase* GetLoader() const { return OwnLoader; }

	void SetDispatcher(UAvatarDispatcherBase* InDispatcher) { OwnDispatcher = InDispatcher; }
	UAvatarDispatcherBase* GetDispatcher() const { return OwnDispatcher; }
	// getter

	// IInterface_AssetUserData -> bp
	UFUNCTION(BlueprintCallable, Category = AvatarPartTask)
	void AddPartUserData(UAssetUserData* InUserData) { AddAssetUserData(InUserData); }
	UFUNCTION(BlueprintCallable, Category = AvatarPartTask)
	void RemovePartUserDataOfClass(TSubclassOf<UAssetUserData> InUserDataClass) { RemoveUserDataOfClass(InUserDataClass); }
	UFUNCTION(BlueprintCallable, Category = AvatarPartTask)
	UAssetUserData* GetPartUserDataOfClass(TSubclassOf<UAssetUserData> InUserDataClass) { return GetAssetUserDataOfClass(InUserDataClass); }
	// IInterface_AssetUserData -> bp
	
	// IAvatarSoftCollector
	virtual void CollectSoftObjects(TArray<FSoftObjectPath>& Paths) const;
	// IAvatarSoftCollector

	// pipline
	UFUNCTION(BlueprintCallable, Category = AvatarPartTask)
	void Start();
	UFUNCTION(BlueprintCallable, Category = AvatarPartTask)
	void Cancel();
	// pipline

	FOnAvatarPartStateChanged OnAvatarPartStateChanged;
protected:
	//~ Begin IInterface_AssetUserData Interface
	virtual void AddAssetUserData(UAssetUserData* InUserData) override;
	virtual void RemoveUserDataOfClass(TSubclassOf<UAssetUserData> InUserDataClass) override;
	virtual UAssetUserData* GetAssetUserDataOfClass(TSubclassOf<UAssetUserData> InUserDataClass) override;
	virtual const TArray<UAssetUserData*>* GetAssetUserDataArray() const override;
	//~ End IInterface_AssetUserData Interface

#if WITH_EDITOR
	virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;
#endif
	
	// state
	void MoveToNextState(FSimpleDelegate EventBeforePost);
	void ResetState(FSimpleDelegate EventBeforePost);
	void SetState(EAvatarPartState InState, FSimpleDelegate EventBeforePost);
	// state

	// pipline
	void StartResourceLoad();
	void ResourceLoaded();
	void ApplyModifiersBegin();
	void ApplyModifiersEnd();
	void TaskDone();

	virtual void OnPreStart() {};
	virtual void OnCancel() {};
	virtual void OnStartResourceLoad(){};
	virtual void OnResourceLoaded() {};
	virtual void OnApplyModifiersBegin() {};
	virtual void OnApplyModifiersEnd() {};
	virtual void OnTaskDone() {};
	// pipline

	TArray<FSoftObjectPath> GetSoftPaths() const;

	UPROPERTY(SkipSerialization)
	USkeletalMeshComponent* TargetMeshComp;

	UPROPERTY(EditAnywhere, Category = AvatarPartTask, SkipSerialization)
	TArray<UAvatarPartModifierBase*> Modifiers;

private:
	UPROPERTY(EditAnywhere, AdvancedDisplay, Category = AvatarPartTask, SkipSerialization)
	TArray<UAssetUserData*> AssetUserData;

	UPROPERTY(EditAnywhere, SkipSerialization)
	FName PartName;

	UPROPERTY(VisibleAnywhere, SkipSerialization)
	EAvatarPartState CurState;

	UPROPERTY(VisibleAnywhere, SkipSerialization)
	UAvatarLoaderBase* OwnLoader;

	UPROPERTY(VisibleAnywhere, SkipSerialization)
	UAvatarDispatcherBase* OwnDispatcher;
};
