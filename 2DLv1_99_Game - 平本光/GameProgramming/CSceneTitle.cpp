#include "CSceneTitle.h"
#include "CKey.h"
extern CTexture Texture2;
void CSceneTitle::Init() {
	//�e�N�X�`���t�@�C����ǂݍ���
	//�t�H���g�̐ݒ�
	CText::mFont.Load("font.tga");
	Texture2.Load("Image2.tga");
	BGM1.Load("Title.wav");
	//�V�[���̐ݒ�
	mScene = ETITLE;
	BGM1.Play();	
}

//�X�V�����̃I�[�o�[���C�h
void CSceneTitle::Update() {

	//������̕`��

	CText::DrawString("BEAR'S", -250, 0, 50, 50);

	CText::DrawString("Push ENTER Key",
		-200, -100, 16, 16);
	if (CKey::Once(VK_RETURN)) {
		//���̃V�[���̓Q�[��
		mScene = EGAME;
	}
}
//���̃V�[���̎擾
CScene::EScene CSceneTitle::GetNextScene() {
	return mScene;
}
