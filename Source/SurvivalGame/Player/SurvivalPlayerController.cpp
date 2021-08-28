//SurvivalGame Project - The Unreal C++ Survival Game Course - Copyright Reuben Ward 2020


#include "SurvivalPlayerController.h"
#include "SurvivalCharacter.h"
#include "Widgets/SurvivalHUD.h"
#include "Framework/SurvivalGameStateBase.h"
#include "Kismet/GameplayStatics.h"

#define LOCTEXT_NAMESPACE "SurvivalPlayerController"

ASurvivalPlayerController::ASurvivalPlayerController()
{
}

void ASurvivalPlayerController::ClientShowNotification_Implementation(const FText& Message)
{
	if (ASurvivalHUD* HUD = Cast<ASurvivalHUD>(GetHUD()))
	{
		HUD->ShowNotification(Message);
	}
}

void ASurvivalPlayerController::Died(class ASurvivalCharacter* Killer)
{
	if (ASurvivalGameStateBase* GS = Cast<ASurvivalGameStateBase>(UGameplayStatics::GetGameState(GetWorld())))
	{
		//Force the player to respawn 
		FTimerHandle DummyHandle;
		GetWorldTimerManager().SetTimer(DummyHandle, this, &ASurvivalPlayerController::Respawn, GS->RespawnTime, false);

		if (ASurvivalHUD* HUD = Cast<ASurvivalHUD>(GetHUD()))
		{
			HUD->ShowDeathWidget(Killer);
		}
	}
}

void ASurvivalPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	InputComponent->BindAxis("Turn", this, &ASurvivalPlayerController::Turn);
	InputComponent->BindAxis("LookUp", this, &ASurvivalPlayerController::LookUp);

	InputComponent->BindAction("OpenInventory", IE_Pressed, this, &ASurvivalPlayerController::OpenInventory);

	InputComponent->BindAction("Pause", IE_Pressed, this, &ASurvivalPlayerController::PauseGame);

	InputComponent->BindAction("OpenMap", IE_Pressed, this, &ASurvivalPlayerController::OpenMap);
	InputComponent->BindAction("OpenMap", IE_Released, this, &ASurvivalPlayerController::CloseMap);

	InputComponent->BindAction("Reload", IE_Pressed, this, &ASurvivalPlayerController::StartReload);


}

void ASurvivalPlayerController::BeginPlay()
{
	Super::BeginPlay();
}

void ASurvivalPlayerController::ClientShotHitConfirmed_Implementation()
{
	if (ASurvivalHUD* HUD = Cast<ASurvivalHUD>(GetHUD()))
	{
		HUD->ShowHitmarker();
	}
}

void ASurvivalPlayerController::Respawn()
{
	UnPossess();
	ChangeState(NAME_Inactive);

	if (Role < ROLE_Authority)
	{
		ServerRespawn();
	}
	else
	{
		ServerRestartPlayer();
	}
}

bool ASurvivalPlayerController::IsInventoryOpen() const
{
	if (ASurvivalHUD* HUD = Cast<ASurvivalHUD>(GetHUD()))
	{
		return HUD->IsInventoryOpen();
	}

	return false;
}

void ASurvivalPlayerController::ServerRespawn_Implementation()
{
	Respawn();
}

bool ASurvivalPlayerController::ServerRespawn_Validate()
{
	return true;
}

void ASurvivalPlayerController::OpenInventory()
{
	if (ASurvivalHUD* HUD = Cast<ASurvivalHUD>(GetHUD()))
	{
		HUD->OpenInventoryWidget();
	}
}

void ASurvivalPlayerController::OpenMap()
{
	if (ASurvivalHUD* HUD = Cast<ASurvivalHUD>(GetHUD()))
	{
		HUD->OpenMap();
	}
}

void ASurvivalPlayerController::CloseMap()
{
	if (ASurvivalHUD* HUD = Cast<ASurvivalHUD>(GetHUD()))
	{
		HUD->CloseMap();
	}
}

void ASurvivalPlayerController::PauseGame()
{
	if (ASurvivalHUD* HUD = Cast<ASurvivalHUD>(GetHUD()))
	{
		HUD->OpenPauseWidget();
	}
}

