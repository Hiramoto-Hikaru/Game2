#ifndef CSCENEGAME2_H
#define CSCENEGAME2_H
#include "CScene.h"
#include "CBullet.h"
#include"CPlayer.h"
#include"CEnemy.h"
#include"CKey.h"
#include "CRectangle.h"
#include"CText.h"

#include"CSound.h"

/*
ゲームのシーン
*/
//CSceneクラスを継承する
class CSceneGame2 : public CScene {
public:
	int ZankiCount;

	static int Coin;
	//初期化処理のオーバーライド
	void Init();
	//更新処理のオーバーライド
	void Update();
	CSound Bgm;
	CSound Se;
	
	CScene::EScene GetNextScene();
	//デストラクタの宣言
	~CSceneGame2();


};

#endif
