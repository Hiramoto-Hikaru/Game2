#ifndef CSCENEGAME_H
#define CSCENEGAME_H
#include "CScene.h"
#include "CBullet.h"
#include"CPlayer.h"
#include"CEnemy.h"
#include"CKey.h"
#include "CRectangle.h"
#include"CText.h"
#include"CSound.h"

/*
�Q�[���̃V�[��
*/
//CScene�N���X���p������
class CSceneGame : public CScene {



public:
	int ZankiCount;
	
	static int SCore ;//static���\�b�h���g�p���ăN���X�O�ł����p
	static int Life;
	static int Treasure ;
	static int BossLife;//�{�X�̗̑�
	static int mEBossAniCount;//�{�X�̃A�j���[�V����
	static int ItemPoint;
	static int mZanki;
	//�����������̃I�[�o�[���C�h
	void Init();
	//�X�V�����̃I�[�o�[���C�h
	void Update();
	//CSound�N���X�̃C���X�^���X�쐬	
	CSound Bgm;
    CSound Se;
	CSound Se2;
	CSound Se3;
	CScene::EScene GetNextScene();
	//�f�X�g���N�^�̐錾
	~CSceneGame();

	
	
};

#endif
