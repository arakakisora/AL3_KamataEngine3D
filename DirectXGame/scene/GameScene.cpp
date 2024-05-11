#include "GameScene.h"
#include "TextureManager.h"
#include <cassert>


GameScene::GameScene() {}

GameScene::~GameScene() {
	delete model_;
	delete player_;
	delete blockModel_;

	for (std::vector<WorldTransform*>& worldTransformBlockLine : worldTransformBlocks_) {
		for (WorldTransform* worldTransformBlock : worldTransformBlockLine) {

			delete worldTransformBlock;
		}
	}
	worldTransformBlocks_.clear();
}

void GameScene::Initialize() {

	dxCommon_ = DirectXCommon::GetInstance();
	input_ = Input::GetInstance();
	audio_ = Audio::GetInstance();

	//テクスチャ読み込み
	texturHandle_ = TextureManager::Load("uvChecker.png");
	//3Dモデルの生成
	model_ = Model::Create();
	//ビュープロジェクションの初期化
	viewProjection_.Initialize();
	player_ = new Player();
	player_->Initialize(model_, texturHandle_, &viewProjection_);


	blockModel_ = Model::Create();
	//要素数
	const uint32_t kNumBlokVirtical = 10;
	const uint32_t kNumBlokHorizontal = 20;
	//ブロック1個分の横幅
	const float kBlockwidth = 2.0f;
	const float kBlockheight = 2.0f;
	//要素数を変更する
	//列数を設定
	worldTransformBlocks_.resize(kNumBlokVirtical);
	for(uint32_t i = 0; i < kNumBlokVirtical; ++i) {
	
		worldTransformBlocks_[i].resize(kNumBlokHorizontal);
	
	}
	//キューブ生成
	for (uint32_t i = 0; i < kNumBlokVirtical; ++i) {
		for (uint32_t j = 0; j < kNumBlokHorizontal; ++j) {
			if (i % 2 == 0) {
				if (j % 2 == 0) {

					worldTransformBlocks_[i][j] = new WorldTransform();
					worldTransformBlocks_[i][j]->Initialize();
					worldTransformBlocks_[i][j]->translation_.x = kBlockwidth * j;
					worldTransformBlocks_[i][j]->translation_.y = kBlockheight * i;
				}
			}


			
		}
	}

}

void GameScene::Update() { 
	player_->Update();

	

	for (std::vector<WorldTransform*>& worldTransformBlockLine : worldTransformBlocks_) {
		for (WorldTransform* worldTransformBlock : worldTransformBlockLine) {
			if (!worldTransformBlock)
				continue;
			worldTransformBlock->matWorld_ = MakeAffineMatrix(worldTransformBlock->scale_, worldTransformBlock->rotation_, worldTransformBlock->translation_);
			// 定数バッファに転送する
			worldTransformBlock->TransferMatrix();
		}
	}
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
	
	//player_->Draw();
	
	for (std::vector<WorldTransform*>& worldTransformBlockLine : worldTransformBlocks_) {
		for (WorldTransform* worldTransformBlock : worldTransformBlockLine) {
			if (!worldTransformBlock)
				continue;
			blockModel_->Draw(*worldTransformBlock, viewProjection_);
		}
	}



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
