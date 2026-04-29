// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerPawn.h"

#include "BulletActor.h"
#include "Components/BoxComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputActionValue.h"
#include "Components/ArrowComponent.h"


// Sets default values
APlayerPawn::APlayerPawn()
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	// 충돌체를 생성해서 
	BoxComp = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxComp"));
	// 충돌체를 루트로 하고싶다.
	SetRootComponent(BoxComp);
	// 외형을 생성하고 싶다.
	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComp"));
	// 외형을 루트에 붙이고싶다.
	MeshComp->SetupAttachment(RootComponent);
	
	// 총구를 생성해서
	FirePointComp = CreateDefaultSubobject<UArrowComponent>(TEXT("FirePointComp"));
	// 루트에 붙이고싶다.
	FirePointComp->SetupAttachment(RootComponent);
	FirePointComp->SetRelativeLocationAndRotation(FVector(0, 0, 100.f), FRotator(90, 0, 0));
}

// Called when the game starts or when spawned
void APlayerPawn::BeginPlay()
{
	Super::BeginPlay();
	
	auto* pc = Cast<APlayerController>(Controller);
	if (pc)
	{
		auto* subsys = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(pc->GetLocalPlayer());
		if (subsys)
		{
			subsys->RemoveMappingContext(IMC_Player);
			subsys->AddMappingContext(IMC_Player, 0);
		}
	}
	
}

// Called every frame
void APlayerPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	// P = P0 + vt
	FVector p0 = GetActorLocation();
	//Direction.Normalize();
	FVector v = Direction.GetSafeNormal() * Speed;
	SetActorLocation(p0 + v * DeltaTime);
	Direction = FVector::ZeroVector;
}

// Called to bind functionality to input
void APlayerPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	
	auto* input = Cast<UEnhancedInputComponent>(PlayerInputComponent);
	if (input)
	{
		input->BindAction(IA_PlayerMove, ETriggerEvent::Triggered, this, &APlayerPawn::OnMyMove);
		
		input->BindAction(IA_PlayerFire, ETriggerEvent::Started, this, &APlayerPawn::OnMyFire);
	}
}

void APlayerPawn::OnMyMove(const FInputActionValue& value)
{
	FVector2D v = value.Get<FVector2D>();
	Direction.Y = v.Y;
	Direction.Z = v.X;
}

void APlayerPawn::OnMyFire(const struct FInputActionValue& value)
{
	MakeBullet();
}

void APlayerPawn::MakeBullet()
{
	FTransform t = FirePointComp->GetComponentTransform();
	GetWorld()->SpawnActor<ABulletActor>(BulletFactory, t);
}

