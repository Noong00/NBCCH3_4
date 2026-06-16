// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MyActor2.generated.h"

UCLASS()
class NBCCH3_SAMPLE_API AMyActor2 : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMyActor2();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	//component
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="AMyActor1|Components")
	USceneComponent *SceneRoot;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="AMyActor2|Components")
	UStaticMeshComponent *StaticMesh;
	
	//멤버변수
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="AMyActor2|Properties")
	float LocationSpeed;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="AMyActor2|Properties")
	FVector LocationDirection;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="AMyActor2|Properties")
	bool IsMaxRange;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="AMyActor2|Properties")
	float MoveRange;
	
	FVector StartLocation;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
