#ifndef CENEMY4_H
#define CENEMY4_H
#include"CRectangle.h"

class CEnemy4 :public CRectangle {
public:
	int mFx; //X�������̈ړ� -1:�� 0:�ړ����Ȃ� 1:�E�ֈړ�
	int mFy; //Y�������̈ړ� -1:�� 0:�ړ����Ȃ� 1:��ֈړ�
	int mEAniCount;
	int mCount;
	int mVj;//�W�����v�p���x
	int mMoveCount;

	CEnemy4();

	void Update();

	void Render();

	void Collision(CRectangle* iii, CRectangle* yyy);
};
#endif