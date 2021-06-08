#include "CEnemy.h"
#include "CTexture.h"
#include"CSceneGame.h"
#include"CItem.h"
#include"CEnemyBullet.h"
//extern：他のソースファイルの外部変数にアクセスする宣言
extern CTexture Texture;
#define EANICOUNT 30

CEnemy::CEnemy()
: mFx(1.0f), mFy(0.0f), mFireCount(120)
{
	//列挙型
	mTag = EENEMY;
	w = 23;
	h = 23;
}

void CEnemy::Update() {
	//mEnabledがfalseなら戻る
	if (!mEnabled) return;
	//60フレームに1回発射
	if (mFireCount > 0) {
		mFireCount--;
	}
	else {
		//弾を4発四方へ発射する
		for (int i = 0; i < 4; i++) {
			CEnemyBullet* EBullet = new CEnemyBullet();
			//座標設定
			EBullet->x = x;
			EBullet->y = y-5;
			//移動量設定
			EBullet->mFx = (i - 2) % 2 * 2;
			EBullet->mFy = (i - 1) % 2 * 2;
			//有効にする
			EBullet->mEnabled = true;
			EBullet->mTag = EENEMYBULLET;
		}
		mFireCount = 120;
	}
	x += mFx;
	y += mFy;
}
/*
親のCollisionをオーバーライドする
衝突すると移動方向を反対にする
*/
bool CEnemy::Collision(const CRectangle &r) {
	//mEnabledがfalseなら戻る
	if (!mEnabled) return false;
	//親のCollisionメソッドを呼び出す
	if (CRectangle::Collision(r)) {
		switch (r.mTag) {
		case EBLOCK:
			//衝突していれば反転
			mFx *= -1;
			mFy *= -1;

			break;
		case EPLAYERBULLET:
			//プレイヤーの弾に当たると、無効にする
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
	mEAniCount++;//１ずつ加算される
	mEAniCount %= EANICOUNT;

	if (mEAniCount < EANICOUNT / 2)/*	EANICOUNT(30)を２で割ったものより
								小さいとき*/
	{

		if (mFx >= 0) //ｘ方向に進んでいれば
		{
			CRectangle::Render(Texture, 128, 155, 193, 161);//(左、右、下、上)
		}
		else //-x方向に進んでいれば
		{
			CRectangle::Render(Texture, 155, 128, 193, 161);//(左、右、下、上)
		}
	}
	else//EANICOUNT(15)より大きいとき
	{
		if (mFx >= 0) //ｘ方向に進んでいれば

		{
			CRectangle::Render(Texture, 160, 187, 193, 161);//(左、右、下、上)
		}
		else //-x方向に進んでいれば
		{
			CRectangle::Render(Texture, 187, 160, 193, 161);//(左、右、下、上)
		}
	}
	
}

void CEnemy::Collision(CRectangle *i, CRectangle *y) {
	
	if (Collision(*y))
	{
		
	}

}
