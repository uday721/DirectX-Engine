#include "Material.h"






Material::Material(SimplePixelShader ** ps, SimpleVertexShader ** vs)
{
	pixelShader = *ps;
	vertexShader = *vs;
}

Material::~Material()
{
}
