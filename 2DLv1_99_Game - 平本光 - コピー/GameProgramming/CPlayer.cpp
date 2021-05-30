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
#define G  1//重力
#define GD 1
#define VJO 21//ジャンプ力
#define ANICOUNT 30 //アニメーションの切り替え
#define DAMAGECOUNT 15
#define COUNT 2500
#define COUNT2 2000

//extern：他のソースファイルの外部変数にアクセスする宣言
extern CTexture Texture;
CPlayer* CPlayer::spInstance = 0;
int CPlayer::DamageCount = 0;


CPlayer::CPlayer()

//変数の初期化
	: mFx(0.0f), mFy(0.0f)
	,mWorkCount(0.0f)
	, FireCount(0)
	, mVj(0)
	,mDj(0)
	, mJump(0)//０はジャンプ可能
	, mAniCount(0)
	,mjumpcount(0)
	,Count(0)
	{
     //コンストラクタ
	spInstance = this;
	mTag = EPLAYER;
	Se.Load("jump.wav");
	
	w = 20;
	h = 20;
		
	}
void CPlayer::Update() {
	if (CSceneGame::Life > 0&&CSceneGame::Treasure<4)
	    {
		//staticメソッドはどこからでも呼べる
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
		//スペースキーで弾発射
		//0より大きいとき1減算する
		   if (FireCount > 0) {
			FireCount--;
		   }
		//FireContが0で、かつ、スペースキーで弾発射
		     else if (CKey::Once(' ')) {
          
			CBullet* Bullet = new CBullet();
			//発射位置の設定
			Bullet->x = x;
			Bullet->y = y;
			//移動の値を設定
			Bullet->mFx = mFx * 5;
			Bullet->mFy = mFy * 5;
			//有効にする
			Bullet->mEnabled = true;
			//プレイヤーの弾を設定
			Bullet->mTag = CRectangle::EPLAYERBULLET;
			FireCount = 10;
			
		     }
		//ジャンプ可能か
		   if (mJump == 0 && CKey::Push('J')) {
			   //ジャンプ力を速度に設定
			   mVj = VJO;
			   //フラグに１加算
			   mJump++;
			   mjumpcount++;
			   //サウンド再生
			   Se.Play();
		   }
	}
        //ヒットバック(敵に衝突すると後ろに下がる）
			x -= mDj;
        //速度に重力加速度加算
		mVj -= G;
		//速度分移動
		y += mVj;
		//スケボーに乗っているとき
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
			
			mAniCount++;//１ずつ加算される
			mAniCount %= ANICOUNT;
		
			
			//ダメージを受けたとき
			//スケボー
			 if (DamageCount >= 1) {
				
				
				
					 CRectangle::Render(Texture, 193, 219, 191, 157);
				 
			//宇宙服	
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
					if (mAniCount < ANICOUNT / 2)  /*ANICOUNT(30)を２で割ったものより小さいとき*/
					{
						if (mFx > 0)//ｘ方向に進んでいれば
						{
							CRectangle::Render(Texture, 130, 162, 158, 126);
						}
						if (mFx < 0) //-x方向に進んでいれば
						{
							CRectangle::Render(Texture, 162, 130, 158, 126);
						}
					}
					else//ANICOUNT(15)より大きいとき
					{
						if (mFx > 0) //ｘ方向に進んでいれば
						{
							CRectangle::Render(Texture, 162, 194, 159, 129);
						}
						if (mFx < 0)//-x方向に進んでいれば
						{
							CRectangle::Render(Texture, 194, 162, 159, 129);
						}
					}
				}
				//スケボー
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
				//宇宙服
				if (CSceneGame::ItemPoint == 2)
				{
					if (mAniCount < ANICOUNT / 2)  /*ANICOUNT(30)を２で割ったものより小さいとき*/
					{

						if (mFx >= 0) //ｘ方向に進んでいれば
						{
							CRectangle::Render(Texture, 136, 158, 254, 225);
						}
						else//-x方向に進んでいれば
						{
							CRectangle::Render(Texture, 158, 136, 254, 225);
						}
					}
					else//ANICOUNT(15)より大きいとき
					{
						if (mFx >= 0) //ｘ方向に進んでいれば

						{
							CRectangle::Render(Texture, 168, 190, 256, 226);
						}
						else//-x方向に進んでいれば
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
			//abs(x) xの絶対値を求める
			//移動量が少ない方向だけ移動させる
			if (abs(mx) < abs(my))
			{
				//Rectをxだけ移動する
				x += mx;
			
			}
			   else {
				//Rectをyだけ移動する
				y += my;
				//着地
				mVj = 0; //ジャンプ速度０
				mDj = 0;
				   if (my > 0)
				   {
					//ジャンプ可能
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
			//abs(x) xの絶対値を求める
			//移動量が少ない方向だけ移動させる
			if (abs(mx) < abs(my))
			{
				//Rectをxだけ移動する
				x += mx;
			}
			  else {
				//Rectをyだけ移動する
				y += my;
				//着地
				mVj = 0; //ジャンプ速度０
				   if (my > 0)
				   {
					//ジャンプ可能
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
				//abs(x) xの絶対値を求める
				//移動量が少ない方向だけ移動させる
				if (abs(mx) < abs(my)) {
					//Rectをxだけ移動する
					x += mx;
				}
				   else
				   {
					//Rectをyだけ移動する
					y += my;
					//着地
					mVj = 0; //ジャンプ速度０
					   if (my > 0)
					   {
						//ジャンプ可能
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
			//abs(x) xの絶対値を求める
			//移動量が少ない方向だけ移動させる
			if (abs(mx) < abs(my))
			{
				
				//フラグに１加算
				mJump++;
				mjumpcount++;
				mVj = VJO;
				
				
			}
			else {
				//フラグに１加算
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
							//abs(x) xの絶対値を求める
							//移動量が少ない方向だけ移動させる
							if (abs(mx) < abs(my))
							{
								//Rectをxだけ移動する
								x += mx;
							}
							else {
								//Rectをyだけ移動する
								y += my;
								//着地
								mVj = 0; //ジャンプ速度０
								if (my > 0)
								{
									//ジャンプ可能
									mJump = 0;
								}
							}
						}
					
				}
				if (ry->mTag == EOBJECT)
				{
					//当たり判定なし
				}


	//ここからダメージを受けるクラスとの衝突判定
	

	
	   if (ry->mTag == EENEMY) 
	   {
		  if (ri->Collision(*ry))
		  {

			//フラグに１加算
			mJump++;
			mjumpcount++;
            mVj = VDO;
			mDj = VDO;
			mDj -= GD;
		
			//宇宙服なら２加算
			  if (CSceneGame::ItemPoint == 1) 
			  {
				DamageCount += 2;
				
			  }
			//スケボーなら１加算
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
			//フラグに１加算
			mJump++;
			mjumpcount++;
            mVj = VDO;
			mDj = VDO;
			mDj -= GD;
        
			//宇宙服なら２加算
			   if (CSceneGame::ItemPoint == 1)
			   {
				  
				DamageCount += 2;
			   }
			   //スケボーなら１加算
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
			//フラグに１加算
			mJump++;
			mjumpcount++;

            mVj = VDO;
			mDj = VDO;
			mDj -= GD;
          
			//宇宙服なら２加算
			   if (CSceneGame::ItemPoint == 1)
			   {
				DamageCount += 2;
			   }
			   //スケボーなら１加算
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
				//フラグに１加算
			mJump++;
			mjumpcount++;
		
			//宇宙服なら２加算
				if (CSceneGame::ItemPoint == 1)
				{
              DamageCount+=2;
				}
			//スケボーなら１加算
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
				//フラグに１加算
				mJump++;
				mjumpcount++;
				mVj = VDO;
				mDj = VDO;
				mDj -= GD;
				
				//宇宙服なら２加算
				if (CSceneGame::ItemPoint == 1)
				{
					
				        	DamageCount += 2;
				}
				//スケボーなら１加算
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
					//フラグに１加算
					mJump++;
					mjumpcount++;
					mVj = VDO;
					mDj = VDO;
					mDj -= GD;
					
					//宇宙服なら２加算
					if (CSceneGame::ItemPoint == 1)
					{
						
						DamageCount += 2;
					}
					//スケボーなら１加算
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
						//フラグに１加算
						mJump++;
						mjumpcount++;
						mVj = VDO;
						mDj = VDO;
						mDj -= GD;
					}
				}
	
  }	
}