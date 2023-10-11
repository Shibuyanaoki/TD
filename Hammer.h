#pragma once
#include "Audio.h"
#include "DirectXCommon.h"
#include "Input.h"
#include "Model.h"
#include "SafeDelete.h"
#include "Sprite.h"
#include "ViewProjection.h"
#include "WorldTransform.h"
class Hammer {	
public:

	~Hammer();

	Hammer();

	void Initialize(Model* model, uint32_t textureHandle, Vector3 position);

	void Update();

	void Draw(ViewProjection viewProjection_);

private:
	DirectXCommon* dxCommon_ = nullptr;
	Input* input_ = nullptr;
	Audio* audio_ = nullptr;

	//テクスチャハンドル
	uint32_t textureHandle_ = 0;

	// ワールドトランスフォーム
	WorldTransform worldTransform_;

	//3Dモデル
	Model* model_ = nullptr;
	

};
