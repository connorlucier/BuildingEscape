// Copyright Connor Lucier 2018

#include "PressurePlate.h"

UPressurePlate::UPressurePlate()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UPressurePlate::BeginPlay()
{
	Super::BeginPlay();
}

void UPressurePlate::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	UpdatePressurePlateTrigger();

	if (IsPlateTriggered())
	{
		OffsetPlate.Broadcast();
	}
	else
	{
		RevertPlate.Broadcast();
	}
}

void UPressurePlate::UpdatePressurePlateTrigger()
{
	if (PlateTrigger)
	{
		float TotalMassOnPlate = 0.f;
		TArray<AActor*> ActorsInTriggerVolume;
		PlateTrigger->GetOverlappingActors(ActorsInTriggerVolume);

		for (const auto* Actor : ActorsInTriggerVolume)
		{
			if (Actor)
			{
				TotalMassOnPlate += Actor->FindComponentByClass<UPrimitiveComponent>()->GetMass();
			}
		}

		MassCurrentlyOnPlate = TotalMassOnPlate;
	}
}

bool UPressurePlate::IsPlateTriggered() const
{
	return (MassCurrentlyOnPlate >= TriggerMass);
}