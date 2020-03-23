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
	Path = CreateDefaultSubobject<USplineComponent>(TEXT("Path"));
	MicCapture = CreateDefaultSubobject<UAudioCaptureComponent>(TEXT("Mic"));
	MicCapture->bAutoActivate = true;
}
void ABikePath::Envelope(const float EnvelopeValue)
{
	EnvelopeSum += EnvelopeValue;
}
// Called when the game starts or when spawned
void ABikePath::BeginPlay()
{
	Super::BeginPlay();
	if(MicCapture != nullptr)
	MicCapture->OnAudioEnvelopeValue.AddDynamic(this, &ABikePath::Envelope);
	if (PointToStartFrom < Path->GetNumberOfSplinePoints())
		TotalDistanceElapsed = Path->GetDistanceAlongSplineAtSplinePoint(PointToStartFrom);
}

void ABikePath::OnConstruction(const FTransform & Transform)
{
	TimeBetweenPoints.SetNum(Path->GetNumberOfSplinePoints()-1);
	TimeToTraverseSpline = 0;
	for (int i = 0; i < TimeBetweenPoints.Num(); ++i)
	{
		FVector DifferenceOfPoints = Path->GetLocationAtSplinePoint(i, ESplineCoordinateSpace::World) - Path->GetLocationAtSplinePoint(i + 1, ESplineCoordinateSpace::World);
		float Distance = DifferenceOfPoints.Size();
		TimeBetweenPoints[i] = Distance / CycleSpeed;
		TimeToTraverseSpline += Distance / CycleSpeed;
	}
	TimeToTraverseSpline /= 60;
	for (float &a : TimeBetweenPoints)
		if (a <= 0.0) a = 1.;
}

// Called every frame
void ABikePath::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (TimeElapsed > TimeBetweenIntervals)
	{
		LastKnownSum = EnvelopeSum;
		EnvelopeSum = 0;
		TimeElapsed = 0;
		
	}
	TimeElapsed += DeltaTime;

	

	APawn* Player = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
	if (Player == nullptr)
	{
		return;
	}

	if (TotalDistanceElapsed < Path->GetSplineLength())
	{
		Player->SetActorTransform(Path->GetTransformAtDistanceAlongSpline(TotalDistanceElapsed, ESplineCoordinateSpace::World));
		TotalDistanceElapsed += LastKnownSum * SpeedScalar;
	}
}

