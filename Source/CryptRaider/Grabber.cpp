// Fill out your copyright notice in the Description page of Project Settings.


#include "Grabber.h"

#include "Engine/World.h"
#include "DrawDebugHelpers.h"

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

	//Sets the physics handle component and checks if the physics handle is valid
	if(!SetPhysicsHandle(GetPhysicsHandle()))
	{
		//logs error
		UE_LOG(LogTemp, Error, TEXT("Physics handle not found on %s"), *GetOwner()->GetName());
		//disables the component
		this->Deactivate();
		//stops component from ticking
		PrimaryComponentTick.bCanEverTick = false; // Disable ticking
		return;
	}
}


// Called every frame
void UGrabber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	
	//checks if the physics handle is valid and if the player is holding something
	if(PhysicsHandle && PhysicsHandle->GetGrabbedComponent() != nullptr)
	{
		//calculates how far the object should be from the player
		FVector TargetLocation = GetComponentLocation() + GetForwardVector() * HoldDistance;

		//updates grabed items location and rotation
		PhysicsHandle->SetTargetLocationAndRotation(TargetLocation, GetComponentRotation());
	}
}

void UGrabber::Grab()
{
	//checks if the physics handle is valid
	if(PhysicsHandle == nullptr)
		return;

	//fires a line trace and stores the result in HitResult
	FHitResult HitResult;
	if(GetGrabbableInReach(HitResult))
	{
		//grabs the component that was hit
		UPrimitiveComponent* HitComponent = HitResult.GetComponent();
		//kickstarts the physics on the grabbed component
		HitComponent->WakeAllRigidBodies();
		//adds the grabbed tag to the actor
		HitResult.GetActor()->Tags.Add("Grabbed");
		//grabs the component
		PhysicsHandle->GrabComponentAtLocationWithRotation(
			HitComponent,
			NAME_None,
			HitResult.ImpactPoint,
			GetComponentRotation()
		);
	}
}

void UGrabber::Release()
{
	//checks if the physics handle is valid and if the player is holding something
	if(PhysicsHandle && PhysicsHandle->GetGrabbedComponent() != nullptr)
	{
		//gets the PhysicsHandle's PrimitiveComponent
		UPrimitiveComponent* PrimitiveComponent = PhysicsHandle->GetGrabbedComponent();
		//removes the grabbed tag from the actor
		PrimitiveComponent->GetOwner()->Tags.Remove("Grabbed");
		//kickstarts the physics on the grabbed component
		PrimitiveComponent->WakeAllRigidBodies();
		//releases the component
		PhysicsHandle->ReleaseComponent();
	}
}	

UPhysicsHandleComponent* UGrabber::GetPhysicsHandle() const
{
	//finds the physics handle component on the owner of this component
	return GetOwner()->FindComponentByClass<UPhysicsHandleComponent>();
}

bool UGrabber::SetPhysicsHandle(UPhysicsHandleComponent* NewPhysicsHandle)
{
	if(NewPhysicsHandle != nullptr)
	{
		PhysicsHandle = NewPhysicsHandle;
		return true;
	} else
	{
		return false;
	}
}

bool UGrabber::GetGrabbableInReach(FHitResult& OutHitResult) const
{
	//creates the start and end of the line trace
	FVector LineStart = GetComponentLocation();
	FVector LineEnd = LineStart + GetForwardVector() * Reach;

	//creates the shape for the line trace
	FCollisionShape Sphere = FCollisionShape::MakeSphere(Radius);

	//creates the line trace stores the result in HitResult and returns true if it hits something
	return GetWorld()->SweepSingleByChannel(
		OutHitResult,
		LineStart, LineEnd,
		FQuat::Identity,
		ECC_GameTraceChannel2,
		Sphere
	);
}