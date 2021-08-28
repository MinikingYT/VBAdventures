//SurvivalGame Project - The Unreal C++ Survival Game Course - Copyright Reuben Ward 2020

#pragma once

#include "CoreMinimal.h"
#include "Items/EquippableItem.h"
#include "WeaponItem.generated.h"

/**
 * 
 */
UCLASS(Blueprintable)
class SURVIVALGAME_API UWeaponItem : public UEquippableItem
{
	GENERATED_BODY()
public:

	UWeaponItem();

	virtual bool Equip(class ASurvivalCharacter* Character) override;
	virtual bool UnEquip(class ASurvivalCharacter* Character) override;

	//The weapon class to give to the player upon equipping this weapon item
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Weapon")
	TSubclassOf<class AWeapon> WeaponClass;
};
