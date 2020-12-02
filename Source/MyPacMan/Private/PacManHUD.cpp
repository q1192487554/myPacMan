// Fill out your copyright notice in the Description page of Project Settings.

#include "Public/PacManHUD.h"
#include "MyPacManGameModeBase.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/Canvas.h"
#include "Public/PacManCharacter.h"

void APacManHUD::DrawHUD()
{
	class AMyPacManGameModeBase* GameMode = Cast<AMyPacManGameModeBase>(UGameplayStatics::GetGameMode(this));
	switch (GameMode->GetCurrentState())
	{
	case EGameState::EMenu:
		DrawText(TEXT("Welcome To PacMan!\n\nN to start a new game \nP to pause the game"), FColor::White, (Canvas->SizeX / 2.0f) - 300.0f, (Canvas->SizeY / 2.0f) - 200.0f, HUDFont,3);
		break;

	case EGameState::EPlaying:
	{
		APacManCharacter * PacMan = Cast<APacManCharacter>(UGameplayStatics::GetPlayerPawn(this, 0));
		if (PacMan) {
		FString LiveString = TEXT("Lives:") + FString::FromInt(PacMan->Lives);
		DrawText(LiveString, FColor::Green, 50, 50, HUDFont,2);

		FString CollectablesToEatString = TEXT("CollectablesToEat:") + FString::FromInt(PacMan->CollectablesToEat);
		DrawText(CollectablesToEatString, FColor::Red, Canvas->SizeX - 350, 50, HUDFont,2);
		}
	}
	break;
	case EGameState::EPause:
		DrawText(TEXT("P To Continue"), FColor::White, (Canvas->SizeX / 2.0f) - 150.0f, (Canvas->SizeY / 2.0f) - 100.0f, HUDFont,3);
		break;
		case EGameState::EWin:
			DrawText(TEXT("You Win!\n\n R for another"), FColor::White, (Canvas->SizeX / 2.0f) - 150.0f, (Canvas->SizeY / 2.0f) - 100.0f, HUDFont,3);
			break;
		case EGameState::EGameOver:
			DrawText(TEXT("GameOver£¡\n\n R for another"), FColor::White, (Canvas->SizeX / 2.0f) - 150.0f, (Canvas->SizeY / 2.0f) - 100.0f, HUDFont,3);
			break;
		default:
			break;
	}
}
