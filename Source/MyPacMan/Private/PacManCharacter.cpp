// Fill out your copyright notice in the Description page of Project Settings.

#include "Public/PacManCharacter.h"
#include "Kismet/GameplayStatics.h"
#include "Public/Collectables.h"
#include "Components/CapsuleComponent.h"
#include "Public/EngineUtils.h"

// Sets default values
APacManCharacter::APacManCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void APacManCharacter::BeginPlay()
{
	Super::BeginPlay();

	//todo 角色生命值 
	Lives = 3;

	//todo 设置角色初始位置	
	StartPoint = GetActorLocation();
	//UE_LOG(LogTemp, Warning, TEXT("StartPoint: %s"), *StartPoint.ToString());

	//todo 获取 GameMode 然后赋值 
	GameMode =Cast<AMyPacManGameModeBase> (UGameplayStatics::GetGameMode(this));

	//todo 获取胶囊体  绑定碰撞函数
	GetCapsuleComponent()->OnComponentBeginOverlap.AddDynamic(this,&APacManCharacter::OnCollision);

	//todo 迭代器 在我们的世界场景中找到  一个总数就加一个
	for (TActorIterator<ACollectables> CollectableItr(GetWorld()); CollectableItr; ++CollectableItr) {
		CollectablesToEat++;
	}

	//todo 打印log
	//UE_LOG(LogTemp,Warning,TEXT("Total Collectable is %d"),CollectablesToEat);
}

// Called every frame
void APacManCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
}

// Called to bind functionality to input
void APacManCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	//todo 绑定 MoveXAxis MoveYAxis
	PlayerInputComponent->BindAxis("MoveX", this, &APacManCharacter::MoveXAxis);
	PlayerInputComponent->BindAxis("MoveY", this, &APacManCharacter::MoveYAxis);

	//todo 绑定事件
	PlayerInputComponent->BindAction("NewGame",IE_Pressed, this, &APacManCharacter::NewGame);
	PlayerInputComponent->BindAction("ReStart", IE_Pressed, this, &APacManCharacter::ReStart);
	PlayerInputComponent->BindAction("Pause", IE_Pressed, this, &APacManCharacter::Pause);
}

void APacManCharacter::MoveXAxis(float AxisValue)
{
	if (GameMode->GetCurrentState() == EGameState::EPlaying)
	{
		CurrentVelocity.X = AxisValue;
		AddMovementInput(CurrentVelocity);
	}
}

void APacManCharacter::MoveYAxis(float AxisValue)
{
	if (GameMode->GetCurrentState() == EGameState::EPlaying)
	{
		CurrentVelocity.Y = AxisValue;
		AddMovementInput(CurrentVelocity);
	}
}

//todo 重新开始
void APacManCharacter::ReStart()
{	
	//todo 获取世界 > 获取玩家控制器 > ConsoleCommand
	GetWorld()->GetFirstPlayerController()->ConsoleCommand(TEXT("RestartLevel"));
}

//todo 开始游戏
void APacManCharacter::NewGame()
{	
	//todo 暂停
	if (GameMode->GetCurrentState() == EGameState::EMenu) {
		GameMode->SetCurrentState(EGameState::EPlaying);
	}
}

//todo 暂停
void APacManCharacter::Pause()
{	
	//todo 判断是不是游戏中
	if (GameMode->GetCurrentState() == EGameState::EPlaying) {
		GameMode->SetCurrentState(EGameState::EPause);
	}
	//todo 暂停
	else if (GameMode->GetCurrentState() == EGameState::EPause) {
		GameMode->SetCurrentState(EGameState::EPlaying);
	}
}

//todo 玩家受伤
void APacManCharacter::Killed()
{	
	//todo 判断玩家是否死亡
	if (--Lives == 0) {
		//todo 游戏结束
		GameMode->SetCurrentState(EGameState::EGameOver);
	}
	else {
		//todo 玩家受伤回到初始位置
		SetActorLocation(StartPoint);
	}
}


//todo 碰撞事件
void APacManCharacter::OnCollision(UPrimitiveComponent * HitComp, AActor * OtherActor, UPrimitiveComponent * OtherComp, int OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	//todo 判断游戏是否在进行中华
	if (GameMode->GetCurrentState() == EGameState::EPlaying) {
		//todo 判断碰撞的是不是 ACollectables这个类
		if (OtherActor->IsA(ACollectables::StaticClass())) {
			//UE_LOG(LogTemp, Warning, TEXT("66666"));
			ACollectables* collectable= Cast<ACollectables>(OtherActor);

			if (collectable->bIsSuperCollectable) {
				GameMode->SetEnemyVulnerable();
			}

			OtherActor->Destroy();

			//todo 剩余豆子数量 ==0 就赢了
			if (--CollectablesToEat == 0) {
				GameMode->SetCurrentState(EGameState::EWin);
			}
			//UE_LOG(LogTemp, Warning, TEXT("Remain Collectable is %d"), CollectablesToEat);
		}
	}
}


