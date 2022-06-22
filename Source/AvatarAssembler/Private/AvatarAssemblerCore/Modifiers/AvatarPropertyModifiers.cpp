// Copyright (c) 2022 mood701


#include "AvatarAssemblerCore/Modifiers/AvatarPropertyModifiers.h"
#include "AvatarUtils/AvatarMacros.h"

TArray<FSoftObjectPath> FAvatarPropertyModifier_UObject::CollectSoftObjects() const
{
	return TArray<FSoftObjectPath>{ObjPath};
}

void FAvatarPropertyModifier_UObject::ApplyToTarget(UObject* TargetObj) const
{
	UObject* Obj = ObjPath.TryLoad();
	AVATAR_CHECK(TargetObj);
	AVATAR_CHECK(Obj);

	if(TargetObj && Obj)
	{
		FProperty* Prop = TargetObj->GetClass()->FindPropertyByName(ParamName);
		FObjectProperty* TargetProp = CastFieldChecked<FObjectProperty>(Prop);
		if(TargetProp)
		{
			bool IsClassValid = Obj->GetClass()->IsChildOf(TargetProp->PropertyClass);
			AVATAR_CHECK(IsClassValid);
			if(IsClassValid)
			{
				UObject** TargetPropPtr = TargetProp->ContainerPtrToValuePtr<UObject*>(TargetObj);
				*TargetPropPtr = Obj;
			}
		}
	}
}

void FAvatarPropertyModifier_Float::ApplyToTarget(UObject* TargetObj) const
{
	AVATAR_CHECK(TargetObj);
	
	if(TargetObj)
	{
		FProperty* Prop = TargetObj->GetClass()->FindPropertyByName(ParamName);
		FFloatProperty* TargetProp = CastFieldChecked<FFloatProperty>(Prop);

		if(TargetProp)
		{
			float* TargetPropPtr = TargetProp->ContainerPtrToValuePtr<float>(TargetObj);
			*TargetPropPtr = Value;
		}
	}
}

void FAvatarPropertyModifier_Int::ApplyToTarget(UObject* TargetObj) const
{
	AVATAR_CHECK(TargetObj);

	if (TargetObj)
	{
		FProperty* Prop = TargetObj->GetClass()->FindPropertyByName(ParamName);
		FIntProperty* TargetProp = CastFieldChecked<FIntProperty>(Prop);

		if (TargetProp)
		{
			int* TargetPropPtr = TargetProp->ContainerPtrToValuePtr<int>(TargetObj);
			*TargetPropPtr = Value;
		}
	}
}
