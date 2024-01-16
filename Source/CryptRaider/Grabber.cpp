// Fill out your copyright notice in the Description page of Project Settings.


#include "Grabber.h"

#include "Engine/World.h"
#include "DrawDebugHelpers.h"
#include "PhysicsEngine/PhysicsHandleComponent.h"

// Sets default values for this component's properties
UGrabber::UGrabber()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UGrabber::BeginPlay()
{
	Super::BeginPlay();

	//finds the physics handle component on the owner of this component
	UPhysicsHandleComponent* PhysicsHandle = GetOwner()->FindComponentByClass<UPhysicsHandleComponent>();
	//if the physics handle is found
	if(PhysicsHandle!= nullptr)
	{
		// PhysicsHandle->GetName();
		UE_LOG(LogTemp, Display, TEXT("Physics handle found: %s"), *PhysicsHandle->GetName());
	}else
	{
		UE_LOG(LogTemp, Error, TEXT("Physics handle not found on %s"), *GetOwner()->GetName());
	}
}


// Called every frame
void UGrabber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	
	//Finds the physics handle component on the owner of this component
	UPhysicsHandleComponent* PhysicsHandle = GetOwner()->FindComponentByClass<UPhysicsHandleComponent>();
	if(PhysicsHandle != nullptr)
		return;

	//calculates the how far the object should be from the player
	FVector TargetLocation = GetComponentLocation() + GetForwardVector() * HoldDistance;
	//updates grabed items location and rotation
	PhysicsHandle->SetTargetLocationAndRotation(TargetLocation, GetComponentRotation());
}

void UGrabber::Grab()
{
	//Finds the physics handle component on the owner of this component
	UPhysicsHandleComponent* PhysicsHandle = GetOwner()->FindComponentByClass<UPhysicsHandleComponent>();
	if(PhysicsHandle != nullptr)
		return;

	//creates the start and end of the line trace
	FVector LineStart = GetComponentLocation();
	FVector LineEnd = LineStart + GetForwardVector() * Reach;

	//creates the shape for the line trace
	FCollisionShape Sphere = FCollisionShape::MakeSphere(Radius);

	//creates the line trace stores the result in HitResult and returns true if it hits something
	FHitResult HitResult;
	bool HasHit = GetWorld()->SweepSingleByChannel(
		HitResult,
		LineStart, LineEnd,
		FQuat::Identity,
		ECC_GameTraceChannel2,
		Sphere
	);

	//if the line trace hits something, Grabs the component at the impact point
	if(HasHit)
	{
		PhysicsHandle->GrabComponentAtLocationWithRotation(
			HitResult.GetComponent(),
			NAME_None,
			HitResult.ImpactPoint,
			GetComponentRotation()
		);
	}
}

void UGrabber::Release()
{
	UE_LOG(LogTemp, Display, TEXT("Grab released"));
}	