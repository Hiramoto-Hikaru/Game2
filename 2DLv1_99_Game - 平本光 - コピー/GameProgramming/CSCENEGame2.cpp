#include "CSceneGame2.h"
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
#include"CItem.h"
#include"CEnemy3.h"
#include"CDeathBlock.h"
#include"CDisappear.h"
#include"CDisappear2.h"
#include"CCoin.h"
#include"CSound.h"
#include"CBackGround3.h"


extern CTexture Texture5;
void CSceneGame2::Init() {
	//static変数にすれば、クラス外でも使用できる
	
	
	ZankiCount = CSceneGame::mZanki - 1;
	CSceneGame::Treasure = 0;
	CSceneGame2::Coin = 0;
	//シーンの設定
	mScene = EGAME2;
	//サウンドファイル（wav）の読み込み
	Bgm.Load("BGM.wav");
	Se.Load("jump.wav");
	//サウンドファイルの繰り返し再生
	Bgm.Repeat();

	Texture.Load("Image.tga");
	Texture5.Load("imagesss.tga");
	//文字画像の読み込み
	CText::mFont.Load("font.tga");

	

	int map[40][50] =
	{
		{ 01,00,00,00,00,00,00,00,00,01,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00} ,
		{ 01,00,00,00,00,00,00,00,00,01,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00} ,
		{ 01,00,00,00,00,00,00,00,00,01,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00} ,
		{ 01,00,00,00,00,00,00,06,00,01,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00} ,
		{ 01,00,00,00,00,00,00,00,00,01,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00},
		{ 01,01,01,01,01,01,01,01,11,01,01,01,01,01,01,01,01,01,01,01,01,01,01,01,01,01,01,01,01,01,01,01,01,01,01,01,01,01,01,01,01,01,01,01,01,01,01,01,01,01},
		{ 01,00,00,00,00,00,00,01,11,01,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,06,00,00,01},
		{ 01,00,00,00,00,00,00,01,11,01,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,11,11,00,00,11,03,11,00,00,06,00,00,00,01},
		{ 01,00,00,11,00,00,00,01,11,01,00,00,00,00,00,00,00,00,00,00,00,00,00,11,11,00,00,00,00,00,00,00,00,00,00,00,00,00,02,00,00,11,00,00,00,00,00,00,00,01},
		{ 01,00,11,07,11,00,00,01,11,01,00,00,00,00,00,11,00,00,00,11,00,00,00,00,00,00,11,00,00,00,00,00,11,11,00,00,00,00,00,00,00,00,00,00,00,00,06,00,00,01},
		{ 01,00,00,11,00,00,00,01,11,01,00,00,00,00,11,11,00,00,00,00,01,00,01,01,01,00,00,00,00,00,00,00,00,00,00,00,01,01,01,00,00,00,00,00,01,01,01,00,11,01},
		{ 01,00,00,00,00,00,00,01,11,01,00,00,00,00,00,01,01,01,01,00,00,00,00,00,00,00,00,01,01,01,01,00,00,01,01,00,00,00,00,00,00,01,00,00,00,00,00,00,11,01},
		{ 01,00,00,00,00,00,00,14,11,00,00,00,00,00,00,00,00,00,14,00,00,00,00,00,00,00,00,00,00,14,00,00,00,00,00,00,00,00,00,00,00,00,14,00,00,00,00,00,11,01},
		{ 01,00,00,00,00,00,00,00,11,00,00,01,01,01,10,00,00,00,00,10,00,10,00,00,00,10,10,00,00,00,00,10,10,00,00,10,00,00,00,10,10,00,10,10,01,00,00,00,11,01},
		{ 01,01,01,01,01,01,01,01,01,01,01,01,01,01,01,01,01,01,01,01,01,01,01,01,01,01,01,01,01,01,01,01,01,01,01,01,01,01,01,01,01,01,01,01,00,00,00,00,11,01},
		{ 01,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,06,00,00,00,00,00,00,00,00,00,00,00,00,00,00,11,01},
		{ 01,00,00,00,00,00,00,00,00,02,00,00,00,00,00,01,00,00,00,00,02,00,00,00,00,00,00,00,00,00,00,01,00,00,00,00,06,00,00,00,00,00,00,00,00,00,00,00,01,01},
		{ 01,00,01,00,00,11,11,00,00,00,00,00,00,00,00,11,00,11,11,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,11,11,00,00,00,00,00,00,11,11,00,00,00,00,01},
		{ 01,00,00,03,00,00,00,00,00,00,00,07,00,00,00,11,00,01,00,00,00,00,01,00,11,00,00,00,00,00,00,11,00,00,06,01,01,00,00,00,00,00,00,00,00,00,00,00,00,01},
		{ 01,11,00,00,01,01,00,00,00,00,00,01,01,01,00,11,00,00,00,00,01,00,00,00,00,00,01,00,01,00,00,00,00,06,00,00,00,00,00,06,00,00,01,01,00,00,01,01,01,01},
		{ 01,01,11,00,00,00,00,14,01,01,00,00,00,00,00,01,00,00,01,00,00,00,00,00,01,00,00,00,00,14,01,01,00,01,00,00,00,01,01,01,01,00,00,00,00,00,00,00,00,01},
		{ 01,00,11,01,00,00,10,10,00,00,10,00,00,00,10,00,10,10,14,10,10,10,10,10,00,00,00,10,00,10,00,00,10,00,10,00,00,00,00,00,00,10,14,00,10,10,00,00,00,01},
		{ 01,00,11,01,01,01,01,01,01,01,01,01,01,01,01,01,01,01,01,01,01,01,01,01,01,01,01,01,01,01,01,01,01,01,01,01,01,01,01,01,01,01,01,01,01,01,01,01,01,01},
		{ 01,00,01,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,01},
		{ 01,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,11,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,01},
		{ 01,01,00,00,00,00,11,00,00,00,00,00,00,00,00,00,00,00,00,00,00,13,00,00,11,00,00,00,00,11,11,00,13,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,01},
		{ 01,11,00,00,00,00,11,00,13,00,01,00,00,00,00,11,11,11,00,01,00,01,00,00,01,00,00,00,00,00,00,00,01,00,01,00,13,00,00,11,11,11,00,00,00,00,00,00,00,01},
		{ 01,11,00,00,01,00,01,00,01,00,00,11,00,00,00,00,00,00,00,00,00,00,00,01,00,00,00,13,01,00,00,01,00,00,00,01,01,00,00,00,00,03,00,00,00,00,00,00,00,01},
		{ 01,00,01,00,00,00,00,00,00,00,00,01,00,00,13,00,01,01,00,00,00,00,00,00,00,00,01,01,00,00,00,00,00,00,00,00,00,00,00,13,07,13,00,01,01,00,01,11,00,01},
		{ 01,00,00,00,00,00,00,14,00,00,00,00,00,01,01,00,00,00,14,00,00,00,00,00,00,00,00,00,00,14,00,00,00,00,00,00,00,00,00,01,01,01,14,00,00,00,00,11,01,01},
		{ 01,10,00,10,00,10,00,10,00,10,00,00,10,00,00,10,00,00,10,00,00,00,10,00,00,10,00,00,00,10,10,00,00,10,10,00,00,10,10,00,00,00,10,00,00,10,01,11,00,01},
		{ 01,01,01,01,01,01,01,01,01,01,01,01,01,01,01,01,01,01,01,01,01,01,01,01,01,01,01,01,01,01,01,01,01,01,01,01,01,01,01,01,01,01,01,01,01,01,01,11,00,01},
		{ 01,00,00,00,00,00,00,14,00,00,00,01,00,00,00,00,00,00,14,00,00,00,00,00,00,00,00,00,00,14,00,00,00,00,00,00,00,00,00,00,00,00,01,14,00,00,00,01,00,01},
		{ 01,00,00,00,00,11,00,00,00,00,00,01,00,00,00,00,00,11,00,00,00,00,12,00,00,00,00,00,00,00,11,00,00,00,00,00,00,00,00,00,00,00,01,00,00,00,00,00,00,01},
		{ 01,00,00,00,11,03,11,00,00,00,00,00,00,00,00,00,04,00,00,00,11,11,00,00,00,00,00,00,00,00,04,00,11,00,00,00,11,11,00,00,00,00,01,00,00,00,00,00,00,01},
		{ 01,00,00,00,00,11,00,00,00,00,00,00,00,00,00,01,00,00,00,01,12,00,00,01,00,00,11,00,11,00,00,00,12,00,00,00,04,04,00,11,00,00,01,00,00,00,00,00,01,01},
		{ 01,00,00,00,00,00,00,00,00,00,00,01,00,04,04,00,00,00,12,00,00,04,00,00,00,04,00,00,12,01,00,00,00,00,01,00,00,00,00,12,01,00,05,00,00,00,00,00,00,01},
		{ 01,00,00,00,00,00,00,00,00,00,00,01,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,01,05,00,00,00,00,00,00,01},
		{ 01,01,01,01,01,01,01,01,01,01,01,01,01,01,01,01,01,01,01,01,01,01,01,01,01,01,01,01,01,01,01,01,01,01,01,01,01,01,01,01,01,01,01,01,01,01,01,01,01,01},

	};

	for (int j = 0; j < 40; j++) {
		for (int i = 0; i < 50; i++) {
			if (map[j][i] == 14) {
				CBackGround3* BackGround3 = new CBackGround3();
				/*iはx=-350から加算,jはy=250から減算していって
				２のある場所を探す
				*/
				BackGround3->x = i * 55 - 350;
				BackGround3->y = j * -55 + 250;
			}
		}
	}
//クラスのメンバ変数への代入
	CPlayer* Player = new CPlayer();
	Player->x = -220;
	Player->y = 0;
	Player->w = 20;
	Player->h = 20;
	Player->mEnabled = true;
	for (int j = 0; j < 40; j++) {
		for (int i = 0; i < 50; i++) {
			

			//mapの要素が1の時、四角形配置
			if (map[j][i] == 01) {
				CMap* Map = new CMap();
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
				CEnemy* Enemy = new CEnemy();
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
				CDisappear* Disappear = new CDisappear();
				/*iはx=-350から加算,jはy=250から減算していって
				4のある場所を探す
				*/
				Disappear->x = i * 55 - 350;
				Disappear->y = j * -55 + 250;
			}
			else if (map[j][i] == 5) {
				CDoor* Door = new CDoor();
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
				Enemy2->y = j * -55 + 250;
			}
			else if (map[j][i] == 7) {
				CItem* Item = new CItem();
				/*iはx=-350から加算,jはy=250から減算していって
				２のある場所を探す
				*/
				Item->x = i * 55 - 350;
				Item->y = j * -55 + 250;

			}

			else if (map[j][i] == 10) {
				CDeathBlock* DeathBlock = new CDeathBlock();
				/*iはx=-350から加算,jはy=250から減算していって
				２のある場所を探す
				*/
				DeathBlock->x = i * 55 - 350;
				DeathBlock->y = j * -55 + 250;

			}
			else if (map[j][i] == 11) {
				CCoin* Coin = new CCoin();
				/*iはx=-350から加算,jはy=250から減算していって
				２のある場所を探す
				*/
				Coin->x = i * 55 - 350;
				Coin->y = j * -55 + 250;

			}
			else if (map[j][i] == 12) {
				CDisappear2* Disappear2 = new CDisappear2();
				/*iはx=-350から加算,jはy=250から減算していって
				4のある場所を探す
				*/
				Disappear2->x = i * 55 - 350;
				Disappear2->y = j * -55 + 250;
			}
			else if (map[j][i] == 13) {
				CEnemy3* Enemy3 = new CEnemy3();
				/*iはx=-350から加算,jはy=250から減算していって
				２のある場所を探す
				*/
				Enemy3->x = i * 55 - 350;
				Enemy3->y = j * -55 + 250;
				//右へ移動
				Enemy3->mFx = -1;
				Enemy3->mFy = 0;
			}


		}
	}
}

