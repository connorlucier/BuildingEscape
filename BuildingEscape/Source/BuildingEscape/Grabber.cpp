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

	if (PhysicsHandle && PhysicsHandle->GrabbedComponent)
	{
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

	if (GrabActor && GrabComponent)
	{
		PhysicsHandle->GrabComponentAtLocationWithRotation(
			GrabComponent,
			NAME_None,
			GrabActor->GetActorLocation(),
			GrabActor->GetActorRotation()
		);
	}
}

void UGrabber::Release()
{
	if (PhysicsHandle)
	{
		PhysicsHandle->ReleaseComponent();
	}
}

void UGrabber::AttachPhysicsHandle()
{
	PhysicsHandle = GetOwner()->FindComponentByClass<UPhysicsHandleComponent>();

	if (!PhysicsHandle)
	{
		UE_LOG(LogCore, Error, TEXT("%s missing physics handle component."), *GetOwner()->GetName())
	}
}

void UGrabber::SetInputComponent()
{
	Input = GetOwner()->FindComponentByClass<UInputComponent>();

	if (Input)
	{
		Input->BindAction("Grab", IE_Pressed, this, &UGrabber::Grab);
		Input->BindAction("Grab", IE_Released, this, &UGrabber::Release);
	}
	else
	{
		UE_LOG(LogCore, Error, TEXT("%s missing physics handle component."), *GetOwner()->GetName())
	}
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
