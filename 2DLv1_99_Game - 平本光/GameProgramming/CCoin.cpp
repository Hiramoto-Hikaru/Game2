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
	//�L���Ȏ�
	if (mEnabled) {
		CoinAni++;//�P�����Z�����
		CoinAni %= CoinCount;

		if (CoinAni < CoinCount / 2)/*	EANICOUNT(30)���Q�Ŋ��������̂��
									�������Ƃ�*/
		{
			CRectangle::Render(Texture, 159, 168, 24, 12);//(���A�E�A���A��)

		}
		else//EANICOUNT(15)���傫���Ƃ�
		{

			CRectangle::Render(Texture, 145, 154, 25, 13);//(���A�E�A���A��)

		}
		
	}
}