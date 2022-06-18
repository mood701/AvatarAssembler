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

#define AVATAR_LOG_ADV(Fmt, ...) AVATAR_LOG("[%s %s] %s", *AVATAR_FUNCNAME, *AVATAR_LINE, *FString::Printf(TEXT(Fmt), ##__VA_ARGS__))
#define AVATAR_WRN_ADV(Fmt, ...) AVATAR_WRN("[%s %s] %s", *AVATAR_FUNCNAME, *AVATAR_LINE, *FString::Printf(TEXT(Fmt), ##__VA_ARGS__))
#define AVATAR_ERR_ADV(Fmt, ...) AVATAR_ERR("[%s %s] %s", *AVATAR_FUNCNAME, *AVATAR_LINE, *FString::Printf(TEXT(Fmt), ##__VA_ARGS__))
//

// for assert
#define AVATAR_CHECK(EXPR) check(EXPR)
#define AVATAR_VERIFY(EXPR) verify(EXPR)
#define AVATAR_ENSURE(EXPR) ensure(EXPR)

#define AVATAR_CHECKF(EXPR, Fmt, ...) checkf(EXPR, TEXT(Fmt), ##__VA_ARGS__)
//

// for create object
#define AVATAR_SIMLPE_UOBJECT_EVENT(FUNC_NAME) FSimpleDelegate::CreateUObject(this, &##FUNC_NAME)
//
