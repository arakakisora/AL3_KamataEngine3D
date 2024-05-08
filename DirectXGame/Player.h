#pragma once
#include "Model.h"
#include "WorldTransform.h"
#include "assert.h"
class Player {

public:
	
	

	//初期化
	void Initialize(Model*model,uint32_t textureHandle,ViewProjection* viewProjection);

	//更新
	void Update();

	//描画
	void Draw();

private:

	//ワールド変換データ
	WorldTransform worldTransform_;
	
	//モデル
	Model* model_ = nullptr;
	uint32_t texthureHandle_ = 0u;

	ViewProjection* viewProjection_=nullptr;
	




};

