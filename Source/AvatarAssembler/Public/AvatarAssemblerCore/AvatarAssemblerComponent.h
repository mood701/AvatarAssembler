// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "AvatarAssemblerComponent.generated.h"

class UAvatarPartTaskBase;
class UAvatarLoaderBase;
class UAvatarDispatcherBase;

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class AVATARASSEMBLER_API UAvatarAssemblerComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UAvatarAssemblerComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, SkipSerialization)
	TMap<FName, UAvatarPartTaskBase*> PartTasks;

	UPROPERTY(VisibleAnywhere, SkipSerialization)
	TArray<USkeletalMeshComponent*> MeshComponentPool;

	UPROPERTY(VisibleAnywhere, SkipSerialization)
	UAvatarLoaderBase* OwnLoader;

	UPROPERTY(VisibleAnywhere, SkipSerialization)
	UAvatarDispatcherBase* Dispatcher;

	virtual USkeletalMeshComponent* GetOrNewMeshComponent();
	virtual void RetainMeshComponent(USkeletalMeshComponent* MeshComp);
	virtual bool CanRetainMeshComponent(USkeletalMeshComponent* MeshComp);
	USkeletalMeshComponent* GetMaster() const;

public:	

	UFUNCTION(BlueprintCallable, Category=AvatarAssemblerComponent)
	void AddTask(UAvatarPartTaskBase* Task);
	UFUNCTION(BlueprintCallable, Category = AvatarAssemblerComponent)
	void StartRemainTasks();
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
};
