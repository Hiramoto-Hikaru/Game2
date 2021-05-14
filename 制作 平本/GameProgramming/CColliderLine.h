#ifndef CCOLLIDERLINE_H
#define CCOLLIDERLINE_H

#include"CCollider.h"

class CColliderLine :public CCollider {
public:
	CColliderLine(){}
	//�R���X�g���N�^(�����R���C�_)
	//�e�̓v���C���[
	//CColliderLine(�e�A�e�s��A���_�P�A���_�Q�j
	CColliderLine(CCharacter* parent, CMatrix* matrix, const CVector& v0, const CVector& v1);
	//�����R���C�_�̐ݒ�
	//Set(�e�A�e�s��A���_�P�A���_�Q�j
	void Set(CCharacter* parent, CMatrix* matrix, const CVector& v0, const CVector& v1);
	//�`��
	void Render();
	void ChangePriority();
};
#endif
