// Copyright Connor Lucier 2018

#include "DoorOpener.h"

UDoorOpener::UDoorOpener()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UDoorOpener::BeginPlay()
{
	Super::BeginPlay();
}

void UDoorOpener::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (AllPlatesTriggered())
	{
		OpenDoor.Broadcast();
	}
	else
	{
		CloseDoor.Broadcast();
	}
}

bool UDoorOpener::AllPlatesTriggered() const
{
	for (auto Plate : PressurePlates)
	{
		if (Plate && !Plate->FindComponentByClass<UPressurePlate>()->IsPlateTriggered())
		{
			return false;
		}
	}

	return (PressurePlates.Num() > 0);
}

