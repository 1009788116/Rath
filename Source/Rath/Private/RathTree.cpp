// Fill out your copyright notice in the Description page of Project Settings.


#include "RathTree.h"

#include "Components/StaticMeshComponent.h"

// Sets default values
ARathTree::ARathTree()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
}

// Called when the game starts or when spawned
void ARathTree::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ARathTree::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

