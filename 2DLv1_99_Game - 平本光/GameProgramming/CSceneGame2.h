#ifndef CSCENEGAME2_H
#define CSCENEGAME2_H
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
class CSceneGame2 : public CScene {
public:
	int ZankiCount;

	static int Coin;
	//�����������̃I�[�o�[���C�h
	void Init();
	//�X�V�����̃I�[�o�[���C�h
	void Update();
	CSound Bgm;
	CSound Se;
	
	CScene::EScene GetNextScene();
	//�f�X�g���N�^�̐錾
	~CSceneGame2();


};

#endif
