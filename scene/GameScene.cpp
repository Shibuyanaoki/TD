#include "GameScene.h"
#include "TextureManager.h"
#include <cassert>
#include <stdlib.h>
#include <time.h>

GameScene::GameScene() {}

GameScene::~GameScene() {
	delete enemyModel_;
	delete bouringModel_;

	for (Enemy* enemy : enemys_) {
		delete enemy;
	}

	for (Bouring* bouring : bourings_) {
		delete bouring;
	}
}

void GameScene::Initialize() {

	dxCommon_ = DirectXCommon::GetInstance();
	input_ = Input::GetInstance();
	audio_ = Audio::GetInstance();

	// ファイル名を指定してテクスチャを読み込む
	textureHandle_ = TextureManager::Load("haikei.png");
	// ハンマーのテクスチャ
	hammerTextureHandle_ = TextureManager::Load("white1x1.png");
	// スコア文字テクスチャ
	textureHandleSCORE = TextureManager::Load("score.png");
	// スコアの数字テクスチャ
	textureHandleNumber = TextureManager::Load("number.png");
	// スコアのスプライト描画
	for (int i = 0; i < 4; i++) {
		spriteNumber_[i] = Sprite::Create(textureHandleNumber, {130.0f + i * 26, 10});
	}
	// 背景スプライト
	haikeiTextureHandle_ = TextureManager::Load("haikei.png");

	// サウンドデータの読み込み
	// soundDataHandle_ = audio_->LoadWave("");

	// スプライト描画
	haikei_ = Sprite::Create(haikeiTextureHandle_, {0, 0});

	// 3Dモデルの生成
	model_ = Model::Create();
	// ハンマーの生成
	hammerModel_ = Model::Create();
	// 敵の生成
	enemyModel_ = Model::CreateFromOBJ("Enemy", true);
	// ボウリングの生成
	bouringModel_ = Model::CreateFromOBJ("bouring", true);
	// スコアのスプライト描画
	spriteScore = Sprite::Create(textureHandleSCORE, {0.0f, 10});
	// ワールドトランスフォームの初期化
	worldTransform_.Initialize();
	// ビューポートプロジェクションの初期化
	viewProjection_.Initialize();
	// プレイヤーの生成
	hammer_ = new Hammer;
	// デバッグカメラの生成
	debugCamera_ = new DebugCamera(1280, 720);
	// ハンマーの初期ポジション
	Vector3 hammerPosition = {-50.0f, 23.0f, 40.0f};
	// ハンマーの初期化
	hammer_->Initialize(hammerModel_, hammerTextureHandle_, hammerPosition);
	// ランダム関数
	srand((unsigned int)time(NULL));
}

