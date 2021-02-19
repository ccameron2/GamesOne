// Fill out your copyright notice in the Description page of Project Settings.
#include "CustomPlayerController.h"
#include "CustomMovementComponent.h"
#include "Blueprint/UserWidget.h"

void ACustomPlayerController::BeginPlay()
{
	Super::BeginPlay();
	MyPawn = Cast<APlayableCharacter>(GetPawn());

	TimesShot = 0;
	ShotsLeft = MaximumAmmo;
	if (MyPawn)
	{
		HUDWidget = CreateWidget(this, HUDClass);
		MinimapWidget = CreateWidget(this, MinimapClass);
		if (HUDWidget != nullptr)
		{
			HUDWidget->AddToViewport();
		}
		if (MinimapWidget != nullptr)
		{
			MinimapWidget->AddToViewport();
		}
	}
	
}

void ACustomPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	check(InputComponent);
	InputComponent->BindAxis("Move Forwards", this, &ACustomPlayerController::CallForward);
	InputComponent->BindAxis("Turn", this, &ACustomPlayerController::CallTurn);
	InputComponent->BindAction("Fire", EInputEvent::IE_Pressed, this, &ACustomPlayerController::CallFire);
	InputComponent->BindAxis("Strafe", this, &ACustomPlayerController::CallStrafe);
	InputComponent->BindAction("Jump", EInputEvent::IE_Pressed, this, &ACustomPlayerController::CallJump);
	InputComponent->BindAxis("Look Up", this, &ACustomPlayerController::CallLookUp);
	InputComponent->BindAction("Land Mine", EInputEvent::IE_Pressed, this, &ACustomPlayerController::CallLandMine);
	InputComponent->BindAction("DamagingActor", EInputEvent::IE_Pressed, this, &ACustomPlayerController::CallDamagingActor);

}

void ACustomPlayerController::CallForward(float Value)
{
	if (MyPawn)
	{
		MyPawn->MoveForward(Value);
	}
}

void ACustomPlayerController::CallTurn(float Value)
{
	if (MyPawn)
	{
		MyPawn->Turn(Value);
	}
}


void ACustomPlayerController::CallFire()
{
	if (TimesShot < MaximumAmmo)
	{
		if (MyPawn)
		{
			TimesShot++;
			ShotsLeft = MaximumAmmo - TimesShot;
			MyPawn->Fire();
		}
	}
	
}

void ACustomPlayerController::CallStrafe(float Value)
{
	if (MyPawn)
	{
		MyPawn->Strafe(Value);
	}
}

void ACustomPlayerController::CallJump()
{
	if (MyPawn)
	{
		MyPawn->Jump();
	}
}

void ACustomPlayerController::CallLookUp(float Value)
{
	if (MyPawn)
	{
		MyPawn->LookUp(Value);
	}
}

void ACustomPlayerController::CallLandMine()
{
	if (MyPawn)
	{
		MyPawn->LandMine();
	}

}

void ACustomPlayerController::CallDamagingActor()
{
	if (MyPawn)
	{
		MyPawn->DamagingActor();
	}

}



int ACustomPlayerController::GetShots()
{
	return ShotsLeft;
}

int ACustomPlayerController::GetHealth()
{
	if (MyPawn != nullptr)
	{
		return MyPawn->GetHealth();
	}
	else
	{
		return 0;
	}
}

int ACustomPlayerController::GetPoints()
{
	if (MyPawn != nullptr)
	{
		return MyPawn->GetPoints();
	}
	else
	{
		return 0;
	}
}

void ACustomPlayerController::ResetAmmoCount()
{
	
	TimesShot = 0;
	ShotsLeft = 30;
}
