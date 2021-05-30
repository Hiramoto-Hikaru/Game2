#ifndef CSCENEGAME3_H
#define CSCENEGAME3_H

#include"CKey.h"
#include "CRectangle.h"
#include"CText.h"

#include"CSound.h"

/*
ゲームのシーン
*/
//CSceneクラスを継承する
class CSceneGame3 : public CScene {
public:
	static int Coin;
	//初期化処理のオーバーライド
	void Init();
	//更新処理のオーバーライド
	void Update();
	CSound Bgm;
	CSound Se;
	CScene::EScene GetNextScene();
	//デストラクタの宣言
	~CSceneGame3();


};

#endif

