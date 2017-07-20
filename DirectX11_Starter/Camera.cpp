#include "Camera.h"



Camera::Camera()
{
}


Camera::~Camera()
{
}

void Camera::Update()
{
	XMVECTOR forward = XMLoadFloat3(&forwardVector);
	XMVECTOR camPos = XMLoadFloat3(&cameraPosition);
	XMVECTOR upAxis = XMLoadFloat3(&upVector);
	XMVECTOR left = XMVector3Cross(forward, upAxis);
	XMStoreFloat3(&leftVector, left);
	XMMATRIX view = XMLoadFloat4x4(&viewMatrix);
	view = XMMatrixLookToLH(camPos, forward, upAxis);
	XMStoreFloat4x4(&viewMatrix, XMMatrixTranspose(view));

}

void Camera::Move(float dist)
{
	XMVECTOR camPos = XMLoadFloat3(&cameraPosition);
	XMVECTOR forward = XMLoadFloat3(&forwardVector);
	camPos += forward*dist;
	XMStoreFloat3(&cameraPosition, camPos);
}

void Camera::Rotate(float rotation)
{
	XMVECTOR forwardDirection = XMLoadFloat3(&forwardVector);
	XMVECTOR camPos = XMLoadFloat3(&cameraPosition);
	XMVECTOR rot = XMQuaternionRotationRollPitchYaw(0, rotation, 0);
	XMStoreFloat3(&forwardVector, forwardDirection);
}

void Camera::Strafe(float dist)
{
	XMVECTOR camPos = XMLoadFloat3(&cameraPosition);
	XMVECTOR left = XMLoadFloat3(&leftVector);
	camPos += left*dist;
	XMStoreFloat3(&cameraPosition, camPos);
	XMStoreFloat3(&leftVector, left);

}

void Camera::VerticalMovement(float dist)
{
	XMVECTOR camPos = XMLoadFloat3(&cameraPosition);
	XMVECTOR upDir = XMLoadFloat3(&upVector);
	camPos += upDir*dist;
	XMStoreFloat3(&cameraPosition, camPos);
}

void Camera::MouseMovement(float x, float y)
{
	rot_X = x;
	rot_Y = y;
	XMVECTOR camFarDir = XMLoadFloat3(&forwardVector);
	XMVECTOR camUpDir = XMLoadFloat3(&upVector);
	XMMATRIX pitch = XMMatrixRotationAxis(-XMVector3Cross(camFarDir, camUpDir), rot_X);
	XMMATRIX yaw = XMMatrixRotationAxis(camUpDir, rot_Y);
	XMVECTOR newCamFarDir = XMVector3Transform(camFarDir, pitch);
	newCamFarDir = XMVector3Transform(newCamFarDir, yaw);
	XMStoreFloat3(&forwardVector, newCamFarDir);

}


void Camera::OnResize(float aspectRatio)
{
	// Handle base-level DX resize stuff

	// Update our projection matrix since the window size changed
	XMMATRIX P = XMMatrixPerspectiveFovLH(
		0.25f * 3.1415926535f,	// Field of View Angle
		aspectRatio,		  	// Aspect ratio
		0.1f,				  	// Near clip plane distance
		100.0f);			  	// Far clip plane distance
	XMStoreFloat4x4(&projectionMatrix, XMMatrixTranspose(P)); // Transpose for HLSL!
}

