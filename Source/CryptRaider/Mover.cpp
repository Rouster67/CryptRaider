// Fill out your copyright notice in the Description page of Project Settings.


#include "Mover.h"

#include "Math/UnrealMathUtility.h"

// Sets default values for this component's properties
UMover::UMover()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UMover::BeginPlay()
{
	Super::BeginPlay();

	//set the spawn location
	SpawnLocation = GetOwner()->GetActorLocation();

	//defaults the updatable values to the set values
	NewMoveOffset = MoveOffset;
	NewMoveTime = MoveTime;

	//set the start location and rotation
	StartLocation = GetOwner()->GetActorLocation();
	StartRotation = GetOwner()->GetActorRotation();
	
	//calculate the target location and rotation
	TargetLocation= StartLocation + MoveOffset;
	TargetRotation = StartRotation + FRotator(RotateOffset.Pitch, RotateOffset.Yaw, RotateOffset.Roll);
}


// Called every frame
void UMover::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if(ShouldMove)
		Move(DeltaTime);
	if(ShouldOscillate)
		Oscillate(DeltaTime);
	if(ShouldRotate)
		Rotate(DeltaTime);
}

void UMover::SetMoveOffset(FVector UpdateMoveOffset)
{
	MoveOffset = NewMoveOffset;
}

void UMover::SetMoveTime(float UpdateMoveTime)
{
	MoveTime = NewMoveTime;
}

void UMover::Move(float DeltaTime)
{
	//get the current location
	FVector CurrentLocation = GetOwner()->GetActorLocation();
	//calculate the speed
	float Speed = FVector::Distance(StartLocation, TargetLocation) / MoveTime;
	//interpolate the location
	FVector NewLocation = FMath::VInterpConstantTo(CurrentLocation, TargetLocation, DeltaTime, Speed);
	//set the new location
	GetOwner()->SetActorLocation(NewLocation);
}

void UMover::Oscillate(float DeltaTime)
{

	if(FVector::Dist(StartLocation, GetOwner()->GetActorLocation()) >= FVector::Dist(StartLocation, TargetLocation))
	{
		//Sets the location to the exact target location
		GetOwner()->SetActorLocation(TargetLocation);

		//Swaps the start and target locations
		FVector Temp = StartLocation;
		StartLocation = TargetLocation;
		TargetLocation = Temp;

		//Reverse the direction of the offset
		MoveOffset *= -1;

		//Recalculate the target location if needed
		if(StartLocation == SpawnLocation)
		{
			MoveTime = NewMoveTime;
			MoveOffset = NewMoveOffset;
			TargetLocation= StartLocation + MoveOffset;
		}
	}
}

void UMover::Rotate(float DeltaTime)
{
	//get the current rotation
	FRotator CurrentRotation = GetOwner()->GetActorRotation();
	//calculate the speed
	float Speed = 90 / RotateTime;
	//interpolate the rotation
	FRotator NewRotation = FMath::RInterpConstantTo(CurrentRotation, TargetRotation, DeltaTime, Speed);
	//set the new rotation
	GetOwner()->SetActorRotation(NewRotation);
}