#include "CEnemy3.h"
#include "CTexture.h"
#include"CSceneGame.h"
#include"CItem.h"
#include"CEnemyBullet2.h"
//extern�F���̃\�[�X�t�@�C���̊O���ϐ��ɃA�N�Z�X����錾
extern CTexture Texture;
#define EANICOUNT 30
#define G  1//�d��
#define VJO 17//�W�����v��

#define VBO 10
//�W�����v��
CEnemy3::CEnemy3()   //�n���}�[�u���X
	: mFx(1.0f),
	mFy(0.0f),
	mFireCount(0)
	,mVj(0)
	, mJump(0)//�O�̓W�����v�\
{
	//�񋓌^
	mTag = EENEMY3;
	w = 25;
	h = 25;
	
}

void CEnemy3::Update() {
	//mEnabled��false�Ȃ�߂�
	if (!mEnabled) return;
	
	
	if (mFireCount > 0) {
		mFireCount--;
	}
	if(mFireCount==0){
		//�e��4���l���֔��˂���
		for (int i = 0; i < 1; i++) {
			CEnemyBullet2* EBullet2 = new CEnemyBullet2();
			//���W�ݒ�
			EBullet2->x = x;
			EBullet2->y = y;
			//�ړ��ʐݒ�
			EBullet2->mFx -= 1;
			EBullet2->mFy += 0;
			//�L���ɂ���
			EBullet2->mEnabled = true;
			EBullet2->mTag = EENEMYBULLET2;
			if (mJump == 0){
				EBullet2->mFx -= 2;
				mFireCount = 0;
		    }

		}
		mFireCount = 60;
	}
	//���x�ɏd�͉����x���Z
	if (mJump > 0) {
		mJump --;
	}
	//�W�����v�\��
	if (mJump == 0) {
		//�W�����v�͂𑬓x�ɐݒ�
		mVj = VJO;
		//�t���O��60���Z
		mJump += 200;
		
	}
	//���x�ɏd�͉����x���Z
	mVj -= G;
	
	//���x���ړ�
	y += mVj;

	
}
/*
�e��Collision���I�[�o�[���C�h����
�Փ˂���ƈړ������𔽑΂ɂ���
*/
bool CEnemy3::Collision(const CRectangle& rrr) {
	//mEnabled��false�Ȃ�߂�
	if (!mEnabled) return false;
	//�e��Collision���\�b�h���Ăяo��
	if (CRectangle::Collision(rrr)) {
		switch (rrr.mTag) {
		
		}
		return true;
	}
	return false;

}
void CEnemy3::Collision(CRectangle* iii, CRectangle* yyy) {
	if (iii->mEnabled && yyy->mEnabled) {
		if (yyy->mTag == EBLOCK) {
			//�Փ˂��Ă����蔲���Ȃ�
			int mx, my;
			if (CRectangle::Collision(yyy, &mx, &my)) {
				//abs(x) x�̐�Βl�����߂�
				//�ړ��ʂ����Ȃ����������ړ�������
				if (abs(mx) < abs(my)) {
					//Rect��x�����ړ�����
					x += mx;

				}
				else {
					//Rect��y�����ړ�����
					y += my;
					//���n
					mVj = 0; //�W�����v���x�O
					
				}
			}
		
		}
	
			if (yyy->mTag == EPLAYER) {
				if (iii->Collision(*yyy)) {
					
						mEnabled = false;
						CSceneGame::Life -= 1;
						CSceneGame::ItemPoint -= 1;
					
					

				}
			}
		
		if (yyy->mTag == EPLAYERBULLET) {
			if (iii->Collision(*yyy)) {
				mEnabled = false;
				CSceneGame::SCore += 300;
			}
		}
	}
}


void CEnemy3::Render() {
	mEAniCount++;//�P�����Z�����
	mEAniCount %= EANICOUNT;

	if (mEAniCount < EANICOUNT / 2)/*	EANICOUNT(30)���Q�Ŋ��������̂��
								�������Ƃ�*/
	{
			CRectangle::Render(Texture, 155, 128, 193, 161);//(���A�E�A���A��)
		
	}
	else//EANICOUNT(15)���傫���Ƃ�
	{
		
			CRectangle::Render(Texture, 187, 160, 193, 161);//(���A�E�A���A��)
		
	}

}

