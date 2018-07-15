// Copyright Connor Lucier 2018

#pragma once

#include "CoreMinimal.h"
#include "Runtime/Engine/Classes/Engine/TriggerVolume.h"
#include "PressurePlate.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BUILDINGESCAPE_API UPressurePlate : public UActorComponent
{
	GENERATED_BODY()

public:
	UPressurePlate();
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	void UpdatePressurePlateTrigger();
	bool IsPlateTriggered();

protected:
	virtual void BeginPlay() override;

private:
	UPROPERTY(EditAnywhere)
	float MassToTriggerPlate = 50.f;

	UPROPERTY(EditAnywhere)
	ATriggerVolume* PlateTrigger = nullptr;

	UPROPERTY(VisibleAnywhere)
	float MassCurrentlyOnPlate = 0.f;
};
