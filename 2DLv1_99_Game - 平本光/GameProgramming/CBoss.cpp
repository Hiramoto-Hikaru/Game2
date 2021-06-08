#include"CBoss.h"
#include"CRectangle.h"
#include"CSceneGame.h"

#include"CBullet.h"
#include"CEnemyBullet.h"
#include"CScene.h"
#include"CTexture.h"
#include"CEnemyBullet2.h"

extern CTexture Texture;

int CBoss::bosscount = 0;
#define G  1//�d��
#define VJO 25//�W�����v��
 #define ANICOUNT 33 //�A�j���[�V�����̐؂�ւ�
CBoss::CBoss()
	: mFx(-1.0f)
	, mFy(0.0f)
	, mFireCount(0)
    , mVj(0)
	, mJump(0)//�O�̓W�����v�\
	
{
	//�񋓌^
	mTag = EBOSS;
	w = 50;
	h = 50;
	
}
void CBoss::Update() {
	
		//mEnabled��false�Ȃ�߂�
		if (!mEnabled) return;
		if (CSceneGame::BossLife >= 0) {
			//60�t���[����1�񔭎�
			if (mFireCount > 0) {
				mFireCount--;
			}
			else {
				//�e��4���l���֔��˂���
			
				for (int i = 0; i < 5; i++) {
					CEnemyBullet* EBossBullet = new CEnemyBullet();
					//���W�ݒ�
					EBossBullet->x = x;
					EBossBullet->y = y;
					//�ړ��ʐݒ�
					EBossBullet->mFx = (i - 2) % 2 * 2;
					EBossBullet->mFy = (i - 3) % 2 * 2;

					//�L���ɂ���
					EBossBullet->mEnabled = true;
					EBossBullet->mTag = EBOSSBULLET;

				}
				mFireCount = 60;
			}


			if (mJump > 0) {
				mJump--;
			}

           //���x�ɏd�͉����x���Z
		   mVj -= G;
		}
		if (mFireCount == 0) {
			
			for (int j = 0; j < 1; j++) {
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
				

			}
			
		}
		//�W�����v�\��
		if (mJump == 0) {
			//�W�����v�͂𑬓x�ɐݒ�
			mVj = VJO;

			//�t���O��60���Z
			mJump +=60;
		}
		

		//���x���ړ�
		y += mVj;
		 
		if (CSceneGame::BossLife <=0) {
			
			mFy --;
           
		}
		if (y <= -600) {
			mEnabled = false;
			CSceneGame::SCore += 5000;
		}
		
	
		if (bosscount > 0) {
          bosscount--;
		}
		
		



}

void CBoss::Render() {
     bosscount %= ANICOUNT;
	 if (bosscount >ANICOUNT / 2) {
		 CRectangle::Render(Texture, 159, 141, 119, 100);//(���A�E�A���A��)
	 }
	 else {

		 if (CSceneGame::BossLife > 0) {

			 CRectangle::Render(Texture, 122, 104, 178, 159);//(���A�E�A���A��)


		 }
		 if (CSceneGame::BossLife <= 0) {
			 CRectangle::Render(Texture, 254, 236, 159, 177);//(���A�E�A���A��)

		 }
		 /*else
			 //-x�����ɐi��ł����
		 {
			 CRectangle::Render(Texture, 155, 128, 178, 161);//(���A�E�A���A��)
		 }*/
	 }
}
	


void CBoss::Collision(CRectangle* i, CRectangle* y) {

	if (CSceneGame::BossLife > 0) {
		 
		if (y->mTag == EBLOCK) {
			
			int mx, my;
			if (CRectangle::Collision(y, &mx, &my)) {
				//abs(x) x�̐�Βl�����߂�
				//�ړ��ʂ����Ȃ����������ړ�������
				if (abs(mx) < abs(my)) {
					//Rect��x�����ړ�����
					x += mx;
					//�Փ˂��Ă���Δ��]
					mFx *= -1;

				}
				else {
			
					//Rect��y�����ړ�����
					 y += my;
					 //���n
					 mVj = 0; //�W�����v���x�O
					 if (my > 0)
					 {
						 //�W�����v�\
						 mJump = 0;
					 }
					 
				}
             return;
			}
			


		}
		if (y->mTag == EDEATHBLOCK) {

			int mx, my;
			if (CRectangle::Collision(y, &mx, &my))
			{
				//abs(x) x�̐�Βl�����߂�
				//�ړ��ʂ����Ȃ����������ړ�������
				if (abs(mx) < abs(my))
				{
					//Rect��x�����ړ�����
					x += mx;
				
				}
				else {
					//Rect��y�����ړ�����
					y += my;
					//���n
					mVj = 0; //�W�����v���x�O
					if (my > 0)
					{
						//�W�����v�\
						mJump = 0;
					}


				}
			}
			

		}
		if (y->mTag == EENEMY4) {

			int mx, my;
			if (CRectangle::Collision(y, &mx, &my))
			{
				//abs(x) x�̐�Βl�����߂�
				//�ړ��ʂ����Ȃ����������ړ�������
				if (abs(mx) < abs(my))
				{
					CSceneGame::BossLife -= 20;

				}
				else {
					CSceneGame::BossLife -= 20;

				}
			}

		}
		
	}
}