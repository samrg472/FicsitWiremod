// 

#pragma once

#include "CoreMinimal.h"
#include "ConnectionType.generated.h"

UENUM(BlueprintType)
enum EConnectionType
{
	Unknown,
	Boolean,
	Number,
	String,
	Vector,
	Inventory,
	PowerGrid,
	Entity,
	Recipe,
	Color,
	ArrayOfBoolean,
	ArrayOfNumber,
	ArrayOfString,
	ArrayOfVector,
	ArrayOfEntity,
	ArrayOfColor,
	Stack,
	ArrayOfStack,
	Any,
	Integer,
	CustomStruct,
	AnyArray,
	AnyNonArray,
	ArrayOfPowerGrid,
	ArrayOfInventory,
	ArrayOfRecipe,
	NonReferenceable,
	ItemAmount,
	ArrayOfItemAmount,
	ArrayOfCustomStruct
};

UENUM(BlueprintType)
enum EConnectionDirection
{
	Input,
	Output
};


UCLASS()
class UConnectionTypeFunctions : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:


	UFUNCTION(BlueprintPure)
	static bool IsValidConnectionPair(EConnectionType Input, EConnectionType Output)
	{
		if(Input == Unknown || Output == Unknown) return false;
		if(Input == Any) return true;
		if(Input == Output) return true;
		if(Input == AnyArray) return IsArrayType(Output);
		if(Input == AnyNonArray) return !IsArrayType(Output);
		if(Input == Number || Input == Integer) return Output == Number || Output == Integer;
		if(Input == NonReferenceable) return Output != Inventory && Output != PowerGrid;
		
		return false;
	}

	UFUNCTION(BlueprintPure)
	static EConnectionType BaseToArray(EConnectionType in)
	{
		switch (in)
		{
		case Unknown: return Unknown;
		case Boolean: return ArrayOfBoolean;
		case String: return ArrayOfString;
		case Integer:
		case Number: return ArrayOfNumber;
		case Color: return ArrayOfColor;
		case Vector: return ArrayOfVector;
		case Entity: return ArrayOfEntity;
		case PowerGrid: return ArrayOfPowerGrid;
		case Inventory: return ArrayOfInventory;
		case Stack: return ArrayOfStack;
		case Recipe: return ArrayOfRecipe;
		case Any: return Any;
		case AnyNonArray: return AnyArray;
		case ItemAmount: return ArrayOfItemAmount;
		case CustomStruct: return ArrayOfCustomStruct;
		default:
			UE_LOG(LogTemp, Error,TEXT("[WIREMOD] Failed to find a switch case for EConnectionType::%d in function BASE_TO_ARRAY"), in);
			return Unknown;
		}
	}

	UFUNCTION(BlueprintPure)
	static EConnectionType ArrayToBase(EConnectionType in)
	{
		switch (in)
		{
		case Unknown: return Unknown;
		case ArrayOfBoolean: return Boolean;
		case ArrayOfNumber: return Number;
		case ArrayOfString: return String;
		case ArrayOfVector: return Vector;
		case ArrayOfColor: return Color;
		case ArrayOfEntity: return Entity;
		case ArrayOfInventory: return Inventory;
		case ArrayOfStack: return Stack;
		case ArrayOfPowerGrid: return PowerGrid;
		case ArrayOfRecipe: return Recipe;
		case Any: return Any;
		case AnyArray: return AnyNonArray;
		case ArrayOfItemAmount: return ItemAmount;
		case ArrayOfCustomStruct: return CustomStruct;
		default:
			UE_LOG(LogTemp, Error,TEXT("[WIREMOD] Failed to find a switch case for EConnectionType::%d in function ARRAY_TO_BASE"), in);
			return Unknown;
		}
	}

	UFUNCTION(BlueprintPure)
	static bool IsArrayType(EConnectionType type)
	{
		switch (type)
		{
		case EConnectionType::ArrayOfBoolean:
		case EConnectionType::ArrayOfVector:
		case EConnectionType::ArrayOfColor:
		case EConnectionType::ArrayOfEntity:
		case EConnectionType::ArrayOfInventory:
		case EConnectionType::ArrayOfNumber:
		case EConnectionType::ArrayOfStack:
		case EConnectionType::ArrayOfString:
		case EConnectionType::ArrayOfPowerGrid:
		case EConnectionType::ArrayOfRecipe:
		case EConnectionType::ArrayOfItemAmount:
		case EConnectionType::ArrayOfCustomStruct:
			return true;

		default: return false;
		}
	}

	UFUNCTION(BlueprintPure)
	static bool IsUtilityType(EConnectionType Type)
	{
		switch (Type)
		{
		case Any:
		case AnyArray:
		case AnyNonArray:
		case NonReferenceable:
			return true;

		default: return false;
		}
	}
};