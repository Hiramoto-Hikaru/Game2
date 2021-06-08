#include"CEnemy4.h"
#include"CTexture.h"
#include"CRectangle.h"
#include"CSceneGame.h"
//extern：他のソースファイルの外部変数にアクセスする宣言
extern CTexture Texture;
#define EANICOUNT 15
#define G  1//重力


CEnemy4::CEnemy4() 
	: mFx(0.0f),
	  mFy(0.0f),
	  mCount(0),
	  mVj(0),
	  mEAniCount(0),
	  mMoveCount(0)
{
		//列挙型
		mTag = EENEMY4;
		w = 25;
		h = 25;


}
void CEnemy4::Update() {
	

	//mEnabledがfalseなら戻る
	if (!mEnabled) return;
	x += mFx;
	y += mVj;
	mVj -= G;
	if (mMoveCount == 1) {
		mFx ==3;

	}
	
	
}
void CEnemy4::Render() {
	mEAniCount++;
	mEAniCount %= EANICOUNT;

	if (mCount == 0) {

		if (mEAniCount < EANICOUNT / 2)
		{/*	EANICOUNT(30)を２で割ったものより
									小さいとき*/
			if (mFx >= 0) //ｘ方向に進んでいれば
			{
				CRectangle::Render(Texture, 132, 101, 74, 49);//(左、右、下、上)

			}


			else
				//-x方向に進んでいれば
			{
				CRectangle::Render(Texture, 101, 132, 74, 49);//(左、右、下、上)
			}
		}
		else {
			if (mFx >= 0) //ｘ方向に進んでいれば
			{
				CRectangle::Render(Texture, 131, 100, 99, 74);//(左、右、下、上)

			}


			else
				//-x方向に進んでいれば
			{
				CRectangle::Render(Texture, 100, 131, 99, 74);//(左、右、下、上)
			}

		}
	}
	if (mCount == 1) {
		CRectangle::Render(Texture, 103, 119, 114, 99);
	}
	
}
void CEnemy4::Collision(CRectangle* iii, CRectangle* yyy) {

	if( yyy->mTag == EBLOCK)
	{
		int mx, my;
		if (CRectangle::Collision(yyy, &mx, &my))
		{
			//abs(x) xの絶対値を求める
			//移動量が少ない方向だけ移動させる
			if (abs(mx) < abs(my))
			{
				//Rectをxだけ移動する
				x += mx;
				if (mMoveCount >= 1) {
					mFx *= -1;
				}
				
			}
			else {
				//Rectをyだけ移動する
				y += my;
				mVj=0;
				
				
			}
		}
	}
	if (yyy->mTag == EDEATHBLOCK) {
		
			int mx, my;
			if (CRectangle::Collision(yyy, &mx, &my))
			{
				//abs(x) xの絶対値を求める
				//移動量が少ない方向だけ移動させる
				if (abs(mx) < abs(my))
				{
					//Rectをxだけ移動する
					x += mx;
					if (mMoveCount >= 1) {
						mFx *= -1;
					}

				}
				else {
					//Rectをyだけ移動する
					y += my;
					mVj = 0;


				}
			}
		
	}
	
	if (yyy->mTag == EPLAYER) {
		int mx, my;
		if (CRectangle::Collision(yyy, &mx, &my)) {
			if (abs(mx) < abs(my))
			{
				if (mCount == 0) {
                mEnabled = false;
				
				}
				if (mMoveCount == 1) {
					mEnabled = false;
				
				}
			}
			else {
				if (mCount == 0) {
					mCount += 1;
				}
				
				if (mCount == 1) {
					mMoveCount += 1;
				}
				
			}
		}
	}
}