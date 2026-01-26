// Fill out your copyright notice in the Description page of Project Settings.


#include "ODGameMode.h"
#include "Core/ODPlayerController.h"

AODGameMode::AODGameMode()
{
	PlayerControllerClass = AODPlayerController::StaticClass();
}
