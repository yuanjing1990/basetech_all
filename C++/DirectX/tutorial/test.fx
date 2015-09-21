float4 g_MAC;
float4 g_MDC;
int g_nNL;
float3 g_LD[3];
float4 g_LDf[3];
float4 g_LA;
texture g_MT;
float g_fT;
float4x4 g_mW;
float4x4 g_mWVP;
sampler MTS = 
sampler_state
{
	Texture = <g_MT>;
	MipFilter = LINEAR;
	MinFilter = LINEAR;
	MagFilter = LINEAR;
};
struct VS_OUTPUT
{
	float4 Position:POSITION;
	float2 TextureUV:TEXCOORD0;
	float4 Diffuse:COLOR0;
};
VS_OUTPUT RenderSceneVS(float4 vPos:POSITION,
	float3 vNormal:NORMAL,
	float2 vTexCoord0:TEXCOORD0,
	uniform int nNumLights,
	uniform bool bTexture,
	uniform bool bAnimate)
{
	VS_OUTPUT Output;
	float3 vNWS;
	float4 vAP = vPos;
	if(bAnimate)
		vAP+=float4(vNormal,0)*(sin(g_fT+5.5)+0.5)*5;
	Output.Position = mul(vAP,g_mWVP);
	vNWS = normalize(mul(vNormal,(float3x3)g_mW));
	float3 vTLD = float3(0,0,0);
	for(int i = 0; i < nNumLights; i++)
		vTLD+=g_LDf[i]*max(0,dot(vNWS,g_LD[i]));
	Output.Diffuse.rgb=g_MDC*vTLD+g_MAC*g_LA;
	Output.Diffuse.a = 1.0f;
	if(bTexture)
		Output.TextureUV=vTexCoord0;
	else
		Output.TextureUV=0;
	return Output;
}
struct PS_OUTPUT
{
	float4 RGBColor:COLOR0;
};
PS_OUTPUT RenderScenePS(VS_OUTPUT In,
	uniform bool bTexture)
{
	PS_OUTPUT Output;
	if(bTexture)
		Output.RGBColor = tex2D(MTS,In.TextureUV)*In.Diffuse;
	else
		Output.RGBColor = In.Diffuse;
	return Output;
}
technique RenderSceneWithTexture1Light
{
	pass P0
	{
		VertexShader = compile vs_1_1 RenderSceneVS(1,true,true);
		PixelShader = compile ps_1_1 RenderScenePS(true);
	}
}