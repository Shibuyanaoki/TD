#include "Hammer.h"
#include "TextureManager.h"
#include <cassert>

Hammer::~Hammer() { delete model_; }

Hammer::Hammer() {}

void Hammer::Initialize(Model* model, uint32_t textureHandle, Vector3 position) {
	assert(model);

	worldTransform_.scale_ = {5.0f, 5.0f, 5.0f};

	input_ = Input::GetInstance();
	// ワールドトランスホームフォームの初期化
	worldTransform_.Initialize();

	// モデル
	model_ = model;
	// テクスチャハンドル
	textureHandle_ = textureHandle;
	// X,Y,Z方向の平行移動を設定
	worldTransform_.translation_ = position;
}

void Hammer::Update() {

	Vector3 move = {0, 0, 0};

	if (input_->PushKey(DIK_SPACE)) {
		move.y -= 2;
	}

	worldTransform_.translation_.y = move.y;

	worldTransform_.UpdateMatrix();
}

void Hammer::Draw(ViewProjection viewProjection) {

	model_->Draw(worldTransform_, viewProjection, textureHandle_);
}

Vector3 Hammer::GetWorldPosition() {
	// ワールド座標を入れる変数
	Vector3 worldPos;

	// ワールド行列の平行移動成分を取得(ワールド座標)
	worldPos.x = worldTransform_.matWorld_.m[3][0];
	worldPos.y = worldTransform_.matWorld_.m[3][1];
	worldPos.z = worldTransform_.matWorld_.m[3][2];

	return worldPos;

}

void Hammer::OnColllision() {}
