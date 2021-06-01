#ifndef CSCENEGAME_H
#define CSCENEGAME_H
#include "CScene.h"
#include"CVector.h"
#include"CModel.h"
#include"CCharacter.h"
#include "CPlayer.h"
#include"CEnemy.h"
#include"CCollisionManager.h"

#include"CBillBoard.h"
#include"CCamera.h"
#include"CColliderTriangle.h"
#include"CColliderMesh.h"
/*
�Q�[���̃V�[��
*/

class CSceneGame : public CScene {
public:
	CVector mEye; //�J�������_�̒ǉ�
	CModel mModel;//CModel�N���X�̃C���X�^���X�ϐ�
	CModel mBackGround;//�w�i���f��
	CMatrix mMatrixRotate;//��]�s��
	CMatrix mMatrix;//�����s��
	CMatrix mBackGroundMatrix;
	CPlayer mPlayer;
	
	//���f������R���C�_����
	CColliderMesh mColliderMesh;

	//�G���f���̃C���X�^���X�i�N���X�Ɠ������͎̂g���Ȃ��j
	CModel mModelC5;
	CModel mModelc5;
	CModel mModelW;
	//�O�p�R���C�_�̍쐬
	CColliderTriangle mColliderTriangle;
	CColliderTriangle mColliderTriangle2;

	

	//�����������̃I�[�o�[���C�h

	void Init();
	
	//�X�V�����̃I�[�o�[���C�h
	void Update();
};

#endif