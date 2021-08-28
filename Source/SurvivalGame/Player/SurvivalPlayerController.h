//SurvivalGame Project - The Unreal C++ Survival Game Course - Copyright Reuben Ward 2020

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "SurvivalPlayerController.generated.h"

class UQuest;
class UQuestState;

/**
 * 
 */
UCLASS()
class SURVIVALGAME_API ASurvivalPlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:


	ASurvivalPlayerController();
	
	UFUNCTION(Client, Reliable, BlueprintCallable)
	void ClientShowNotification(const FText& Message);

protected:

	virtual void BeginPlay() override;
	virtual void SetupInputComponent() override;

public:

	void Died(class ASurvivalCharacter* Killer);

	UFUNCTION(Client, Unreliable)
	void ClientShotHitConfirmed();

	UFUNCTION(BlueprintCallable)
	void Respawn();

	UFUNCTION(Server, Reliable, WithValidation)
	void ServerRespawn();

	//Only works for the local player.
	UFUNCTION(BlueprintPure)
	bool IsInventoryOpen() const;

protected:

	void OpenInventory();

	void OpenMap();
	void CloseMap();

	void PauseGame();

	UFUNCTION(BlueprintCallable)
	void ResumeGame();

public:

	/**Applies recoil to the camera.
	@param RecoilAmount the amount to recoil by. X is the yaw, Y is the pitch
	@param RecoilSpeed the speed to bump the camera up per second from the recoil
	@param RecoilResetSpeed the speed the camera will return to center at per second after the recoil is finished
	@param Shake an optional camera shake to play with the recoil*/
	void ApplyRecoil(const FVector2D& RecoilAmount, const float RecoilSpeed, const float RecoilResetSpeed);

	//The amount of recoil to apply. We store this in a variable as we smoothly apply the recoil over several frames
	UPROPERTY(VisibleAnywhere, Category = "Recoil")
	FVector2D RecoilBumpAmount;

	//The amount of recoil the gun has had, that we need to reset (After shooting we slowly want the recoil to return to normal.)
	UPROPERTY(VisibleAnywhere, Category = "Recoil")
	FVector2D RecoilResetAmount;

	//The speed at which the recoil bumps up per second
	UPROPERTY(EditDefaultsOnly, Category = "Recoil")
	float CurrentRecoilSpeed;

	//The speed at which the recoil resets per second
	UPROPERTY(EditDefaultsOnly, Category = "Recoil")
	float CurrentRecoilResetSpeed;

	//The last time that we applied recoil
	UPROPERTY(VisibleAnywhere, Category = "Recoil")
	float LastRecoilTime;

	void Turn(float Rate);
	void LookUp(float Rate);

	void StartReload();

};
