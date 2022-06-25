// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AvatarAssemblerCore/AvatarPropertyModifierBase.h"

class UTexture;
struct AVATARASSEMBLER_API FAvatarPropertyModifier_MaterialScalar : public FAvatarPropertyModifierBase
{
public:
	void SetValue(float InValue) { ScalarValue = InValue; };

	DEL_PROPERTY_MODIFIER_CONSTURCT(MaterialScalar)
		//FAvatarPropertyModifier_UObject(const FName& InParamName) : FAvatarPropertyModifierBase(InParamName){}

protected:
	virtual void ApplyToTarget(UObject* TargetObj) const override;

	float ScalarValue;
};

struct AVATARASSEMBLER_API FAvatarPropertyModifier_MaterialVector : public FAvatarPropertyModifierBase
{
public:
	void SetValue(const FLinearColor& InValue) { VectorValue = InValue; };

	DEL_PROPERTY_MODIFIER_CONSTURCT(MaterialVector)
		//FAvatarPropertyModifier_UObject(const FName& InParamName) : FAvatarPropertyModifierBase(InParamName){}

protected:
	virtual void ApplyToTarget(UObject* TargetObj) const override;

	FLinearColor VectorValue;
};

struct AVATARASSEMBLER_API FAvatarPropertyModifier_MaterialTexture : public FAvatarPropertyModifierBase
{
public:
	void SetValue(UTexture* InValue) { TextureValue = InValue; };

	DEL_PROPERTY_MODIFIER_CONSTURCT(MaterialTexture)
		//FAvatarPropertyModifier_UObject(const FName& InParamName) : FAvatarPropertyModifierBase(InParamName){}

protected:
	virtual void ApplyToTarget(UObject* TargetObj) const override;

	TWeakObjectPtr<UTexture> TextureValue;
};
