#include "Matrix4x4.h"





//static const int kRowHeight = 20;
//static const int kColumnWidth = 60;

//void MatrixScreenPrintf(int x, int y, const Matrix4x4& matrix) {
//	for (int row = 0; row < 4; ++row) {
//		for (int column = 0; column < 4; ++column) {
//			Novice::ScreenPrintf(
//				x + column* kColumnWidth, y + row * kRowHeight, "%6.02f", matrix.m[row][column]);
//		}
//	}
//}



Matrix4x4 Add(const Matrix4x4& mt1, const Matrix4x4& mt2);

Matrix4x4 Subtract(const Matrix4x4& mt1, const Matrix4x4& mt2);

Matrix4x4 Multiply(const Matrix4x4& mt1, const Matrix4x4& mt2);

Matrix4x4 Inverse(const Matrix4x4& mt1);


Matrix4x4 Transpose(const Matrix4x4& mt1);

Matrix4x4 MekeIdentity4x4();


