// Copyright (c) 2022 mood701

#pragma once

#include "CoreMinimal.h"
#include "AvatarAssemblerCore/AvatarDispatcherBase.h"
#include "AvatarAssemblerCore/AvatarHandleBase.h"
#include "AvatarCommonDispatcher.generated.h"

USTRUCT()
struct AVATARASSEMBLER_API FAvatarCommonWorkHandle : public FAvatarHandleBase
{
	GENERATED_BODY()
public:
	virtual void CancelHandle() override;
	virtual bool IsValid() const override;
	void Reset(UAvatarCommonDispatcher* InDispatcher, int InID, const FSimpleDelegate& InWorkerFunc, const FSimpleDelegate& InCallback)
	{ 
		Dispatcher = InDispatcher;
		ID = InID;
		WorkerFunc = InWorkerFunc;
		Callback = InCallback;
	}
	void DoWork();
	int GetID() const { return ID; }
private:
	TWeakObjectPtr<UAvatarCommonDispatcher> Dispatcher;
	int ID = 0;
	FSimpleDelegate WorkerFunc;
	FSimpleDelegate Callback;
};

class FAvatarCommonDispatherStrategy : public FAvatarDispatherStrategyBase
{
public:
	virtual void Start() override { CurCount = 0; };
	virtual bool Next() override { return MaxCount > CurCount++; }
	void Init(int InMax) { MaxCount = InMax; };
private:
	int CurCount = 0;
	int MaxCount = 0;
};

UCLASS()
class AVATARASSEMBLER_API UAvatarCommonDispatcher : public UAvatarDispatcherBase
{
	GENERATED_BODY()
public:
	virtual void AddOrExecuteWork(EAvatarWorkType WorkType, FSimpleDelegate WorkerFunc,
		TSharedPtr<FAvatarHandleBase>& WorkerHandle, FSimpleDelegate Callback = nullptr) override;
	
	void CancelByID(int ID);
	bool IsIDValid(int ID);
	int GetCurID() const { return CurID; }

	virtual void Tick(float DeltaSeconds) override;

protected:
	int GetNextID();

	TSharedPtr<FAvatarHandleBase> CreateWorkerHandle(FSimpleDelegate WorkerFunc, FSimpleDelegate Callback);
	bool DoFrameWork(int ID);

	TMap<int, TSharedPtr<FAvatarCommonWorkHandle>> Workers;
	TQueue<int> WorkerIndexQueue;

	constexpr static int MAX_ID = 10000;
	int CurID = 0;
};
