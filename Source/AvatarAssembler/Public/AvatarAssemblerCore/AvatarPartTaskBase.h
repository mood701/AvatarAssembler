// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Interfaces/Interface_AssetUserData.h"
#include "AvatarAssemblerInterface/AvatarSoftCollector.h"
#include "AvatarAssemblerCore/AvatarCommonDefine.h"
#include "AvatarPartTaskBase.generated.h"

class UAvatarPartModifierBase;
DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FOnAvatarPartStateChanged, UAvatarPartTaskBase*, PartTask, EAvatarPartState, PreState, EAvatarPartState, CurState);

UCLASS()
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

	// getter
	UFUNCTION(BlueprintCallable, Category = AvatarPartTask)
	FName GetPartName() const { return PartName; }
	UFUNCTION(BlueprintCallable, Category = AvatarPartTask)
	EAvatarPartState GetCurState() const { return CurState; }
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
	virtual TArray<FSoftObjectPath> CollectSoftObjects_Implement() const;
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
	void MoveToNextState();
	void ResetState();
	void SetState(EAvatarPartState InState);
	// state

	// pipline
	void StartResourceLoad();
	void OnResourceLoaded();
	void ApplyModifiers();
	void TaskDone();
	// pipline

private:
	UPROPERTY(EditAnywhere, AdvancedDisplay, Category = AvatarPartTask)
	TArray<UAssetUserData*> AssetUserData;

	UPROPERTY(EditAnywhere, Category = AvatarPartTask)
	TArray<UAvatarPartModifierBase*> Modifiers;

	UPROPERTY(EditAnywhere)
	FName PartName;

	UPROPERTY(VisibleAnywhere)
	EAvatarPartState CurState;
};
