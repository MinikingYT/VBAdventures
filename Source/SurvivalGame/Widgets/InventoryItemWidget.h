//SurvivalGame Project - The Unreal C++ Survival Game Course - Copyright Reuben Ward 2020

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "InventoryItemWidget.generated.h"

/**
 * 
 */
UCLASS()
class SURVIVALGAME_API UInventoryItemWidget : public UUserWidget
{
	GENERATED_BODY()

public:

	UPROPERTY(BlueprintReadOnly, Category = "Inventory Item Widget", meta = (ExposeOnSpawn = true))
		class UItem* Item;
};
