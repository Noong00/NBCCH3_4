// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"

#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/SpringArmComponent.h"

#include "MyPawn.generated.h"

struct FInputActionValue; // Enhanced Input이 액션값 받을때 쓸 구조체

UCLASS()
class NBCCH3_SAMPLE_API AMyPawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AMyPawn();

protected:
	
	//component
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="MyPawn|Components")
	TObjectPtr<UCapsuleComponent> CapsuleComp;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="MyPawn|Components")
	TObjectPtr<USkeletalMeshComponent> SkeletalMeshComp;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="MyPawn|Components")
	TObjectPtr<USpringArmComponent> SpringArmComp;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="MyPawn|Components")
	TObjectPtr<UCameraComponent> CameraComp;
	
	//IA 처리할 함수
	UFUNCTION()
	void Move(const FInputActionValue& value);
	UFUNCTION()
	void Look(const FInputActionValue& value);
	
public:	
	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
