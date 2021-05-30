#ifndef CSCENECLEAR_H
#define CSCENECLEAR_H

#include"CScene.h"
#include"CText.h"
class CSceneClear : public CScene {
public:
	//初期化処理のオーバーライド
	void Init();
	//更新処理のオーバーライド
	void Update();
	//次のシーンの取得
	EScene GetNextScene();
};






#endif
