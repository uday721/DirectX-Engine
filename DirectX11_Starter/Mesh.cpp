#include "Mesh.h"
#include <DirectXMath.h>
#include <vector>
#include <fstream>

using namespace DirectX;

Mesh::Mesh(Vertex* vertArray, int numVerts, unsigned int* indexArray, int numIndices, ID3D11Device* device)
{
	CreateBuffers(vertArray, numVerts, indexArray, numIndices, device);
}

Mesh::Mesh(ID3D11Device* device, char* objFile)
{
	// File input object
	std::ifstream obj(objFile);
	
	// Check for successful open
	if (!obj.is_open())
		return;

	// declaring variables used in .Obj load code
	std::vector<XMFLOAT3> positions;
	std::vector<XMFLOAT3> normals;
	std::vector<XMFLOAT2> uvs;
	std::vector<Vertex> verts;
	std::vector<UINT> indices;
	unsigned int vertCounter = 0;
	char chars[100];


	// Still good?
	while (obj.good())
	{
		// Get the line (100 characters should be more than enough)
		obj.getline(chars, 100);

		// Check the type of line
		if (chars[0] == 'v' && chars[1] == 'n')
		{
			// Read the 3 numbers directly into an XMFLOAT3
			XMFLOAT3 norm;
			sscanf_s(
				chars,
				"vn %f %f %f",
				&norm.x, &norm.y, &norm.z);

			// Add to the list of normals
			normals.push_back(norm);
		}
		else if (chars[0] == 'v' && chars[1] == 't')
		{
			// Read the 2 numbers directly into an XMFLOAT2
			XMFLOAT2 uv;
			sscanf_s(
				chars,
				"vt %f %f",
				&uv.x, &uv.y);

			// Add to the list of uv's
			uvs.push_back(uv);
		}
		else if (chars[0] == 'v')
		{
			// Read the 3 numbers directly into an XMFLOAT3
			XMFLOAT3 pos;
			sscanf_s(
				chars,
				"v %f %f %f",
				&pos.x, &pos.y, &pos.z);

			// Add to the positions
			positions.push_back(pos);
		}
		else if (chars[0] == 'f')
		{
			// Read the 9 face indices into an array
			unsigned int i[9];
			sscanf_s(
				chars,
				"f %d/%d/%d %d/%d/%d %d/%d/%d",
				&i[0], &i[1], &i[2],
				&i[3], &i[4], &i[5],
				&i[6], &i[7], &i[8]);

			// - Create the verts by looking up
			//    corresponding data from vectors
			// - OBJ File indices are 1-based, so
			//    they need to be adusted
			Vertex v1;
			v1.Position = positions[i[0] - 1];
			v1.UV = uvs[i[1] - 1];
			v1.Normal = normals[i[2] - 1];

			Vertex v2;
			v2.Position = positions[i[3] - 1];
			v2.UV = uvs[i[4] - 1];
			v2.Normal = normals[i[5] - 1];

			Vertex v3;
			v3.Position = positions[i[6] - 1];
			v3.UV = uvs[i[7] - 1];
			v3.Normal = normals[i[8] - 1];

			// Flip the UV's since they're probably "upside down"
			v1.UV.y = 1.0f - v1.UV.y;
			v2.UV.y = 1.0f - v2.UV.y;
			v3.UV.y = 1.0f - v3.UV.y;

			// Add the verts to the vector
			verts.push_back(v1);
			verts.push_back(v2);
			verts.push_back(v3);

			// Add three more indices
			indices.push_back(vertCounter++);
			indices.push_back(vertCounter++);
			indices.push_back(vertCounter++);
		}
	}

	// Close
	obj.close();

	// Create the buffers
	CreateBuffers(&verts[0], vertCounter, &indices[0], vertCounter, device);
	
}


Mesh::~Mesh(void)
{
	vb->Release(); vb = 0;
	ib->Release(); ib = 0;
}


void Mesh::CreateBuffers(Vertex* vertArray, int numVerts, unsigned int* indexArray, int numIndices, ID3D11Device* device)
{
	// Create the vertex buffer
	D3D11_BUFFER_DESC vbd;
    vbd.Usage					= D3D11_USAGE_IMMUTABLE;
    vbd.ByteWidth				= sizeof(Vertex) * numVerts; // Number of vertices
    vbd.BindFlags				= D3D11_BIND_VERTEX_BUFFER;
    vbd.CPUAccessFlags			= 0;
    vbd.MiscFlags				= 0;
	vbd.StructureByteStride		= 0;
    D3D11_SUBRESOURCE_DATA initialVertexData;
    initialVertexData.pSysMem	= vertArray;
    device->CreateBuffer(&vbd, &initialVertexData, &vb);

	// Create the index buffer
	D3D11_BUFFER_DESC ibd;
    ibd.Usage					= D3D11_USAGE_IMMUTABLE;
	ibd.ByteWidth				= sizeof(unsigned int) * numIndices; // Number of indices
    ibd.BindFlags				= D3D11_BIND_INDEX_BUFFER;
    ibd.CPUAccessFlags			= 0;
    ibd.MiscFlags				= 0;
	ibd.StructureByteStride		= 0;
    D3D11_SUBRESOURCE_DATA initialIndexData;
    initialIndexData.pSysMem	= indexArray;
    device->CreateBuffer(&ibd, &initialIndexData, &ib);

	// Save the indices
	this->numIndices = numIndices;
}