void GameScene::Update() {

	enemyTimer--;
	bouringTimer--;

#ifdef _DEBUG

	if (input_->TriggerKey(DIK_1)) {
		isDebugCameraActive_ = 1;
	} else if (input_->TriggerKey(DIK_1) && isDebugCameraActive_ == 1) {
		isDebugCameraActive_ = 0;
	}

#endif
	// カメラの処理
	if (isDebugCameraActive_ == 1) {
		// デバックカメラの更新
		debugCamera_->Update();
		viewProjection_.matView = debugCamera_->GetViewProjection().matView;
		viewProjection_.matProjection = debugCamera_->GetViewProjection().matProjection;

		// ビュープロジェクション行列の転送
		viewProjection_.TransferMatrix();
	} else {
		// ビュープロジェクション行列の更新と転送
		viewProjection_.UpdateMatrix();
	}

	// ハンマーの更新
	hammer_->Update();

	// 敵の更新
	for (Enemy* enemy : enemys_) {
		enemy->Update();
	}

	for (Bouring* bouring : bourings_) {
		bouring->Update();
	}

	// 当たり判定の処理
	CheckAllCollisions();

	if (enemyTimer <= 0) {
		// 敵のランダムポジションX
		int enemyRondamPositionX = rand() % 90 - 30;
		// 敵の初期ポジション
		Vector3 enemyPosition = {(float)enemyRondamPositionX, -15, 40};

		// 敵の生成処理
		EnemyGenerate(enemyPosition);

		enemyTimer = 60;
	}

	if (bouringTimer <= 0) {
		// 敵のランダムポジションX
		int bouringRondamPositionX = rand() % 51 - 25;
		// 敵の初期ポジション
		Vector3 bouringPosition = {(float)bouringRondamPositionX, -15, 40};

		// 敵の生成処理
		BouringGenerate(bouringPosition);

		bouringTimer = 60;
	}

	// デスフラグの立った敵を削除
	enemys_.remove_if([](Enemy* enemy) {
		if (enemy->IsDead()) {
			delete enemy;
			return true;
		}
		return false;
	});

	// デスフラグの立った敵を削除
	bourings_.remove_if([](Bouring* bouring) {
		if (bouring->IsDead()) {
			delete bouring;
			return true;
		}
		return false;
	});
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

	haikei_->Draw();

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

	// 敵の描画
	for (Enemy* enemy : enemys_) {
		enemy->Draw(viewProjection_);
	}

	for (Bouring* bouring : bourings_) {
		bouring->Draw(viewProjection_);
	}

	// ステージの描画
	// model_->Draw(worldTransform_, viewProjection_, textureHandle_);

	// 3Dオブジェクト描画後処理
	Model::PostDraw();
#pragma endregion

#pragma region 前景スプライト描画
	// 前景スプライト描画前処理
	Sprite::PreDraw(commandList);

	/// <summary>
	/// ここに前景スプライトの描画処理を追加できる
	/// </summary>

	GamePlayDraw2DNear();

	// スプライト描画後処理
	Sprite::PostDraw();

#pragma endregion
}

void GameScene::CheckAllCollisions() {

#pragma
	// 判定対象AとBの座標
	Vector3 posA, posB, posC;

	// 自キャラリストの取得
	posA = hammer_->GetWorldPosition();

	for (Enemy* enemy : enemys_) {
		posB = enemy->GetWorldPosition();

		float dist = (posA.x - posB.x) * (posA.x - posB.x) + (posA.y - posB.y) * (posA.y - posB.y) +
		            (posA.z - posB.z) * (posA.z - posB.z);

		float enemyRadius = (hammer_->GetRadius() + enemy->GetRadius()) *
		                    (hammer_->GetRadius() + enemy->GetRadius());

		if (dist <= enemyRadius) {
			// 敵の衝突時コールバックを呼び出す
			enemy->OnCollision();
			gameScore++;
		}
	}

#pragma endregion

#pragma

	for (Bouring* bouring : bourings_) {
		posC = bouring->GetWorldPosition();

		float dist = (posA.x - posC.x) * (posA.x - posC.x) + (posA.y - posC.y) * (posA.y - posC.y) +
		             (posA.z - posC.z) * (posA.z - posC.z);

		float bouringRadius = (hammer_->GetRadius() + bouring->GetRadius()) *
		                      (hammer_->GetRadius() + bouring->GetRadius());

		if (dist <= bouringRadius) {
			// ボウリングの衝突時コールバックを呼び出す
			bouring->OnCollision();
			gameScore++;
		}
	}
#pragma endregion
}

void GameScene::EnemyGenerate(Vector3 position) {
	// 敵の生成
	Enemy* enemy = new Enemy;
	// 敵の初期化
	enemy->Initialize(enemyModel_, position);
	enemys_.push_back(enemy);
}

void GameScene::BouringGenerate(Vector3 position) {
	// ボウリング玉の生成
	Bouring* bouring = new Bouring;
	// ボウリング玉の初期化
	bouring->Initialize(bouringModel_, position);
	bourings_.push_back(bouring);
}

void GameScene::GamePlayDraw2DNear() {
	// 描画

	spriteScore->Draw();
	DrawScore();
}

void GameScene::DrawScore() {
	int eachNumber[4] = {};
	int number = gameScore;

	int keta = 1000;
	for (int i = 0; i < 4; i++) {
		eachNumber[i] = number / keta;
		number = number % keta;
		keta = keta / 10;
	}
	for (int i = 0; i < 4; i++) {
		spriteNumber_[i]->SetSize({32, 64});
		spriteNumber_[i]->SetTextureRect({32.0f * eachNumber[i], 0}, {32, 64});
		spriteNumber_[i]->Draw();
	}
}