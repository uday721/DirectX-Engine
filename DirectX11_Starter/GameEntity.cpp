#include "GameEntity.h"





GameEntity::GameEntity(Mesh * mesh)
{
	this->mesh = mesh;

	XMStoreFloat4x4(&worldMatrix, XMMatrixIdentity());
	position = XMFLOAT3(0, 0, 0);
	rotation = XMFLOAT3(0, 0, 0);
	scale = XMFLOAT3(1, 1, 1);
}

GameEntity::~GameEntity()
{
}

void GameEntity::UpdateWorldMatrix()
{
	XMMATRIX translation = XMMatrixTranslation(position.x, position.y, position.z);
	XMMATRIX rotateX = XMMatrixRotationX(rotation.x);
	XMMATRIX rotateY = XMMatrixRotationY(rotation.y);
	XMMATRIX rotateZ = XMMatrixRotationZ(rotation.z);
	XMMATRIX sc = XMMatrixScaling(scale.x, scale.y, scale.z);

	XMMATRIX total = sc * rotateZ * rotateY * rotateX * translation;
	XMStoreFloat4x4(&worldMatrix, XMMatrixTranspose(total));
}

void GameEntity::Move(float x, float y, float z)
{
	position.x = x;
	position.y = y;
	position.z = z;
}
