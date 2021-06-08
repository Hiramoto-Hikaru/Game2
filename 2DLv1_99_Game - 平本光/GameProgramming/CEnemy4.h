#ifndef CENEMY4_H
#define CENEMY4_H
#include"CRectangle.h"

class CEnemy4 :public CRectangle {
public:
	int mFx; //X軸方向の移動 -1:左 0:移動しない 1:右へ移動
	int mFy; //Y軸方向の移動 -1:下 0:移動しない 1:上へ移動
	int mEAniCount;
	int mCount;
	int mVj;//ジャンプ用速度
	int mMoveCount;

	CEnemy4();

	void Update();

	void Render();

	void Collision(CRectangle* iii, CRectangle* yyy);
};
#endif