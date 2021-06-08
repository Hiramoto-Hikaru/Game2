#include "CEnemy3.h"
#include "CTexture.h"
#include"CSceneGame.h"
#include"CItem.h"
#include"CEnemyBullet2.h"
//extern：他のソースファイルの外部変数にアクセスする宣言
extern CTexture Texture;
#define EANICOUNT 30
#define G  1//重力
#define VJO 17//ジャンプ力

#define VBO 10
//ジャンプ力
CEnemy3::CEnemy3()   //ハンマーブロス
	: mFx(1.0f),
	mFy(0.0f),
	mFireCount(0)
	,mVj(0)
	, mJump(0)//０はジャンプ可能
{
	//列挙型
	mTag = EENEMY3;
	w = 25;
	h = 25;
	
}

void CEnemy3::Update() {
	//mEnabledがfalseなら戻る
	if (!mEnabled) return;
	
	
	if (mFireCount > 0) {
		mFireCount--;
	}
	if(mFireCount==0){
		//弾を4発四方へ発射する
		for (int i = 0; i < 1; i++) {
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
			if (mJump == 0){
				EBullet2->mFx -= 2;
				mFireCount = 0;
		    }

		}
		mFireCount = 60;
	}
	//速度に重力加速度加算
	if (mJump > 0) {
		mJump --;
	}
	//ジャンプ可能か
	if (mJump == 0) {
		//ジャンプ力を速度に設定
		mVj = VJO;
		//フラグに60加算
		mJump += 200;
		
	}
	//速度に重力加速度加算
	mVj -= G;
	
	//速度分移動
	y += mVj;

	
}
/*
親のCollisionをオーバーライドする
衝突すると移動方向を反対にする
*/
bool CEnemy3::Collision(const CRectangle& rrr) {
	//mEnabledがfalseなら戻る
	if (!mEnabled) return false;
	//親のCollisionメソッドを呼び出す
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
			//衝突してもすり抜けない
			int mx, my;
			if (CRectangle::Collision(yyy, &mx, &my)) {
				//abs(x) xの絶対値を求める
				//移動量が少ない方向だけ移動させる
				if (abs(mx) < abs(my)) {
					//Rectをxだけ移動する
					x += mx;

				}
				else {
					//Rectをyだけ移動する
					y += my;
					//着地
					mVj = 0; //ジャンプ速度０
					
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
	mEAniCount++;//１ずつ加算される
	mEAniCount %= EANICOUNT;

	if (mEAniCount < EANICOUNT / 2)/*	EANICOUNT(30)を２で割ったものより
								小さいとき*/
	{
			CRectangle::Render(Texture, 155, 128, 193, 161);//(左、右、下、上)
		
	}
	else//EANICOUNT(15)より大きいとき
	{
		
			CRectangle::Render(Texture, 187, 160, 193, 161);//(左、右、下、上)
		
	}

}

