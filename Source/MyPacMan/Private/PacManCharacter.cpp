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
	Lives = 3;
	StartPoint = GetActorLocation();
	//UE_LOG(LogTemp, Warning, TEXT("StartPoint: %s"), *StartPoint.ToString());
	GameMode =Cast<AMyPacManGameModeBase> (UGameplayStatics::GetGameMode(this));
	GetCapsuleComponent()->OnComponentBeginOverlap.AddDynamic(this,&APacManCharacter::OnCollision);

	for (TActorIterator<ACollectables> CollectableItr(GetWorld()); CollectableItr; ++CollectableItr) {
		CollectablesToEat++;
	}
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

void APacManCharacter::ReStart()
{
	GetWorld()->GetFirstPlayerController()->ConsoleCommand(TEXT("RestartLevel"));
}

void APacManCharacter::NewGame()
{
	if (GameMode->GetCurrentState() == EGameState::EMenu) {
		GameMode->SetCurrentState(EGameState::EPlaying);
	}
}

void APacManCharacter::Pause()
{
	if (GameMode->GetCurrentState() == EGameState::EPlaying) {
		GameMode->SetCurrentState(EGameState::EPause);
	}
	else if (GameMode->GetCurrentState() == EGameState::EPause) {
		GameMode->SetCurrentState(EGameState::EPlaying);
	}
}

void APacManCharacter::Killed()
{
	if (--Lives == 0) {
		GameMode->SetCurrentState(EGameState::EGameOver);
	}
	else {
		SetActorLocation(StartPoint);
	}
}



void APacManCharacter::OnCollision(UPrimitiveComponent * HitComp, AActor * OtherActor, UPrimitiveComponent * OtherComp, int OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	if (GameMode->GetCurrentState() == EGameState::EPlaying) {
		if (OtherActor->IsA(ACollectables::StaticClass())) {
			//UE_LOG(LogTemp, Warning, TEXT("66666"));
			ACollectables* collectable= Cast<ACollectables>(OtherActor);

			if (collectable->bIsSuperCollectable) {
				GameMode->SetEnemyVulnerable();
			}

			OtherActor->Destroy();
			if (--CollectablesToEat == 0) {
				GameMode->SetCurrentState(EGameState::EWin);
			}
			//UE_LOG(LogTemp, Warning, TEXT("Remain Collectable is %d"), CollectablesToEat);
		}
	}
}


