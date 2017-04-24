// Copyright 2016 Florida International University School of Computing Sciences | All Rights Reserved
// Designed by Alain Galvan (Alain.xyz)

#include "celestialdemo.h"
#include "SpaceSky.h"
#include "Engine.h"

ASpaceSky::ASpaceSky(const class FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	PrimaryActorTick.bCanEverTick = true;
	SimulationSpeed = 1.0;
	TotalElapsedTime = 0;
}

void ASpaceSky::BeginPlay()
{
	Super::BeginPlay();
	SkyShader = new FCubeRenderTargetShader(GetWorld()->Scene->GetFeatureLevel());
	SkyShader->RunShader(RenderTargetCube, TotalElapsedTime);
}
void ASpaceSky::BeginDestroy()
{
	Super::BeginDestroy();

	if (NULL != SkyShader)
	{
		delete SkyShader;
	}
}

void ASpaceSky::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	TotalElapsedTime += DeltaSeconds;

	if (NULL != SkyShader)
		SkyShader->RunShader(RenderTargetCube, TotalElapsedTime);
}