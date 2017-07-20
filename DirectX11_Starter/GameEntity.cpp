#include "GameEntity.h"





GameEntity::GameEntity(Mesh * mesh, Material* material)
{
	this->mesh = mesh;

	XMStoreFloat4x4(&worldMatrix, XMMatrixIdentity());
	position = XMFLOAT3(0, 0, 0);
	rotation = XMFLOAT3(0, 0, 0);
	scale = XMFLOAT3(1, 1, 1);

	entityMaterial = material;
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

void GameEntity::PrepareMaterial(XMFLOAT4X4 viewMatrix, XMFLOAT4X4 projMatrix)
{
	entityMaterial->GetVertexShader()->SetMatrix4x4("world", worldMatrix);
	entityMaterial->GetVertexShader()->SetMatrix4x4("view", viewMatrix);
	entityMaterial->GetVertexShader()->SetMatrix4x4("projection", projMatrix);
	entityMaterial->GetVertexShader()->SetShader(true);
	entityMaterial->GetPixelShader()->SetShader(true);
}

void GameEntity::Move(float x, float y, float z)
{
	position.x = x;
	position.y = y;
	position.z = z;
}
