// Copyright (c) 2022 mood701


#include "AvatarAssemblerCore/Dispatcher/AvatarCommonDispatcher.h"
#include "AvatarAssemblerCore/AvatarCommonDefine.h"
#include "AvatarUtils/AvatarMacros.h"

void UAvatarCommonDispatcher::AddOrExecuteWork(EAvatarWorkType WorkType, FSimpleDelegate WorkerFunc, TSharedPtr<FAvatarHandleBase>& WorkerHandle, FSimpleDelegate Callback /*= nullptr*/)
{
	if (WorkType == EAvatarWorkType::SYNC)
	{
		WorkerHandle.Reset();
		WorkerFunc.ExecuteIfBound();
		Callback.ExecuteIfBound();
	}
	else if(WorkType == EAvatarWorkType::ANY || WorkType == EAvatarWorkType::FRAME)
	{
		WorkerHandle = CreateWorkerHandle(WorkerFunc, Callback);
	}
	// todo
}

void UAvatarCommonDispatcher::CancelByID(int ID)
{
	if(ID <= 0 || ID > MAX_ID)
	{
		return;
	}

	if(Workers.Contains(ID))
	{
		// just remove this handle from Workers
		Workers.Remove(ID);
	}
}

bool UAvatarCommonDispatcher::IsIDValid(int ID)
{
	if (ID <= 0 || ID > MAX_ID)
	{
		return false;
	}
	return Workers.Contains(ID);
}

void UAvatarCommonDispatcher::Tick(float DeltaSeconds)
{
	AVATAR_CHECK(Strategy);
	Strategy->Start();
	while(Strategy->Next())
	{
		if (WorkerIndexQueue.IsEmpty())
		{
			return;
		}
		int ID = 0;
		while (WorkerIndexQueue.Dequeue(ID))
		{
			if (DoFrameWork(ID))
			{
				break;
			}
		}
	}
}

int UAvatarCommonDispatcher::GetNextID()
{
	++CurID;
	if(CurID > MAX_ID)
	{
		CurID -= MAX_ID;
	}
	return CurID;
}

TSharedPtr<FAvatarHandleBase> UAvatarCommonDispatcher::CreateWorkerHandle(FSimpleDelegate WorkerFunc, FSimpleDelegate Callback)
{
	TSharedPtr<FAvatarCommonWorkHandle> WorkerHandle = MakeShareable(new FAvatarCommonWorkHandle());
	WorkerHandle->Reset(this, GetNextID(), WorkerFunc, Callback);
	AVATAR_CHECK(!Workers.Contains(CurID));

	Workers.Add(CurID, WorkerHandle);
	WorkerIndexQueue.Enqueue(CurID);
	return WorkerHandle;
}

bool UAvatarCommonDispatcher::DoFrameWork(int ID)
{
	if(IsIDValid(ID))
	{
		Workers[ID]->DoWork();
		Workers.Remove(ID);
		return true;
	}
	else
	{
		return false;
	}
}

void FAvatarCommonWorkHandle::CancelHandle()
{
	if(Dispatcher.IsValid())
	{
		Dispatcher->CancelByID(ID);
		ID = 0;
	}
}

bool FAvatarCommonWorkHandle::IsValid() const
{
	AVATAR_CHECK(Dispatcher.IsValid());
	return Dispatcher.IsValid() && Dispatcher->IsIDValid(ID);
}

void FAvatarCommonWorkHandle::DoWork()
{
	WorkerFunc.ExecuteIfBound();
	Callback.ExecuteIfBound();
}