void CSceneGame2::Update() {

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
			delete* itr;//配列要素の参照　　*変数名
			//リストからも削除
			itr = VectorRect.erase(itr);//配列要素の削除
		}
	}



	//描画範囲変数の作成　範囲下：-300　範囲上：300 固定
	double mLeft, mRight, mBottom, mTop;
	mBottom = CPlayer::spInstance->y - 270.0;
		mTop = mBottom + 600.0f;
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
	CText::DrawString("COIN", -350, 220, 16, 16);
	
	CText::DrawString("TAKARA", 100, 250, 16, 16);
	CText::DrawString("ZANKI", 100, 220, 16, 16);

	char buf[10];//スコアの描画
	sprintf(buf, "%d ", CSceneGame::SCore);
	CText::DrawString(buf, -170, 250, 16, 16);

    //コインの枚数の描画
	sprintf(buf, "%d", CSceneGame2::Coin);
	CText::DrawString(buf, -170, 220, 16, 16);

     //宝の個数の描画
	sprintf(buf, "%d/4", CSceneGame::Treasure);
	CText::DrawString(buf, 300, 250, 16, 16);

	//残機
	sprintf(buf, "%d", CSceneGame::mZanki);
	CText::DrawString(buf, 300, 220, 16, 16);



	if (CSceneGame::Life <= 0) {
		if (ZankiCount >= 0) {
			sprintf(buf, "ZANKI %d->", CSceneGame::mZanki);
			CText::DrawString(buf, -150, -100, 16, 16);
			sprintf(buf, " %d", ZankiCount);
			CText::DrawString(buf, 100, -100, 16, 16);
		}
		CText::DrawString("GAMEOVER", -270, 0, 40, 40);
		CText::DrawString("Push ENTER Key", -200, -200, 16, 16);
		if (CKey::Once(VK_RETURN)) {
			CSceneGame::mZanki -= 1;
			CSceneGame::Life = 1;
			mScene = EGAMER2;
            if (CSceneGame::mZanki<= -1 ) {
			mScene = ETITLE;
			CSceneGame::mZanki += 4;
		    }
		}
		


	}
	if (CSceneGame::Life > 0 && CSceneGame::Treasure ==4) {
		CText::DrawString("STAGE2 CLEAR", -350, 0, 30, 30);
		CText::DrawString("Push ENTER Key", -200, -100, 16, 16);
		if (CKey::Once(VK_RETURN)) {
			mScene = EGAME3;
		}



	}
	if (CSceneGame2::Coin == 30) {
		CSceneGame::mZanki += 1;
		CSceneGame2::Coin -= 30;

	}

}


//次のシーンの取得
CScene::EScene CSceneGame2::GetNextScene() {
	return mScene;
}
//デストラクタ
CSceneGame2::~CSceneGame2() {
	//全てのインスタンスを削除します
	for (int i = 0; i < VectorRect.size(); i++) {
		//インスタンスの削除
		delete VectorRect[i];
	}
	//可変長配列のクリア
	VectorRect.clear();
}
