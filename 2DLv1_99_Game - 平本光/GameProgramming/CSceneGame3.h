#ifndef CSCENEGAME3_H
#define CSCENEGAME3_H

#include"CKey.h"
#include "CRectangle.h"
#include"CText.h"

#include"CSound.h"

/*
�Q�[���̃V�[��
*/
//CScene�N���X���p������
class CSceneGame3 : public CScene {
public:
	static int Coin;
	//�����������̃I�[�o�[���C�h
	void Init();
	//�X�V�����̃I�[�o�[���C�h
	void Update();
	CSound Bgm;
	CSound Se;
	
	CScene::EScene GetNextScene();
	//�f�X�g���N�^�̐錾
	~CSceneGame3();


};

#endif

