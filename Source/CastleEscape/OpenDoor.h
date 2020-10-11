// Copyright Henrique Rachti Assumpção 2020

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Engine/TriggerVolume.h"
#include "OpenDoor.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class CASTLEESCAPE_API UOpenDoor : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UOpenDoor();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	
	
private:
	void OpenDoor(float DeltaTime);
	void CloseDoor(float DeltaTime);
	void MoveDoor(float DeltaTime, float TargetYaw, float Speed);
	
	float ClosedYaw;
	float CurrentYaw;

	UPROPERTY(EditAnywhere)
	float OpenedYaw;

	float LastTimeDoorOpened = 0.f;
	
	UPROPERTY(EditAnywhere)
	float DoorCloseDelay = .8f;

	UPROPERTY(EditAnywhere)
	float OpenDoorSpeed = 1.f;

	UPROPERTY(EditAnywhere)
	float CloseDoorSpeed = 2.0f;


	UPROPERTY(EditAnywhere)
		ATriggerVolume* PressurePlate;

	UPROPERTY(EditAnywhere)
		AActor* ActorThatOpens;


};
