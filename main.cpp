#include <Novice.h>
#include <Vector3.h>
#include <Matrix4x4.h>
#include <cstdint>
#include <cmath>
#include <cassert>
#include <imgui.h>
#include <numbers>

const char kWindowTitle[] = "LE2B_13_サトウ_リュウセイ_MT3_03_02";

// 加算
Vector3 Add(const Vector3 & v1, const Vector3 & v2);
// 減算
Vector3 Subtract(const Vector3 & v1, const Vector3 & v2);
// スカラー倍
Vector3 Multiply(float scalar, const Vector3 & v);

// 行列の加法
Matrix4x4 Add(const Matrix4x4 & m1, const Matrix4x4 & m2);
// 行列の減法
Matrix4x4 Subtract(const Matrix4x4 & m1, const Matrix4x4 & m2);
// 行列の積
Matrix4x4 Multiply(const Matrix4x4 & m1, const Matrix4x4 & m2);

// x軸回転行列
Matrix4x4 MakeRotateXMatrix(float radian);

// y軸回転行列
Matrix4x4 MakeRotateYMatrix(float radian);

// z軸回転行列
Matrix4x4 MakeRotateZMatrix(float radian);

// 演算子オーバーロード
Vector3 operator+(const Vector3& v1, const Vector3& v2) { return Add(v1, v2); }
Vector3 operator-(const Vector3& v1, const Vector3& v2) { return Subtract(v1, v2); }
Vector3 operator*(float s, const Vector3& v) { return Multiply(s, v); }
Vector3 operator*(const Vector3& v, float s) { return s * v; }
Vector3 operator/(const Vector3& v, float s) { return Multiply(1.0f / s, v); }
Vector3 operator-(const Vector3& v) { return { -v.x, -v.y, -v.z }; }
Vector3 operator+(const Vector3& v) { return v; }
Matrix4x4 operator+(const Matrix4x4& m1, const Matrix4x4& m2) { return Add(m1, m2); }
Matrix4x4 operator-(const Matrix4x4& m1, const Matrix4x4& m2) { return Subtract(m1, m2); }
Matrix4x4 operator*(const Matrix4x4& m1, const Matrix4x4& m2) { return Multiply(m1, m2); }

// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {

	// ライブラリの初期化
	Novice::Initialize(kWindowTitle, 1280, 720);

	Vector3 a{ 0.2f,1.0f,0.0f };
	Vector3 b{ 2.4f,3.1f,1.2f };

	Vector3 c = a + b;
	Vector3 d = a - b;
	Vector3 e = a * 2.4f;
	Vector3 rotate{ 0.4f,1.43f,-0.8f };
	Matrix4x4 rotateXMatrix = MakeRotateXMatrix(rotate.x);
	Matrix4x4 rotateYMatrix	= MakeRotateYMatrix(rotate.y);
	Matrix4x4 rotateZMatrix	= MakeRotateZMatrix(rotate.z);
	Matrix4x4 rotateMatrix = rotateXMatrix * rotateYMatrix * rotateZMatrix;
	// キー入力結果を受け取る箱
	char keys[256] = {0};
	char preKeys[256] = {0};

	// ウィンドウの×ボタンが押されるまでループ
	while (Novice::ProcessMessage() == 0) {
		// フレームの開始
		Novice::BeginFrame();

		// キー入力を受け取る
		memcpy(preKeys, keys, 256);
		Novice::GetHitKeyStateAll(keys);

		///
		/// ↓更新処理ここから
		///
		ImGui::Begin("Window");
		ImGui::Text("c:%f,%f,%f", c.x, c.y, c.z);
		ImGui::Text("d:%f,%f,%f", d.x, d.y, d.z);
		ImGui::Text("e:%f,%f,%f", e.x, e.y, e.z);
		ImGui::Text(
			"matrix:\n%f,%f,%f,%f\n%f,%f,%f,%f\n%f,%f,%f,%f\n%f,%f,%f,%f\n",
			rotateMatrix.m[0][0], rotateMatrix.m[0][1], rotateMatrix.m[0][2], rotateMatrix.m[0][3],
			rotateMatrix.m[1][0], rotateMatrix.m[1][1], rotateMatrix.m[1][2], rotateMatrix.m[1][3],
			rotateMatrix.m[2][0], rotateMatrix.m[2][1], rotateMatrix.m[2][2], rotateMatrix.m[2][3],
			rotateMatrix.m[3][0], rotateMatrix.m[3][1], rotateMatrix.m[3][2], rotateMatrix.m[3][3]);
		ImGui::End();
		///
		/// ↑更新処理ここまで
		///

		///
		/// ↓描画処理ここから
		///

		///
		/// ↑描画処理ここまで
		///

		// フレームの終了
		Novice::EndFrame();

		// ESCキーが押されたらループを抜ける
		if (preKeys[DIK_ESCAPE] == 0 && keys[DIK_ESCAPE] != 0) {
			break;
		}
	}

	// ライブラリの終了
	Novice::Finalize();
	return 0;
}

