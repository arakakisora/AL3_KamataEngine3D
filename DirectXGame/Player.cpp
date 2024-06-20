#define NOMINMAX
#include "Player.h"
#include "MapChipField.h"
#include <DebugText.h>

void Player::Initialize(Model* model, ViewProjection* viewProjection, const Vector3& position) {
	assert(model);
	model_ = model;
	// texthureHandle_ = textureHandle;
	worldTransform_.Initialize();
	worldTransform_.translation_ = position;
	worldTransform_.rotation_.y = std::numbers::pi_v<float> / 2.0f;
	// worldTransform_.rotation_.y = 0;
	viewProjection_ = viewProjection;
}

void Player::Update() {

	// 移動入力
	// 左右移動操作
	if (onGround_) {

		PrayerMove();
		// 衝突判定を初期化
		CollisionMapInfo collisionMapInfo;
		// 移動量に速度の値をコピー
		collisionMapInfo.move = velocity_;
		// マップ衝突チェック
		MapCollision(collisionMapInfo);

		if (Input::GetInstance()->PushKey(DIK_UP)) {

			velocity_.x += 0;
			velocity_.y += kJampAcceleration;
			velocity_.z += 0;
		}

	} else {
		// 落下速度
		velocity_.x += 0;
		velocity_.y += -kGravityAccleration;
		velocity_.z += 0;
		// 落下速度制限

		velocity_.y = std::max(velocity_.y, -kLimitFallSpeed);
	}

	if (turnTimer_ > 0.0f) {
		turnTimer_ -= 1.0f / 60.0f;

		// 左右の角度テーブル
		float destinationRotationYTable[] = {
		    std::numbers::pi_v<float> / 2.0f,
		    std::numbers::pi_v<float> * 3.0f / 2.0f,
		};
		// 状態に応じた角度を取得する
		float destinationRotationY = destinationRotationYTable[static_cast<uint32_t>(lrDirection_)];
		// 自キャラの角度を設定する
		worldTransform_.rotation_.y = destinationRotationY * EaseOutSine(turnTimer_);
		;
		;
	}
	// 着地フラグ
	bool landing = false;
	// 地面との当たり判定
	// 落下途中？
	if (velocity_.y < 0) {
		// 座標が地面以下になったら着地
		if (worldTransform_.translation_.y <= 1.0f) {

			landing = true;
		}
	}

	// 接地判定
	if (onGround_) {
		// ジャンプ開始
		if (velocity_.y > 0.0f) {

			onGround_ = false;
		}
	} else {
		// 着地
		if (landing) {
			// めり込み排斤
			worldTransform_.translation_.y = 1.0f;
			// 摩擦で横方向速度が減衰する
			velocity_.x *= (1.0f - kAttenuation);
			// 下方向速度をリセット
			velocity_.y = 0.0f;
			// 接地状態に移行
			onGround_ = true;
		}
	}

	// 移動
	worldTransform_.translation_.x += velocity_.x;
	worldTransform_.translation_.y += velocity_.y;
	worldTransform_.translation_.y += velocity_.y;

	worldTransform_.UpdateMatrix();

	// 行列を定数バッファに転送
	worldTransform_.TransferMatrix();
}

void Player::Draw() { model_->Draw(worldTransform_, *viewProjection_); }

void Player::PrayerMove() {
	if (Input::GetInstance()->PushKey(DIK_RIGHT) || Input::GetInstance()->PushKey(DIK_LEFT)) {
		// 左右加速
		Vector3 accceleration = {};
		if (Input::GetInstance()->PushKey(DIK_RIGHT)) {

			if (velocity_.x < 0.0f) {
				velocity_.x *= (1.0f - kAttenuation);
			}

			if (lrDirection_ != LRDirecion::kright) {
				lrDirection_ = LRDirecion::kright;
				turnFirstRotationY_ = worldTransform_.rotation_.y;
				turnTimer_ = kLimitRunSpeed;
			}

			accceleration.x += kAccleration;

		} else if (Input::GetInstance()->PushKey(DIK_LEFT)) {

			if (velocity_.x > 0.0f) {
				velocity_.x *= (1.0f - kAttenuation);
			}
			if (lrDirection_ != LRDirecion::kLeft) {
				lrDirection_ = LRDirecion::kLeft;
				turnFirstRotationY_ = worldTransform_.rotation_.y;
				turnTimer_ = kLimitRunSpeed;
			}

			accceleration.x -= kAccleration;
		}
		velocity_.x += accceleration.x;
		velocity_.y += accceleration.y;
		velocity_.z += accceleration.z;

		velocity_.x = std::clamp(velocity_.x, -kLimitRunSpeed, kLimitRunSpeed);

	} else {

		velocity_.x *= (1.0f - kAttenuation);
		velocity_.y *= (1.0f - kAttenuation);
		velocity_.z *= (1.0f - kAttenuation);
	}
}

