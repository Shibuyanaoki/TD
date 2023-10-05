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

	void Initialize();

	void Updata();

	void Draw();

private:
	DirectXCommon* dxCommon_ = nullptr;
	Input* input_ = nullptr;
	Audio* audio_ = nullptr;

	//テクスチャハンドル
	uint32_t textureHandle_ = 0;

	// ワールドトランスフォーム
	WorldTransform worldTransform_;
	// ビューポートプロジェクション
	ViewProjection viewProjection_;

	//3Dモデル
	Model* model_ = nullptr;
	

};
