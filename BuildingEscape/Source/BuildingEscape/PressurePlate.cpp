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
}

void UPressurePlate::UpdatePressurePlateTrigger()
{
	if (PlateTrigger)
	{
		float TotalMassOnPlate = 0.f;
		TArray<AActor*> OverlappingActors;
		PlateTrigger->GetOverlappingActors(OverlappingActors);

		for (const auto* Actor : OverlappingActors)
		{
			if (Actor)
			{
				TotalMassOnPlate += Actor->FindComponentByClass<UPrimitiveComponent>()->GetMass();
			}
		}

		MassCurrentlyOnPlate = TotalMassOnPlate;
	}
}

bool UPressurePlate::IsPlateTriggered()
{
	return (MassCurrentlyOnPlate >= TriggerMass);
}

