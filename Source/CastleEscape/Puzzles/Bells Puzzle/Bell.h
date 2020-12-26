// Copyright Henrique Rachti Assumpção 2020

#pragma once

#include "CoreMinimal.h"


#include "PlayerController/InteractableObject.h"
#include "Bell.generated.h"




UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class CASTLEESCAPE_API UBell : public UInteractableObject
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UBell();

	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Speed = 1.f;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	AActor* BellBeater = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	AActor* BellClapper = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	USoundBase* BellSound = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EInteractableObjectStats CurrentBellStats = EInteractableObjectStats::STOP;

	void PlayBell();

	protected:
	// Called when the game starts
	virtual void BeginPlay() override;


private:

	void SettingBellAudioComponent();
	void MoveBell(float DeltaTime);
	void MoveBellBeater(float DeltaTime);

	UPROPERTY()
	UAudioComponent* BellAudioComponent = nullptr;

	

	UPROPERTY()
	bool IsBellPlaying = false;

};
