#ifndef CBOSS_H
#define CBOSS_H
#include "CRectangle.h"
#include "CBullet.h"


class CBoss : public CRectangle {
public:
	
	int mFx, mFy;
	int mFireCount;
	static int bosscount;
	int mJump;//�W�����v�t���O
	int mVj;//�W�����v�p���x
	int BossAniCount;
	
	CBoss();

	void Update();

	void Render();

	void Collision(CRectangle* i, CRectangle* y);


};



#endif
