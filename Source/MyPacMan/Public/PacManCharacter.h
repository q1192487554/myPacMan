// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "MyPacManGameModeBase.h"
#include "PacManCharacter.generated.h"

UCLASS()
class MYPACMAN_API APacManCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	APacManCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	
	//todo 声明函数
	void MoveXAxis(float AxisValue);
	void MoveYAxis(float AxisValue);

	//todo 重启
	void ReStart();
	//todo 再来一局
	void NewGame();
	//todo 暂停
	void Pause();

	void Killed();

	//todo 需要是豆子的数量值
	int CollectablesToEat;

	//todo 当前生命值
	int Lives;

	//todo 碰撞函数
	UFUNCTION()
	void OnCollision(class UPrimitiveComponent* HitComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);

private:
	FVector CurrentVelocity;
	FVector StartPoint;			

	//todo GameMode变量
	AMyPacManGameModeBase* GameMode;		


};

