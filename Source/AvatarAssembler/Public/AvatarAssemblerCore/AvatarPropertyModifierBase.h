// Copyright (c) 2022 mood701

#pragma once

#include "CoreMinimal.h"

#define DEL_PROPERTY_MODIFIER_CONSTURCT(TYPE_NAME) FAvatarPropertyModifier_##TYPE_NAME(const FName& InParamName) : FAvatarPropertyModifierBase(InParamName){}

struct AVATARASSEMBLER_API FAvatarPropertyModifierBase
{
public:
	FAvatarPropertyModifierBase(const FName& InParamName) : ParamName(InParamName) {}
	virtual ~FAvatarPropertyModifierBase() {}

	void ApplyModify() const;
	void AddTargetObj(UObject* TargetObj);
	void ClearTargetObjs() { TargetObjs.Empty(); }
	// struct can't use unreal interface
	virtual TArray<FSoftObjectPath> CollectSoftObjects() const { return TArray<FSoftObjectPath>(); }
protected:
	virtual void ApplyToTarget(UObject* TargetObj) const {}

	TArray<TWeakObjectPtr<UObject>> TargetObjs;
	FName ParamName;

public:
	template<class ModifierClass>
	static TSharedPtr<ModifierClass> Create(const FName& InParamName)
	{
		static_assert(TPointerIsConvertibleFromTo<ModifierClass, FAvatarPropertyModifierBase>::Value, "ModifierClass must is sub class of FAvatarPropertyModifierBase.");
		return MakeShareable<ModifierClass>(new ModifierClass(InParamName));
	}

	template<class ModifierClass>
	static TSharedPtr<ModifierClass> Create(const FName& InParamName, UObject* TargetObj)
	{
		TSharedPtr<ModifierClass> Modifier = Create<ModifierClass>(InParamName);
		Modifier->AddTargetObj(TargetObj);
		return Modifier;
	}
};
