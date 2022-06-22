// Copyright (c) 2022 mood701


#include "AvatarAssemblerCore/AvatarPropertyModifierBase.h"

void FAvatarPropertyModifierBase::ApplyModify() const
{
	for(auto& TargetObj : TargetObjs)
	{
		if(TargetObj.IsValid())
		{
			ApplyToTarget(TargetObj.Get());
		}
	}
}

void FAvatarPropertyModifierBase::AddTargetObj(UObject* TargetObj)
{
	if(TargetObj)
	{
		TargetObjs.Add(TargetObj);
	}
}
