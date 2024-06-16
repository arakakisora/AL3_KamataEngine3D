#pragma once

#include "Audio.h"
#include "DebugCamera.h"
#include "DirectXCommon.h"
#include "Input.h"
#include "MapChipField.h"
#include "Model.h"
#include "Player.h" //プレイヤー
#include "Skydome.h"
#include "Sprite.h"
#include "MyMath.h"
#include "ViewProjection.h"
#include "WorldTransform.h"
#include "CameraController.h"
#include <vector>

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
	/// ブロックの生成
	/// </summary>
	void GenerateBlokcs();

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

	// テクスチャハンドル
	uint32_t texturHandle_ = 0;

	// Player
	Model* model_ = nullptr;        // 3Dモデル
	ViewProjection viewProjection_; // ビュープロジェクション　ゲーム中に共通で一つ
	Player* player_ = nullptr;      // 自機

	// MapBlock
	Model* blockModel_ = nullptr;
	bool isDebugCameraActive_ = false;
	DebugCamera* debugCamera_ = nullptr;

	// SkyDome
	Skydome* skydome_ = nullptr;
	Model* modelSkydome_ = nullptr;
	std::vector<std::vector<WorldTransform*>> worldTransformBlocks_;

	// MapChipField
	MapChipField* mapChipField_;

	//CameraController
	CameraController* cameraController_=nullptr;

};
