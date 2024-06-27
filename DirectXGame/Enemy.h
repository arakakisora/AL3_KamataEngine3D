#pragma once
#include "Model.h"
#include "WorldTransform.h"
#include "assert.h"
#include <algorithm>
#include <algorithm>
#include <numbers>

class Enemy {
public:
	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize(Model* model, ViewProjection* viewProjection, const Vector3& position);

	/// <summary>
	/// 毎フレーム処理
	/// </summary>
	void Update();

	/// <summary>
	/// 描画
	/// </summary>
	void Draw();

private:
	WorldTransform worldTransform_;            // ワールド変換データ
	Model* model_ = nullptr;                   // モデル
	ViewProjection* viewProjection_ = nullptr; // ViewProjection
	// 敵の動き
	static inline const float kWalkSpeed = 0.01f; // 歩行の速さ
	Vector3 velocity_ = {};                      // 速度
	//敵のアニメーション
	static inline const float kWalkMotionAngleStart = 0.1f;//最初の角度
	static inline const float kWalkMotionAngleEnd = 0.5f;//最後の角度
	static inline const float kWalkMotionTime = 0.1f;//アニメーションの時間
	float walkTimer_ = 0.0f;
};
