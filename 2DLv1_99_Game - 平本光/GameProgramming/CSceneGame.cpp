#include "CSceneGame.h"
#include "CTexture.h"
#include "CMap.h"
#include "CKey.h"
#include "CRectangle.h"
#include "CBullet.h"
#include "CPlayer.h"
#include "CEnemy.h"
#include "CText.h"
#include"CTreasure.h"
#include"CBoss.h"
#include"CDoor.h"
#include"CDoor2.h"
#include "CEnemy2.h"
#include"CEnemy3.h"
#include"CItem.h"
#include"CDeathBlock.h"
#include"CCoin.h"
#include"CSound.h"
#include"CBackGround.h"
#include"CTexture.h"
#include"CBackGround2.h"
#include"CButton.h"

int CSceneGame::SCore = 0;//static変数にすれば、クラス外でも使用できる
int CSceneGame::Life = 1;
int CSceneGame::Treasure = 0;
int CSceneGame::BossLife = 20;
int CSceneGame::ItemPoint = 0;
int CSceneGame::mZanki = 3;

void CSceneGame::Init() {
	//サウンドファイル（wav）の読み込み
	Bgm.Load("BGM.wav");
	
	Se.Load("jump.wav");
	
	
    //サウンドファイルの繰り返し再生
	Bgm.Repeat();
    Texture.Load("Image.tga");
	Texture2.Load("Image2.tga");
	Texture3.Load("image3.tga");
	Texture4.Load("image4.tga");
	//文字画像の読み込み
	CText::mFont.Load("font.tga");
	
	ZankiCount = mZanki - 1;
	Life = 1;
	Treasure = 0;
	SCore = 0;
	BossLife = 20;
	ItemPoint = 0;
	//シーンの設定
	mScene = EGAME;
	
	

	

	int map[12][80] =
	{
		{ 1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
		{ 1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,1},
		{ 1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,6,1,1,0,1,1,1,0,0,0,0,0,0,0,0,0,1,3,0,0,0,0,2,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,1},
		{ 1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,0,0,0,0,6,0,0,0,0,0,0,0,0,6,0,0,0,0,0,0,1,0,0,0,6,6,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,1},
		{ 1,0,0,0,0,0,0,0,0,0,11,0,0,0,0,0,0,0,0,0,0,6,1,0,6,0,0,0,11,0,0,0,0,0,0,0,0,0,0,1,0,0,1,0,1,0,1,0,1,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,1},
		{ 1,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,6,0,0,0,0,0,0,0,0,0,1,0,0,2,0,0,0,0,1,0,0,0,0,12,0,0,0,0,0,0,7,0,0,1,12,0,0,0,0,0,0,0,0,0,12,0,0,0,0,0,0,0,1,12,0,0,0,0,1},
		{ 1,0,0,0,0,0,0,0,0,0,0,7,0,0,0,0,0,6,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,1,1,1,0,0,1,0,0,0,0,0,0,0,0,0,0,0,4,0,0,0,0,0,0,1,0,0,3,0,0,1},
		{ 1,0,0,0,0,0,0,0,0,1,1,1,0,0,0,0,0,0,0,1,1,0,0,0,0,0,7,0,0,0,1,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,3,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,13,0,0,1,0,0,0,0,0,1},
		{ 1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,6,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,1,0,0,1,0,0,0,0,0,0,0,0,0,0,0,5,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,0,0,8,0,0,0,0,0,1},
		{ 1,0,0,0,0,0,0,0,0,0,0,0,6,0,0,1,1,0,0,0,0,6,0,0,0,0,9,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,6,6,0,0,0,0,0,0,9,0,5,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,1,0,8,0,0,0,0,0,1},
		{ 1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,1,1,1,1,0,0,1,1,1,1,1,1,1,1,1,1,1,0,0,1,1,1,1,1,1,1,1,1,1,1,1,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
		{ 0,0,0,0,0,0,0,0,0,0,0,0,0,10,10,0,0,0,0,10,10,0,0,0,0,0,0,0,0,0,0,0,10,10,0,0,0,0,0,0,0,0,0,0,0,0,10,10,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	};
	for (int j = 0; j < 13; j++) {
		for (int i = 0; i < 80; i++) {
			if (map[j][i] == 11) {
			CBackGround* BackGround = new CBackGround();
			/*iはx=-350から加算,jはy=250から減算していって
			２のある場所を探す
			*/
			BackGround->x = i * 55 - 350;
			BackGround->y = j * -55 + 250;

			}
			else if (map[j][i] == 12) {
				CBackGround2* BackGround2 = new CBackGround2();
				/*iはx=-350から加算,jはy=250から減算していって
				２のある場所を探す
				*/
				BackGround2->x = i * 55 - 350;
				BackGround2->y = j * -55 + 250;
			}
		}
	}
	for (int j = 0; j < 13; j++) {
		for (int i = 0; i < 80; i++) {
			
			//mapの要素が1の時、四角形配置
			if (map[j][i] == 1) {
				CMap *Map = new CMap();
				//四角形に値を設定
				Map->mEnabled = true;
				/*iはx=-350から加算,jはy=250から減算していって
				１のある場所を探す
				*/
				Map->x = i * 55 - 350;
				Map->y = j * -55 + 250;
				Map->w = 30;
				Map->h = 30;
			}
			else if (map[j][i] == 2) {
				CEnemy *Enemy = new CEnemy();
				/*iはx=-350から加算,jはy=250から減算していって
				２のある場所を探す
				*/
				Enemy->x = i * 55 - 350;
				Enemy->y = j * -55 + 250;
				//右へ移動
				Enemy->mFx = -1;
				Enemy->mFy = 0;
			}

			else if (map[j][i] == 3) {
				CTreasure* Treasure = new CTreasure();
				/*iはx=-350から加算,jはy=250から減算していって
				3のある場所を探す
				*/
				Treasure->x = i * 55 - 350;
				Treasure->y = j * -55 + 250;
			}
			else if (map[j][i] == 4) {
				CBoss* Boss = new CBoss();
				/*iはx=-350から加算,jはy=250から減算していって
				4のある場所を探す
				*/
				Boss->x = i * 55 - 350;
				Boss->y = j * -55 + 250;
			}
			else if (map[j][i] == 5) {
				CDoor*Door=new CDoor();
				/*iはx=-350から加算,jはy=250から減算していって
				4のある場所を探す
				*/
				Door->x = i * 55 - 350;
				Door->y = j * -55 + 250;
			}
			
			else if (map[j][i] == 6) {
				CEnemy2* Enemy2 = new CEnemy2();
				/*iはx=-350から加算,jはy=250から減算していって
				4のある場所を探す
				*/
				Enemy2->x = i * 55 - 350;
				Enemy2->y = j * -55+ 250;
			}
			else if (map[j][i] == 7) {
				CItem* Item = new CItem();
				/*iはx=-350から加算,jはy=250から減算していって
				２のある場所を探す
				*/
				Item->x = i * 55 - 350;
				Item->y = j * -55 + 250;
				
			}
			else if (map[j][i] == 8) {
				CDoor2* Door2 = new CDoor2();
				/*iはx=-350から加算,jはy=250から減算していって
				4のある場所を探す
				*/
				Door2->x = i * 55- 350;
				Door2->y = j * -55 + 250;
			}
			else if (map[j][i] == 9) {
				CEnemy3* Enemy3 = new CEnemy3();
				/*iはx=-350から加算,jはy=250から減算していって
				２のある場所を探す
				*/
				Enemy3->x = i * 55- 350;
				Enemy3->y = j * -55 + 250;
				//右へ移動
				Enemy3->mFx = -1;
				Enemy3->mFy = 0;
			}
			else if (map[j][i] == 10) {
				CDeathBlock* DeathBlock = new CDeathBlock();
				/*iはx=-350から加算,jはy=250から減算していって
				２のある場所を探す
				*/
				DeathBlock->x = i * 55 - 350;
				DeathBlock->y = j * -55 + 250;
				
			}
			else if (map[j][i] == 13) {
				CButton* Button = new CButton();
				/*iはx=-350から加算,jはy=250から減算していって
				２のある場所を探す
				*/
				Button->x = i * 55 - 350;
				Button->y = j * -55 + 250;

			}
		}
	}
	//クラスのメンバ変数への代入
	CPlayer *Player = new CPlayer();
	Player->x = -220;
	Player->y = -250;
	Player->w = 20;
	Player->h = 20;
	Player->mEnabled = true;
	
}

void CSceneGame::Update() {
	
	
	/*
	配列の要素分繰り返す
	配列名.size()
	配列の要素数を取得する
	*/
	for (int i = 0; i < VectorRect.size(); i++) {
		/*
		配列の参照
		配列名[添え字]
		通常の配列同様に添え字で要素にアクセスできる
		*/
		//更新処理
		VectorRect[i]->Update();

	}
	for (int i = 0; i < VectorRect.size() - 1; i++) {
		//衝突処理
		for (int j = i + 1; j < VectorRect.size(); j++) {
			VectorRect[i]->Collision(VectorRect[i], VectorRect[j]);
			VectorRect[j]->Collision(VectorRect[j], VectorRect[i]);
		}
	}
	//リストから削除する
	//イテレータの生成
	std::vector<CRectangle*>::iterator itr;//vectorの配列にアクセス
	//イテレータを先頭
	itr = VectorRect.begin();//配列の先頭
	//最後まで繰り返し
	while (itr != VectorRect.end()) {//配列の最後
		if ((*itr)->mEnabled) {
			//配列の次の要素へ
			itr++;
		}
		else {
			//falseのインスタンスを削除
			delete *itr;//配列要素の参照　　*変数名
			//リストからも削除
			itr = VectorRect.erase(itr);//配列要素の削除
		}
	}
	

	
		//描画範囲変数の作成　範囲下：-300　範囲上：300 固定
		double mLeft, mRight, mBottom = -300.0, mTop = 300.0;
		
        //画面範囲左の設定
		mLeft = CPlayer::spInstance->x - 400;
		//画面範囲右の設定
		mRight = mLeft + 800.0f;
		
		
		//画面投影範囲の変更
		//行列をプロジェクションモードに変更
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();//行列を初期化
		//２Dの画面を設定
		gluOrtho2D(mLeft, mRight, mBottom, mTop);
		for (int i = 0; i < VectorRect.size(); i++) {
			//描画処理
			VectorRect[i]->Render();
		}



		glLoadIdentity();//行列を初期化
		//２Dの投影範囲を設定
		gluOrtho2D(-400, 400, -300, 300);
		//画面に固定する文字列の描画
		//CText::DrawString("(-380,280)", -380, 280, 16, 16);
        //文字列の描画
		CText::DrawString("SCORE", -350, 250, 16, 16);
		CText::DrawString("TAKARA", 100, 250, 16, 16);
		CText::DrawString("ZANKI", 100, 220, 16, 16);

		
		char buf[10];//スコアの描画
		sprintf(buf, "%d ", SCore);
		CText::DrawString(buf, -170, 250, 16, 16);

		//宝の個数の描画
		sprintf(buf, "%d/4", Treasure);
		CText::DrawString(buf, 300, 250, 16, 16);

		//残機
		sprintf(buf, "%d",mZanki);
		CText::DrawString(buf, 300, 220, 16, 16);


		if (Life <= 0) {
			
			if (ZankiCount >= 0) {
            sprintf(buf, "ZANKI %d->", mZanki);
			CText::DrawString(buf, -150, -100, 16, 16);
			sprintf(buf, " %d", ZankiCount);
			CText::DrawString(buf, 100, -100, 16, 16);
			}
			

			CText::DrawString("GAMEOVER", -270, 0, 40, 40);
			CText::DrawString("Push ENTER Key", -200, -200, 16, 16);

			if (CKey::Once(VK_RETURN)) {
				mZanki -= 1;
				mScene = EGAMER1;
              if (mZanki <= -1) {
              mScene = ETITLE;
			  mZanki += 4;
			  }

			}
			


		}
		if (Life > 0 &&Treasure==4) {
			CText::DrawString("STAGE1 CLEAR", -300, 0, 30, 30);
			CText::DrawString("Push ENTER Key", -200, -100, 16, 16);
			if (CKey::Once(VK_RETURN)) {
				mScene = EGAME2;
			}



		}
	

}


//次のシーンの取得
CScene::EScene CSceneGame::GetNextScene() {
	return mScene;
}
//デストラクタ
CSceneGame::~CSceneGame() {
	//全てのインスタンスを削除します
	for (int i = 0; i < VectorRect.size(); i++) {
		//インスタンスの削除
		delete VectorRect[i];
	}
	//可変長配列のクリア
	VectorRect.clear();
}
