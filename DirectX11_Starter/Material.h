#pragma once
#include"SimpleShader.h"
//#include"DDSTextureLoader.h"
//#include"DirectXGameCore.h"
#include"WICTextureLoader.h"

using namespace DirectX;

class Material
{
public:
	Material(SimplePixelShader **ps, SimpleVertexShader **vs);
	Material(SimpleVertexShader** vs, SimplePixelShader** ps, ID3D11Device** device, ID3D11DeviceContext** deviceContext, ID3D11SamplerState** sampler, ID3D11ShaderResourceView** texSRV, const wchar_t* texture);
	SimpleVertexShader* GetVertexShader() { return vertexShader; }
	SimplePixelShader* GetPixelShader() { return pixelShader; }
	
	~Material();
	void UpdateShaderResource();
	
private:
	SimplePixelShader* pixelShader;
	SimpleVertexShader* vertexShader;
	ID3D11SamplerState* samplerState;
	ID3D11ShaderResourceView* txtSource;

};

