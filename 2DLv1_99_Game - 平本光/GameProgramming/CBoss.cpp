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
#define G  1//重力
#define VJO 25//ジャンプ力
 #define ANICOUNT 33 //アニメーションの切り替え
CBoss::CBoss()
	: mFx(-1.0f)
	, mFy(0.0f)
	, mFireCount(0)
    , mVj(0)
	, mJump(0)//０はジャンプ可能
	
{
	//列挙型
	mTag = EBOSS;
	w = 50;
	h = 50;
	
}
void CBoss::Update() {
	
		//mEnabledがfalseなら戻る
		if (!mEnabled) return;
		if (CSceneGame::BossLife >= 0) {
			//60フレームに1回発射
			if (mFireCount > 0) {
				mFireCount--;
			}
			else {
				//弾を4発四方へ発射する
			
				for (int i = 0; i < 5; i++) {
					CEnemyBullet* EBossBullet = new CEnemyBullet();
					//座標設定
					EBossBullet->x = x;
					EBossBullet->y = y;
					//移動量設定
					EBossBullet->mFx = (i - 2) % 2 * 2;
					EBossBullet->mFy = (i - 3) % 2 * 2;

					//有効にする
					EBossBullet->mEnabled = true;
					EBossBullet->mTag = EBOSSBULLET;

				}
				mFireCount = 60;
			}


			if (mJump > 0) {
				mJump--;
			}

           //速度に重力加速度加算
		   mVj -= G;
		}
		if (mFireCount == 0) {
			
			for (int j = 0; j < 1; j++) {
				CEnemyBullet2* EBullet2 = new CEnemyBullet2();
				//座標設定
				EBullet2->x = x;
				EBullet2->y = y;
				//移動量設定
				EBullet2->mFx -= 1;
				EBullet2->mFy += 0;
				//有効にする
				EBullet2->mEnabled = true;
				EBullet2->mTag = EENEMYBULLET2;
				

			}
			
		}
		//ジャンプ可能か
		if (mJump == 0) {
			//ジャンプ力を速度に設定
			mVj = VJO;

			//フラグに60加算
			mJump +=60;
		}
		

		//速度分移動
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
		 CRectangle::Render(Texture, 159, 141, 119, 100);//(左、右、下、上)
	 }
	 else {

		 if (CSceneGame::BossLife > 0) {

			 CRectangle::Render(Texture, 122, 104, 178, 159);//(左、右、下、上)


		 }
		 if (CSceneGame::BossLife <= 0) {
			 CRectangle::Render(Texture, 254, 236, 159, 177);//(左、右、下、上)

		 }
		 /*else
			 //-x方向に進んでいれば
		 {
			 CRectangle::Render(Texture, 155, 128, 178, 161);//(左、右、下、上)
		 }*/
	 }
}
	


void CBoss::Collision(CRectangle* i, CRectangle* y) {

	if (CSceneGame::BossLife > 0) {
		 
		if (y->mTag == EBLOCK) {
			
			int mx, my;
			if (CRectangle::Collision(y, &mx, &my)) {
				//abs(x) xの絶対値を求める
				//移動量が少ない方向だけ移動させる
				if (abs(mx) < abs(my)) {
					//Rectをxだけ移動する
					x += mx;
					//衝突していれば反転
					mFx *= -1;

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
             return;
			}
			


		}
		if (y->mTag == EDEATHBLOCK) {

			int mx, my;
			if (CRectangle::Collision(y, &mx, &my))
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
		if (y->mTag == EENEMY4) {

			int mx, my;
			if (CRectangle::Collision(y, &mx, &my))
			{
				//abs(x) xの絶対値を求める
				//移動量が少ない方向だけ移動させる
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