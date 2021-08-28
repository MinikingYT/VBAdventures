// SurvivalGame Project - The Unreal C++ Survival Game Course - Copyright Reuben Ward 2020

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "SurvivalHUD.generated.h"

/**
 * 
 */
UCLASS()
class SURVIVALGAME_API ASurvivalHUD : public AHUD
{
	GENERATED_BODY()
	
public:

	ASurvivalHUD();

	virtual void BeginPlay() override;

	void OpenInventoryWidget();

	void OpenPauseWidget();
	void ClosePauseWidget();

	void CreateGameplayWidget();

	void CreateNotificationWidget();
	void ShowNotification(const FText& NotificationText);

	void ShowDeathWidget(class ASurvivalCharacter* Killer);

	void OpenMap();
	void CloseMap();

	void OpenLootWidget();
	void CloseLootWidget();

	void ShowHitmarker();

	bool IsInventoryOpen() const;

protected:

	/**Widget classes and refs*/
	UPROPERTY(EditDefaultsOnly, Category = "Widgets")
	TSubclassOf<class UInventoryWidget> InventoryWidgetClass;

	UPROPERTY(EditDefaultsOnly, Category = "Widgets")
	TSubclassOf<class UNotificationWidget> NotificationWidgetClass;

	UPROPERTY(EditDefaultsOnly, Category = "Widgets")
	TSubclassOf<class UGameplayWidget> GameplayWidgetClass;

	UPROPERTY(EditDefaultsOnly, Category = "Widgets")
	TSubclassOf<class UMapWidget> MapWidgetClass;

	UPROPERTY(EditDefaultsOnly, Category = "Widgets")
	TSubclassOf<class UDeathWidget> DeathWidgetClass;

	UPROPERTY(EditDefaultsOnly, Category = "Widgets")
	TSubclassOf<class ULootWidget> LootWidgetClass;

	UPROPERTY(EditDefaultsOnly, Category = "Widgets")
	TSubclassOf<class UPauseWidget> PauseWidgetClass;

public:

	UPROPERTY(BlueprintReadOnly, Category = "Widgets")
	class UInventoryWidget* InventoryWidget;

	UPROPERTY(BlueprintReadOnly, Category = "Widgets")
	class UNotificationWidget* NotificationWidget;

	UPROPERTY(BlueprintReadOnly, Category = "Widgets")
	class UGameplayWidget* GameplayWidget;

	UPROPERTY(BlueprintReadOnly, Category = "Widgets")
	class UMapWidget* MapWidget;

	UPROPERTY(BlueprintReadOnly, Category = "Widgets")
	class UDeathWidget* DeathWidget;

	UPROPERTY(BlueprintReadOnly, Category = "Widgets")
	class ULootWidget* LootWidget;

	UPROPERTY(BlueprintReadOnly, Category = "Widgets")
	class UPauseWidget* PauseWidget;

};
