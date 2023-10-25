// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/TimelineComponent.h"
#include "Math/Axis.h"
#include "Door.generated.h"

UCLASS()
class MDN_TEST_FINAL_API ADoor : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ADoor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	//Door parameters
	UPROPERTY(EditAnywhere)
	bool bIsRotatingDoor{true};
	UPROPERTY(EditAnywhere)
	FRotator RotationAngle;
	UPROPERTY(EditAnywhere)
	float Speed{1.f};
	
	bool bIsOpen{};
	FRotator InitialRotation;
	float DotWithInteractor;
	UPROPERTY(EditAnywhere)
	TEnumAsByte<EAxis::Type> ForwardAxis {EAxis::X}; 
	FVector ForwardVector;

	//Geometry components
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	class UStaticMeshComponent* Door;

	// Timeline to move/rotate the door
	FTimeline TLRotate;
	UPROPERTY(EditAnywhere)
	UCurveFloat* CurveTLFloat;

	UFUNCTION()
	void RotateUpdate(float InterpolationValue);

	static FVector GetForwardVFromDefinedAxis(TEnumAsByte<EAxis::Type> const ForwardAxis);

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable, Category="Interaction Functions")
	void OnInteract(AActor* Interactor);
};
