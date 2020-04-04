// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/SplineComponent.h"

#include "BikePath.generated.h"


UCLASS()
class SPINBIKEVR_API ABikePath : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ABikePath();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void OnConstruction(const FTransform& Transform) override;
public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;



public:
	UPROPERTY(BlueprintReadWrite)	
	float LastKnownSum = 0;
};