// 加算
Vector3 Add(const Vector3& v1, const Vector3& v2) {
	Vector3 AddResult = {};
	AddResult.x = v1.x + v2.x;
	AddResult.y = v1.y + v2.y;
	AddResult.z = v1.z + v2.z;
	return AddResult;
}
// 減算
Vector3 Subtract(const Vector3& v1, const Vector3& v2) {
	Vector3 SubtractResult = {};
	SubtractResult.x = v1.x - v2.x;
	SubtractResult.y = v1.y - v2.y;
	SubtractResult.z = v1.z - v2.z;
	return SubtractResult;
}
// スカラー倍
Vector3 Multiply(float scalar, const Vector3& v) {
	Vector3 MultiplyResult = {};
	MultiplyResult.x = scalar * v.x;
	MultiplyResult.y = scalar * v.y;
	MultiplyResult.z = scalar * v.z;
	return MultiplyResult;
}

// 行列の加法
Matrix4x4 Add(const Matrix4x4& m1, const Matrix4x4& m2) {
	Matrix4x4 resultAdd = {};
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			resultAdd.m[j][i] = m1.m[j][i] + m2.m[j][i];
		}
	}
	return resultAdd;
}
// 行列の減法
Matrix4x4 Subtract(const Matrix4x4& m1, const Matrix4x4& m2) {
	Matrix4x4 resultSubtract = {};
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			resultSubtract.m[j][i] = m1.m[j][i] - m2.m[j][i];
		}
	}
	return resultSubtract;
}
// 行列の積
Matrix4x4 Multiply(const Matrix4x4& m1, const Matrix4x4& m2) {
	Matrix4x4 resultMultiply = {};
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			resultMultiply.m[i][j] = m1.m[i][0] * m2.m[0][j] + m1.m[i][1] * m2.m[1][j] + m1.m[i][2] * m2.m[2][j] + m1.m[i][3] * m2.m[3][j];
		}
	}
	return resultMultiply;
}

// x軸回転行列
Matrix4x4 MakeRotateXMatrix(float radian) {
	Matrix4x4 resultRotateXMatrix = {};
	resultRotateXMatrix.m[0][0] = 1;
	resultRotateXMatrix.m[1][1] = std::cos(radian);
	resultRotateXMatrix.m[1][2] = std::sin(radian);
	resultRotateXMatrix.m[2][1] = -std::sin(radian);
	resultRotateXMatrix.m[2][2] = std::cos(radian);
	resultRotateXMatrix.m[3][3] = 1;
	return resultRotateXMatrix;
}

// y軸回転行列
Matrix4x4 MakeRotateYMatrix(float radian) {
	Matrix4x4 resultRotateYMatrix = {};
	resultRotateYMatrix.m[0][0] = std::cos(radian);
	resultRotateYMatrix.m[0][2] = -std::sin(radian);
	resultRotateYMatrix.m[1][1] = 1;
	resultRotateYMatrix.m[2][0] = std::sin(radian);
	resultRotateYMatrix.m[2][2] = std::cos(radian);
	resultRotateYMatrix.m[3][3] = 1;
	return resultRotateYMatrix;
}

// z軸回転行列
Matrix4x4 MakeRotateZMatrix(float radian) {
	Matrix4x4 resultRotateZMatrix = {};
	resultRotateZMatrix.m[0][0] = std::cos(radian);
	resultRotateZMatrix.m[0][1] = std::sin(radian);
	resultRotateZMatrix.m[1][0] = -std::sin(radian);
	resultRotateZMatrix.m[1][1] = std::cos(radian);
	resultRotateZMatrix.m[2][2] = 1;
	resultRotateZMatrix.m[3][3] = 1;
	return resultRotateZMatrix;
}
