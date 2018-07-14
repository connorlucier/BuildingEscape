// Copyright Connor Lucier 2018
#include "Grabber.h"
#include "assert.h"
#include "Engine/World.h"
#include "Runtime/Engine/Classes/Components/PrimitiveComponent.h"

UGrabber::UGrabber()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UGrabber::BeginPlay()
{
	Super::BeginPlay();

	AttachPhysicsHandle();
	SetInputComponent();
}

void UGrabber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (PhysicsHandle->GrabbedComponent) {
		FVector PlayerViewLocation, LineTraceEnd;
		FRotator PlayerViewRotation;
		
		GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(PlayerViewLocation, PlayerViewRotation);
		LineTraceEnd = PlayerViewLocation + PlayerViewRotation.Vector() * Reach;
		PhysicsHandle->SetTargetLocation(LineTraceEnd);
	}
}

void UGrabber::Grab()
{	
	auto HitResult = GetFirstPhysicsBodyInReach();
	auto GrabActor = HitResult.GetActor();
	auto GrabComponent = HitResult.GetComponent();

	if (GrabActor)
	{
		PhysicsHandle->GrabComponentAtLocation(
			GrabComponent,
			NAME_None,
			GrabComponent->GetOwner()->GetActorLocation()
		);
	}
}

void UGrabber::Release()
{
	PhysicsHandle->ReleaseComponent();
}

void UGrabber::AttachPhysicsHandle()
{
	PhysicsHandle = GetOwner()->FindComponentByClass<UPhysicsHandleComponent>();
	assert(PhysicsHandle);
}

void UGrabber::SetInputComponent()
{
	Input = GetOwner()->FindComponentByClass<UInputComponent>();
	assert(Input);

	Input->BindAction("Grab", IE_Pressed, this, &UGrabber::Grab);
	Input->BindAction("Grab", IE_Released, this, &UGrabber::Release);
}

FHitResult UGrabber::GetFirstPhysicsBodyInReach()
{
	FVector PlayerViewLocation, LineTraceEnd;
	FRotator PlayerViewRotation;

	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(PlayerViewLocation, PlayerViewRotation);
	LineTraceEnd = PlayerViewLocation + PlayerViewRotation.Vector() * Reach;

	FHitResult Hit;
	GetWorld()->LineTraceSingleByObjectType(
		Hit,
		PlayerViewLocation,
		LineTraceEnd,
		FCollisionObjectQueryParams(ECollisionChannel::ECC_PhysicsBody),
		FCollisionQueryParams(FName(TEXT("")), false, GetOwner())
	);

	return Hit;
}
