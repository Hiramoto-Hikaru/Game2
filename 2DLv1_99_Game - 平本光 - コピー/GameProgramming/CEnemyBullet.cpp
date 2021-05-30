#include "CBoss.h"
#include "CTexture.h"
#include "CSceneGame.h"
#include"CItem.h"
#include"CEnemyBullet.h"


//extern：他のソースファイルの外部変数にアクセスする宣言
extern CTexture Texture;

//デフォルトコンストラクタ
CEnemyBullet::CEnemyBullet()
	: mFx(0), mFy(0)
{
	mEnabled = false;
	w = 10;	//幅設定
	h = 10;	//高さ設定
}

//更新処理
void CEnemyBullet::Update() {
	//有効な時
	if (mEnabled) {
		//移動
		x += mFx;
		y += mFy;
    }
	/*if (y > 600 || y < -400) { //枠外に移動したとき
		mEnabled = false;

	}*/
}

//描画処理
void CEnemyBullet::Render() {
	//有効な時
	if (mEnabled) {
		//親の描画メソッドを呼ぶ
		CRectangle::Render(Texture, 241, 255, 31, 17);
	}
}

void CEnemyBullet::Collision(CRectangle* ii, CRectangle* yy) {
	//	if (i->mEnabled && y->mEnabled) {
	if (yy->mTag == EBLOCK) {
		if (ii->Collision(*yy)) {
			mEnabled = false;
			return;
		}
	}

	
		if (ii->mTag == EENEMYBULLET && yy->mTag == EPLAYER) {
			
				if (ii->Collision(*yy)) {
					mEnabled = false;
					CSceneGame::Life -= 1;
					if (CSceneGame::ItemPoint >= 1) {
						CSceneGame::ItemPoint -= 1;
					}

					return;
				}
			
		}
	

	if (ii->mTag == EENEMYBULLET && yy->mTag == EPLAYERBULLET) {
		if (ii->Collision(*yy)) {
			mEnabled = false;
			return;
		}

	}
	
		if (ii->mTag == EBOSSBULLET && yy->mTag == EPLAYER) {
			
				if (ii->Collision(*yy)) {

					mEnabled = false;
					CSceneGame::Life -= 1;
					CSceneGame::ItemPoint -= 1;
					
					return;
				}
			
		}
	
	

	



}