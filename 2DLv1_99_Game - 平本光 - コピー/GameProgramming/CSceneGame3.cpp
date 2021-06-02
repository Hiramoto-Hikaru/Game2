#include "CTexture.h"
#include "CMap.h"
#include "CKey.h"
#include "CRectangle.h"
#include "CBullet.h"
#include "CPlayer.h"
#include "CText.h"
#include"CTreasure.h"
#include"CBoss.h"
#include"CDoor.h"
#include"CDoor2.h"
#include "CEnemy2.h"
#include "CEnemy4.h"
#include"CItem.h"
#include"CEnemy3.h"
#include"CDeathBlock.h"
#include"CDisappear.h"
#include"CDisappear2.h"
#include"CCoin.h"
#include"CSound.h"
#include"CSceneGame3.h"
#include"CSceneGame2.h"
#include"CTrophy.h"
#include"CObject.h"


void CSceneGame3::Init() {
	//static変数にすれば、クラス外でも使用できる
    CSceneGame::BossLife = 20;
	CSceneGame::Treasure = 0;
	CSceneGame2::Coin = 0;
	//シーンの設定
	mScene = EGAME3;
	//サウンドファイル（wav）の読み込み
	Bgm.Load("BGM.wav");
	Se.Load("jump.wav");
	//サウンドファイルの繰り返し再生
	Bgm.Repeat();

	Texture.Load("Image.tga");
	//文字画像の読み込み
	CText::mFont.Load("font.tga");

	//クラスのメンバ変数への代入
	CPlayer* Player = new CPlayer();
	Player->x = 0;
	Player->y = -200;
	
	Player->mEnabled = true;

	int map[12][70] =
	{
		{00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00} ,
		{00,00,00,00,00,00,01,00,00,00,00,00,00,00,00,00,00,00,00,00,11,11,11,11,11,00,00,00,00,00,00,00,11,11,11,11,11,11,11,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00} ,
		{00,00,00,00,00,01,00,01,00,00,00,00,00,00,00,00,00,00,00,00,11,11,11,11,11,00,00,00,00,00,00,00,11,11,11,11,11,11,11,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00} ,
		{00,00,00,00,01,06,06,06,01,00,00,00,00,00,00,00,00,00,00,00,11,11,11,11,11,00,00,00,04,00,00,00,11,11,11,11,11,11,11,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00} ,
		{00,00,00,01,01,01,01,01,01,01,00,00,00,00,00,00,00,11,11,11,11,11,11,01,14,11,11,11,11,11,11,11,11,11,11,11,11,01,14,11,11,11,11,11,11,11,11,11,11,11,01,01,01,01,11,11,00,00,00,00,00,00,00,00,00,00} ,
		{00,00,01,00,00,00,00,00,00,00,01,00,00,00,00,00,00,11,11,11,01,01,01,01,01,11,11,11,11,11,11,01,01,01,01,01,01,01,01,11,11,11,11,11,11,11,11,11,01,14,11,11,11,11,11,11,00,00,00,00,00,00,00,00,00,00} ,
		{00,01,01,00,00,00,00,00,00,00,01,01,00,00,00,00,00,11,11,11,11,11,11,11,11,11,11,11,11,11,11,11,11,11,11,11,11,11,11,11,11,11,11,11,11,11,01,01,01,01,11,11,11,11,11,11,00,00,00,00,00,00,00,00,00,00} ,
		{00,00,01,00,00,00,00,00,00,00,01,00,00,05,00,00,00,11,11,11,11,11,11,11,11,11,11,11,11,11,11,11,11,11,11,11,11,11,11,11,11,11,11,11,11,11,11,11,11,11,11,11,11,11,11,11,00,00,00,02,00,00,00,00,00,00} ,
		{00,00,01,00,00,00,00,00,00,00,00,00,00,01,14,00,00,11,11,11,11,11,11,11,01,11,11,11,11,11,01,14,11,11,11,11,11,11,11,01,11,11,11,11,11,11,11,11,11,11,11,11,11,11,11,11,01,01,01,01,01,01,01,01,01,01} ,
		{00,00,01,01,01,01,01,01,01,01,01,01,01,01,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,00,10,10,10,10,10,10,10,10,10} ,
		{00,00,01,01,01,01,01,01,01,01,01,01,01,01,01,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00} ,

		
	};

	for (int j = 0; j < 12; j++) {
		for (int i = 0; i < 60; i++) {


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

			//mapの要素が1の時、四角形配置
			if (map[j][i] == 02) {
				CTrophy* Trophy = new CTrophy();
				
				/*iはx=-350から加算,jはy=250から減算していって
				１のある場所を探す
				*/
				Trophy->x = i * 55 - 350;
				Trophy->y = j * -55 + 250;
				
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
				CObject*Object = new CObject();
				/*iはx=-350から加算,jはy=250から減算していって
				4のある場所を探す
				*/
				Object->x = i * 55 - 350;
				Object->y = j * -55 + 250;
			}
			else if (map[j][i] == 6) {
				CEnemy2* Enemy2 = new CEnemy2();
				/*iはx=-350から加算,jはy=250から減算していって
				4のある場所を探す
				*/
				Enemy2->x = i * 55 - 350;
				Enemy2->y = j * -55 + 250;
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
			
		
			else if (map[j][i] == 14) {
			CEnemy4* Enemy4 = new CEnemy4();
			/*iはx=-350から加算,jはy=250から減算していって
			２のある場所を探す
			*/
			Enemy4->x = i * 55 - 350;
			Enemy4->y = j * -55 + 250;
			//右へ移動
			Enemy4->mFx = -1;
			Enemy4->mFy = 0;
			}



		}
	}
}

void CSceneGame3::Update() {

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
	double mLeft, mRight,mBottom,mTop;
	mBottom = - 270.0;
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
	gluOrtho2D(mLeft, mRight,mBottom,mTop);
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
	CText::DrawString("ZANKI", 100, 220, 16, 16);
	CText::DrawString("TROPHY", 100, 250, 16, 16);

	char Buf[10];//残機の描画
	sprintf(Buf, "%d", CSceneGame::mZanki);
	CText::DrawString(Buf, 300, 220, 16, 16);

	char buf[10];//スコアの描画
	sprintf(buf, "%d ", CSceneGame::SCore);
	CText::DrawString(buf, -170, 250, 16, 16);

	char duf[10];//コインの枚数の描画
	sprintf(duf, "%d", CSceneGame2::Coin);
	CText::DrawString(duf, -170, 220, 16, 16);

	char puf[10];//宝の個数の描画
	sprintf(puf, "%d/1", CSceneGame::Treasure);
	CText::DrawString(puf, 300, 250, 16, 16);




	if (CSceneGame::Life <= 0) {
		if (CSceneGame::mZanki > 0) {
          CSceneGame::mZanki--;//CSceneGameごとに残機の変数を作る
		}
      
		CText::DrawString("GAMEOVER", -270, 0, 40, 40);

		CText::DrawString("Push ENTER Key", -200, -100, 16, 16);
		if (CKey::Once(VK_RETURN)) {
			
				
			CSceneGame::mZanki += 3;
			mScene = ETITLE;
		}


	}
	if (CSceneGame::Life > 0 && CSceneGame::Treasure == 4) {
		if (CSceneGame::mZanki > 1) {
			CSceneGame::mZanki--;
		}

		CText::DrawString("BONUS STAGE CLEAR", -300, 0, 20, 20);
		CText::DrawString("Push ENTER Key", -200, -100, 16, 16);
		if (CKey::Once(VK_RETURN)) {
			CTrophy::TrophyCount -= 1;
			CSceneGame::mZanki += 2;
			mScene = ETITLE;
		}



	}
	if (CSceneGame2::Coin == 30) {
		CSceneGame::mZanki += 1;
		CSceneGame2::Coin -= 30;

	}

}


//次のシーンの取得
CScene::EScene CSceneGame3::GetNextScene() {
	return mScene;
}
//デストラクタ
CSceneGame3::~CSceneGame3() {
	//全てのインスタンスを削除します
	for (int i = 0; i < VectorRect.size(); i++) {
		//インスタンスの削除
		delete VectorRect[i];
	}
	//可変長配列のクリア
	VectorRect.clear();
}
