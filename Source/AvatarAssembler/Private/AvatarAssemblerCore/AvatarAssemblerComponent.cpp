// Fill out your copyright notice in the Description page of Project Settings.


#include "AvatarAssemblerCore/AvatarAssemblerComponent.h"
#include "AvatarAssemblerCore/AvatarPartTaskBase.h"
#include "AvatarUtils/AvatarMacros.h"
#include "AvatarAssemblerCore/AvatarCommonDefine.h"

// Sets default values for this component's properties
UAvatarAssemblerComponent::UAvatarAssemblerComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UAvatarAssemblerComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


void UAvatarAssemblerComponent::AddTask(UAvatarPartTaskBase* Task)
{
	AVATAR_CHECK(Task);
	const FName PartName = Task->GetPartName();
	AVATAR_CHECK(PartName.IsValid());

	if(PartTasks.Contains(PartName))
	{
		UAvatarPartTaskBase* PrevTaskBase = PartTasks[PartName];
		if(PrevTaskBase != Task)
		{
			PrevTaskBase->Cancel();
			PartTasks[PartName] = Task;
		}
	}
	else
	{
		PartTasks.Add(PartName, Task);
	}
}

void UAvatarAssemblerComponent::StartRemainTasks()
{
	for(auto& KV : PartTasks)
	{
		UAvatarPartTaskBase* Task = KV.Value;
		EAvatarPartState State = Task->GetCurState();
		if(State == EAvatarPartState::NONE)
		{
			Task->Start();
		}
	}
}

// Called every frame
void UAvatarAssemblerComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

