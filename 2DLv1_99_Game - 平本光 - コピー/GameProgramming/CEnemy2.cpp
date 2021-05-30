#include"CEnemy2.h"
#include"CRectangle.h"
#include "CTexture.h"
#include"CSceneGame.h"

extern CTexture Texture;
CEnemy2::CEnemy2()
	: mFx(1.0f), 
	  mFy(0.0f)
{
	//列挙型
	mTag = EENEMY2;
	w = 23;
	h = 20;
}

void CEnemy2::Update() {  //クリボー
	//mEnabledがfalseなら戻る
	if (!mEnabled) return;
	x -= mFx;
}
void CEnemy2::Render() {

	if (mFx >= 0) //ｘ方向に進んでいれば
	{
		CRectangle::Render(Texture, 122, 104, 178, 159);//(左、右、下、上)

	}


	else
		//-x方向に進んでいれば
	{
		CRectangle::Render(Texture, 104, 122, 178, 159);//(左、右、下、上)
	}
}
void CEnemy2::Collision(CRectangle* i, CRectangle* y) {
	//親のCollisionメソッドを呼び出す
	if (CRectangle::Collision(*y)) {
		switch (y->mTag) {
		case EBLOCK:
			//衝突していれば反転
			mFx *= -1;
			mFy *= -1;

			break;
		case EPLAYERBULLET:
			

			//プレイヤーの弾に当たると、無効にする
			mEnabled = false;
			CSceneGame::SCore += 10;
		    
			break;
			
		case EPLAYER:
         
		      	mEnabled = false;
				
                 CSceneGame::Life -= 1;
                  CSceneGame::ItemPoint -= 1;
				
				
				
			
			
				break;

			
		}

	}
	

}
