//SurvivalGame Project - The Unreal C++ Survival Game Course - Copyright Reuben Ward 2020

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "SurvivalCharacter.generated.h"

USTRUCT()
struct FInteractionData
{
	GENERATED_BODY()

	FInteractionData()
	{
		ViewedInteractionComponent = nullptr;
		LastInteractionCheckTime = 0.f;
		bInteractHeld = false;
	}

	//The current interactable component we're viewing, if there is one
	UPROPERTY()
	class UInteractionComponent* ViewedInteractionComponent;

	//The time when we last checked for an interactable
	UPROPERTY()
	float LastInteractionCheckTime;

	//Whether the local player is holding the interact key
	UPROPERTY()
	bool bInteractHeld;

};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnEquippedItemsChanged, const EEquippableSlot, Slot, const UEquippableItem*, Item);

UCLASS()
class SURVIVALGAME_API ASurvivalCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ASurvivalCharacter();

	//The mesh to have equipped if we dont have an item equipped - ie the bare skin meshes
	UPROPERTY(BlueprintReadOnly, Category = Mesh)
	TMap<EEquippableSlot, USkeletalMesh*> NakedMeshes;

	//The players body meshes.
	UPROPERTY(BlueprintReadOnly, Category = Mesh)
	TMap<EEquippableSlot, USkeletalMeshComponent*> PlayerMeshes;

	/**Our players inventory*/
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Components")
	class UInventoryComponent* PlayerInventory;

	/**Interaction component used to allow other players to loot us when we have died*/
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Components")
	class UInteractionComponent* LootPlayerInteraction;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* SpringArmComponent;

	UPROPERTY(EditAnywhere, Category = "Components")
	class UCameraComponent* CameraComponent;

	UPROPERTY(EditAnywhere, Category = "Components")
	class USkeletalMeshComponent* HelmetMesh;

	UPROPERTY(EditAnywhere, Category = "Components")
	class USkeletalMeshComponent* ChestMesh;

	UPROPERTY(EditAnywhere, Category = "Components")
	class USkeletalMeshComponent* LegsMesh;

	UPROPERTY(EditAnywhere, Category = "Components")
	class USkeletalMeshComponent* FeetMesh;

	UPROPERTY(EditAnywhere, Category = "Components")
	class USkeletalMeshComponent* VestMesh;

	UPROPERTY(EditAnywhere, Category = "Components")
	class USkeletalMeshComponent* HandsMesh;

	UPROPERTY(EditAnywhere, Category = "Components")
	class USkeletalMeshComponent* BackpackMesh;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Components")
	class USceneCaptureComponent2D* InventoryPlayerCapture;

