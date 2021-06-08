#include"CDeathBlock.h"
#include "CTexture.h"
#include "CSceneGame.h"


//extern：他のソースファイルの外部変数にアクセスする宣言
extern CTexture Texture;

CDeathBlock::CDeathBlock()

{   //触ると死ぬブロック
	//列挙型
	mTag = EDEATHBLOCK;
	w = 27;	//幅設定
	h = 27;	//高さ設定
	mEnabled = true;
}

void CDeathBlock::Update() {

}
void CDeathBlock::Render() {
	CRectangle::Render(Texture, 176,192, 46, 32);//(左、右、下、上)
}

void CDeathBlock::Collision(CRectangle* iiy, CRectangle* yyr) {
	if (iiy->mEnabled && yyr->mEnabled) {
		if (yyr->mTag == EPLAYER) {
			if (iiy->Collision(*yyr)) {
				CSceneGame::Life =0;
				CSceneGame::ItemPoint = 0;
				return;
			}



		}
	}
}