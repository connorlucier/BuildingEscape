// Copyright Connor Lucier 2018

#pragma once

#include "CoreMinimal.h"
#include "Runtime/Engine/Classes/Engine/TriggerVolume.h"
#include "DoorOpener.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BUILDINGESCAPE_API UDoorOpener : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UDoorOpener();
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

protected:
	virtual void BeginPlay() override;

private:
	UPROPERTY(EditAnywhere)
	float DoorOpenAngle = -90.f;

	UPROPERTY(EditAnywhere)
	TArray<AActor*> PressurePlates = TArray<AActor*>();
};
