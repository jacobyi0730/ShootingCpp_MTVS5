// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "EnemyActor.generated.h"

UCLASS()
class SHOOTINGCPP_MTVS5_API AEnemyActor : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AEnemyActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
	// 충돌체
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MyVar")
	TObjectPtr<class UBoxComponent> BoxComp;
	
	// 외형
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MyVar")
	TObjectPtr<UStaticMeshComponent> MeshComp;

	
	// 태어날 때 방향을 정하고싶다.
	// 30%의 확률로 주인공 방향으로,
	// 나머지 확률로 앞 방향으로 
	
	// 살아가면서 그 방향으로 계속 이동하고싶다.
	
	// 방향, 크기
	FVector Direction;
	float Speed = 500.f;
	
	
};
