#ifndef CMATRIX_H
#define CMATRIX_H
/*
�}�g���N�X�N���X
�S�s�S��̃f�[�^������*/
class CMatrix {
public:
		//�S*�S�̃f�[�^��ݒ�
		float mM[4][4];
	//�\���m�F�p
	void Print();
	//�f�t�H���g�R���X�g���N�^
	CMatrix();
	//�P�ʍs��̍쐬
	CMatrix Identity();
	//�g��k���s��̍쐬
	//Scale(�{��X�A�{��Y�A�{��Z,�j
	CMatrix CMatrix::Scale(float sx, float sy, float sz);
	//��]�s��iY���j�̍쐬
	//RotateY�i�p�x)
	
	CMatrix RotateY(float degree);
	//��]�s��iZ���j�̍쐬
	CMatrix RotateZ(float degree);
	//��]�s��iX���j�̍쐬
	CMatrix RotateX(float degree);
	//�ړ��s��̍쐬
	//Translate(�ړ���X�A�ړ���Y,�ړ���Z�j
	CMatrix Translate(float mx, float my, float mZ);
	//*���Z�q�̃I�[�o�[���[�h
	//CMatrix*CMatrix�̉��Z���ʂ�������
	CMatrix operator*(const CMatrix& m);
	
};
#endif