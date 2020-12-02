// Fill out your copyright notice in the Description page of Project Settings.

#include "Public/AIEnemy.h"
#include "AI/Navigation/NavigationSystem.h"
#include "Public/TimerManager.h"
#include "Kismet/GameplayStatics.h"


void AAIEnemy::Possess(class APawn* InPawn) {
	Super::Possess(InPawn);
	Bot = Cast<AEnemy>(InPawn);
	HomeLocation = Bot->GetActorLocation();
	GameMode=Cast<AMyPacManGameModeBase>(UGameplayStatics::GetGameMode(this));
	//UE_LOG(LogTemp, Warning, TEXT("HelloPoint: %s"), *HomeLocation.ToString());
	SearchNewPoint();
}

void AAIEnemy::OnMoveCompleted(FAIRequestID RequestID, const FPathFollowingResult & Result)
{
	if (!Bot->bIsDead&&GameMode->GetCurrentState()!=EGameState::EPause) SearchNewPoint();
}


void AAIEnemy::SearchNewPoint()
{
	UNavigationSystem* NavMesh = UNavigationSystem::GetCurrent(this);
	if (NavMesh) {
		const float SearchRadius = 10000.0f;
		FNavLocation RandomPt;
		const bool bFound = NavMesh->GetRandomReachablePointInRadius(Bot->GetActorLocation(), SearchRadius, RandomPt);
		if (bFound) {

			MoveToLocation(RandomPt);
		}
	}
}

void AAIEnemy::GoHome()
{
	MoveToLocation(HomeLocation);
	GetWorldTimerManager().SetTimer(DeadTime, this, &AAIEnemy::ReArm, 5.0f, false);
}

void AAIEnemy::ReArm()
{
	GetWorldTimerManager().ClearTimer(DeadTime);
	Bot->ReArm();
}

void AAIEnemy::StopMove()
{
	MoveToLocation(Bot->GetActorLocation());
}
