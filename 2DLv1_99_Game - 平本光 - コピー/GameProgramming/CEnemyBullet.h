#ifndef CENEMYBULLET_H
#define CENEMYBULLET_H

#include "CRectangle.h"

/*
CBullet
弾クラス
CRectangleクラスを継承する
親：CRectangleクラス
子：CBulletクラス
*/
class CEnemyBullet : public CRectangle {
public:
	int mFx, mFy;	//移動量

	//デフォルトコンストラクタ
	CEnemyBullet();
	//更新処理
	void Update();

	//描画処理
	void Render();

	void Collision(CRectangle* ii, CRectangle* yy);

};

#endif

