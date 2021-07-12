#ifndef CVECTOR_H
#define CVECTOR_H
#include"CMatrix.h"

/*
�x�N�g���N���X
�x�N�g���f�[�^�̈���*/

class CVector {
public:


	//+���Z�q�̃I-�o�[���[�h
	//CVector+CVector �̉��Z���ʂ�������
	CVector operator+(const CVector& v);

//�f�t�H���g�R���X�g���N�^
    CVector();
	CVector(float x, float y, float z);//�����R���X�g���N�^

	//����
	//Dot(�x�N�g���j
	float Dot(const CVector& v);

	//�O��
	//Cross(�x�N�g���j
	CVector Cross(const CVector& v);
	//*���Z�q�̃I�[�o�[���[�h
	//CVector*float�̉��Z���ʂ�������	
	CVector operator*(const float& f);

	//���K��
	//�傫���P�̃x�N�g����������
	CVector Normalize();

//�R���X�g���N�^
//CVector(X���W�AY���W�AZ���W�j

	//�RD�e���ł̒l��ݒ�
	float mX, mY, mZ;

	void Set(float x, float y, float z);
	/*
	x;x���W�̒l����
	y�Gy���W�̒l����
	z�Gz���W�̒l����*/
	//CVector*CMatrix�̌��ʂ�CVector�ŕԂ�
	CVector operator*(const CMatrix &m);
	
	//���Z�q�̃I�[�o�[���[�h
	//CVector-Cvector�̉��Z���ʂ�������
	CVector operator-(const CVector& v);
	//�x�N�g���̒�����������
	float Length();

};

#endif