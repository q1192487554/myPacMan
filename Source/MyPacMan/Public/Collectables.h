// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/SphereComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Collectables.generated.h"


UCLASS()
class MYPACMAN_API ACollectables : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACollectables();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	//todo 声明网格体组件
	UPROPERTY(VisibleAnywhere, Category = Collectable)
	UStaticMeshComponent* CollectableMesh;

	//todo 声明碰撞组件
	UPROPERTY(EditDefaultsOnly, Category = Collectable)
	USphereComponent* BaseCollisionComponent;
	
	//todo 添加一个属性
	UPROPERTY(EditAnywhere, Category = Collectable)
	bool bIsSuperCollectable;
};
