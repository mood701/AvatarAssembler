// Fill out your copyright notice in the Description page of Project Settings.


#include "AvatarAssemblerCore/AvatarAssemblerComponent.h"
#include "AvatarAssemblerCore/AvatarPartTaskBase.h"
#include "AvatarUtils/AvatarMacros.h"
#include "AvatarAssemblerCore/AvatarCommonDefine.h"
#include "AvatarCore/Lib/AvatarMeshLib.h"
#include "AvatarAssemblerCore/Modifiers/PartModifiers/AvatarPartModifier_AttachTo.h"
#include "GameFramework/Character.h"

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


USkeletalMeshComponent* UAvatarAssemblerComponent::GetOrNewMeshComponent()
{
	USkeletalMeshComponent* MeshComp = nullptr;
	if(MeshComponentPool.Num())
	{
		MeshComp = MeshComponentPool.Pop();
	}
	else
	{
		AActor* Owner = GetOwner();
		MeshComp = NewObject<USkeletalMeshComponent>(Owner);
	}

	MeshComp->SetHiddenInGame(false);
	return MeshComp;
}

void UAvatarAssemblerComponent::RetainMeshComponent(USkeletalMeshComponent* MeshComp)
{
	AVATAR_CHECK(MeshComp);
	if(MeshComp)
	{
		if(CanRetainMeshComponent(MeshComp))
		{
			FAvatarMeshLib::ClearAnimInstanceSafe(MeshComp);
			MeshComp->SetSkeletalMesh(nullptr);
			MeshComp->SetHiddenInGame(true);
			MeshComponentPool.Add(MeshComp);
		}
		else
		{
			MeshComp->DestroyComponent();
		}
	}
}

bool UAvatarAssemblerComponent::CanRetainMeshComponent(USkeletalMeshComponent* MeshComp)
{
	// keep component pool count less than 5
	return MeshComponentPool.Num() < 5;
}

USkeletalMeshComponent* UAvatarAssemblerComponent::GetMaster() const
{
	AActor* Owner = GetOwner();
	AVATAR_CHECK(Owner);
	if(ACharacter* Character = Cast<ACharacter>(Owner))
	{
		return Character->GetMesh();
	}
	else if(Owner)
	{
		return Owner->FindComponentByClass<USkeletalMeshComponent>();
	}
	return nullptr;
}

void UAvatarAssemblerComponent::AddTask(UAvatarPartTaskBase* Task)
{
	AVATAR_CHECK(Task);
	const FName PartName = Task->GetPartName();
	AVATAR_CHECK(PartName.IsValid());

	if(PartName.IsNone() || Task == nullptr)
	{
		return;
	}

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
			if(Task->GetTargetMeshComponent() == nullptr)
			{
				UAvatarPartModifier_AttachTo* AttachTo = NewObject<UAvatarPartModifier_AttachTo>(this);
				AttachTo->Init(GetMaster());
				Task->AddModifier(AttachTo);
				Task->SetTargetMeshComponent(GetOrNewMeshComponent());
			}
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

