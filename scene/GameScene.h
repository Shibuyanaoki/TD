#pragma once

#include "Audio.h"
#include "DirectXCommon.h"
#include "Input.h"
#include "Model.h"
#include "SafeDelete.h"
#include "Sprite.h"
#include "ViewProjection.h"
#include "WorldTransform.h"
#include "Hammer.h"
#include "Enemy.h"
#include <memory>

/// <summary>
/// ゲームシーン
/// </summary>
class GameScene {

public: // メンバ関数
	/// <summary>
	/// コンストクラタ
	/// </summary>
	GameScene();

	/// <summary>
	/// デストラクタ
	/// </summary>
	~GameScene();

	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize();

	/// <summary>
	/// 毎フレーム処理
	/// </summary>
	void Update();

	/// <summary>
	/// 描画
	/// </summary>
	void Draw();

private: // メンバ変数
	DirectXCommon* dxCommon_ = nullptr;
	Input* input_ = nullptr;
	Audio* audio_ = nullptr;

	/// <summary>
	/// ゲームシーン用
	// テクスチャハンドル
	uint32_t textureHandle_ = 0;
	//テクスチャハンドル
	uint32_t hammerTextureHandle_ = 0;

	//ワールドトランスフォーム
	WorldTransform worldTransform_;
	//ビューポートプロジェクション
	ViewProjection viewProjection_;
	// ハンマー読み込み
	Hammer* hammer_ = nullptr;
	//敵の読み込み
	Enemy* enemy_ = nullptr;
	// 3Dモデル
	Model* model_ = nullptr;
	//ハンマーの3D描画
	Model* hammerModel_ = nullptr;

	/// </summary>
};
