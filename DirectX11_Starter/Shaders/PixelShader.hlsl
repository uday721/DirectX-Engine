
Texture2D diffuseTexture	: register(t0);
SamplerState basicSampler	: register(s0);

struct DirectionalLight
{
	float4 AmbientColor;
	float4 DiffuseColor;
	float3 Direction;
};



cbuffer externalData : register(b0)
{
	DirectionalLight dirLight;
}

float4 CalculateDirectionalLight(float3 normal, DirectionalLight light)
{
	float4 output;
	float3 dirOfLight = normalize(-light.Direction);
	normal = normalize(normal);
	float NdotL = saturate(dot(normal, dirOfLight));
	output = light.DiffuseColor * NdotL + light.AmbientColor;
	
	return output;

}



struct VertexToPixel
{
	// Data type
	//  |
	//  |   Name          Semantic
	//  |    |                |
	//  v    v                v
	float4 position		: SV_POSITION;
	float3 normal		: NORMAL;
	float3 worldPos     : TEXCOORD0;
	float2 uv           : TEXCOORD1;
};

// --------------------------------------------------------
// The entry point (main method) for our pixel shader
// 
// - Input is the data coming down the pipeline (defined by the struct)
// - Output is a single color (float4)
// - Has a special semantic (SV_TARGET), which means 
//    "put the output of this into the current render target"
// - Named "main" because that's the default the shader compiler looks for
// --------------------------------------------------------
float4 main(VertexToPixel input) : SV_TARGET
{
	float4 output;
	//normalise the incoming data
	input.normal = normalize(input.normal);

	float4 surfaceColor = diffuseTexture.Sample(basicSampler, input.uv);
	output = CalculateDirectionalLight(input.normal, dirLight);
	return surfaceColor*output;

	
}