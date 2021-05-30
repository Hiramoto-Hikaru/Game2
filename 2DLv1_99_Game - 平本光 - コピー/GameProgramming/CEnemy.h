#ifndef CENEMY_H
#define CENEMY_H

#include "CRectangle.h"
#include "CBullet.h"

class CEnemy : public CRectangle {
public:
	int mFx; //X�������̈ړ� -1:�� 0:�ړ����Ȃ� 1:�E�ֈړ�
	int mFy; //Y�������̈ړ� -1:�� 0:�ړ����Ȃ� 1:��ֈړ�
	int mEAniCount;
	int mFireCount;

	CEnemy();

	void Update();
	
	void Render();
    bool Collision(const CRectangle &r);
	void Collision(CRectangle *i, CRectangle *y);
};

#endif
