//--------------------------------------------------------------------------------------
// File: BasicHLSL.fx
//
// The effect file for the BasicHLSL sample.  
// 
// Copyright (c) Microsoft Corporation. All rights reserved.
//--------------------------------------------------------------------------------------

float4x4 wvpMatrix;
float4 color;

struct VS_INPUT
{
    float4 Position : POSITION;
};

//--------------------------------------------------------------------------------------
// Vertex shader output structure
//--------------------------------------------------------------------------------------
struct VS_OUTPUT
{
    float4 Position   : POSITION;   // vertex position 
    float4 color      : COLOR;
};


//--------------------------------------------------------------------------------------
// This shader computes standard transform and lighting
//--------------------------------------------------------------------------------------
VS_OUTPUT SetColor( VS_INPUT input )
{
    VS_OUTPUT Output;
    Output.Position = mul(input.Position,wvpMatrix);
    Output.color = color;    
    return Output;    
}

