#include "Material.h"

Material::Material(SimplePixelShader ** ps, SimpleVertexShader ** vs)
{
	pixelShader = *ps;
	vertexShader = *vs;
}

Material::Material(SimpleVertexShader ** vs, SimplePixelShader ** ps, ID3D11Device ** device, ID3D11DeviceContext ** deviceContext, ID3D11SamplerState ** sampler, ID3D11ShaderResourceView ** texSRV, const wchar_t * texture)
{
	vertexShader = *vs;
	pixelShader = *ps;
	samplerState = *sampler;

	CreateWICTextureFromFile(*device, *deviceContext, texture, 0, texSRV);
	txtSource = *texSRV;
}



Material::~Material()
{
}

//using to set the shaders
void Material::UpdateShaderResource()
{
	pixelShader->SetShaderResourceView("diffuseTexture", txtSource);
	pixelShader->SetSamplerState("basicSampler", samplerState);
}
