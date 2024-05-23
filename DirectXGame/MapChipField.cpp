#include "MapChipField.h"
#include <fstream>
#include <map>
#include <sstream>

namespace {

std::map<std::string, MapChipType> mapChipTable = {
    {"0", MapChipType::kBlank},
    {"1", MapChipType::kBlock},
};

}

void MapChipField::ResetMapChipData() {

	mapChipData_.data.clear();
	mapChipData_.data.resize(kNumBlockVirtical);
	for (std::vector<MapChipType>& mapChipDataLine : mapChipData_.data) {
		mapChipDataLine.resize(kNumBlockHorizontal);
	}
}

void MapChipField::LoadMapChipCsv(const std::string& filePath) {
	// マップチップデータをリセット
	ResetMapChipData();

	// ファイルを開く
	std::ifstream file;
	file.open(filePath);
	assert(file.is_open());

	// マップチップCSV
	std::stringstream mapChipCsv;
	// ファイルの内容を文字列ストリームにコピー
	mapChipCsv << file.rdbuf();
	// ファイルを閉じる
	file.close();

	// csvからマップチップデータを読み込む
	for (uint32_t y = 0; y < kNumBlockVirtical; ++y) {

		std::string line;
		getline(mapChipCsv, line);

		// 1桁分の文字列をストリームに変換して解析しやすくする
		std::istringstream lien_stream(line);

		for (uint32_t x = 0; x < kNumBlockVirtical; ++x) {

			std::string word;
			getline(lien_stream, word, ',');

			if (mapChipTable.contains(word)) {
				mapChipData_.data[y][x] = mapChipTable[word];
			}
		}
	}
}

MapChipType MapChipField::GetMapChipTypeByIndex(uint32_t xIndex, uint32_t yIndex) {

	if (xIndex < 0 || kNumBlockHorizontal - 1 < xIndex) {
		return MapChipType::kBlank;
	}
	if (yIndex < 0 || kNumBlockVirtical - 1 < yIndex) {
		return MapChipType::kBlank;
	}
	return mapChipData_.data[yIndex][xIndex];
}

Vector3 MapChipField::GetMapChipPostionByIndex(uint32_t xIndex, uint32_t yIndex) { 

	return Vector3(kBlockWidth * xIndex, kBlockHeight * (kNumBlockVirtical - 1) - yIndex, 0);
}
