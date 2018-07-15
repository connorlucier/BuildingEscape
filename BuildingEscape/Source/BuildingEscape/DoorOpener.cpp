// Copyright Connor Lucier 2018

#include "DoorOpener.h"
#include "PressurePlate.h"
#include "assert.h"

UDoorOpener::UDoorOpener()
{
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

void UDoorOpener::BeginPlay()
{
	Super::BeginPlay();
}

void UDoorOpener::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	bool bAllPlatesTriggered = true;
	for (auto Plate : PressurePlates)
	{
		assert(Plate);

		if (!Plate->FindComponentByClass<UPressurePlate>()->IsPlateTriggered())
		{
			bAllPlatesTriggered = false;
		}
	}

	if (bAllPlatesTriggered)
	{
		GetOwner()->SetActorRotation(FRotator(0.f, DoorOpenAngle, 0.f));
	}
}

