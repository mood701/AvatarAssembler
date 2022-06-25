// Copyright (c) 2022 mood701

#pragma once

#include "CoreMinimal.h"
#include "AvatarAssemblerCore/AvatarPropertyModifierBase.h"

struct AVATARASSEMBLER_API FAvatarPropertyModifier_UObject : public FAvatarPropertyModifierBase
{
public:
	void SetValue(const FSoftObjectPath& InObjPath) { ObjPath = InObjPath; };
	virtual TArray<FSoftObjectPath> CollectSoftObjects() const;

	DEL_PROPERTY_MODIFIER_CONSTURCT(UObject)
	//FAvatarPropertyModifier_UObject(const FName& InParamName) : FAvatarPropertyModifierBase(InParamName){}

protected:
	virtual void ApplyToTarget(UObject* TargetObj) const override;

	FSoftObjectPath ObjPath;
};

struct AVATARASSEMBLER_API FAvatarPropertyModifier_Float : public FAvatarPropertyModifierBase
{
public:
	DEL_PROPERTY_MODIFIER_CONSTURCT(Float)
	void SetValue(float InValue) { Value = InValue; };

protected:
	virtual void ApplyToTarget(UObject* TargetObj) const override;

	float Value;
};

struct AVATARASSEMBLER_API FAvatarPropertyModifier_Int : public FAvatarPropertyModifierBase
{
public:
	DEL_PROPERTY_MODIFIER_CONSTURCT(Int)
	void SetValue(int InValue) { Value = InValue; };

protected:
	virtual void ApplyToTarget(UObject* TargetObj) const override;

	int Value;
};
