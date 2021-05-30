#include "CTexture.h"
#include "CSceneGame.h"
#include"CItem.h"
#include"CEnemyBullet2.h"


//extern：他のソースファイルの外部変数にアクセスする宣言
extern CTexture Texture;
#define EBULLETCOUNT 15

#define VBO 20//弾の上昇値
#define G  1//重力


//デフォルトコンストラクタ
CEnemyBullet2::CEnemyBullet2()
	: mFx(0),mFy(0),mbulletcount(0)
{
	mEnabled = false;
	w = 15;	//幅設定
	h = 15;	//高さ設定	
	mFy = VBO;
}

//更新処理
void CEnemyBullet2::Update() {
	//有効な時
	if (mEnabled) {
		//移動
		mFx = -3;
		x += mFx;
	
		
	}
    y += mFy;
	mFy -= G;
	if (y < -2000) {
		mEnabled = false;
	}
	
	
}

//描画処理
void CEnemyBullet2::Render() {


	
     mbulletcount ++;
	 mbulletcount %= EBULLETCOUNT;
	 if (mbulletcount < EBULLETCOUNT/ 2)
	  {
		//親の描画メソッドを呼ぶ
		CRectangle::Render(Texture, 191, 208, 126, 112);
	 }
	  else {
		CRectangle::Render(Texture, 208, 225, 126, 112);
	  }
	
}

void CEnemyBullet2::Collision(CRectangle* iii, CRectangle* yyy) {
	//	if (i->mEnabled && y->mEnabled) {
	

		if (iii->mTag == EENEMYBULLET2 && yyy->mTag == EPLAYER) {
			
				if (iii->Collision(*yyy)) {
					mEnabled = false;
					CSceneGame::Life -= 1;
					CSceneGame::ItemPoint -= 1;
					
					return;
				}
			
		}
	

	if (iii->mTag == EENEMYBULLET2 && yyy->mTag == EPLAYERBULLET) {
		if (iii->Collision(*yyy)) {
			mEnabled = false;
			return;
		}

	}

	
	



}