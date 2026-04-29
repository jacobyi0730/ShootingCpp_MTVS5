// Fill out your copyright notice in the Description page of Project Settings.


#include "BulletActor.h"

#include "Components/BoxComponent.h"

// Sets default values
ABulletActor::ABulletActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	// 충돌체를 만들어서 루트로 하고 싶다.
	BoxComp = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxComp"));
	SetRootComponent(BoxComp);
	// 외형을 만들어서 루트에 붙이고 싶다.
	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComp"));
	MeshComp->SetupAttachment(RootComponent);

}

// Called when the game starts or when spawned
void ABulletActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABulletActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	// 앞방향으로 계속 이동하고싶다.
	// P = P0 + vt
	FVector p0 = GetActorLocation();
	FVector v = GetActorForwardVector() * Speed;
	SetActorLocation(p0 + v * DeltaTime);
	
}

