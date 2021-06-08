#include "glut.h"
#include "CKey.h"
#include "CRectangle.h"
#include "CBullet.h"
#include "CPlayer.h"
#include "CEnemy.h"
#include "CText.h"
#include "CSceneManager.h"

// テクスチャクラスのインクルード
#include "CTexture.h"
CTexture Texture; //マップの画像
CTexture Texture2;
CTexture Texture3;
CTexture Texture4;
CTexture Texture5;
CTexture Texture6;
//シーンマネージャのインスタンス
CSceneManager SceneManager;

//Init関数
//最初に一度だけ呼ばれる関数
void Init() {
	Texture.Load("Image.tga");
    Texture2.Load("Image2.tga");
	Texture3.Load("image3.Tga");
	Texture4.Load("image4.tga");
	Texture5.Load("imagesss.tga");
	Texture6.Load("exp.tga");
	//シーンマネージャの初期化
	SceneManager.Init();
	
}
//Update関数
//プログラムの実行中、繰り返し呼ばれる関数
void Update() {
	//シーンマネージャの更新
	SceneManager.Update();
	
}
