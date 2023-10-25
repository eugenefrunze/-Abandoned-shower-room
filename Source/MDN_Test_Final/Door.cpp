// Fill out your copyright notice in the Description page of Project Settings.


#include "Door.h" 

// Sets default values
ADoor::ADoor()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Door = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Door Mesh Component"));
	Door->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void ADoor::BeginPlay()
{
	Super::BeginPlay();
	
	InitialRotation = GetActorRotation();
	ForwardVector = GetForwardVFromDefinedAxis(ForwardAxis);
	
	if (CurveTLFloat)
	{
		FOnTimelineFloat TLOpenProgress;
		TLOpenProgress.BindDynamic(this, &ADoor::RotateUpdate);
		TLRotate.AddInterpFloat(CurveTLFloat, TLOpenProgress);
	}
}

// Called every frame
void ADoor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	TLRotate.TickTimeline(DeltaTime);
}

void ADoor::OnInteract(AActor* Interactor)
{
	if(bIsRotatingDoor)
	{
		if(bIsOpen)
		{
			bIsOpen = false;
			TLRotate.Reverse();
		}
		else
		{
			bIsOpen = true;
			DotWithInteractor = FVector::DotProduct(Interactor->GetActorLocation() - GetActorLocation(), ForwardVector);
			TLRotate.Play();
		}
	}
	
	// GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, FString::Printf(TEXT("Dot is: %s"), bIsOpen ? TEXT("Open") : TEXT("Closed")));
}

void ADoor::RotateUpdate(float InterpolationValue)
{
	FRotator TargetRot;
	TargetRot = DotWithInteractor >= 0 ? InitialRotation - RotationAngle : InitialRotation + RotationAngle;
	Door->SetRelativeRotation(FRotator(0.f, TargetRot.Yaw * InterpolationValue, 0.f));
}

FVector ADoor::GetForwardVFromDefinedAxis(TEnumAsByte<EAxis::Type> const ForwardAxis)
{
	switch (ForwardAxis)
	{
	case 1:
		return FVector(1.f, 0.f, 0.f);
		break;
	case 2:
		return FVector(0.f, 1.f, 0.f);
		break;
	case 3:
		return FVector(0.f, 0.f, 1.f);
		break;
	default:
		return FVector(0.f, 0.f, 0.f);
		break;
	}
}
