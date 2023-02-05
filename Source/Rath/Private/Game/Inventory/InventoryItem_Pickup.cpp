// Fill out your copyright notice in the Description page of Project Settings.
#include "Rath/Public/Game/Inventory/InventoryItem_Pickup.h"
#include "Components/SphereComponent.h"
#include "Components/StaticMeshComponent.h"

// Sets default values
AInventoryItem_Pickup::AInventoryItem_Pickup()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Root=CreateDefaultSubobject<USceneComponent>(TEXT("场景根组件"));
	SetRootComponent(Root);
	
	ItemStaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("物品网格体"));
	ItemStaticMeshComponent->SetupAttachment(RootComponent);
	
	SphereComponent = CreateDefaultSubobject<USphereComponent>(TEXT("监听触发器"));
	SphereComponent->SetupAttachment(RootComponent);
	SphereComponent->SetSphereRadius(100.0f);
	SphereComponent->SetGenerateOverlapEvents(true);
	SphereComponent->SetCollisionProfileName(TEXT("OverlapAll"));
	SphereComponent->OnComponentBeginOverlap.AddDynamic(this,&AInventoryItem_Pickup::OnOverlapBegin);
}

// Called when the game starts or when spawned
void AInventoryItem_Pickup::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AInventoryItem_Pickup::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AInventoryItem_Pickup::OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	UE_LOG(LogTemp, Warning, TEXT("Overlap Begin"));
}

// void AInventoryItem::PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent)
// {
// 	Super::PostEditChangeProperty(PropertyChangedEvent);
// 	if(PropertyChangedEvent.Property && PropertyChangedEvent.Property->GetName() == GET_MEMBER_NAME_CHECKED(AItem,Visibility).ToString())
// 	{
// 		//SphereComponent->SetVisibility(Visibility);
// 		FString msg=FString::Printf(TEXT("Visibility:%s"),&Visibility);
// 		UKismetSystemLibrary::PrintString(GetWorld(),msg);
// 	}
// }
