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
	//static�ϐ��ɂ���΁A�N���X�O�ł��g�p�ł���
    CSceneGame::BossLife = 20;
	CSceneGame::Treasure = 0;
	CSceneGame2::Coin = 0;
	//�V�[���̐ݒ�
	mScene = EGAME3;
	//�T�E���h�t�@�C���iwav�j�̓ǂݍ���
	Bgm.Load("BGM.wav");
	
	Se.Load("jump.wav");

	//�T�E���h�t�@�C���̌J��Ԃ��Đ�
	Bgm.Repeat();

	Texture.Load("Image.tga");
	//�����摜�̓ǂݍ���
	CText::mFont.Load("font.tga");

	//�N���X�̃����o�ϐ��ւ̑��
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


			//map�̗v�f��1�̎��A�l�p�`�z�u
			if (map[j][i] == 01) {
				CMap* Map = new CMap();
				//�l�p�`�ɒl��ݒ�
				Map->mEnabled = true;
				/*i��x=-350������Z,j��y=250���猸�Z���Ă�����
				�P�̂���ꏊ��T��
				*/
				Map->x = i * 55 - 350;
				Map->y = j * -55 + 250;
				Map->w = 30;
				Map->h = 30;
			}

			//map�̗v�f��1�̎��A�l�p�`�z�u
			if (map[j][i] == 02) {
				CTrophy* Trophy = new CTrophy();
				
				/*i��x=-350������Z,j��y=250���猸�Z���Ă�����
				�P�̂���ꏊ��T��
				*/
				Trophy->x = i * 55 - 350;
				Trophy->y = j * -55 + 250;
				
			}


			else if (map[j][i] == 3) {
				CTreasure* Treasure = new CTreasure();
				/*i��x=-350������Z,j��y=250���猸�Z���Ă�����
				3�̂���ꏊ��T��
				*/
				Treasure->x = i * 55 - 350;
				Treasure->y = j * -55 + 250;
			}
			else if (map[j][i] == 4) {
				CBoss* Boss = new CBoss();
				/*i��x=-350������Z,j��y=250���猸�Z���Ă�����
				4�̂���ꏊ��T��
				*/
				Boss->x = i * 55 - 350;
				Boss->y = j * -55 + 250;
			}
			else if (map[j][i] == 5) {
				CObject*Object = new CObject();
				/*i��x=-350������Z,j��y=250���猸�Z���Ă�����
				4�̂���ꏊ��T��
				*/
				Object->x = i * 55 - 350;
				Object->y = j * -55 + 250;
			}
			else if (map[j][i] == 6) {
				CEnemy2* Enemy2 = new CEnemy2();
				/*i��x=-350������Z,j��y=250���猸�Z���Ă�����
				4�̂���ꏊ��T��
				*/
				Enemy2->x = i * 55 - 350;
				Enemy2->y = j * -55 + 250;
			}
			else if (map[j][i] == 10) {
				CDeathBlock* DeathBlock = new CDeathBlock();
				/*i��x=-350������Z,j��y=250���猸�Z���Ă�����
				�Q�̂���ꏊ��T��
				*/
				DeathBlock->x = i * 55 - 350;
				DeathBlock->y = j * -55 + 250;

			}
			else if (map[j][i] == 11) {
				CCoin* Coin = new CCoin();
				/*i��x=-350������Z,j��y=250���猸�Z���Ă�����
				�Q�̂���ꏊ��T��
				*/
				Coin->x = i * 55 - 350;
				Coin->y = j * -55 + 250;

			}
			
		
			else if (map[j][i] == 14) {
			CEnemy4* Enemy4 = new CEnemy4();
			/*i��x=-350������Z,j��y=250���猸�Z���Ă�����
			�Q�̂���ꏊ��T��
			*/
			Enemy4->x = i * 55 - 350;
			Enemy4->y = j * -55 + 250;
			//�E�ֈړ�
			Enemy4->mFx = -1;
			Enemy4->mFy = 0;
			}



		}
	}
}

