#include "GameScene.h"
#include "TextureManager.h"
#include <cassert>

GameScene::GameScene() {}

GameScene::~GameScene() {}

void GameScene::Initialize() {

	dxCommon_ = DirectXCommon::GetInstance();
	input_ = Input::GetInstance();
	audio_ = Audio::GetInstance();

	// ファイル名を指定してテクスチャを読み込む
	textureHandle_ = TextureManager::Load("sample.png"); 
	hammerTextureHandle_ = TextureManager::Load("white1x1.png");
	enemyTextureHandle_ = TextureManager::Load("tex1.png");


	// 3Dモデルの生成
	model_ = Model::Create();
	hammerModel_ = Model::Create();
	enemyModel_ = Model::Create();
	//ワールドトランスフォームの初期化
	worldTransform_.Initialize();
	//ビューポートプロジェクションの初期化
	viewProjection_.Initialize();
	//プレイヤーの生成
	hammer_ = new Hammer;
	//敵の生成
	enemy_ = new Enemy;

	//ハンマーの初期ポジション
	Vector3 hammerPosition = {10, 10, 10};
	//敵の初期ポジション
	Vector3 enemyPosition = {0, 0, 0};
	//ハンマーの初期化
	hammer_->Initialize(hammerModel_,hammerTextureHandle_,hammerPosition);
	//敵の初期化
	enemy_->Initialize(enemyModel_,enemyTextureHandle_,enemyPosition);

}

void GameScene::Update() {
	
	//ハンマーの更新
	hammer_->Update();
	//敵の更新
	enemy_->Update();

}

void GameScene::Draw() {

	// コマンドリストの取得
	ID3D12GraphicsCommandList* commandList = dxCommon_->GetCommandList();

#pragma region 背景スプライト描画
	// 背景スプライト描画前処理
	Sprite::PreDraw(commandList);

	/// <summary>
	/// ここに背景スプライトの描画処理を追加できる
	/// </summary>

	// スプライト描画後処理
	Sprite::PostDraw();
	// 深度バッファクリア
	dxCommon_->ClearDepthBuffer();
#pragma endregion

#pragma region 3Dオブジェクト描画
	// 3Dオブジェクト描画前処理
	Model::PreDraw(commandList);

	/// <summary>
	/// ここに3Dオブジェクトの描画処理を追加できる
	/// </summary>
	
	
	// ハンマーの描画
	hammer_->Draw(viewProjection_);

	//敵の描画
	enemy_->Draw(viewProjection_);

	// ステージの描画
	//model_->Draw(worldTransform_, viewProjection_, textureHandle_);

	// 3Dオブジェクト描画後処理
	Model::PostDraw();
#pragma endregion

#pragma region 前景スプライト描画
	// 前景スプライト描画前処理
	Sprite::PreDraw(commandList);

	/// <summary>
	/// ここに前景スプライトの描画処理を追加できる
	/// </summary>

	// スプライト描画後処理
	Sprite::PostDraw();

#pragma endregion
}

void GameScene::CheckAllCollisions() {

	//判定対象AとBの座標
	Vector3 posA, posB;

	//自キャラリストの取得
	

}
