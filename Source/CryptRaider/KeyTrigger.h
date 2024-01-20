// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Mover.h"
#include "GameFramework/Actor.h"

#include "CoreMinimal.h"
#include "Components/BoxComponent.h"
#include "KeyTrigger.generated.h"

/**
 * 
 */
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class CRYPTRAIDER_API UKeyTrigger : public UBoxComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UKeyTrigger();
	
protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(BlueprintCallable)
		void SetMover(UMover* NewMover);


private:
	UPROPERTY(EditAnywhere, category = "KeyTrigger")
		FName KeyName = "SkeletonKey";
	UPROPERTY(EditAnywhere, category = "KeyTrigger")
		bool AttachSnap = false;
	UPROPERTY(EditAnywhere, category = "KeyTrigger")
		UMover* Mover;

	AActor* GetAcceptableActor() const;
};

/*
	add error logging if mover is null
*/