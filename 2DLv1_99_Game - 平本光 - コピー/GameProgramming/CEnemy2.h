#ifndef CENEMY2_H
#define CENEMY2_H
#include"CRectangle.h"
#include "CBullet.h"
class CEnemy2 :public CRectangle {
public:
	int mFx; //X�������̈ړ� -1:�� 0:�ړ����Ȃ� 1:�E�ֈړ�
	int mFy; //Y�������̈ړ� -1:�� 0:�ړ����Ȃ� 1:��ֈړ�
	CEnemy2();
	void Update();
	
//	bool Collision(const CRectangle& vr);
    void Render();
	void Collision(CRectangle* i, CRectangle* y);
};
#endif