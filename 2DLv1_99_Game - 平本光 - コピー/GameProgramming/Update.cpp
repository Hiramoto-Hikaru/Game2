#include "glut.h"
#include "CKey.h"
#include "CRectangle.h"
#include "CBullet.h"
#include "CPlayer.h"
#include "CEnemy.h"
#include "CText.h"
#include "CSceneManager.h"

// �e�N�X�`���N���X�̃C���N���[�h
#include "CTexture.h"
CTexture Texture; //�}�b�v�̉摜
CTexture Texture2;
CTexture Texture3;
CTexture Texture4;
CTexture Texture5;
CTexture Texture6;
//�V�[���}�l�[�W���̃C���X�^���X
CSceneManager SceneManager;

//Init�֐�
//�ŏ��Ɉ�x�����Ă΂��֐�
void Init() {
	Texture.Load("Image.tga");
    Texture2.Load("Image2.tga");
	Texture3.Load("image3.Tga");
	Texture4.Load("image4.tga");
	Texture5.Load("imagesss.tga");
	Texture6.Load("exp.tga");
	//�V�[���}�l�[�W���̏�����
	SceneManager.Init();
	
}
//Update�֐�
//�v���O�����̎��s���A�J��Ԃ��Ă΂��֐�
void Update() {
	//�V�[���}�l�[�W���̍X�V
	SceneManager.Update();
	
}