void Player::MapCollision(CollisionMapInfo& info) {

	CollisionMapInfoTop(  info);
	/*CollisionMapInfoBootm(info);
	CollisionMapInfoRight(info);
	CollisionMapInfoLeft( info);*/
}

Vector3 Player::CornerPosition(const Vector3& center, Corner corner) {

	Vector3 offseetTable[kNumCorner] = {

	    {+kWidth / 2.0f, -kHeight / 2.0f, 0},
        {-kWidth / 2.0f, -kHeight / 2.0f, 0},
        {+kWidth / 2.0f, +kHeight / 2.0f, 0},
        {-kWidth / 2.0f, +kHeight / 2.0f, 0}
	};

	return center + offseetTable[static_cast<uint32_t>(corner)];

	/*if (corner == kRightBottom) {
	    return centor + Vector3{+kWidth / 2.0f, -kHeight / 2.0f, 0};
	} else if (corner == kLeftBottom){
	    return centor + Vector3{-kWidth / 2.0f, -kHeight / 2.0f, 0};
	} else if (corner == kRightTop) {
	    return centor + Vector3{+kWidth / 2.0f, +kHeight / 2.0f, 0};
	} else {
	    return centor + Vector3{-kWidth / 2.0f, +kHeight / 2.0f, 0};
	}*/
}

void Player::PlayerCollisionMove(const CollisionMapInfo& info) {
	//移動
	worldTransform_.translation_ += info.move;
}

//天井当たった？
void Player::CeilingCollisionMove(const CollisionMapInfo& info) {

	if (info.ceiling) {
	
	 DebugText::GetInstance()->ConsolePrintf("hit ceiling\n");
		velocity_.y = 0;
	}

}

void Player::CollisionMapInfoTop(CollisionMapInfo& info) {

	std::array<Vector3, 4> positionsNew;
	for (uint32_t i = 0; i < positionsNew.size(); ++i) {
		positionsNew[i] = CornerPosition(worldTransform_.translation_ + info.move, static_cast<Corner>(i));
	}
	if (info.move.y <= 0) {
		return;
	}

	MapChipType mapChipType;
	// 真上の当たり判定
	bool hit = false;
	// 左点の判定
	IndexSet indexSet;
	indexSet = mapChipFild_->GetMapVhipIndexSetByPosition(positionsNew[kLeftTop]);
	mapChipType = mapChipFild_->GetMapChipTypeByIndex(indexSet.xIndex, indexSet.yIndex);
	if (mapChipType == MapChipType::kBlock) {
		hit = true;
	
	}
	//右点の判定
	//  左点の判定
	
	indexSet = mapChipFild_->GetMapVhipIndexSetByPosition(positionsNew[kRightTop]);
	mapChipType = mapChipFild_->GetMapChipTypeByIndex(indexSet.xIndex, indexSet.yIndex);
	if (mapChipType == MapChipType::kBlock) {
		hit = true;
	}
	//hit
	if (hit) {
	//めり込みを排除する方向に移動量を設定する
		indexSet = mapChipFild_->GetMapVhipIndexSetByPosition(worldTransform_.translation_ + Vector3(0, +kHeight / 2.0f, 0));
	//めり込み先ブロックの範囲矩形
		Rect rect = mapChipFild_->GetRectByIndex(indexSet.xIndex, indexSet.yIndex);
		info.move.y = std::max(0.0f, rect.bottom - worldTransform_.translation_.y - (kHeight / 2.0f + kBlank));
		//天井に当たったらことを記録する
		info.ceiling = true;
	}

}

float Player::EaseOutSine(float x) { return cosf((x * std::numbers::pi_v<float>) / 2); }
