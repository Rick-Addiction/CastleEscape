// Copyright Henrique Rachti Assumpção 2020


#include "Bell.h"
#include "Components/AudioComponent.h"

// Sets default values for this component's properties
UBell::UBell()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

// Called when the game starts
void UBell::BeginPlay()
{
	Super::BeginPlay();

	if(BellSound)
	{
		SettingBellAudioComponent();
	}
	else
	{
		UE_LOG(LogTemp,Error,TEXT("The beel %s doesn't have a SoundBase attached on it"),*GetOwner()->GetName());
	}
}

void UBell::SettingBellAudioComponent()
{
	BellAudioComponent = NewObject<UAudioComponent>(GetOwner());
	BellAudioComponent->SetSound(BellSound);	
}

// Called every frame
void UBell::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if(CurrentBellStats == EInteractableObjectStats::PLAY)
	{
		FRotator CurrentBellRotation = GetOwner()->GetActorRotation();
		if (CurrentBellRotation.Pitch < 45.f)
		{
			MoveBell(DeltaTime);
			MoveBellBeater(DeltaTime);
		}
		else
		{
			CurrentBellStats = EInteractableObjectStats::STOP;
			UPrimitiveComponent* BellPrimitiveComponent = GetOwner()->FindComponentByClass<UPrimitiveComponent>();
			BellPrimitiveComponent->SetEnableGravity(true);
		}
		
	}

}

void UBell::PlayBell()
{
	if(CurrentBellStats == EInteractableObjectStats::STOP)
	{		
		FTimerHandle handle;
		
		BellAudioComponent->Play();
		GetWorld()->GetTimerManager().SetTimer(handle, [this]() {
                BellAudioComponent->FadeOut(2,0);
             },1,0);
		
		//BellAudioComponent->Stop();
		FRotator CurrentBellRotation = GetOwner()->GetActorRotation();
		CurrentBellRotation.Pitch = 0;
		GetOwner()->SetActorRotation(CurrentBellRotation);

		CurrentBellStats = EInteractableObjectStats::PLAY;
		UPrimitiveComponent* BellPrimitiveComponent = GetOwner()->FindComponentByClass<UPrimitiveComponent>();
		BellPrimitiveComponent->SetEnableGravity(false);
		UE_LOG(LogTemp,Warning,TEXT("DISABLE GRAVITYY"));
	}	
}

void UBell::MoveBell(float DeltaTime)
{
	
	FRotator CurrentBellRotation = GetOwner()->GetActorRotation();		
			CurrentBellRotation.Pitch = FMath::FInterpTo(CurrentBellRotation.Pitch, 50.0 , DeltaTime, Speed);
			GetOwner()->SetActorRotation(CurrentBellRotation);

	if(BellClapper)
	{
		FRotator CurrentBellClapperRotation = BellClapper->GetActorRotation();		
		CurrentBellClapperRotation.Pitch = FMath::FInterpTo(CurrentBellClapperRotation.Pitch, 65.0 , DeltaTime, Speed);
		BellClapper->SetActorRotation(CurrentBellClapperRotation);
		
	}
}

void UBell::MoveBellBeater(float DeltaTime)
{
	if(BellBeater)
	{
		FRotator CurrentBellBeaterRotation = BellBeater->GetActorRotation();
		CurrentBellBeaterRotation.Pitch = FMath::FInterpTo(CurrentBellBeaterRotation.Pitch, 18.0 , DeltaTime, Speed);
		BellBeater->SetActorRotation(CurrentBellBeaterRotation);
	}
}
