#include "CSceneTitle.h"
#include "CKey.h"
extern CTexture Texture2;
void CSceneTitle::Init() {
	//テクスチャファイルを読み込む
	//フォントの設定
	CText::mFont.Load("font.tga");
	Texture2.Load("Image2.tga");
	BGM1.Load("Title.wav");
	//シーンの設定
	mScene = ETITLE;
	BGM1.Play();	
}

//更新処理のオーバーライド
void CSceneTitle::Update() {

	//文字列の描画

	CText::DrawString("BEAR'S", -250, 0, 50, 50);

	CText::DrawString("Push ENTER Key",
		-200, -100, 16, 16);
	if (CKey::Once(VK_RETURN)) {
		//次のシーンはゲーム
		mScene = EGAME;
	}
}
//次のシーンの取得
CScene::EScene CSceneTitle::GetNextScene() {
	return mScene;
}
