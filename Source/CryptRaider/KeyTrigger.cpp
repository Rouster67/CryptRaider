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

    //Checks if the actor is valid and if the mover is valid and if the actor is not grabbed
    AActor* Actor = GetAcceptableActor();
    if(Actor && Mover != nullptr)
    {   
        //Casts the actor to a primitive component and sets it to not simulate physics
        UPrimitiveComponent* Component = Cast<UPrimitiveComponent>(Actor->GetRootComponent());
        if(Component != nullptr)
            Component->SetSimulatePhysics(false);
        
        //Attaches the actor to the key trigger with the option to snap or not
        if(AttachSnap)
            Actor->AttachToComponent(this, FAttachmentTransformRules::SnapToTargetNotIncludingScale);
        else
            Actor->AttachToComponent(this, FAttachmentTransformRules::KeepWorldTransform);


        //Sets the mover to move
        Mover->SetShouldMove(true);
    }else
    {
        Mover->SetShouldMove(false);
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

    // Iterate through the array and return the first actor that is not grabbed and has keyname as a tag
    for(AActor* Actor : OverlappingActors)
    {
        if(Actor->ActorHasTag(KeyName) && !Actor->ActorHasTag("Grabbed"))
        {
            return Actor;
        }
    }

    // If no actor has keyname as a tag, return nullptr
    return nullptr;
}