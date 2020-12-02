// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "Public/Enemy.h"
#include "MyPacManGameModeBase.generated.h"

/**
 *
 */
//todo 游戏状态
enum class EGameState :short {
	EMenu,
	EPlaying,
	EPause,
	EWin,
	EGameOver
};

UCLASS()
class MYPACMAN_API AMyPacManGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

public:

	virtual void BeginPlay() override;

	//todo 获取游戏状态
	EGameState GetCurrentState() const;

	//todo 设置游戏状态
	void SetCurrentState(EGameState value);

	void SetEnemyVulnerable();

private:
	EGameState currentState;
	TArray<class AEnemy*> Enemys;
};

//todo 内敛函数
FORCEINLINE EGameState AMyPacManGameModeBase::GetCurrentState() const {
	return currentState;
};