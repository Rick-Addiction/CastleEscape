// Copyright Henrique Rachti Assumpção 2020

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "InteractableObject.generated.h"

UENUM(BlueprintType)
enum class EInteractableObjectAction : uint8 {
	NONE UMETA(DisplayName = "NONE"),
	PLAYING UMETA(DisplayName = "PLAYING"),
    STOPPING UMETA(DisplayName = "STOPPING")
};

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class CASTLEESCAPE_API UInteractableObject : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UInteractableObject();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	
	virtual void Play() { check(0 && "You must override this"); };
};
