#pragma once
#include"SimpleShader.h"
class Material
{
public:
	Material(SimplePixelShader **ps, SimpleVertexShader **vs);
	SimplePixelShader* GetPixelShader() { return pixelShader; }
	SimpleVertexShader* GetVertexShader() { return vertexShader; }
	~Material();

private:
	SimplePixelShader* pixelShader;
	SimpleVertexShader* vertexShader;
};

