#include "CBoss.h"
#include "CBullet.h"
#include "CTexture.h"
#include "CSceneGame.h"
#include"CItem.h"
#include"CBoss.h"

//extern：他のソースファイルの外部変数にアクセスする宣言
extern CTexture Texture;

//デフォルトコンストラクタ
CBullet::CBullet()
: mFx(0), mFy(0)
{
	mEnabled = false;
	w = 10;	//幅設定
	h = 10;	//高さ設定
	if (CSceneGame::ItemPoint == 2) {
		w = 18;
		h = 18;
	}
}

//更新処理
void CBullet::Update() {
	//有効な時
	
	if (mEnabled) {  //if(CSceneGame::ItemPoint=1){}  ファイアマリオみたいになる
		//移動
		x += mFx;
		y += mFy;
		if (CSceneGame::ItemPoint == 1) {
			x += 2*mFx;
			y += 2*mFy;
		}
		

	}
}

//描画処理
void CBullet::Render() {
	//有効な時
	if (mEnabled) {
		//親の描画メソッドを呼ぶ
	CRectangle::Render(Texture, 192,207 ,110, 98);
	}
}

void CBullet::Collision(CRectangle* i, CRectangle* y) {
//	if (i->mEnabled && y->mEnabled) {
		if (y->mTag == EBLOCK) {
			if (i->Collision(*y)) {
				mEnabled = false;
				return;
			}
		}
		

		
		if (i->mTag == EPLAYERBULLET && y->mTag == EENEMY) {
			if (i->Collision(*y)) {
				CSceneGame::SCore += 50;
				mEnabled = false;
				return;
			}

		}
		if (i->mTag == EPLAYERBULLET && y->mTag == EENEMY2) {
			if (i->Collision(*y)) {
				
				mEnabled = false;
				return;
			}

		}

		if (i->mTag == EPLAYERBULLET && y->mTag == EBOSS) {

			if (i->Collision(*y)) {
				CBoss::bosscount += 60;
				CSceneGame::BossLife -= 1;
				mEnabled = false;
				return;

			}
		}
       
		if (i->mTag == EENEMYBULLET  && y->mTag ==EPLAYERBULLET) {
			if (i->Collision(*y)) {
				mEnabled = false;
				return;
			}

		}
		if (i->mTag == EPLAYERBULLET && y->mTag == EENEMYBULLET) {
			if (i->Collision(*y)) {
				mEnabled = false;
				return;
			}

		}
		if (i->mTag == EPLAYERBULLET && y->mTag == EBOSSBULLET) {
			if (i->Collision(*y)) {
				mEnabled = false;
				return;
			}

		}
		if (i->mTag == EPLAYERBULLET && y->mTag == EENEMYBULLET2) {
			if (i->Collision(*y)) {
				mEnabled = false;
				return;
			}

		}
		if (i->mTag == EPLAYERBULLET && y->mTag == EENEMY2) {
			if (i->Collision(*y)) {
				mEnabled = false;
				return;
			}

		}
		if (i->mTag == EPLAYERBULLET && y->mTag == EENEMY3) {
			if (i->Collision(*y)) {
				mEnabled = false;
				return;
			}

		}


		
		
		

}
