#pragma once
#include<DirectXMath.h>
#include"Mesh.h"

using namespace DirectX;

class GameEntity
{
public:
	GameEntity(Mesh* mesh);
	~GameEntity();

	void UpdateWorldMatrix();

	void Move(float x, float y, float z);

	Mesh* GetMesh() { return mesh; }
	XMFLOAT4X4* GetWorldMatrix() { return &worldMatrix; }

private:
	XMFLOAT4X4 worldMatrix;
	XMFLOAT3 scale;
	XMFLOAT3 rotation;
	XMFLOAT3 position;

	Mesh* mesh;
};

