#pragma once
#include "Input.h"
#include "Model.h"
#include "WorldTransform.h"
#include "assert.h"
#include <algorithm>
#include <numbers>
#include<algorithm>

enum class LRDirecion {
	kright,
	kLeft,
};

class Player {

public:
	// 初期化
	void Initialize(Model* model, ViewProjection* viewProjection, const Vector3& position);

	// 更新
	void Update();

	// 描画
	void Draw();

	float EaseOutSine(float x);
	const WorldTransform &GetWorldTransform() { return worldTransform_; }
	const Vector3& GetVelocity() const { return velocity_; }

private:

	WorldTransform worldTransform_;             // ワールド変換データ
	Model* model_ = nullptr;                    // モデル
	ViewProjection* viewProjection_ = nullptr;  // ViewProjection
	//移動
	Vector3 velocity_ = {};                     // 速度
	static inline const float kAccleration = 0.01f; // 定数加速度
	static inline const float kAttenuation = 0.2f;//速度減衰率
	static inline const float kLimitRunSpeed = 1.0f;//最大速度制限
	//振り向き
	LRDirecion lrDirection_ = LRDirecion::kright;
	float turnFirstRotationY_ = 0.0f;           // 現在の向き
	float turnTimer_ = 0.0f;                    // 振り向き時間
	static inline const float KtimeTurn = 0.5f; // 角度補間タイム
	//ジャンプ
	bool onGround_ = true; // 接点状態フラグ
	static inline const float kGravityAccleration = 0.1f;//重力加速度
	static inline const float kLimitFallSpeed = 0.5f;//最大落下速度
	static inline const float kJampAcceleration = 1.0f;//ジャンプ初速


};
