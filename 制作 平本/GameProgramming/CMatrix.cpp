#include"CMatrix.h"
//�W�����o�͗p�̃C���N���[�h
#include <stdio.h>
//�~����M_PI��L���ɂ���
#define _USE_MATH_DEFINES
//���w�֐��̃C���N���[�h
#include<math.h>

//�f�t�H���g�R���X�g���N�^
CMatrix::CMatrix() {
	//�^��Identity�̌Ăяo��
	Identity();
}
//�g��k���s��̍쐬
	//Scale(�{��X�A�{��Y�A�{��Z,�j
CMatrix CMatrix::Scale(float sx, float sy, float sz) {
	
	/*sx,sy,sz��ǉ����邱�Ƃ�X���AY���AZ���̊g��A�k����
	�ȒP�ɂł���
	*/
	mM[0][0] = sx; mM[1][1] = sy; mM[2][2] = sz;
	//�������Ƃ����Ȃ�
  /*mM[0][0] = sx; mM[0][1] = 0; mM[0][2] = 0; mM[0][3] = 0;
	mM[1][0] = 0; mM[1][1] = sy; mM[1][2] = 0; mM[1][3] = 0;
	mM[2][0] = 0; mM[2][1] = 0; mM[2][2] = sz; mM[2][3] = 0;
	mM[3][0] = 0; mM[3][1] = 0; mM[3][2] = 0; mM[3][3] = 1;*/
	//���̍s���Ԃ�
	return* this;
}
//�P�ʍs��̍쐬
CMatrix CMatrix::Identity() {
	

mM[0][0] = 1; mM[0][1] = 0; mM[0][2] = 0; mM[0][3] = 0;
mM[1][0] = 0; mM[1][1] = 1; mM[1][2] = 0; mM[1][3] = 0;
mM[2][0] = 0; mM[2][1] = 0; mM[2][2] = 1; mM[2][3] = 0;
mM[3][0] = 0; mM[3][1] = 0; mM[3][2] = 0; mM[3][3] = 1;
//���̍s���Ԃ�
	return*this;
}
void CMatrix::Print() {
	
	//4�̕���������	
	printf("%10f%10f%10f%10f\n",
		mM[0][0], mM[0][1], mM[0][2], mM[0][3]);
	printf("%10f%10f%10f%10f\n",
		mM[1][0], mM[1][1], mM[1][2], mM[1][3]);
	printf("%10f%10f%10f%10f\n",
		mM[2][0], mM[2][1], mM[2][2], mM[2][3]);
	printf("%10f%10f%10f%10f\n",
		mM[3][0], mM[3][1], mM[3][2], mM[3][3]);
}
//��]�s��iY���j�̍쐬
//RptateY(�p�x�j
CMatrix CMatrix::RotateY(float degree) {
	//�p�x���烉�W�A�������o��
	//M_PI=�~�����̒萔
	/*rad�����W�A���i�~����Ŕ��a�Ɠ��������̌�
	����邽�߂̂Q�{�̐��ō����p�x�j*/
	float rad = degree / 180.0f * M_PI;
	//�P�ʍs��ɂ���
	Identity();
	//Y���ŉ�]����s��̐ݒ�
	//�s���sy�̂Ƃ��낪�P�ɂȂ�Asx,sz��cos�ɂ��ĉ�]
	/*cos 0 -sin 0
	  0   1   0  0
	  sin 0  cos 0
	  0   0   0  1*/
	mM[0][0] = mM[2][2] = cosf(rad);//cos��
	mM[0][2] = -sinf(rad);//-sin��
	mM[2][0] = -mM[0][2];//sin��
	//�s���Ԃ�
	return *this;
}
CMatrix CMatrix::RotateZ(float degree) {
	//�p�x���烉�W�A�������o��
	//M_PI=�~�����̒萔
	/*rad�����W�A���i�~����Ŕ��a�Ɠ��������̌�
	����邽�߂̂Q�{�̐��ō����p�x�j*/
	//degree=�x��
	//180.0f=180��
	float rad = degree / 180.0f * M_PI;
	//�P�ʍs��ɂ���
	Identity();
	//Z���ŉ�]����s��̐ݒ�
	//�s���sz�̂Ƃ��낪�P�ɂȂ�Asx,sy��cos�ɂ��ĉ�]
	/*cos 0 -sin 0
	  sin cos 0  0
	   0  0   1  0
	   0  0   0  1*/
	mM[0][0] = mM[1][1] = cosf(rad);//cos��
	mM[0][1] = sinf(rad);//sin��
	mM[1][0] = -mM[0][1];//-sin��
	//�s���Ԃ�
	return *this;
}
CMatrix CMatrix::RotateX(float degree) {
	//�p�x���烉�W�A�������o��
	//M_PI=�~�����̒萔
	/*rad�����W�A���i�~����Ŕ��a�Ɠ��������̌�
	����邽�߂̂Q�{�̐��ō����p�x�j*/
	float rad = degree / 180.0f * M_PI;
	//�P�ʍs��ɂ���
	Identity();
	//X���ŉ�]����s��̐ݒ�
	//�s���sx�̂Ƃ��낪�P�ɂȂ�Asy,sz��cos�ɂ��ĉ�]
	/*1   0   0  0
	  0  cos sin 0
	  0 -sin cos 0
	  0   0   0  1*/
	mM[1][1] = mM[2][2] = cosf(rad);//cos��
	mM[1][2] = sinf(rad);//sin��
	mM[2][1] = -mM[1][2];//-sin��
	//�s���Ԃ�
	return *this;
}
CMatrix CMatrix::Translate(float mx, float my, float mz) {
	//3D�̍��W���ړ�������
	Identity();
	mM[3][0] = mx,
	mM[3][1] = my,
	mM[3][2] = mz;
	//���̍s���Ԃ�
	return*this;
}
//*���Z�q�̃I�[�o�[���[�h
//CMatrix*CMatrix�̉��Z���ʂ�������
CMatrix CMatrix::operator*(const CMatrix& m){
	
	CMatrix t;
	//��]�A�g��k���A�ړ��̍s����������邱�ƂŁA���l��ς����Ƃ��ȒP�ɂȂ�
	//�g���Ă���s�񂪂��ׂĂ�M[4][4]�Ȃ̂ō������\
	t.mM[0][0] = mM[0][0] * m.mM[0][0] + mM[0][1] * m.mM[1][0] + mM[0][2] * m.mM[2][0] + mM[0][3] * m.mM[3][0];
	t.mM[0][1] = mM[0][0] * m.mM[0][1] + mM[0][1] * m.mM[1][1] + mM[0][2] * m.mM[2][1] + mM[0][3] * m.mM[3][1];
	t.mM[0][2] = mM[0][0] * m.mM[0][2] + mM[0][1] * m.mM[1][2] + mM[0][2] * m.mM[2][2] + mM[0][3] * m.mM[3][2];
	t.mM[0][3] = mM[0][0] * m.mM[0][3] + mM[0][1] * m.mM[1][3] + mM[0][2] * m.mM[2][3] + mM[0][3] * m.mM[3][3];
	t.mM[1][0] = mM[1][0] * m.mM[0][0] + mM[1][1] * m.mM[1][0] + mM[1][2] * m.mM[2][0] + mM[1][3] * m.mM[3][0];
	t.mM[1][1] = mM[1][0] * m.mM[0][1] + mM[1][1] * m.mM[1][1] + mM[1][2] * m.mM[2][1] + mM[1][3] * m.mM[3][1];
	t.mM[1][2] = mM[1][0] * m.mM[0][2] + mM[1][1] * m.mM[1][2] + mM[1][2] * m.mM[2][2] + mM[1][3] * m.mM[3][2];
	t.mM[1][3] = mM[1][0] * m.mM[0][3] + mM[1][1] * m.mM[1][3] + mM[1][2] * m.mM[2][3] + mM[1][3] * m.mM[3][3];
	t.mM[2][0] = mM[2][0] * m.mM[0][0] + mM[2][1] * m.mM[1][0] + mM[2][2] * m.mM[2][0] + mM[2][3] * m.mM[3][0];
	t.mM[2][1] = mM[2][0] * m.mM[0][1] + mM[2][1] * m.mM[1][1] + mM[2][2] * m.mM[2][1] + mM[2][3] * m.mM[3][1];
	t.mM[2][2] = mM[2][0] * m.mM[0][2] + mM[2][1] * m.mM[1][2] + mM[2][2] * m.mM[2][2] + mM[2][3] * m.mM[3][2];
	t.mM[2][3] = mM[2][0] * m.mM[0][3] + mM[2][1] * m.mM[1][3] + mM[2][2] * m.mM[2][3] + mM[2][3] * m.mM[3][3];
	t.mM[3][0] = mM[3][0] * m.mM[0][0] + mM[3][1] * m.mM[1][0] + mM[3][2] * m.mM[2][0] + mM[3][3] * m.mM[3][0];
	t.mM[3][1] = mM[3][0] * m.mM[0][1] + mM[3][1] * m.mM[1][1] + mM[3][2] * m.mM[2][1] + mM[3][3] * m.mM[3][1];
	t.mM[3][2] = mM[3][0] * m.mM[0][2] + mM[3][1] * m.mM[1][2] + mM[3][2] * m.mM[2][2] + mM[3][3] * m.mM[3][2];
	t.mM[3][3] = mM[3][0] * m.mM[0][3] + mM[3][1] * m.mM[1][3] + mM[3][2] * m.mM[2][3] + mM[3][3] * m.mM[3][3];

	return t;
}