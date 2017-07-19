#pragma once
#include <DirectXMath.h>
#include "Vertex.h"
#include "DirectXGameCore.h"
#include <d3d11.h>

class Mesh
{
public:
	
	Mesh(Vertex* vertexobj, int noOfVertices, unsigned int* indices, int noOfIndices, ID3D11Device* devicePointer);
	ID3D11Buffer * GetVertexBuffer() { return vertexBuffer; }
	ID3D11Buffer * GetIndexBuffer() { return indexBuffer; }

	int indicesCount;
	
	~Mesh();

private:
	ID3D11Buffer* vertexBuffer;
	ID3D11Buffer* indexBuffer;
	
	
	
};

