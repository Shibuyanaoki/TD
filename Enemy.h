#pragma once
#include "Audio.h"
#include "DirectXCommon.h"
#include "Input.h"
#include "Model.h"
#include "SafeDelete.h"
#include "Sprite.h"
#include "ViewProjection.h"
#include "WorldTransform.h"
class Enemy {

public:
	void Initialize(Model* model, uint32_t textureHandle, Vector3 position);

	void Update();

	void Draw(ViewProjection viewProjection);

	Vector3 GetWorldPosition();

	void OnColllision();

private:
	DirectXCommon* dxCommon_ = nullptr;
	Input* input_ = nullptr;
	Audio* audio_ = nullptr;

	WorldTransform worldTransform_;
	
	uint32_t textureHandle_ = 0;
	Model* model_ = nullptr;
};
