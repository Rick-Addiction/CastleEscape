// Copyright Henrique Rachti Assumpção 2020

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Engine/TriggerVolume.h"
#include "UObject/Object.h"
#include "Components/AudioComponent.h"
#include "DoorMovement.generated.h"

UENUM(BlueprintType)
enum class EDoorStatus : uint8 {
	NONE UMETA(DisplayName = "NONE"),
	OPEN UMETA(DisplayName = "OPEN"),
	CLOSE UMETA(DisplayName = "CLOSE")
};


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class CASTLEESCAPE_API UDoorMovement : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UDoorMovement();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	void SetDoorMovement(EDoorStatus NewDoorStatus);
	
	
private:
	
	UPROPERTY(EditAnywhere)
	float OpenedYaw;

	UPROPERTY(EditAnywhere)
	float DoorCloseDelay = .8f;

	UPROPERTY(EditAnywhere)
	float OpenDoorSpeed = 1.f;

	UPROPERTY(EditAnywhere)
	float CloseDoorSpeed = 2.0f;

	UPROPERTY(EditAnywhere)
		USoundBase* OpenDoorSound = nullptr;
	UPROPERTY(EditAnywhere)
		USoundBase* CloseDoorSound = nullptr;

	UAudioComponent* OpenDoorAudioComponent = nullptr;

	UAudioComponent* CloseDoorAudioComponent = nullptr;



	EDoorStatus DoorStatus = EDoorStatus::NONE;
	EDoorStatus LastDoorStatus = EDoorStatus::CLOSE;

	bool DoorOpened = false;
	bool DoorClosed = true;
	float ClosedYaw;
	float CurrentYaw;

	void FindAudioComponent();
	void CloseDoor(float DeltaTime);
	void MoveDoor(float DeltaTime, float TargetYaw, float Speed);
	void OpenDoor(float DeltaTime);

	
};