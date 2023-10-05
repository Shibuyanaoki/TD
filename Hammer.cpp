#include "Hammer.h"
#include "TextureManager.h"
#include <cassert>

Hammer::~Hammer() { delete model_; }

Hammer::Hammer() {}

void Hammer::Initialize() {
	//ファイル名を指定してテクスチャを読み込む
	textureHandle_ = TextureManager::Load("white1x1.png");
	// 3Dモデルの生成
	model_ = Model::Create();
	//ワールドトランスホームフォームの初期化
	worldTransform_.Initialize();
	//ビュープロジェクションの初期化
	viewProjection_.Initialize();

}

void Hammer::Updata() {}

void Hammer::Draw() {

model_->Draw(worldTransform_, viewProjection_, textureHandle_);

}
