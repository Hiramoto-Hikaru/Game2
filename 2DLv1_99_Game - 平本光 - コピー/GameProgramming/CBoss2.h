#ifndef CBOSS2_H
#define CBOSS2_H
#include "CRectangle.h"
#include "CBullet.h"


class CBoss2 : public CRectangle {
public:

	int mFx, mFy;
	int mFireCount;
	int bosscount;
	int mJump;//�W�����v�t���O
	int mVj;//�W�����v�p���x

	CBoss2();

	void Update();

	void Render();

	void Collision(CRectangle* i, CRectangle* y);


};



#endif