void CSceneGame3::Update() {

	/*
	�z��̗v�f���J��Ԃ�
	�z��.size()
	�z��̗v�f�����擾����
	*/
	for (int i = 0; i < VectorRect.size(); i++) {
		/*
		�z��̎Q��
		�z��[�Y����]
		�ʏ�̔z�񓯗l�ɓY�����ŗv�f�ɃA�N�Z�X�ł���
		*/
		//�X�V����
		VectorRect[i]->Update();

	}
	for (int i = 0; i < VectorRect.size() - 1; i++) {
		//�Փˏ���
		for (int j = i + 1; j < VectorRect.size(); j++) {
			VectorRect[i]->Collision(VectorRect[i], VectorRect[j]);
			VectorRect[j]->Collision(VectorRect[j], VectorRect[i]);
		}
	}
	//���X�g����폜����
	//�C�e���[�^�̐���
	std::vector<CRectangle*>::iterator itr;//vector�̔z��ɃA�N�Z�X
	//�C�e���[�^��擪
	itr = VectorRect.begin();//�z��̐擪
	//�Ō�܂ŌJ��Ԃ�
	while (itr != VectorRect.end()) {//�z��̍Ō�
		if ((*itr)->mEnabled) {
			//�z��̎��̗v�f��
			itr++;
		}
		else {
			//false�̃C���X�^���X���폜
			delete* itr;//�z��v�f�̎Q�Ɓ@�@*�ϐ���
			//���X�g������폜
			itr = VectorRect.erase(itr);//�z��v�f�̍폜
		}
	}



	//�`��͈͕ϐ��̍쐬�@�͈͉��F-300�@�͈͏�F300 �Œ�
	double mLeft, mRight,mBottom,mTop;
	mBottom = - 270.0;
	mTop = mBottom + 600.0f;
	//��ʔ͈͍��̐ݒ�
	mLeft = CPlayer::spInstance->x - 400;
	//��ʔ͈͉E�̐ݒ�
	mRight = mLeft + 800.0f;
	//��ʓ��e�͈͂̕ύX
	//�s����v���W�F�N�V�������[�h�ɕύX
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();//�s���������
	//�QD�̉�ʂ�ݒ�
	gluOrtho2D(mLeft, mRight,mBottom,mTop);
	for (int i = 0; i < VectorRect.size(); i++) {
		//�`�揈��
		VectorRect[i]->Render();
	}



	glLoadIdentity();//�s���������
	//�QD�̓��e�͈͂�ݒ�
	gluOrtho2D(-400, 400, -300, 300);
	//��ʂɌŒ肷�镶����̕`��
	//CText::DrawString("(-380,280)", -380, 280, 16, 16);
	//������̕`��
	CText::DrawString("SCORE", -350, 250, 16, 16);
	CText::DrawString("COIN", -350, 220, 16, 16);
	CText::DrawString("ZANKI", 100, 220, 16, 16);
	CText::DrawString("TROPHY", 100, 250, 16, 16);

	char Buf[10];//�c�@�̕`��
	sprintf(Buf, "%d", CSceneGame::mZanki);
	CText::DrawString(Buf, 300, 220, 16, 16);

	char buf[10];//�X�R�A�̕`��
	sprintf(buf, "%d ", CSceneGame::SCore);
	CText::DrawString(buf, -170, 250, 16, 16);

	char duf[10];//�R�C���̖����̕`��
	sprintf(duf, "%d", CSceneGame2::Coin);
	CText::DrawString(duf, -170, 220, 16, 16);

	char puf[10];//��̌��̕`��
	sprintf(puf, "%d/1", CSceneGame::Treasure);
	CText::DrawString(puf, 300, 250, 16, 16);




	if (CSceneGame::Life <= 0) {
		
		if (CSceneGame::mZanki > 0) {
          CSceneGame::mZanki--;//CSceneGame���ƂɎc�@�̕ϐ������
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


//���̃V�[���̎擾
CScene::EScene CSceneGame3::GetNextScene() {
	return mScene;
}
//�f�X�g���N�^
CSceneGame3::~CSceneGame3() {
	//�S�ẴC���X�^���X���폜���܂�
	for (int i = 0; i < VectorRect.size(); i++) {
		//�C���X�^���X�̍폜
		delete VectorRect[i];
	}
	//�ϒ��z��̃N���A
	VectorRect.clear();
}
