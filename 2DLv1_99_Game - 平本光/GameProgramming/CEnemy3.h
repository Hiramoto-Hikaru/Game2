#ifndef CENEMY3_H
#define CENEMY3_H

#include "CRectangle.h"
#include "CBullet.h"

class CEnemy3 : public CRectangle {
public:
	int mFx; //X�������̈ړ� -1:�� 0:�ړ����Ȃ� 1:�E�ֈړ�
	int mFy; //Y�������̈ړ� -1:�� 0:�ړ����Ȃ� 1:��ֈړ�
	int mEAniCount;
	int mFireCount;
	int mVj;//�W�����v�p���x
	int mJump;
	CEnemy3();

	void Update();

	void Render();
	bool Collision(const CRectangle& rrr);
	void Collision(CRectangle* iii, CRectangle* yyy);
};

#endif