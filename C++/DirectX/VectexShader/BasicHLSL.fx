//BasicHLSL.txt

float4x4 wvpMatrix;
float4 color;

struct VS_INPUT
{
	float4 position:POSITION;
};

struct VS_OUTPUT
{
	float4 position:POSITION;
	float4 color:COLOR;
};

VS_OUTPUT SetColor( VS_INPUT input )
{
	VS_OUTPUT output;
	output.position = mul(input.position,wvpMatrix);
	output.color = color;
	return output;
}