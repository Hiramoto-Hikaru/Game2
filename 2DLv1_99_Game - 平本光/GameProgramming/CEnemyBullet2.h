#ifndef CENEMYBULLET2_H
#define CENEMYBULLET2_H

#include "CRectangle.h"

/*
CBullet
�e�N���X
CRectangle�N���X���p������
�e�FCRectangle�N���X
�q�FCBullet�N���X
*/
class CEnemyBullet2 : public CRectangle {
public:
	int mFx, mFy;	//�ړ���
	int mbulletcount;
	//�f�t�H���g�R���X�g���N�^
	CEnemyBullet2();
	//�X�V����
	void Update();

	//�`�揈��
	void Render();

	void Collision(CRectangle* iii, CRectangle* yyy);

};

#endif

