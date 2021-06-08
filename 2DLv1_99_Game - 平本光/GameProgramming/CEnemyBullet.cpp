#include "CBoss.h"
#include "CTexture.h"
#include "CSceneGame.h"
#include"CItem.h"
#include"CEnemyBullet.h"


//extern�F���̃\�[�X�t�@�C���̊O���ϐ��ɃA�N�Z�X����錾
extern CTexture Texture;

//�f�t�H���g�R���X�g���N�^
CEnemyBullet::CEnemyBullet()
	: mFx(0), mFy(0)
{
	mEnabled = false;
	w = 10;	//���ݒ�
	h = 10;	//�����ݒ�
}

//�X�V����
void CEnemyBullet::Update() {
	//�L���Ȏ�
	if (mEnabled) {
		//�ړ�
		x += mFx;
		y += mFy;
    }
	/*if (y > 600 || y < -400) { //�g�O�Ɉړ������Ƃ�
		mEnabled = false;

	}*/
}

//�`�揈��
void CEnemyBullet::Render() {
	//�L���Ȏ�
	if (mEnabled) {
		//�e�̕`�惁�\�b�h���Ă�
		CRectangle::Render(Texture, 241, 255, 31, 17);
	}
}

void CEnemyBullet::Collision(CRectangle* ii, CRectangle* yy) {
	//	if (i->mEnabled && y->mEnabled) {
	if (yy->mTag == EBLOCK) {
		if (ii->Collision(*yy)) {
			mEnabled = false;
			return;
		}
	}

	
		if (ii->mTag == EENEMYBULLET && yy->mTag == EPLAYER) {
			
				if (ii->Collision(*yy)) {
					mEnabled = false;
					CSceneGame::Life -= 1;
					if (CSceneGame::ItemPoint >= 1) {
						CSceneGame::ItemPoint -= 1;
					}

					return;
				}
			
		}
	

	if (ii->mTag == EENEMYBULLET && yy->mTag == EPLAYERBULLET) {
		if (ii->Collision(*yy)) {
			mEnabled = false;
			return;
		}

	}
	
		if (ii->mTag == EBOSSBULLET && yy->mTag == EPLAYER) {
			
				if (ii->Collision(*yy)) {

					mEnabled = false;
					CSceneGame::Life -= 1;
					CSceneGame::ItemPoint -= 1;
					
					return;
				}
			
		}
	
	

	



}