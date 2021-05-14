#ifndef CTRIANGLE _H
#define CTRIANGLE _H
#include"CVector.h"

/*
�O�p�`�N���X
*/
class CTriangle {
public:
	int mMaterialIdx;//�}�e���A���ԍ�
	CVector mV[3];//���_���W[1�`3]
	CVector mN[3];//�@���x�N�g��
	CVector mUv[3];//�e�N�X�`���}�b�s���O
	//���_���W�ݒ�
	//SetVertex�i���_�P�C���_�Q�C���_�R�j
	void SetVertex(const CVector& v0, const CVector& v1, const CVector& v2);
	//�@���ݒ�
	//SetNormal�i�@���x�N�g��1�A �@���x�N�g���Q�C�@���x�N�g��3�j
	void SetNormal(const CVector& n); //�����@��
    void SetNormal(const CVector& v0, CVector const& v1, CVector const& v2);
	//�`��
	void Render();
	void Render(const CMatrix& m);
};
#endif