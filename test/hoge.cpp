#include <cstdint>

#include <DxLibrary/DxLib.h>

#include <StewLib/Math/vec2d.hpp>
#include <CCS/StewDxEngine/include/graph.hpp>

// プログラムは WinMain から始まります
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	//ウィンドウモードに設定
	DxLib::ChangeWindowMode(true);

	//ウィンドウサイズを指定
	DxLib::SetGraphMode(1024, 768, 16);
	if (DxLib::DxLib_Init() == -1)		// ＤＸライブラリ初期化処理
	{
		return -1;			// エラーが起きたら直ちに終了
	}

	const auto path = "C:\\Users\\shnsk\\152_20211207014702.png";

	StewDxEngine::Graph graph = {path};
	DxLib::SetDrawScreen(DX_SCREEN_BACK);

	int count = 0;
	int increment = 1;
	while(DxLib::ProcessMessage() == 0 && DxLib::CheckHitKey(KEY_INPUT_ESCAPE) == 0)
	{
		// 画面を初期化する
		DxLib::ClearDrawScreen();

		const auto size = graph.get_size();
		DxLib::printfDx("size: (%d, %d)\n", size.x, size.y);
		graph.draw<StewDxEngine::Arg::Center>({ .pos = {512, 384}, .extend_rate = StewDxEngine::Vec2D<int>{1, 1} * count / 60.0 });

		//裏画面の内容を表画面に反映させる
		DxLib::ScreenFlip();

		if(count == 60 || count == -1) increment *= -1;
		count += increment;
	}
	

	DxLib::DxLib_End();				// ＤＸライブラリ使用の終了処理

	return 0;				// ソフトの終了 
}

// #include "C:\msys64\home\shnsk\StewProgramming_MSYS2\StewLib\Math\vec2d.hpp"

// #include <type_traits>

// template<typename T>
// using vec2d = StewLib::Math::Vec2D<T>;

// int main()
// {

// 	vec2d<int> a{1, 0};
// 	vec2d<double> b{1, 0};
// 	auto c = a * b;
// 	static_assert(std::is_same_v<decltype(c), vec2d<double>>);
// }