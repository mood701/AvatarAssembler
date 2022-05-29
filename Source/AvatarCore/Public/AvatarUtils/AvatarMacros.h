// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

// for log
DECLARE_LOG_CATEGORY_EXTERN(AvatarAssembler, Log, All);

#define AVATAR_LOG(Fmt, ...) UE_LOG(AvatarAssembler, Log, TEXT(Fmt), ##__VA_ARGS__);
#define AVATAR_WRN(Fmt, ...) UE_LOG(AvatarAssembler, Warning, TEXT(Fmt), ##__VA_ARGS__);
#define AVATAR_ERR(Fmt, ...) UE_LOG(AvatarAssembler, Error, TEXT(Fmt), ##__VA_ARGS__);

#define AVATAR_LINE FString::FromInt(__LINE__)
#define AVATAR_FUNCNAME FString(__FUNCTION__)

#define AVATAR_LOG_ADV(Fmt, ...) AVATAR_LOG("[%s %s] %s", *AVATAR_FUNCNAME, *AVATAR_LINE, *FString::Format(TEXT(Fmt), {##__VA_ARGS__}))
#define AVATAR_WRN_ADV(Fmt, ...) AVATAR_WRN("[%s %s] %s", *AVATAR_FUNCNAME, *AVATAR_LINE, *FString::Format(TEXT(Fmt), {##__VA_ARGS__}))
#define AVATAR_ERR_ADV(Fmt, ...) AVATAR_ERR("[%s %s] %s", *AVATAR_FUNCNAME, *AVATAR_LINE, *FString::Format(TEXT(Fmt), {##__VA_ARGS__}))
//
