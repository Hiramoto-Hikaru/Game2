#include"CSceneclear.h"
#include"CText.h"
#include"CScene.h"

void CSceneClear::Init() {
	//テクスチャファイルを読み込む
	//フォントの設定
	CText::mFont.Load("font.tga");
	//シーンの設定
	mScene = ECLEAR;
}

//更新処理のオーバーライド
void CSceneClear::Update() {
	//文字列の描画
	CText::DrawString("GAMECLEAR", -200, 0, 50, 50);
	CText::DrawString("Push ENTER Key",-200, -100, 16, 16);
	if (CKey::Once(VK_RETURN)) {
		//次のシーンはタイトル
		mScene = ETITLE;
	}
}
//次のシーンの取得
CScene::EScene CSceneClear::GetNextScene() {
	return mScene;
}