#include "CPlayer.h"
#include "CKey.h"
#include "CBullet.h"
#include"CText.h"
#include"CEnemy.h"
#include"CKey.h"
#include"CTreasure.h"
#include"CRectangle.h"
#include"CScene.h"
#include"CBoss.h"
#include"CItem.h"
#include"CDisappear.h"
#include"CDisappear2.h"
#include"CSound.h"
#include"CTrophy.h"

#define VDO 5
#define G  1//�d��
#define GD 1
#define VJO 21//�W�����v��
#define ANICOUNT 30 //�A�j���[�V�����̐؂�ւ�
#define DAMAGECOUNT 15
#define COUNT 2500
#define COUNT2 2000

//extern�F���̃\�[�X�t�@�C���̊O���ϐ��ɃA�N�Z�X����錾
extern CTexture Texture;
CPlayer* CPlayer::spInstance = 0;
int CPlayer::DamageCount = 0;


CPlayer::CPlayer()

//�ϐ��̏�����
	: mFx(0.0f), mFy(0.0f)
	,mWorkCount(0.0f)
	, FireCount(0)
	, mVj(0)
	,mDj(0)
	, mJump(0)//�O�̓W�����v�\
	, mAniCount(0)
	,mjumpcount(0)
	,Count(0)
	{
     //�R���X�g���N�^
	spInstance = this;
	mTag = EPLAYER;
	Se.Load("jump.wav");
	
	w = 20;
	h = 20;
		
	}
