#include "Player.h"


void Player::Initialize(Model* model, uint32_t textureHandle, ViewProjection* viewProjection) {
	assert(model);
	model_=model;
	texthureHandle_ = textureHandle;
	worldTransform_.Initialize();
	viewProjection_ = viewProjection;
}

void Player::Update() {

	// 行列を定数バッファに転送
	worldTransform_.TransferMatrix();

}

void Player::Draw() {
	
	model_->Draw(worldTransform_, *viewProjection_, texthureHandle_);

}
