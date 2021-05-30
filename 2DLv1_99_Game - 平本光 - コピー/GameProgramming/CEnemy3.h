#ifndef CENEMY3_H
#define CENEMY3_H

#include "CRectangle.h"
#include "CBullet.h"

class CEnemy3 : public CRectangle {
public:
	int mFx; //X軸方向の移動 -1:左 0:移動しない 1:右へ移動
	int mFy; //Y軸方向の移動 -1:下 0:移動しない 1:上へ移動
	int mEAniCount;
	int mFireCount;
	int mVj;//ジャンプ用速度
	int mJump;
	CEnemy3();

	void Update();

	void Render();
	bool Collision(const CRectangle& rrr);
	void Collision(CRectangle* iii, CRectangle* yyy);
};

#endif