#pragma once

#include "Private/ShaderDeclaration.h"
#include "Engine/TextureRenderTargetCube.h"
#include "SceneView.h"
#include "Engine/TextureRenderTarget.h"
#include "Runtime/Renderer/Private/RendererPrivate.h"
#include "UniformBuffer.h"
#include "ShaderParameters.h"
#include "ScreenRendering.h"
#include "SceneUtils.h"

/**
 * Renders a given FGlobalShader onto a UTextureRenderTargetCube.
 * The shader is encapsulated in the class, and the texture target is a param.
 * Fork from SceneCaptureRendering.h in UE4 Source
 * @NOTE - No mobile support. (Reflected HDR maps)
 */

class SKYBOXSHADER_API FCubeRenderTargetShader
{
public:
	FCubeRenderTargetShader(ERHIFeatureLevel::Type ShaderFeatureLevel);

	//Runs the shader on a given render target.
	void RunShader(UTextureRenderTargetCube* RenderTarget, float time);

private:
	//Boostraps the shader, binds uniform buffers,
	void RunShaderInternal(const FResolveParams& ResolveParams, const FMatrix mat);

	UTextureRenderTargetCube* CurRenderTarget;

	//@TODO Refactor
	bool bIsPixelShaderExecuting;
	bool bMustRegenerateSRV;
	bool bIsUnloading;

	FPixelShaderConstantParameters ConstantParameters;
	FPixelShaderVariableParameters VariableParameters;
	ERHIFeatureLevel::Type FeatureLevel;

	/** Main texture */
	FTexture2DRHIRef CurrentTexture;
};
