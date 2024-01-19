// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Mover.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class CRYPTRAIDER_API UMover : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UMover();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	void SetMoveOffset(FVector UpdateMoveOffset);
	void SetMoveTime(float UpdateMoveTime);

	UFUNCTION(BlueprintCallable)
	void SetShouldMove(bool UpdateShouldMove);

private:
	UPROPERTY(EditAnywhere, Category = "Mover|Movement")
	bool ShouldMove = false;
	UPROPERTY(EditAnywhere, Category = "Mover|Movement")
	bool ShouldReturn = false;
	UPROPERTY(EditAnywhere, Category = "Mover|Movement")
	bool ShouldOscillate = false;
	UPROPERTY(EditAnywhere, Category = "Mover|Movement")
	FVector MoveOffset = FVector(0, 0, 0);
	UPROPERTY(EditAnywhere, Category = "Mover|Movement")
	float MoveTime = 4;

	UPROPERTY(EditAnywhere, Category = "Mover|Rotation")
	bool ShouldRotate = false;
	UPROPERTY(EditAnywhere, Category = "Mover|Rotation")
	FRotator RotateOffset = FRotator(0, 0, 0);
	UPROPERTY(EditAnywhere, Category = "Mover|Rotation")
	float RotateTime = 4;

	UPROPERTY(VisibleAnywhere, Category = "Modifiable")
	FVector NewMoveOffset;
	UPROPERTY(VisibleAnywhere, Category = "Modifiable")
	float NewMoveTime;

	FVector SpawnLocation;
	FVector StartLocation;
	FVector TargetLocation;
	FRotator StartRotation;
	FRotator TargetRotation;

	void Move(float DeltaTime);
	void MoveBack(float DeltaTime);
	void Rotate(float DeltaTime);
	void RotateBack(float DeltaTime);
	void Oscillate(float DeltaTime);
};


/*
	Implement MoveBack()
	Change Move so that it no longer recalculates the target location every frame
	Change Move so that it sets ShouldMove to false when it reaches the target location
		--Apply this to all functions
	Reimplement Oscillate so that it calls upon Move and Return rather than having its own code
	Add and implement a RotateBack() function
	Consider Changing Oscillate so that it can be called upon the move and rotate functions

	Implement tick to be more efficient
*/