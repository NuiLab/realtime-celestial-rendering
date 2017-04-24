#pragma once

#include "GameFramework/Actor.h"
#include "CubeRenderTargetShader.h"
#include "SpaceSky.generated.h"

UCLASS()
class  CELESTIALDEMO_API ASpaceSky : public AActor
{
	GENERATED_BODY()

public:
	ASpaceSky(const class FObjectInitializer& ObjectInitializer);
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaSeconds) override;
	virtual void BeginDestroy() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = ShaderDemo)
		float SimulationSpeed;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = ShaderDemo)
		UTextureRenderTargetCube* RenderTargetCube;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = ShaderDemo)
		float TotalElapsedTime;

private:
	FCubeRenderTargetShader* SkyShader;

};