void CPlayer::Update() {
	if (CSceneGame::Life > 0&&CSceneGame::Treasure<4)
	    {
		//static���\�b�h�͂ǂ�����ł��Ăׂ�
		if (CKey::Push('A')) {
			
			x = x + mFx;
			
			mFx = -3;
			mFy = 0;
		}
		if (CKey::Push('D')) {
			x += 3;
			mFx = 1;
			mFy = 0;
		}
		if (CKey::Push('W')) {
			mFx = 0;
			mFy = 1;
			if (y + h > 300) {
				y = 300 - h;
			}
		}
		if (CKey::Push('S')) {
			mFx = 0;
			mFy = -1;
		}
		//�X�y�[�X�L�[�Œe����
		//0���傫���Ƃ�1���Z����
		   if (FireCount > 0) {
			FireCount--;
		   }
		//FireCont��0�ŁA���A�X�y�[�X�L�[�Œe����
		     else if (CKey::Once(' ')) {
          
			CBullet* Bullet = new CBullet();
			//���ˈʒu�̐ݒ�
			Bullet->x = x;
			Bullet->y = y;
			//�ړ��̒l��ݒ�
			Bullet->mFx = mFx * 5;
			Bullet->mFy = mFy * 5;
			//�L���ɂ���
			Bullet->mEnabled = true;
			//�v���C���[�̒e��ݒ�
			Bullet->mTag = CRectangle::EPLAYERBULLET;
			FireCount = 10;
			
		     }
		//�W�����v�\��
		   if (mJump == 0 && CKey::Push('J')) {
			   //�W�����v�͂𑬓x�ɐݒ�
			   mVj = VJO;
			   //�t���O�ɂP���Z
			   mJump++;
			   mjumpcount++;
			   //�T�E���h�Đ�
			   Se.Play();
		   }
	}
        //�q�b�g�o�b�N(�G�ɏՓ˂���ƌ��ɉ�����j
			x -= mDj;
        //���x�ɏd�͉����x���Z
		mVj -= G;
		//���x���ړ�
		y += mVj;
		//�X�P�{�[�ɏ���Ă���Ƃ�
	  if (CSceneGame::ItemPoint == 1 && CKey::Push('D'))
	  {
		x += 5;
	  }
	   if (CSceneGame::ItemPoint == 1 && CKey::Push('A'))
	   {
		x-= 5;
	   }
	  
	   if (CTrophy::TrophyCount > 0) {
			
			h = 30;
		}
	   if (DamageCount>0) {
		   DamageCount--;
	  }
	
	   
	  

	 


	 
}
void CPlayer::Render() {
	
	if (CSceneGame::Life > 0) {
		if (CTrophy::TrophyCount > 0) {
			CRectangle::Render(Texture, 165, 187, 116, 76);
		}
		else {
			
			mAniCount++;//�P�����Z�����
			mAniCount %= ANICOUNT;
		
			
			//�_���[�W���󂯂��Ƃ�
			//�X�P�{�[
			 if (DamageCount >= 1) {
				
				
				
					 CRectangle::Render(Texture, 193, 219, 191, 157);
				 
			//�F����	
			}
			 else if (DamageCount >= 2) {
				
				
                  CRectangle::Render(Texture, 193, 219, 253, 225);
				 
             
			}

			else if (DamageCount <= 0) {
				if (CSceneGame::ItemPoint <= 0)
				{
					if (mFx == 0.0f)
					{
						CRectangle::Render(Texture, 102, 134, 158, 126);
					}
					if (mAniCount < ANICOUNT / 2)  /*ANICOUNT(30)���Q�Ŋ��������̂�菬�����Ƃ�*/
					{
						if (mFx > 0)//�������ɐi��ł����
						{
							CRectangle::Render(Texture, 130, 162, 158, 126);
						}
						if (mFx < 0) //-x�����ɐi��ł����
						{
							CRectangle::Render(Texture, 162, 130, 158, 126);
						}
					}
					else//ANICOUNT(15)���傫���Ƃ�
					{
						if (mFx > 0) //�������ɐi��ł����
						{
							CRectangle::Render(Texture, 162, 194, 159, 129);
						}
						if (mFx < 0)//-x�����ɐi��ł����
						{
							CRectangle::Render(Texture, 194, 162, 159, 129);
						}
					}
				}
				//�X�P�{�[
				if (CSceneGame::ItemPoint == 1)
				{
					if (mAniCount < ANICOUNT / 2) {
						if (mFx >= 0) {
							CRectangle::Render(Texture, 224, 254, 158, 125);
						}
						else {
							CRectangle::Render(Texture, 254, 224, 158, 125);
						}
					}
					else {
						if (mFx >= 0) {
							CRectangle::Render(Texture, 224, 254, 219, 186);
						}
						else {
							CRectangle::Render(Texture, 254, 224, 219, 186);
						}
					}

				}
				//�F����
				if (CSceneGame::ItemPoint == 2)
				{
					if (mAniCount < ANICOUNT / 2)  /*ANICOUNT(30)���Q�Ŋ��������̂�菬�����Ƃ�*/
					{

						if (mFx >= 0) //�������ɐi��ł����
						{
							CRectangle::Render(Texture, 136, 158, 254, 225);
						}
						else//-x�����ɐi��ł����
						{
							CRectangle::Render(Texture, 158, 136, 254, 225);
						}
					}
					else//ANICOUNT(15)���傫���Ƃ�
					{
						if (mFx >= 0) //�������ɐi��ł����

						{
							CRectangle::Render(Texture, 168, 190, 256, 226);
						}
						else//-x�����ɐi��ł����
						{
							CRectangle::Render(Texture, 190, 168, 256, 226);
						}
					}
				}
			}
		}
	}
	else 
	{
		CRectangle::Render(Texture, 196, 224, 158, 126);
		if (y <= -3000)
		{
		mEnabled = false;
		}

	}
}
void CPlayer::Collision(CRectangle *ri, CRectangle *ry) 
{
  if (CSceneGame::Life > 0)
  {
	 if (ry->mTag == EBLOCK) 
	 {
		int mx, my;
	     if (CRectangle::Collision(ry, &mx, &my))
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
				mDj = 0;
				   if (my > 0)
				   {
					//�W�����v�\
					mJump = 0;
					mjumpcount == 0;
					
				   }
			   }
		 }
     }
	if (ry->mTag == EDISAPPEAR)
	{
	   if (CDisappear::DisappearCount < COUNT/2 ) 
	   {
		 int mx, my;
		  if (CRectangle::Collision(ry, &mx, &my))
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
	}
	if (ry->mTag == EDISAPPEAR2) {
		if (CDisappear::DisappearCount < COUNT2/2 )
		{
			int mx, my;

			if (CRectangle::Collision(ry, &mx, &my))
			{
				//abs(x) x�̐�Βl�����߂�
				//�ړ��ʂ����Ȃ����������ړ�������
				if (abs(mx) < abs(my)) {
					//Rect��x�����ړ�����
					x += mx;
				}
				   else
				   {
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
	}



	if (ry->mTag == EENEMY4)
	{
		int mx, my;
		if (CRectangle::Collision(ry, &mx, &my))
		{
			//abs(x) x�̐�Βl�����߂�
			//�ړ��ʂ����Ȃ����������ړ�������
			if (abs(mx) < abs(my))
			{
				
				//�t���O�ɂP���Z
				mJump++;
				mjumpcount++;
				mVj = VJO;
				
				
			}
			else {
				//�t���O�ɂP���Z
				mJump++;
				mjumpcount++;
				mVj = VJO;
				
			}
		}
	}
	if (ry->mTag == EBUTTON)
				{
					
						int mx, my;
						if (CRectangle::Collision(ry, &mx, &my))
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
				if (ry->mTag == EOBJECT)
				{
					//�����蔻��Ȃ�
				}


	//��������_���[�W���󂯂�N���X�Ƃ̏Փ˔���
	

	
	   if (ry->mTag == EENEMY) 
	   {
		  if (ri->Collision(*ry))
		  {

			//�t���O�ɂP���Z
			mJump++;
			mjumpcount++;
            mVj = VDO;
			mDj = VDO;
			mDj -= GD;
		
			//�F�����Ȃ�Q���Z
			  if (CSceneGame::ItemPoint == 1) 
			  {
				DamageCount += 2;
				
			  }
			//�X�P�{�[�Ȃ�P���Z
			   if (CSceneGame::ItemPoint == 0)
			   {
				DamageCount += 1;
				
			   }
		  }
	   }
	     if (ry->mTag == EENEMYBULLET) 
		 {
		   if (ri->Collision(*ry)) 
		   {
			//�t���O�ɂP���Z
			mJump++;
			mjumpcount++;
            mVj = VDO;
			mDj = VDO;
			mDj -= GD;
        
			//�F�����Ȃ�Q���Z
			   if (CSceneGame::ItemPoint == 1)
			   {
				  
				DamageCount += 2;
			   }
			   //�X�P�{�[�Ȃ�P���Z
			   if (CSceneGame::ItemPoint == 0)
			   {
				
				DamageCount += 1;
			   }
		   }
	     }
	
	     if (ry->mTag == EBOSSBULLET)
		 {
		    if (ri->Collision(*ry)) 
			{
			//�t���O�ɂP���Z
			mJump++;
			mjumpcount++;

            mVj = VDO;
			mDj = VDO;
			mDj -= GD;
          
			//�F�����Ȃ�Q���Z
			   if (CSceneGame::ItemPoint == 1)
			   {
				DamageCount += 2;
			   }
			   //�X�P�{�[�Ȃ�P���Z
			   if (CSceneGame::ItemPoint == 0)
			   {
				DamageCount += 1;
			   }
	     	}
	     }
		if (ry->mTag == EENEMY2)
		{
			if (ri->Collision(*ry))
			{
				//�t���O�ɂP���Z
			mJump++;
			mjumpcount++;
		
			//�F�����Ȃ�Q���Z
				if (CSceneGame::ItemPoint == 1)
				{
              DamageCount+=2;
				}
			//�X�P�{�[�Ȃ�P���Z
				if (CSceneGame::ItemPoint == 0)
				{
						DamageCount+=1;
				}
			    mVj = VDO;
				mDj = VDO;
				mDj -= GD;
			}
		}
		if (ry->mTag == EENEMY3)
		{
			if (ri->Collision(*ry))
			{
				//�t���O�ɂP���Z
				mJump++;
				mjumpcount++;
				mVj = VDO;
				mDj = VDO;
				mDj -= GD;
				
				//�F�����Ȃ�Q���Z
				if (CSceneGame::ItemPoint == 1)
				{
					
				        	DamageCount += 2;
				}
				//�X�P�{�[�Ȃ�P���Z
				if (CSceneGame::ItemPoint == 0) 
				{
					
					DamageCount += 1;
				}
			}
		}
			if (ry->mTag == EENEMYBULLET2)
			{

				if (ri->Collision(*ry))
				{
					//�t���O�ɂP���Z
					mJump++;
					mjumpcount++;
					mVj = VDO;
					mDj = VDO;
					mDj -= GD;
					
					//�F�����Ȃ�Q���Z
					if (CSceneGame::ItemPoint == 1)
					{
						
						DamageCount += 2;
					}
					//�X�P�{�[�Ȃ�P���Z
					if (CSceneGame::ItemPoint == 0)
					{
						
						DamageCount += 1;
					}
				}
			}
				if (ry->mTag == EBOSS)
				{
					if (ri->Collision(*ry))
					{
						//�t���O�ɂP���Z
						mJump++;
						mjumpcount++;
						mVj = VDO;
						mDj = VDO;
						mDj -= GD;
					}
				}
	
  }	
}