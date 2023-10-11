#include "Player.h"
#include "TextureManager.h"
#include <cassert>

void Player::Initialize() {

	dxCommon_ = DirectXCommon::GetInstance();
	input_ = Input::GetInstance();
	audio_ = Audio::GetInstance();

	// ファイル名を指定してテクスチャを読み込む
	textureHandle_ = TextureManager::Load("uvChecker.png");
	// ワールドトランスフォームの初期化
	worldTransform_.Initialize();
	// ビューポートプロジェクションの初期化
	viewProjection_.Initialize();
	// 3Dモデルの生成
	model_ = Model::Create();

	// ハンマーの生成
	//hammer = new Hammer;
	// ハンマーの初期化
	//hammer->Initialize();
}

void Player::Updata() { hammer->Update(); }

void Player::Draw() {
	model_->Draw(worldTransform_, viewProjection_, textureHandle_);
	// hammer->Draw();
}
