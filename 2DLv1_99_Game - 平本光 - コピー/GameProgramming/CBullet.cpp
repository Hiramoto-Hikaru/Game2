#include "CBoss.h"
#include "CBullet.h"
#include "CTexture.h"
#include "CSceneGame.h"
#include"CItem.h"
#include"CBoss.h"

//extern�F���̃\�[�X�t�@�C���̊O���ϐ��ɃA�N�Z�X����錾
extern CTexture Texture;

//�f�t�H���g�R���X�g���N�^
CBullet::CBullet()
: mFx(0), mFy(0)
{
	mEnabled = false;
	w = 10;	//���ݒ�
	h = 10;	//�����ݒ�
	if (CSceneGame::ItemPoint == 2) {
		w = 18;
		h = 18;
	}
}

//�X�V����
void CBullet::Update() {
	//�L���Ȏ�
	
	if (mEnabled) {  //if(CSceneGame::ItemPoint=1){}  �t�@�C�A�}���I�݂����ɂȂ�
		//�ړ�
		x += mFx;
		y += mFy;
		if (CSceneGame::ItemPoint == 1) {
			x += 2*mFx;
			y += 2*mFy;
		}
		

	}
}

//�`�揈��
void CBullet::Render() {
	//�L���Ȏ�
	if (mEnabled) {
		//�e�̕`�惁�\�b�h���Ă�
	CRectangle::Render(Texture, 192,207 ,110, 98);
	}
}

void CBullet::Collision(CRectangle* i, CRectangle* y) {
//	if (i->mEnabled && y->mEnabled) {
		if (y->mTag == EBLOCK) {
			if (i->Collision(*y)) {
				mEnabled = false;
				return;
			}
		}
		

		
		if (i->mTag == EPLAYERBULLET && y->mTag == EENEMY) {
			if (i->Collision(*y)) {
				CSceneGame::SCore += 50;
				mEnabled = false;
				return;
			}

		}
		if (i->mTag == EPLAYERBULLET && y->mTag == EENEMY2) {
			if (i->Collision(*y)) {
				
				mEnabled = false;
				return;
			}

		}

		if (i->mTag == EPLAYERBULLET && y->mTag == EBOSS) {

			if (i->Collision(*y)) {
				CBoss::bosscount += 60;
				CSceneGame::BossLife -= 1;
				mEnabled = false;
				return;

			}
		}
       
		if (i->mTag == EENEMYBULLET  && y->mTag ==EPLAYERBULLET) {
			if (i->Collision(*y)) {
				mEnabled = false;
				return;
			}

		}
		if (i->mTag == EPLAYERBULLET && y->mTag == EENEMYBULLET) {
			if (i->Collision(*y)) {
				mEnabled = false;
				return;
			}

		}
		if (i->mTag == EPLAYERBULLET && y->mTag == EBOSSBULLET) {
			if (i->Collision(*y)) {
				mEnabled = false;
				return;
			}

		}
		if (i->mTag == EPLAYERBULLET && y->mTag == EENEMYBULLET2) {
			if (i->Collision(*y)) {
				mEnabled = false;
				return;
			}

		}
		if (i->mTag == EPLAYERBULLET && y->mTag == EENEMY2) {
			if (i->Collision(*y)) {
				mEnabled = false;
				return;
			}

		}
		if (i->mTag == EPLAYERBULLET && y->mTag == EENEMY3) {
			if (i->Collision(*y)) {
				mEnabled = false;
				return;
			}

		}


		
		
		

}
