#include "CTexture.h"
#include "CSceneGame.h"
#include"CItem.h"
#include"CEnemyBullet2.h"


//extern�F���̃\�[�X�t�@�C���̊O���ϐ��ɃA�N�Z�X����錾
extern CTexture Texture;
#define EBULLETCOUNT 15

#define VBO 20//�e�̏㏸�l
#define G  1//�d��


//�f�t�H���g�R���X�g���N�^
CEnemyBullet2::CEnemyBullet2()
	: mFx(0),mFy(0),mbulletcount(0)
{
	mEnabled = false;
	w = 15;	//���ݒ�
	h = 15;	//�����ݒ�	
	mFy = VBO;
}

//�X�V����
void CEnemyBullet2::Update() {
	//�L���Ȏ�
	if (mEnabled) {
		//�ړ�
		mFx = -3;
		x += mFx;
	
		
	}
    y += mFy;
	mFy -= G;
	if (y < -2000) {
		mEnabled = false;
	}
	
	
}

//�`�揈��
void CEnemyBullet2::Render() {


	
     mbulletcount ++;
	 mbulletcount %= EBULLETCOUNT;
	 if (mbulletcount < EBULLETCOUNT/ 2)
	  {
		//�e�̕`�惁�\�b�h���Ă�
		CRectangle::Render(Texture, 191, 208, 126, 112);
	 }
	  else {
		CRectangle::Render(Texture, 208, 225, 126, 112);
	  }
	
}

void CEnemyBullet2::Collision(CRectangle* iii, CRectangle* yyy) {
	//	if (i->mEnabled && y->mEnabled) {
	

		if (iii->mTag == EENEMYBULLET2 && yyy->mTag == EPLAYER) {
			
				if (iii->Collision(*yyy)) {
					mEnabled = false;
					CSceneGame::Life -= 1;
					CSceneGame::ItemPoint -= 1;
					
					return;
				}
			
		}
	

	if (iii->mTag == EENEMYBULLET2 && yyy->mTag == EPLAYERBULLET) {
		if (iii->Collision(*yyy)) {
			mEnabled = false;
			return;
		}

	}

	
	



}