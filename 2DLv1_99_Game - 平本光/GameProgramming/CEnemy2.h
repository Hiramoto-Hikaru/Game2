#ifndef CENEMY2_H
#define CENEMY2_H
#include"CRectangle.h"
#include "CBullet.h"
class CEnemy2 :public CRectangle {
public:
	int mFx; //X²•ûŒü‚ÌˆÚ“® -1:¶ 0:ˆÚ“®‚µ‚È‚¢ 1:‰E‚ÖˆÚ“®
	int mFy; //Y²•ûŒü‚ÌˆÚ“® -1:‰º 0:ˆÚ“®‚µ‚È‚¢ 1:ã‚ÖˆÚ“®
	CEnemy2();
	void Update();
	
//	bool Collision(const CRectangle& vr);
    void Render();
	void Collision(CRectangle* i, CRectangle* y);
};
#endif