#ifndef CENEMYBULLET2_H
#define CENEMYBULLET2_H

#include "CRectangle.h"

/*
CBullet
弾クラス
CRectangleクラスを継承する
親：CRectangleクラス
子：CBulletクラス
*/
class CEnemyBullet2 : public CRectangle {
public:
	int mFx, mFy;	//移動量
	int mbulletcount;
	//デフォルトコンストラクタ
	CEnemyBullet2();
	//更新処理
	void Update();

	//描画処理
	void Render();

	void Collision(CRectangle* iii, CRectangle* yyy);

};

#endif

