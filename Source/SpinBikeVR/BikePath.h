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
	UPROPERTY(BlueprintReadWrite)
		USplineComponent* Path = nullptr;
public:
	UPROPERTY(EditAnywhere)
		int PointToStartFrom = 0;
	UPROPERTY(EditAnywhere)
		float CycleSpeed = 1000;
	UPROPERTY(EditAnywhere)
		TArray<float> TimeBetweenPoints;
	UPROPERTY(VisibleAnywhere)
		float TimeToTraverseSpline = 0;
	UFUNCTION()
		void Envelope(const float EnvelopeValue);
protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
		class UAudioCaptureComponent* MicCapture;
private:
	float TotalDistanceElapsed = 0;

	float EnvelopeSum = 0;
	float TimeElapsed = 0;
	
	UPROPERTY(EditAnywhere)
	float TimeBetweenIntervals = 1;
	UPROPERTY(EditAnywhere)
	float SpeedScalar = 1;

	float LastKnownSum = 0;
};
