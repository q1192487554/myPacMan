// Fill out your copyright notice in the Description page of Project Settings.

#include "Public/Collectables.h"
#include "UObject/ConstructorHelpers.h"

// Sets default values
ACollectables::ACollectables()
{
 	//todo 设置该actor在每一帧调用Tick()。如果您不需要它，您可以关闭它来提高性能。
	PrimaryActorTick.bCanEverTick = false;		

	//todo 开启碰撞功能
	SetActorEnableCollision(true);

	//todo 创建网格组件
	CollectableMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("CollectableMesh"));

	//todo 创建碰撞体组件
	BaseCollisionComponent = CreateDefaultSubobject<USphereComponent>(TEXT("BaseCollisionComponent"));

	//todo 把网格组件和碰撞体绑定到一起
	CollectableMesh->AttachTo(BaseCollisionComponent);

	//todo 获取球体
	static ConstructorHelpers::FObjectFinder<UStaticMesh> Sphere(TEXT("StaticMesh'/Engine/BasicShapes/Sphere.Sphere'"));
	//todo 判断是否找到球体
	if (Sphere.Succeeded()) {
		//todo 指定给Mesh
		CollectableMesh->SetStaticMesh(Sphere.Object);
	}

	//todo 设置大小
	CollectableMesh->SetWorldScale3D(FVector(0.3, 0.3, 0.3));

	//todo 设置碰撞体直径
	BaseCollisionComponent->SetSphereRadius(16);
}

// Called when the game starts or when spawned
void ACollectables::BeginPlay()
{

	Super::BeginPlay();
	
}

// Called every frame
void ACollectables::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

