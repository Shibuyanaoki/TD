#include "Hammer.h"
#include "TextureManager.h"
#include <cassert>

Hammer::~Hammer() { delete model_; }

Hammer::Hammer() {}

void Hammer::Initialize(Model* model, uint32_t textureHandle, Vector3 position) {
	assert(model);

	input_ = Input::GetInstance();
	// ワールドトランスホームフォームの初期化
	worldTransform_.Initialize();

	//モデル
	model_ = model;
	//テクスチャハンドル
	textureHandle_ = textureHandle;
	// X,Y,Z方向の平行移動を設定
	worldTransform_.translation_ = position;
	
	
}

void Hammer::Update() {

	Vector3 move = {0, 0, 0};

	//const float kSpeed = 0.5;

	/*if (input_->PushKey(DIK_LEFT)) {
		move.x -= kSpeed;
	}

	if (input_->PushKey(DIK_RIGHT)) {
		move.x += kSpeed;
	}*/

	if (input_->PushKey(DIK_SPACE)) {
		move.y += 2;
	}

	worldTransform_.translation_ = move;
	
	worldTransform_.TransferMatrix();

	// 移動限界座標
	const float kMoveLimitX = 31;
	const float kMoveLimitY = 19;

	// 範囲を超えない処理
	worldTransform_.translation_.x = max(worldTransform_.translation_.x, -kMoveLimitX);
	worldTransform_.translation_.x = min(worldTransform_.translation_.x, +kMoveLimitX);
	worldTransform_.translation_.y = max(worldTransform_.translation_.y, -kMoveLimitY);
	worldTransform_.translation_.y = min(worldTransform_.translation_.y, +kMoveLimitY);

}

void Hammer::Draw(ViewProjection viewProjection_) {

model_->Draw(worldTransform_, viewProjection_, textureHandle_);

}
