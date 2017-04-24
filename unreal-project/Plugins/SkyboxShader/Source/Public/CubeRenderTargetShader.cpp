#include "Private/SkyboxShaderPrivatePCH.h"
#include "RHIStaticStates.h"
#include "CubeRenderTargetShader.h"

TGlobalResource<FTextureVertexDeclaration> GTextureVertexDeclaration;

FCubeRenderTargetShader::FCubeRenderTargetShader(ERHIFeatureLevel::Type ShaderFeatureLevel)
{
	FeatureLevel = ShaderFeatureLevel;

	//Sync Uniforms
	ConstantParameters = FPixelShaderConstantParameters();
	VariableParameters = FPixelShaderVariableParameters();

	ConstantParameters.SimulationSpeed = 1.0;

	bMustRegenerateSRV = false;
	bIsPixelShaderExecuting = false;
	bIsUnloading = false;
}

//Render onto every face of the cube texture target.
void FCubeRenderTargetShader::RunShader(UTextureRenderTargetCube* RenderTarget, float time)
{
	//Skip this execution round if we are already executing
	if (bIsUnloading || bIsPixelShaderExecuting)
	{
		return;
	}

	bIsPixelShaderExecuting = true;

	//Sync Variables
	CurRenderTarget = RenderTarget;
	VariableParameters.TotalTimeElapsedSeconds = time;

	//Camera Matrix Struct
	struct FLocal
	{
		/** Creates a transformation for a cubemap face, following the D3D cubemap layout. */
		static FMatrix CalcCubeFaceTransform(ECubeFace Face)
		{
			static const FVector XAxis(1.f, 0.f, 0.f);
			static const FVector YAxis(0.f, 1.f, 0.f);
			static const FVector ZAxis(0.f, 0.f, 1.f);

			// vectors we will need for our basis
			FVector vUp(YAxis);
			FVector vDir;
			switch (Face)
			{
			case CubeFace_PosX:
				vDir = XAxis;
				break;
			case CubeFace_NegX:
				vDir = -XAxis;
				break;
			case CubeFace_PosY:
				//Reversed PosY and -Y...
				vUp = ZAxis;
				vDir = -YAxis;
				break;
			case CubeFace_NegY:
				vUp = -ZAxis;
				vDir = YAxis;
				break;
			case CubeFace_PosZ:
				vDir = ZAxis;
				break;
			case CubeFace_NegZ:
				vDir = -ZAxis;
				break;
			}
			// derive right vector
			FVector vRight(vUp ^ vDir);
			// create matrix from the 3 axes
			return FBasisVectorMatrix(vRight, vUp, vDir, FVector::ZeroVector);
		}
	};

	for (int32 faceidx = 0; faceidx < (int32)ECubeFace::CubeFace_MAX; faceidx++)
	{
		const ECubeFace TargetFace = (ECubeFace)faceidx;
		const FMatrix ViewRotationMatrix = FLocal::CalcCubeFaceTransform(TargetFace);

		ENQUEUE_UNIQUE_RENDER_COMMAND_THREEPARAMETER(
			FPixelShaderRunner,
			FCubeRenderTargetShader*, PixelShader, this,
			ECubeFace, TargetFace, TargetFace,
			FMatrix, ViewRotationMatrix, ViewRotationMatrix,
			{
				PixelShader->RunShaderInternal(FResolveParams(FResolveRect(), TargetFace), ViewRotationMatrix);
			});
	}
}

void FCubeRenderTargetShader::RunShaderInternal(const FResolveParams& ResolveParams, const FMatrix mat)
{
	//Set Uniforms
	VariableParameters.ViewMatrix = mat;

	check(IsInRenderingThread());
	FRHICommandListImmediate& RHICmdList = GRHICommandList.GetImmediateCommandList();

	auto& RenderTarget = CurRenderTarget->GetRenderTargetResource()->GetRenderTargetTexture();
	FPooledRenderTargetDesc Desc(FPooledRenderTargetDesc::Create2DDesc(
		FIntPoint(CurRenderTarget->GetSurfaceWidth(), CurRenderTarget->GetSurfaceHeight()),
		RenderTarget.GetReference()->GetFormat(),
		FClearValueBinding::None,
		TexCreate_None,
		TexCreate_RenderTargetable,
		false));

	SetRenderTarget(RHICmdList, RenderTarget, NULL);
	RHICmdList.SetBlendState(TStaticBlendState<>::GetRHI());
	RHICmdList.SetRasterizerState(TStaticRasterizerState<>::GetRHI());
	RHICmdList.SetDepthStencilState(TStaticDepthStencilState<false, CF_Always>::GetRHI());

	static FGlobalBoundShaderState BoundShaderState;
	TShaderMapRef<FVertexShaderExample> VertexShader(GetGlobalShaderMap(FeatureLevel));
	TShaderMapRef<FShaderDeclaration> PixelShader(GetGlobalShaderMap(FeatureLevel));

	SetGlobalBoundShaderState(RHICmdList, FeatureLevel, BoundShaderState, GTextureVertexDeclaration.VertexDeclarationRHI, *VertexShader, *PixelShader);

	PixelShader->SetUniformBuffers(RHICmdList, ConstantParameters, VariableParameters);

	// Draw a fullscreen quad that we can run our pixel shader on
	FTextureVertex Vertices[4];
	Vertices[0].Position = FVector4(-1.0f, 1.0f, 0, 1.0f);
	Vertices[1].Position = FVector4(1.0f, 1.0f, 0, 1.0f);
	Vertices[2].Position = FVector4(-1.0f, -1.0f, 0, 1.0f);
	Vertices[3].Position = FVector4(1.0f, -1.0f, 0, 1.0f);
	Vertices[0].UV = FVector2D(0, 0);
	Vertices[1].UV = FVector2D(1, 0);
	Vertices[2].UV = FVector2D(0, 1);
	Vertices[3].UV = FVector2D(1, 1);

	DrawPrimitiveUP(RHICmdList, PT_TriangleStrip, 2, Vertices, sizeof(Vertices[0]));

	//Copy onto the RenderTargetCube
	RHICmdList.CopyToResolveTarget(CurRenderTarget->GetRenderTargetResource()->GetRenderTargetTexture(), CurRenderTarget->GetRenderTargetResource()->TextureRHI, false, ResolveParams);

	bIsPixelShaderExecuting = false;
}
