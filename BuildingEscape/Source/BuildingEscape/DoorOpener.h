// Copyright Connor Lucier 2018

#pragma once

#include "CoreMinimal.h"
#include "Runtime/Engine/Classes/Engine/TriggerVolume.h"
#include "DoorOpener.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FDoorRequest);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BUILDINGESCAPE_API UDoorOpener : public UActorComponent
{
	GENERATED_BODY()

public:	
	UDoorOpener();
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	bool AllPlatesTriggered() const;

	UPROPERTY(BlueprintAssignable)
	FDoorRequest OpenDoor;

	UPROPERTY(BlueprintAssignable)
	FDoorRequest CloseDoor;

protected:
	virtual void BeginPlay() override;

private:
	UPROPERTY(EditAnywhere)
	TArray<AActor*> PressurePlates = TArray<AActor*>();
};
