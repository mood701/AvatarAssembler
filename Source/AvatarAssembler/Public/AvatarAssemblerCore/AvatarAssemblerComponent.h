// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "AvatarAssemblerComponent.generated.h"

class UAvatarPartTaskBase;

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

public:	

	UFUNCTION(BlueprintCallable, Category=AvatarAssemblerComponent)
	void AddTask(UAvatarPartTaskBase* Task);
	UFUNCTION(BlueprintCallable, Category = AvatarAssemblerComponent)
	void StartRemainTasks();
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	
};