void ASurvivalPlayerController::ResumeGame()
{
	if (ASurvivalHUD* HUD = Cast<ASurvivalHUD>(GetHUD()))
	{
		HUD->ClosePauseWidget();
	}
}

void ASurvivalPlayerController::ApplyRecoil(const FVector2D& RecoilAmount, const float RecoilSpeed, const float RecoilResetSpeed)
{
	if (IsLocalPlayerController())
	{
		RecoilBumpAmount += RecoilAmount;
		RecoilResetAmount += -RecoilAmount;

		CurrentRecoilSpeed = RecoilSpeed;
		CurrentRecoilResetSpeed = RecoilResetSpeed;

		LastRecoilTime = GetWorld()->GetTimeSeconds();
	}
}

void ASurvivalPlayerController::Turn(float Rate)
{
	//If the player has moved their camera to compensate for recoil we need this to cancel out the recoil reset effect
	if (!FMath::IsNearlyZero(RecoilResetAmount.X, 0.01f))
	{
		if (RecoilResetAmount.X > 0.f && Rate > 0.f)
		{
			RecoilResetAmount.X = FMath::Max(0.f, RecoilResetAmount.X - Rate);
		}
		else if (RecoilResetAmount.X < 0.f && Rate < 0.f)
		{
			RecoilResetAmount.X = FMath::Min(0.f, RecoilResetAmount.X - Rate);
		}
	}

	//Apply the recoil over several frames
	if (!FMath::IsNearlyZero(RecoilBumpAmount.X, 0.1f))
	{
		FVector2D LastCurrentRecoil = RecoilBumpAmount;
		RecoilBumpAmount.X = FMath::FInterpTo(RecoilBumpAmount.X, 0.f, GetWorld()->DeltaTimeSeconds, CurrentRecoilSpeed);

		AddYawInput(LastCurrentRecoil.X - RecoilBumpAmount.X);
	}

	//Slowly reset back to center after recoil is processed
	FVector2D LastRecoilResetAmount = RecoilResetAmount;
	RecoilResetAmount.X = FMath::FInterpTo(RecoilResetAmount.X, 0.f, GetWorld()->DeltaTimeSeconds, CurrentRecoilResetSpeed);
	AddYawInput(LastRecoilResetAmount.X - RecoilResetAmount.X);

	AddYawInput(Rate);

}

void ASurvivalPlayerController::LookUp(float Rate)
{
	if (!FMath::IsNearlyZero(RecoilResetAmount.Y, 0.01f))
	{
		if (RecoilResetAmount.Y > 0.f && Rate > 0.f)
		{
			RecoilResetAmount.Y = FMath::Max(0.f, RecoilResetAmount.Y - Rate);
		}
		else if (RecoilResetAmount.Y < 0.f && Rate < 0.f)
		{
			RecoilResetAmount.Y = FMath::Min(0.f, RecoilResetAmount.Y - Rate);
		}
	}

	//Apply the recoil over several frames
	if (!FMath::IsNearlyZero(RecoilBumpAmount.Y, 0.01f))
	{
		FVector2D LastCurrentRecoil = RecoilBumpAmount;
		RecoilBumpAmount.Y = FMath::FInterpTo(RecoilBumpAmount.Y, 0.f, GetWorld()->DeltaTimeSeconds, CurrentRecoilSpeed);

		AddPitchInput(LastCurrentRecoil.Y - RecoilBumpAmount.Y);
	}

	//Slowly reset back to center after recoil is processed
	FVector2D LastRecoilResetAmount = RecoilResetAmount;
	RecoilResetAmount.Y = FMath::FInterpTo(RecoilResetAmount.Y, 0.f, GetWorld()->DeltaTimeSeconds, CurrentRecoilResetSpeed);
	AddPitchInput(LastRecoilResetAmount.Y - RecoilResetAmount.Y);

	AddPitchInput(Rate);
}

void ASurvivalPlayerController::StartReload()
{
	if (ASurvivalCharacter* SurvivalCharacter = Cast<ASurvivalCharacter>(GetPawn()))
	{
		if (SurvivalCharacter->IsAlive())
		{
			SurvivalCharacter->StartReload();
		}
		else // R key should respawn the player if dead
		{
			Respawn();
		}
	}
}

#undef LOCTEXT_NAMESPACE