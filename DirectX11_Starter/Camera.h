#pragma once
#include<DirectXMath.h>
using namespace DirectX;
class Camera
{
public:
	Camera();
	~Camera();

	XMFLOAT4X4 GetWorldMatrix() { return worldMatrix; }
	XMFLOAT4X4 GetViewMatrix(){ return viewMatrix; }

	XMFLOAT4X4 GetProjectionMatrix(){ return projectionMatrix; }
	void SetRotationOnX(float x){ rot_X = x; }
	void SetRotationOnY(float y){ rot_Y = y; }
	void SetRotationOnZ(float z){ rot_Z = z; }
	void Update();
	void Move(float dist);
	void Rotate(float rotation);
	void Strafe(float dist);
	void VerticalMovement(float dist);
	void MouseMovement(float x, float y);
	void OnResize(float aspectRatio);

private:
	XMFLOAT4X4 worldMatrix;
	XMFLOAT4X4 viewMatrix;
	XMFLOAT4X4 projectionMatrix;
	XMFLOAT3 cameraPosition = XMFLOAT3(0.5,1,-5);
	XMFLOAT3 upVector = XMFLOAT3(0, 1, 0);
	XMFLOAT3 forwardVector= XMFLOAT3(0,0,1);
	XMFLOAT3 leftVector = XMFLOAT3(0, 0, 0);
	float rot_X = 0.0f;
	float rot_Y = 0.0f;
	float rot_Z = 0.0f;

};

