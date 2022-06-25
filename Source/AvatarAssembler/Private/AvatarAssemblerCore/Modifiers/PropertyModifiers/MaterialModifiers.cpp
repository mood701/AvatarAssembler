// Fill out your copyright notice in the Description page of Project Settings.


#include "AvatarAssemblerCore/Modifiers/PropertyModifiers/MaterialModifiers.h"
#include "Materials/MaterialInstanceDynamic.h"

void FAvatarPropertyModifier_MaterialScalar::ApplyToTarget(UObject* TargetObj) const
{
	if(UMaterialInstanceDynamic* MID = Cast<UMaterialInstanceDynamic>(TargetObj))
	{
		MID->SetScalarParameterValue(ParamName, ScalarValue);
	}
}

void FAvatarPropertyModifier_MaterialVector::ApplyToTarget(UObject* TargetObj) const
{
	if (UMaterialInstanceDynamic* MID = Cast<UMaterialInstanceDynamic>(TargetObj))
	{
		MID->SetVectorParameterValue(ParamName, VectorValue);
	}
}

void FAvatarPropertyModifier_MaterialTexture::ApplyToTarget(UObject* TargetObj) const
{
	if (UMaterialInstanceDynamic* MID = Cast<UMaterialInstanceDynamic>(TargetObj))
	{
		MID->SetTextureParameterValue(ParamName, TextureValue.Get());
	}
}
