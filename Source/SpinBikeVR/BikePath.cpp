// Fill out your copyright notice in the Description page of Project Settings.


#include "BikePath.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"
#include "Components/TextRenderComponent.h"
#include "AudioCaptureComponent.h"

// Sets default values
ABikePath::ABikePath()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ABikePath::BeginPlay()
{
	Super::BeginPlay();
}

void ABikePath::OnConstruction(const FTransform & Transform)
{
	
}

// Called every frame
void ABikePath::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

