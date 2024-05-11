#pragma once

#include "Audio.h"
#include "DirectXCommon.h"
#include "Input.h"
#include "Model.h"
#include "Sprite.h"
#include "ViewProjection.h"
#include "WorldTransform.h"
#include "Player.h"//プレイヤー
#include <vector>
#include "Vector3SRT.h"

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
	/// </summary>
	
	//テクスチャハンドル
	uint32_t texturHandle_ = 0;

	
	Model* model_ = nullptr;		//3Dモデル
	ViewProjection viewProjection_;	// ビュープロジェクション　ゲーム中に共通で一つ
	Player* player_ = nullptr;		//自機

	Model* blockModel_ = nullptr;
	//std::vector<std::vector<WorldTransform*>> worldTransformBlocks_;
	std::vector<std::vector<WorldTransform*>> worldTransformBlocks_;
	
};
