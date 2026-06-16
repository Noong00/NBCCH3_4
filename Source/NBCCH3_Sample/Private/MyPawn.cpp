// Fill out your copyright notice in the Description page of Project Settings.


#include "MyPawn.h"

#include "EnhancedInputComponent.h"
#include "MyPlayerController.h"

// Sets default values
AMyPawn::AMyPawn()
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//UCapsuleComponent 생성 및 루트컴포넌트로 설정
	CapsuleComp = CreateDefaultSubobject<UCapsuleComponent>(TEXT("CapsuleComp"));
	SetRootComponent(CapsuleComp);

	//USkeletalMeshComponent 생성 및 UCapsuleComponent 하위컴포넌트로 설정
	SkeletalMeshComp = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("SkeletalMeshComp"));
	SkeletalMeshComp->SetupAttachment(CapsuleComp);

	//USpringArmComponent 생성 및 UCapsuleComponent 하위컴포넌트로 설정
	SpringArmComp = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArmComp"));
	SpringArmComp->SetupAttachment(CapsuleComp);
	// 캐릭터와 카메라 사이의 거리 기본값 300으로 설정
	SpringArmComp->TargetArmLength = 300.0f;
	SpringArmComp->bUsePawnControlRotation = false;

	//UCameraComponent 생성 및 USpringArmComponent 하위컴포넌트로 설정
	CameraComp = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComp"));
	CameraComp->SetupAttachment(SpringArmComp, USpringArmComponent::SocketName);
	CameraComp->bUsePawnControlRotation = false;
	
}



// Called to bind functionality to input
void AMyPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if (UEnhancedInputComponent* EnhancedInput = Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{
		// IA를 가져오기 위해 현재 소유 중인 Controller를 ASpartaPlayerController로 캐스팅
		if (AMyPlayerController* PlayerController = Cast<AMyPlayerController>(GetController()))
		{
			if (PlayerController->MoveAction)
			{
				// IA_Move 액션 키를 "키를 누르고 있는 동안" Move() 호출
				EnhancedInput->BindAction(
					PlayerController->MoveAction,
					ETriggerEvent::Triggered,
					this,
					&AMyPawn::Move
				);
			}

			if (PlayerController->LookAction)
			{
				// IA_Look 액션 마우스가 "움직일 때" Look() 호출
				EnhancedInput->BindAction(
					PlayerController->LookAction,
					ETriggerEvent::Triggered,
					this,
					&AMyPawn::Look
				);
			}
		}
	}
}

void AMyPawn::Move(const FInputActionValue& value)
{
	// 컨트롤러가 있어야 방향 계산이 가능
	if (!Controller) return;

	// Value는 Axis2D로 설정된 IA_Move의 입력값 (WASD)을 담고 있음
	// 예) (X=1, Y=0) → 전진 / (X=-1, Y=0) → 후진 / (X=0, Y=1) → 오른쪽 / (X=0, Y=-1) → 왼쪽
	const FVector2D MoveInput = value.Get<FVector2D>();
	float DeltaTime = GetWorld()->GetDeltaSeconds();
	float MoveSpeed = 300.0f;
	FVector MoveVector = FVector::ForwardVector*MoveInput.X + FVector::RightVector*MoveInput.Y;
	//FVector DeltaLocation = GetActorForwardVector() * MoveInput.Y + GetActorRightVector() * MoveInput.X;
	
	AddActorLocalOffset(MoveVector * MoveSpeed * DeltaTime, true);
}

void AMyPawn::Look(const FInputActionValue& value)
{
	FVector2D LookInput = value.Get<FVector2D>();
	FRotator CurrentRotation = SpringArmComp->GetRelativeRotation();
	float Yaw = LookInput.X;
	float Pitch = -LookInput.Y; // 입력받은 y축 값
	
	float Sensitivity = 100.f; // 입력받는 값이 너무 작아 보정함
	float DeltaTime = GetWorld()->GetDeltaSeconds(); // 프레임에 따른 차이를 보정함
	float CorrectedValue = Sensitivity*DeltaTime;
	
	//AddActorLocalRotation(FRotator(0.f, Yaw, 0.f));
	//SpringArmComp->AddLocalRotation(FRotator(Pitch, 0.f, 0.f));
	
	AddActorLocalRotation(FRotator(0.f, Yaw * CorrectedValue, 0.f));
	
	float NewPitch = FMath::Clamp(CurrentRotation.Pitch + Pitch * CorrectedValue, -80.f, 80.f); //clamp는 카메라 뒤집힘 방지용

	SpringArmComp->SetRelativeRotation(FRotator(NewPitch, 0.f, 0.f));
	
}

