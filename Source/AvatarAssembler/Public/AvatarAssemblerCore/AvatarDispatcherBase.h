// Copyright (c) 2022 mood701

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "AvatarDispatcherBase.generated.h"

struct FAvatarHandleBase;
enum class EAvatarWorkType : uint8;

class FAvatarDispatherStrategyBase
{
public:
	virtual void Start() {};
	virtual bool Next() { return false; };
};

UCLASS()
class AVATARASSEMBLER_API UAvatarDispatcherBase : public UObject
{
	GENERATED_BODY()

public:
	virtual void AddOrExecuteWork(EAvatarWorkType WorkType, FSimpleDelegate WorkerFunc,
		TSharedPtr<FAvatarHandleBase>& WorkerHandle, FSimpleDelegate Callback=nullptr)
		PURE_VIRTUAL(UAvatarDispatcherBase::AddOrExecuteWork, return;);

	virtual void Tick(float DeltaSeconds) {};
	
	void SetStrategy(TSharedPtr <FAvatarDispatherStrategyBase> InStrategy)
	{
		Strategy = InStrategy; 
	}

protected:
	TSharedPtr<FAvatarDispatherStrategyBase> Strategy;
};
