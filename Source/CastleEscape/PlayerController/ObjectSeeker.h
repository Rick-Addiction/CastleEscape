// Copyright Henrique Rachti Assumpção 2020

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "ObjectHandler/ObjectHandler.h"

#include "ObjectSeeker.generated.h"


class UObjectHandler;
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class CASTLEESCAPE_API UObjectSeeker : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UObjectSeeker();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:

	UPROPERTY(EditAnywhere)
	float Reach = 135.f;
	
	UPROPERTY(EditAnywhere)
	float LineThickness = 5.f;

	UPROPERTY()
	UObjectHandler* ObjectHandler = nullptr;

	UPROPERTY()
	AActor* LastFocusedObject = nullptr;

	void Seek();
	void RestartSeeking();
	
	
	void SetupInputComponent();
	void SearchForFocusedObjectToOutline();
};

