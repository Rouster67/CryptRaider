// Fill out your copyright notice in the Description page of Project Settings.


#include "KeyTrigger.h"

// Sets default values for this component's properties
UKeyTrigger::UKeyTrigger()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

// Called when the game starts
void UKeyTrigger::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void UKeyTrigger::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
    Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

    if(GetAcceptableActor() != nullptr)
    {
        UE_LOG(LogTemp, Display, TEXT("KeyTrigger: Key accepted!"));
    }else
    {
        UE_LOG(LogTemp, Display, TEXT("KeyTrigger: No key accepted!"));
    }
}

void UKeyTrigger::SetMover(UMover* NewMover)
{
    Mover = NewMover;
}

AActor* UKeyTrigger::GetAcceptableActor() const
{
    // Get all overlapping actors and store them in an array
    TArray<AActor*> OverlappingActors;
    GetOverlappingActors(OverlappingActors);

    // Iterate through the array and return the first actor that has keyname as a tag
    for(AActor* Actor : OverlappingActors)
    {
        if(Actor->ActorHasTag(KeyName))
        {
            return Actor;
        }
    }

    // If no actor has keyname as a tag, return nullptr
    return nullptr;
}