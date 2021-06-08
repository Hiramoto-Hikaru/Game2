#include "CSceneManager.h"
#include "CSceneGame.h"
#include "CSceneTitle.h"
#include"CSceneClear.h"
#include"CSceneGame2.h"
#include"CSceneGame3.h"
//�R���X�g���N�^
CSceneManager::CSceneManager()
: mpScene(0)
{}
//�f�X�g���N�^�i�폜�����Ƃ��Ɏ��s����܂��j
CSceneManager::~CSceneManager() {
	//�V�[��������΍폜
	if (mpScene)
		//�V�[���̍폜
		delete mpScene;
	mpScene = 0;
}
//����������
void CSceneManager::Init() {
	//�V�[���̎��ʂ�ݒ肷��
	mScene = CScene::ETITLE;
	//�V�[���𐶐����A�|�C���^��ݒ肷��
	mpScene = new CSceneTitle();
	
	//���������N���X�̃��\�b�h���Ă΂��
	mpScene->Init();
}
//�X�V����
void CSceneManager::Update() {
	//�|�C���^��Update���Ă�
	mpScene->Update();
	//���̃V�[�����擾���قȂ邩����
	if (mScene != mpScene->GetNextScene()) {
		mScene = mpScene->GetNextScene();
		delete mpScene;//���̃V�[���폜
		//�Y������V�[���𐶐�
		switch (mScene) {
		case CScene::EGAME:
		case CScene::EGAMER1:
			mpScene = new CSceneGame();
			mpScene->Init();
			break;
		case CScene::ETITLE:
			mpScene = new CSceneTitle();
			mpScene->Init();
			break;
		case CScene::ECLEAR:
			mpScene = new CSceneClear();
			mpScene->Init();
			break;
		case CScene::EGAME2:
		case CScene::EGAMER2:
			mpScene = new CSceneGame2();
			mpScene->Init();

			break;
		case CScene::EGAME3:
			mpScene = new CSceneGame3();
			mpScene->Init();
			break;
		}


	}
}
