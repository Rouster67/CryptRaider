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

private:
	UPROPERTY(EditAnywhere, Category = "Mover|Movement")
	bool ShouldMove = false;
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
	void Oscillate(float DeltaTime);
	void Rotate(float DeltaTime);
};
