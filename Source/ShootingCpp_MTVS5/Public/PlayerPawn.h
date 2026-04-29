// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "PlayerPawn.generated.h"

// 전방선언
class UBoxComponent;

UCLASS()
class SHOOTINGCPP_MTVS5_API APlayerPawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	APlayerPawn();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	
public:
	// 충돌체
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MyVar")
	TObjectPtr<class UBoxComponent> BoxComp;
	
	// 외형
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MyVar")
	TObjectPtr<UStaticMeshComponent> MeshComp;
	
	// 총구
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MyVar")
	TObjectPtr<class UArrowComponent> FirePointComp;
	
	
	// 입력
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MyVar")
	TObjectPtr<class UInputMappingContext> IMC_Player;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MyVar")
	TObjectPtr<class UInputAction> IA_PlayerMove;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MyVar")
	TObjectPtr<class UInputAction> IA_PlayerFire;
	
	UFUNCTION()
	void OnMyMove(const struct FInputActionValue& value);
	
	// 이동하고싶다. 필요요소 : 방향, 크기
	FVector Direction;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MyVar")
	float Speed = 500.f;
	
	// 마우스 왼쪽 버튼을 누르면 총알공장에서 총알을 생성해서 총구에 배치하고싶다.
	UFUNCTION()
	void OnMyFire(const struct FInputActionValue& value);
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MyVar")
	TSubclassOf<class ABulletActor> BulletFactory;
	
	void MakeBullet();
	
};
