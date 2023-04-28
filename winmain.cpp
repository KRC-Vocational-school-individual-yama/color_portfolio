#include "DxLib.h"
#include<stdio.h>
#include <string>
#include<math.h>
#include<direct.h>
#include"squarecollition.h"

namespace {
	enum colors {
		Red,
		Green,
		Blue,
	};

	int mousex = 0;
	int mousey = 0;

	int x[3]={};
	int y[3]={};
	int num[3] = {};
	bool flug[3];
	int colorvalue[3] = {};
}

//最初に1回呼ばれる処理
void Init(){
	if (_mkdir("この中にあるよ！") == 0) {
		//FileError
	}

	for (int i = 0; i < 3; i++) {
		x[i] = 300;
		y[i] = 250+i*120;
		num[i] = 50;
		flug[i] = false;

		colorvalue[i] = 255*  num[i]/  100;
	}
	
}
//毎フレーム呼ばれる処理
void Update() {
	GetMousePoint(&mousex, &mousey);
	if (GetMouseInput() & MOUSE_INPUT_LEFT) {

		for (int i = 0; i < 3; i++) {
			
			
			if (SquareCollition(mousex, mousey, mousex + 1, mousey + 1, x[i], y[i], x[i] + 200, y[i] + 100)) {
				switch (i)
				{
				case Red:
					if (flug[Green] == false && flug[Blue] == false) {
						flug[Red] = true;
					}
					break;
				case Green:
					if (flug[Red] == false && flug[Blue] == false) {
						flug[Green] = true;
					}
					break;
				case Blue:
					if (flug[Green] == false && flug[Red] == false) {
						flug[Blue] = true;
					}
					break;
				default:
					break;
				}
	//			flug[i] = true;
			}
			
			 

			if (flug[i] == true) {
				x[i] = mousex - 100;
				//y[i] = mousey;
			}
			if (x[i] + 100 * 2 > 800) {
				x[i] = 800 - 100 * 2;
			}
			else
				if (x[i] <= 0) {
					x[i] = 0;
				}
			/*
			if (y[i] != 250) {
				y[i] = 250+i*120;
			}
			*/
			num[i] = ((double)x[i] / 600) * 100;
		}


	}

	if ((GetMouseInput() & MOUSE_INPUT_LEFT) == 0) {
		for (int i = 0; i < 3; i++) {
		flug[i] = false;
		}

	}

}
void Draw() {
	SetDrawBright((255 * num[Red]) / 100, (255 * num[Green]) / 100, (255 * num[Blue]) / 100);
	DrawBox(0, 0, 800, 600, GetColor(255, 255, 255), true);

	if (ProcessMessage() == 0) {
		SaveDrawScreenToPNG(0, 0, 800, 600, "この中にあるよ！/colorimg.png");
	}

	SetDrawBright(255, 255, 255);

	for (int i = 0; i < 3; i++) {
		unsigned int color[3] = {};
		switch (i)
		{
		case Red:
			color[Red] = 255;
			break;
		case Green:
			color[Green] = 200;
			break;
		case Blue:
			color[Blue] = 200;
			break;
		default:
			color[i] = 100;
			break;
		}
		DrawBox(x[i], y[i], x[i] + 100 * 2, y[i] + 100, GetColor(color[Red], color[Green], color[Blue]), true);
		DrawBox(x[i], y[i], x[i] + 100 * 2, y[i] + 100, GetColor(150, 150, 150), false);


		colorvalue[i] = 255 * num[i] / 100;
	}

	std::string words[3] = {};
	words[Red]   = "Red  :" + std::to_string(colorvalue[Red]) + "\n";
	words[Green] = "Green:" + std::to_string(colorvalue[Green]) + "\n";
	words[Blue]  = "Blue :" + std::to_string(colorvalue[Blue]) + "\n";
	for (int i = 0; i < 3; i++) {
		printfDx(words[i].c_str());
	}
	if (ProcessMessage() == 0) {
		FILE* fp;
		fopen_s(&fp, "この中にあるよ！/color_value.txt", "w");
		for (int i = 0; i < 3; i++) {
			fprintf(fp, words[i].c_str());
		}


		fclose(fp);

	}
}

void Delete(){
	
}
// プログラムは WinMain から始まります
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	SetOutApplicationLogValidFlag(false);
	ChangeWindowMode(TRUE);	//ウィンドウモードにする
	SetGraphMode(800, 600, 32);	//ウィンドウサイズを設定する
	if (DxLib_Init() == -1)		// ＤＸライブラリ初期化処理
	{
		return -1;			// エラーが起きたら直ちに終了
	}
	SetDrawScreen(DX_SCREEN_BACK);	//裏画面を描画対象へ

	Init();//初期化
	//メイン処理
	while (ProcessMessage() == 0 && CheckHitKey(KEY_INPUT_ESCAPE) == 0) {
		clsDx();
		Update();//更新処理
		Draw();//描画処理

		ScreenFlip();		//裏画面と表画面の入替
		ClearDrawScreen();	//裏画面の描画を全て消去
	}
	Delete();
	DxLib_End();			// ＤＸライブラリ使用の終了処理
	return 0;				// ソフトの終了 
}