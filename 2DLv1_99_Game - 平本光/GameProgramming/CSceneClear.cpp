#include"CSceneclear.h"
#include"CText.h"
#include"CScene.h"

void CSceneClear::Init() {
	//�e�N�X�`���t�@�C����ǂݍ���
	//�t�H���g�̐ݒ�
	CText::mFont.Load("font.tga");
	//�V�[���̐ݒ�
	mScene = ECLEAR;
}

//�X�V�����̃I�[�o�[���C�h
void CSceneClear::Update() {
	//������̕`��
	CText::DrawString("GAMECLEAR", -200, 0, 50, 50);
	CText::DrawString("Push ENTER Key",-200, -100, 16, 16);
	if (CKey::Once(VK_RETURN)) {
		//���̃V�[���̓^�C�g��
		mScene = ETITLE;
	}
}
//���̃V�[���̎擾
CScene::EScene CSceneClear::GetNextScene() {
	return mScene;
}