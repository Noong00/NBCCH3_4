// Fill out your copyright notice in the Description page of Project Settings.


#include "MyActor2.h"

// Sets default values
AMyActor2::AMyActor2()
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
	
	LocationSpeed = 0.0f; //floAT로 바꿔도됨
	LocationDirection = FVector(0.0f, 0.0f, 0.0f);
	IsMaxRange = true;
	MoveRange = 0.0f;
}

// Called when the game starts or when spawned
void AMyActor2::BeginPlay()
{
	Super::BeginPlay();
	StartLocation = GetActorLocation();
}

// Called every frame
void AMyActor2::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	FVector NormalizedFrameMovement = LocationDirection.GetSafeNormal()*LocationSpeed*DeltaTime; //프렘당 움직이는 거리
	FVector TargetDirection = LocationDirection.GetSafeNormal()*MoveRange; //보간해줄 최종
	
	//왔다갔다 이동하기
	if (IsMaxRange)
	{
		
		SetActorLocation(GetActorLocation()+NormalizedFrameMovement);
		
		if (FVector::Dist(StartLocation, GetActorLocation()) >= MoveRange)
		{
			SetActorLocation(StartLocation+TargetDirection);
			
			IsMaxRange = false;
		}
	}
	else
	{
		
		SetActorLocation(GetActorLocation()-NormalizedFrameMovement);
		
		if (FVector::Dist(StartLocation, GetActorLocation()) >= MoveRange)
		{
			SetActorLocation(StartLocation-TargetDirection);
			
			IsMaxRange = true;
		}
	}
	
	// 최종위치는 알수 잇음. 최종위치 도달 시 startLocation을 최종거리로 바꾼다 바꾸는 순간 반대쪽으로 이동할 좌표를 알수 있다. 
	// 반대쪽 도달하는 순간 startLocation을 다시 바꾼다.
	
	// else
	// {
	// 	UE_LOG(LogTemp, Warning, TEXT("else문 실행"))
	// 	SetActorLocation(GetActorLocation()-B);
	// 	//UE_LOG(LogTemp, Warning, TEXT("%s 2단계"), *(GetActorLocation()-B).ToString());
	// 	if (FVector::Dist(StartLocation, GetActorLocation()) <= 1.0f)
	// 	{
	// 		SetActorLocation(StartLocation);
	// 		UE_LOG(LogTemp, Warning, TEXT("%s 강제셋업"), *(StartLocation).ToString());
	// 		IsMaxRange = true;
	// 	}
	// }
	
}

