#ifndef CTRANSFORM_H
#define CTRANSFORM_H
#include"CVector.h"

class CTransform {
public:
	//CMatrix�N���X�ɂ�����̂𗘗p
	CVector mPosition;//�ʒu
	CVector mRotation;//��]
	CVector mRotation2;//��]
	CVector mScale;//�g��k��
	CMatrix mMatrixTranslate;//���s�ړ��s��
	CMatrix mMatrixRotate;//��]�s��
	CMatrix mMatrixRotate2;
	CMatrix mMatrixScale;//�g��k���s��G

	CMatrix mMatrix;//�����s��
	//�s��X�V����
	void Update();

};
#endif
