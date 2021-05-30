#ifndef CENEMYBULLET_H
#define CENEMYBULLET_H

#include "CRectangle.h"

/*
CBullet
�e�N���X
CRectangle�N���X���p������
�e�FCRectangle�N���X
�q�FCBullet�N���X
*/
class CEnemyBullet : public CRectangle {
public:
	int mFx, mFy;	//�ړ���

	//�f�t�H���g�R���X�g���N�^
	CEnemyBullet();
	//�X�V����
	void Update();

	//�`�揈��
	void Render();

	void Collision(CRectangle* ii, CRectangle* yy);

};

#endif

