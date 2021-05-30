#include "CEnemy.h"
#include "CTexture.h"
#include"CSceneGame.h"
#include"CItem.h"
#include"CEnemyBullet.h"
//extern�F���̃\�[�X�t�@�C���̊O���ϐ��ɃA�N�Z�X����錾
extern CTexture Texture;
#define EANICOUNT 30

CEnemy::CEnemy()
: mFx(1.0f), mFy(0.0f), mFireCount(120)
{
	//�񋓌^
	mTag = EENEMY;
	w = 23;
	h = 23;
}

void CEnemy::Update() {
	//mEnabled��false�Ȃ�߂�
	if (!mEnabled) return;
	//60�t���[����1�񔭎�
	if (mFireCount > 0) {
		mFireCount--;
	}
	else {
		//�e��4���l���֔��˂���
		for (int i = 0; i < 4; i++) {
			CEnemyBullet* EBullet = new CEnemyBullet();
			//���W�ݒ�
			EBullet->x = x;
			EBullet->y = y-5;
			//�ړ��ʐݒ�
			EBullet->mFx = (i - 2) % 2 * 2;
			EBullet->mFy = (i - 1) % 2 * 2;
			//�L���ɂ���
			EBullet->mEnabled = true;
			EBullet->mTag = EENEMYBULLET;
		}
		mFireCount = 120;
	}
	x += mFx;
	y += mFy;
}
/*
�e��Collision���I�[�o�[���C�h����
�Փ˂���ƈړ������𔽑΂ɂ���
*/
bool CEnemy::Collision(const CRectangle &r) {
	//mEnabled��false�Ȃ�߂�
	if (!mEnabled) return false;
	//�e��Collision���\�b�h���Ăяo��
	if (CRectangle::Collision(r)) {
		switch (r.mTag) {
		case EBLOCK:
			//�Փ˂��Ă���Δ��]
			mFx *= -1;
			mFy *= -1;

			break;
		case EPLAYERBULLET:
			//�v���C���[�̒e�ɓ�����ƁA�����ɂ���
			mEnabled = false;
			CSceneGame::SCore += 50;
			break;

		case EPLAYER:
			
				mEnabled = false;
				CSceneGame::Life -= 1;
				CSceneGame::ItemPoint -= 1;
			
			
			break;


			
		}

		return true;
	}
	return false;

}

void CEnemy::Render() {
	mEAniCount++;//�P�����Z�����
	mEAniCount %= EANICOUNT;

	if (mEAniCount < EANICOUNT / 2)/*	EANICOUNT(30)���Q�Ŋ��������̂��
								�������Ƃ�*/
	{

		if (mFx >= 0) //�������ɐi��ł����
		{
			CRectangle::Render(Texture, 128, 155, 193, 161);//(���A�E�A���A��)
		}
		else //-x�����ɐi��ł����
		{
			CRectangle::Render(Texture, 155, 128, 193, 161);//(���A�E�A���A��)
		}
	}
	else//EANICOUNT(15)���傫���Ƃ�
	{
		if (mFx >= 0) //�������ɐi��ł����

		{
			CRectangle::Render(Texture, 160, 187, 193, 161);//(���A�E�A���A��)
		}
		else //-x�����ɐi��ł����
		{
			CRectangle::Render(Texture, 187, 160, 193, 161);//(���A�E�A���A��)
		}
	}
	
}

void CEnemy::Collision(CRectangle *i, CRectangle *y) {
	
	if (Collision(*y))
	{
		
	}

}
