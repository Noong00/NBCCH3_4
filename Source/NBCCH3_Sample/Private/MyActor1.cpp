// Fill out your copyright notice in the Description page of Project Settings.


#include "MyActor1.h"

#include "Math/TransformCalculus3D.h"

// Sets default values
AMyActor1::AMyActor1()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	//SceneComponent 생성 및 루트컴포넌트로 설정
	SceneRoot = CreateDefaultSubobject<USceneComponent>(TEXT("SceneRoot"));
	SetRootComponent(SceneRoot);
	
	//StaticMeshComponent 생성 및 SceneComponent 하위컴포넌트로 설정
	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	StaticMesh->SetupAttachment(SceneRoot);
	
	//tick함수 활성화
	PrimaryActorTick.bCanEverTick = true;
	RotationSpeed = 0.0f;
	IsMaxScale = true;
	MaxScale = 0.0f;
}

// Called when the game starts or when spawned
void AMyActor1::BeginPlay()
{
	Super::BeginPlay();
	UE_LOG(LogTemp, Warning, TEXT("BeginPlay 호출됨"));
}

// Called every frame
void AMyActor1::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//회전하기
	if (!FMath::IsNearlyZero(RotationSpeed))
	{
		AddActorLocalRotation(FRotator(0.0f, RotationSpeed*DeltaTime, 0.0f));
	}
	//크기가 커졌다 작아졌다
	FVector CurrentScale = GetActorScale3D();
	
	if (IsMaxScale)
	{
		SetActorScale3D(CurrentScale + FVector(0.001, 0.001, 0.001));
		if (CurrentScale.X >= MaxScale)
		{
			IsMaxScale = false;
		}
	}
	else
	{
		SetActorScale3D(CurrentScale - FVector(0.001, 0.001, 0.001));
		if (CurrentScale.X <= 0.5f)
		{
			IsMaxScale = true;
		}
	}
}

// SetActorLocation(FVector NewLocation) : 액터 위치 이동
// SetActorRotation(FRotator NewRotation) : 액터 회전
// SetActorScale3D(FVector NewScale) : 액터 스케일 변경
// GetActorLocation(),GetActorRotation(),GetActorScale3D() : 현재 Transform 정보 가져오기
// SetActorTransform(FTransform NewTransform) : 위치·회전·스케일을 한 번에 설정