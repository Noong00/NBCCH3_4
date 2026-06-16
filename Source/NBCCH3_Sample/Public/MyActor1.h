// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MyActor1.generated.h"

UCLASS()
class NBCCH3_SAMPLE_API AMyActor1 : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMyActor1();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	//component
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="AMyActor1|Components")
	USceneComponent *SceneRoot;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="AMyActor1|Components")
	UStaticMeshComponent *StaticMesh;
	
	//멤버변수
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="AMyActor1|Properties")
	float RotationSpeed;
	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="AMyActor1|Properties")
	bool IsMaxScale;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="AMyActor1|Properties")
	float MaxScale;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
	

};
