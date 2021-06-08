#ifndef CSCENEGAME_H
#define CSCENEGAME_H
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
class CSceneGame : public CScene {



public:
	int ZankiCount;
	
	static int SCore ;//staticメソッドを使用してクラス外でも利用
	static int Life;
	static int Treasure ;
	static int BossLife;//ボスの体力
	static int mEBossAniCount;//ボスのアニメーション
	static int ItemPoint;
	static int mZanki;
	//初期化処理のオーバーライド
	void Init();
	//更新処理のオーバーライド
	void Update();
	//CSoundクラスのインスタンス作成	
	CSound Bgm;
	
    CSound Se;
	CSound Se2;
	CSound Se3;

	CScene::EScene GetNextScene();
	//デストラクタの宣言
	~CSceneGame();

	
	
};

#endif
