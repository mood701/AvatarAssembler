// Fill out your copyright notice in the Description page of Project Settings.
#include "AvatarAssemblerCore/Tasks/AvatarPartTask_Single.h"
#include "AvatarUtils/AvatarMacros.h"

void UAvatarPartTask_Single::OnPreStart()
{
	AVATAR_LOG("[%s%s]", *AVATAR_FUNCNAME, *AVATAR_LINE);
	StartResourceLoad();
}

void UAvatarPartTask_Single::OnCancel()
{
	AVATAR_LOG("[%s%s]", *AVATAR_FUNCNAME, *AVATAR_LINE);
}

void UAvatarPartTask_Single::OnStartResourceLoad()
{
	AVATAR_LOG("[%s%s]", *AVATAR_FUNCNAME, *AVATAR_LINE);
	ResourceLoaded();
}

void UAvatarPartTask_Single::OnResourceLoaded()
{
	AVATAR_LOG("[%s%s]", *AVATAR_FUNCNAME, *AVATAR_LINE);
	ApplyModifiersBegin();
}

void UAvatarPartTask_Single::OnApplyModifiersBegin()
{
	AVATAR_LOG("[%s%s]", *AVATAR_FUNCNAME, *AVATAR_LINE);
	ApplyModifiersEnd();
}

void UAvatarPartTask_Single::OnApplyModifiersEnd()
{
	AVATAR_LOG("[%s%s]", *AVATAR_FUNCNAME, *AVATAR_LINE);
	TaskDone();
}

void UAvatarPartTask_Single::OnTaskDone()
{
	AVATAR_LOG("[%s%s]", *AVATAR_FUNCNAME, *AVATAR_LINE);
}
