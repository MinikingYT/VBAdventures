// SurvivalGame Project - The Unreal C++ Survival Game Course - Copyright Reuben Ward 2020

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Player/SurvivalCharacter.h"
#include "DeathWidget.generated.h"

/**
 * 
 */
UCLASS()
class SURVIVALGAME_API UDeathWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:

	UPROPERTY(BlueprintReadOnly, Category = "HUD")
	class ASurvivalCharacter* Killer;

};
