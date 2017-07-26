#pragma once

#include <d3d11.h>

#include "Vertex.h"



class Mesh
{
public:
	Mesh(Vertex* vertArray, int numVerts, unsigned int* indexArray, int numIndices, ID3D11Device* device);
	Mesh(ID3D11Device* device, char* objFile);
	~Mesh(void);

	ID3D11Buffer* GetVertexBuffer() { return vb; }
	ID3D11Buffer* GetIndexBuffer() { return ib; }
	int GetIndexCount() { return numIndices; }

	

private:
	ID3D11Buffer* vb;
	ID3D11Buffer* ib;
	int numIndices;

	
	void CreateBuffers(Vertex* vertArray, int numVerts, unsigned int* indexArray, int numIndices, ID3D11Device* device);
};

