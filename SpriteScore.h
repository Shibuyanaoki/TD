#pragma once
#include "Audio.h"
#include "DirectXCommon.h"
#include "Input.h"
#include "Model.h"
#include "SafeDelete.h"
#include "Sprite.h"
#include "ViewProjection.h"
#include "WorldTransform.h"

class SpriteScore {

	void Initialize();

	void Update();

	void Draw();

private:
	DirectXCommon* dxCommon_ = nullptr;
	Input* input_ = nullptr;
	Audio* audio_ = nullptr;

	// ナンバー
	uint32_t textureHandleNumber = 0;
	Sprite* spriteNumber_[4] = {};

	// スコア
	uint32_t textureHandleSCORE = 0;
	Sprite* spriteScore = {};
	int gameScore = 0;

	int gameTimer_ = 0;
};
