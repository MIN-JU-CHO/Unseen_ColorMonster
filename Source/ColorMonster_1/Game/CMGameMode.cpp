// Fill out your copyright notice in the Description page of Project Settings.


#include "Game/CMGameMode.h"

ACMGameMode::ACMGameMode()
{
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassRef(TEXT("/Game/Blueprint/BP_CMPlayer.BP_CMPlayer_C"));
	if (PlayerPawnClassRef.Class)
	{
		DefaultPawnClass = PlayerPawnClassRef.Class;
	}
	static ConstructorHelpers::FClassFinder<APlayerController> PlayerControllerClassRef(TEXT("/Script/ColorMonster_1.CMPlayerController"));
	if (PlayerControllerClassRef.Class)
	{
		PlayerControllerClass = PlayerControllerClassRef.Class;
	}
}
