// Copyright Connor Lucier 2018

#pragma once

#include "CoreMinimal.h"
#include "Engine/World.h"
#include "Runtime/Engine/Classes/Engine/TriggerVolume.h"
#include "PressurePlate.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FPlateRequest);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BUILDINGESCAPE_API UPressurePlate : public UActorComponent
{
	GENERATED_BODY()

public:
	UPressurePlate();
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	void UpdatePressurePlateTrigger();
	bool IsPlateTriggered() const;
	bool IsAnyPhysicsBodyOnPlate() const;

	UPROPERTY(BlueprintAssignable)
	FPlateRequest OffsetPlate;

	UPROPERTY(BlueprintAssignable)
	FPlateRequest RevertPlate;

protected:
	virtual void BeginPlay() override;

private:
	UPROPERTY(EditAnywhere)
	float TriggerMass = 50.f;

	UPROPERTY(EditAnywhere)
	ATriggerVolume* PlateTrigger = nullptr;

	UPROPERTY(VisibleAnywhere)
	int ActorsOnPlate = 0;

	UPROPERTY(VisibleAnywhere)
	float MassCurrentlyOnPlate = 0.f;
};
