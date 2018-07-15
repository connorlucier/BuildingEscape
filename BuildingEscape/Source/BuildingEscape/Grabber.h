// Copyright Connor Lucier 2018

#pragma once

#include "CoreMinimal.h"
#include "assert.h"
#include "Components/InputComponent.h"
#include "Engine/World.h"
#include "PhysicsEngine/PhysicsHandleComponent.h"
#include "Runtime/Engine/Classes/Components/PrimitiveComponent.h"
#include "Grabber.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BUILDINGESCAPE_API UGrabber : public UActorComponent
{
	GENERATED_BODY()

public:
	UGrabber();
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	void Grab();
	void Release();
	void AttachPhysicsHandle();
	void SetInputComponent();
	
	FHitResult GetFirstPhysicsBodyInReach();

protected:
	virtual void BeginPlay() override;

private:
	UPhysicsHandleComponent* PhysicsHandle = nullptr;
	UInputComponent* Input = nullptr;
	float Reach = 150.f;
};
