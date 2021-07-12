#ifndef CCAMERA_H
#define CCAMERA_H
#include"CVector.h"
#include"CTransform.h"
/*�J�����N���X�i�v���C���[�̎��_�ɑ΂��鏈���j*/
class CCamera {
public:
	//���_
	CVector mEye;
	//�����_
	CVector mCenter;
	//�����
	CVector mUp;
	CVector mPosition;
	//�J�����̐ݒ�
	//Set(���_�A�����_(���������j�A������j
	void Set(const CVector& eye, const CVector& center,
		const CVector& up);
		void Update();
	//�J�����K�p
	void Render();
};
//�J�����̊O���Q��
extern CCamera Camera;
#endif
