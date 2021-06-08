#include"CItem.h"
#include "CTexture.h"
#include "CSceneGame.h"
#include"CRectangle.h"
#include"CPlayer.h"
#include"CSound.h"

extern CTexture Texture;
CItem::CItem() {
	
    w = 30;
	h = 10;
	Se3.Load("powerup01.wav");
	

 
   mTag = EITEM;

}
void CItem::Update() {
  if (CSceneGame::ItemPoint >=1) {
		w = 30;
		h = 30;

  }
  else{
	  w = 30;
	  h = 10;

  }

}
void CItem::Render() {
	if (CSceneGame::ItemPoint == 0) {
	CRectangle::Render(Texture, 194, 218, 194, 186);//(左、右、下、上)
    }
	if (CSceneGame::ItemPoint >= 1) {
	CRectangle::Render(Texture, 103, 122, 254, 224);//(左、右、下、上)
	}
}
void CItem::Collision(CRectangle* i, CRectangle* y) {
	if (CSceneGame::Life > 0) {

	
		if (y->mTag == EPLAYER) {
			if (i->Collision(*y)) {
				Se3.Play();
				CSceneGame::SCore += 100;
				
				mEnabled = false;
				if (CSceneGame::Life < 3) {
                 CSceneGame::Life += 1;
				}
                
				if (CSceneGame::ItemPoint < 2){
					CSceneGame::ItemPoint += 1;
			    }
               return;
			}
		}
    }
	
}
bool CItem::Collision(const CRectangle& r) {

	return false;
}
