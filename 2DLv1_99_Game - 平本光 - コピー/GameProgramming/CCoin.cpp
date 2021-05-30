#include "CCoin.h"
#include"CTexture.h"
#include"CSceneGame.h"
#include"CRectangle.h"
#include"CSceneGame2.h"
extern CTexture Texture;
#define CoinCount 10
int CSceneGame2::Coin = 0;
CCoin::CCoin()

{
	w = 10;
	h = 15;
	mTag = ECOIN;
	
}
void CCoin::Collision(CRectangle* i, CRectangle* y) {
	if (CSceneGame::Life > 0) {
		  if (y->mTag == EPLAYER) {
				if (i->Collision(*y)) {
					mEnabled = false;
					CSceneGame::SCore += 10;
					CSceneGame2::Coin += 1;
				}
		  }
		  if (y->mTag == EENEMY4) {
			  if (i->Collision(*y)) {
				  mEnabled = false;
				  CSceneGame::SCore += 10;
				  CSceneGame2::Coin += 1;
			  }
		  }
	}
	
}
void CCoin::Render() {
	//有効な時
	if (mEnabled) {
		CoinAni++;//１ずつ加算される
		CoinAni %= CoinCount;

		if (CoinAni < CoinCount / 2)/*	EANICOUNT(30)を２で割ったものより
									小さいとき*/
		{
			CRectangle::Render(Texture, 159, 168, 24, 12);//(左、右、下、上)

		}
		else//EANICOUNT(15)より大きいとき
		{

			CRectangle::Render(Texture, 145, 154, 25, 13);//(左、右、下、上)

		}
		
	}
}