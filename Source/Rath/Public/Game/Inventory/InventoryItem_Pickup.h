// Copyright © 2022 Rath. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "InventoryItem_Pickup.generated.h"

UCLASS()
class RATH_API AInventoryItem_Pickup : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AInventoryItem_Pickup();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* ItemStaticMeshComponent;

	UPROPERTY(EditAnywhere)
	class USceneComponent* Root;
	
	UPROPERTY(EditAnywhere)
	class USphereComponent* SphereComponent;

	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category = "Property")
	class UItemBase* ItemType;

	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category = "Property")
	int Count = 0;

	UFUNCTION(BlueprintCallable,Category = "Collision")
	virtual void OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
// #if WITH_EDITOR
// 	virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;
// #endif
	
};
