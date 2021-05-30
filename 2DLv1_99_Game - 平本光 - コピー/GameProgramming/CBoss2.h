#ifndef CBOSS2_H
#define CBOSS2_H
#include "CRectangle.h"
#include "CBullet.h"


class CBoss2 : public CRectangle {
public:

	int mFx, mFy;
	int mFireCount;
	int bosscount;
	int mJump;//ジャンプフラグ
	int mVj;//ジャンプ用速度

	CBoss2();

	void Update();

	void Render();

	void Collision(CRectangle* i, CRectangle* y);


};



#endif