protected:
	// Called when the game starts or when spawned	
	virtual void BeginPlay() override;
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
	virtual void Tick(float DeltaTime) override;
	virtual void Restart() override;
	virtual float TakeDamage(float Damage, struct FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;
	virtual void SetActorHiddenInGame(bool bNewHidden) override;

public:

	UFUNCTION(BlueprintCallable)
	void SetLootSource(class UInventoryComponent* NewLootSource);

	UFUNCTION(BlueprintPure, Category = "Looting")
	bool IsLooting() const;

protected:

	//Begin being looted by a player
	UFUNCTION()
	void BeginLootingPlayer(class ASurvivalCharacter* Character);

	UFUNCTION(Server, Reliable, WithValidation, BlueprintCallable)
	void ServerSetLootSource(class UInventoryComponent* NewLootSource);

	/**The inventory that we are currently looting from. */
	UPROPERTY(ReplicatedUsing = OnRep_LootSource, BlueprintReadOnly)
	UInventoryComponent* LootSource;

	UFUNCTION()
	void OnLootSourceOwnerDestroyed(AActor* DestroyedActor);

	UFUNCTION()
	void OnRep_LootSource();

public:

	UFUNCTION(BlueprintCallable, Category = "Looting")
	void LootItem(class UItem* ItemToGive);

	UFUNCTION(Server, Reliable, WithValidation)
	void ServerLootItem(class UItem* ItemToLoot);



	//How often in seconds to check for an interactable object. Set this to zero if you want to check every tick.
	UPROPERTY(EditDefaultsOnly, Category = "Interaction")
	float InteractionCheckFrequency;

	//How far we'll trace when we check if the player is looking at an interactable object
	UPROPERTY(EditDefaultsOnly, Category = "Interaction")
	float InteractionCheckDistance;

	void PerformInteractionCheck();

	void CouldntFindInteractable();
	void FoundNewInteractable(UInteractionComponent* Interactable);

	void BeginInteract();
	void EndInteract();

	UFUNCTION(Server, Reliable, WithValidation)
	void ServerBeginInteract();

	UFUNCTION(Server, Reliable, WithValidation)
	void ServerEndInteract();

	void Interact();

	//Information about the current state of the players interaction
	UPROPERTY()
	FInteractionData InteractionData;

	//Helper function to make grabbing interactable faster
	FORCEINLINE class UInteractionComponent* GetInteractable() const { return InteractionData.ViewedInteractionComponent; }

	FTimerHandle TimerHandle_Interact;

public:

	//True if we're interacting with an item that has an interaction time (for example a lamp that takes 2 seconds to turn on)
	bool IsInteracting() const;

	//Get the time till we interact with the current interactable
	float GetRemainingInteractTime() const;


	//Items

/**[Server] Use an item from our inventory.*/
	UFUNCTION(BlueprintCallable, Category = "Items")
	void UseItem(class UItem* Item);

	UFUNCTION(Server, Reliable, WithValidation)
	void ServerUseItem(class UItem* Item);

	/**[Server] Drop an item*/
	UFUNCTION(BlueprintCallable, Category = "Items")
	void DropItem(class UItem* Item, const int32 Quantity);

	UFUNCTION(Server, Reliable, WithValidation)
	void ServerDropItem(class UItem* Item, const int32 Quantity);

	UFUNCTION()
	void ItemAddedToInventory(class UItem* Item);

	UFUNCTION()
	void ItemRemovedFromInventory(class UItem* Item);

	/**needed this because the pickups use a blueprint base class*/
	UPROPERTY(EditDefaultsOnly, Category = "Item")
	TSubclassOf<class APickup> PickupClass;

public:

	/**Handle equipping an equippable item*/
	bool EquipItem(class UEquippableItem* Item);
	bool UnEquipItem(class UEquippableItem* Item);

	/**These should never be called directly - UGearItem and UWeaponItem call these on top of EquipItem*/
	void EquipGear(class UGearItem* Gear);
	void UnEquipGear(const EEquippableSlot Slot);
	void EquipWeapon(class UWeaponItem* WeaponItem);
	void UnEquipWeapon();

	/**Called to update the inventory*/
	UPROPERTY(BlueprintAssignable, Category = "Items")
	FOnEquippedItemsChanged OnEquippedItemsChanged;

	/**Return the skeletal mesh component for a given slot*/
	class USkeletalMeshComponent* GetSlotSkeletalMeshComponent(const EEquippableSlot Slot);

	UFUNCTION(BlueprintPure)
	FORCEINLINE TMap<EEquippableSlot, UEquippableItem*> GetEquippedItems() const { return EquippedItems; }

	UFUNCTION(BlueprintCallable, Category = "Weapons")
	FORCEINLINE class AWeapon* GetEquippedWeapon() const { return EquippedWeapon; }

protected:

	UFUNCTION(Server, Reliable)
	void ServerUseThrowable();

	UFUNCTION(NetMulticast, Unreliable)
	void MulticastPlayThrowableTossFX(class UAnimMontage* MontageToPlay);

	class UThrowableItem* GetThrowable() const;
	void UseThrowable();
	void SpawnThrowable();
	bool CanUseThrowable() const;

	//Allows for efficient access of equipped items
	UPROPERTY(VisibleAnywhere, Category = "Items")
	TMap<EEquippableSlot, UEquippableItem*> EquippedItems;

	UPROPERTY(ReplicatedUsing = OnRep_Health, BlueprintReadOnly, Category = "Health")
	float Health;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Health")
	float MaxHealth;

public:

	//Modify the players health by either a negative or positive amount. Return the amount of health actually removed
	float ModifyHealth(const float Delta);

	UFUNCTION()
	void OnRep_Health(float OldHealth);

	UFUNCTION(BlueprintImplementableEvent)
	void OnHealthModified(const float HealthDelta);

protected:

	UPROPERTY(VisibleAnywhere, ReplicatedUsing = OnRep_EquippedWeapon)
	class AWeapon* EquippedWeapon;

	UFUNCTION()
	void OnRep_EquippedWeapon();

	void StartFire();
	void StopFire();

	void BeginMeleeAttack();

	UFUNCTION(Server, Reliable)
	void ServerProcessMeleeHit(const FHitResult& MeleeHit);

	UFUNCTION(NetMulticast, Unreliable)
	void MulticastPlayMeleeFX();

	UPROPERTY()
	float LastMeleeAttackTime;

	UPROPERTY(EditDefaultsOnly, Category = Melee)
	float MeleeAttackDistance;

	UPROPERTY(EditDefaultsOnly, Category = Melee)
	float MeleeAttackDamage;

	UPROPERTY(EditDefaultsOnly, Category = Melee)
	class UAnimMontage* MeleeAttackMontage;

	//Called when killed by the player, or killed by something else like the environment
	void Suicide(struct FDamageEvent const& DamageEvent, const AActor* DamageCauser);
	void KilledByPlayer(struct FDamageEvent const& DamageEvent, class ASurvivalCharacter* Character, const AActor* DamageCauser);

	UPROPERTY(ReplicatedUsing = OnRep_Killer)
	class ASurvivalCharacter* Killer;

	UFUNCTION()
	void OnRep_Killer();

	UFUNCTION(BlueprintImplementableEvent)
	void OnDeath();

public:

	UPROPERTY(EditDefaultsOnly, Category = Movement)
	float SprintSpeed;

	UPROPERTY()
	float WalkSpeed;

	UPROPERTY(Replicated, BlueprintReadOnly, Category = Movement)
	bool bSprinting;

	bool CanSprint() const;

	//[local] start and stop sprinting functions
	void StartSprinting();
	void StopSprinting();

	/**[server + local] set sprinting*/
	void SetSprinting(const bool bNewSprinting);

	UFUNCTION(Server, Reliable, WithValidation)
	void ServerSetSprinting(const bool bNewSprinting);

	void StartCrouching();
	void StopCrouching();

	void MoveForward(float Val);
	void MoveRight(float Val);

	void LookUp(float Val);
	void Turn(float Val);

protected:

	bool CanAim() const;

	void StartAiming();
	void StopAiming();

	//Aiming
	void SetAiming(const bool bNewAiming);

	UFUNCTION(Server, Reliable)
	void ServerSetAiming(const bool bNewAiming);

	UPROPERTY(Transient, Replicated)
	bool bIsAiming;

public:	

	void StartReload();

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UFUNCTION(BlueprintPure)
	FORCEINLINE bool IsAlive() const { return Killer == nullptr; };

	UFUNCTION(BlueprintPure, Category = "Weapons")
	FORCEINLINE bool IsAiming() const { return bIsAiming; }

};
