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

int CSceneGame::SCore = 0;//static�ϐ��ɂ���΁A�N���X�O�ł��g�p�ł���
int CSceneGame::Life = 1;
int CSceneGame::Treasure = 0;
int CSceneGame::BossLife = 20;
int CSceneGame::ItemPoint = 0;
int CSceneGame::mZanki = 3;

void CSceneGame::Init() {
	//�T�E���h�t�@�C���iwav�j�̓ǂݍ���
	Bgm.Load("BGM.wav");
	
	Se.Load("jump.wav");
	
	
    //�T�E���h�t�@�C���̌J��Ԃ��Đ�
	Bgm.Repeat();
    Texture.Load("Image.tga");
	Texture2.Load("Image2.tga");
	Texture3.Load("image3.tga");
	Texture4.Load("image4.tga");
	//�����摜�̓ǂݍ���
	CText::mFont.Load("font.tga");
	
	ZankiCount = mZanki - 1;
	Life = 1;
	Treasure = 0;
	SCore = 0;
	BossLife = 20;
	ItemPoint = 0;
	//�V�[���̐ݒ�
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
			/*i��x=-350������Z,j��y=250���猸�Z���Ă�����
			�Q�̂���ꏊ��T��
			*/
			BackGround->x = i * 55 - 350;
			BackGround->y = j * -55 + 250;

			}
			else if (map[j][i] == 12) {
				CBackGround2* BackGround2 = new CBackGround2();
				/*i��x=-350������Z,j��y=250���猸�Z���Ă�����
				�Q�̂���ꏊ��T��
				*/
				BackGround2->x = i * 55 - 350;
				BackGround2->y = j * -55 + 250;
			}
		}
	}
	for (int j = 0; j < 13; j++) {
		for (int i = 0; i < 80; i++) {
			
			//map�̗v�f��1�̎��A�l�p�`�z�u
			if (map[j][i] == 1) {
				CMap *Map = new CMap();
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
			else if (map[j][i] == 2) {
				CEnemy *Enemy = new CEnemy();
				/*i��x=-350������Z,j��y=250���猸�Z���Ă�����
				�Q�̂���ꏊ��T��
				*/
				Enemy->x = i * 55 - 350;
				Enemy->y = j * -55 + 250;
				//�E�ֈړ�
				Enemy->mFx = -1;
				Enemy->mFy = 0;
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
				CDoor*Door=new CDoor();
				/*i��x=-350������Z,j��y=250���猸�Z���Ă�����
				4�̂���ꏊ��T��
				*/
				Door->x = i * 55 - 350;
				Door->y = j * -55 + 250;
			}
			
			else if (map[j][i] == 6) {
				CEnemy2* Enemy2 = new CEnemy2();
				/*i��x=-350������Z,j��y=250���猸�Z���Ă�����
				4�̂���ꏊ��T��
				*/
				Enemy2->x = i * 55 - 350;
				Enemy2->y = j * -55+ 250;
			}
			else if (map[j][i] == 7) {
				CItem* Item = new CItem();
				/*i��x=-350������Z,j��y=250���猸�Z���Ă�����
				�Q�̂���ꏊ��T��
				*/
				Item->x = i * 55 - 350;
				Item->y = j * -55 + 250;
				
			}
			else if (map[j][i] == 8) {
				CDoor2* Door2 = new CDoor2();
				/*i��x=-350������Z,j��y=250���猸�Z���Ă�����
				4�̂���ꏊ��T��
				*/
				Door2->x = i * 55- 350;
				Door2->y = j * -55 + 250;
			}
			else if (map[j][i] == 9) {
				CEnemy3* Enemy3 = new CEnemy3();
				/*i��x=-350������Z,j��y=250���猸�Z���Ă�����
				�Q�̂���ꏊ��T��
				*/
				Enemy3->x = i * 55- 350;
				Enemy3->y = j * -55 + 250;
				//�E�ֈړ�
				Enemy3->mFx = -1;
				Enemy3->mFy = 0;
			}
			else if (map[j][i] == 10) {
				CDeathBlock* DeathBlock = new CDeathBlock();
				/*i��x=-350������Z,j��y=250���猸�Z���Ă�����
				�Q�̂���ꏊ��T��
				*/
				DeathBlock->x = i * 55 - 350;
				DeathBlock->y = j * -55 + 250;
				
			}
			else if (map[j][i] == 13) {
				CButton* Button = new CButton();
				/*i��x=-350������Z,j��y=250���猸�Z���Ă�����
				�Q�̂���ꏊ��T��
				*/
				Button->x = i * 55 - 350;
				Button->y = j * -55 + 250;

			}
		}
	}
	//�N���X�̃����o�ϐ��ւ̑��
	CPlayer *Player = new CPlayer();
	Player->x = -220;
	Player->y = -250;
	Player->w = 20;
	Player->h = 20;
	Player->mEnabled = true;
	
}

void CSceneGame::Update() {
	
	
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
			delete *itr;//�z��v�f�̎Q�Ɓ@�@*�ϐ���
			//���X�g������폜
			itr = VectorRect.erase(itr);//�z��v�f�̍폜
		}
	}
	

	
		//�`��͈͕ϐ��̍쐬�@�͈͉��F-300�@�͈͏�F300 �Œ�
		double mLeft, mRight, mBottom = -300.0, mTop = 300.0;
		
        //��ʔ͈͍��̐ݒ�
		mLeft = CPlayer::spInstance->x - 400;
		//��ʔ͈͉E�̐ݒ�
		mRight = mLeft + 800.0f;
		
		
		//��ʓ��e�͈͂̕ύX
		//�s����v���W�F�N�V�������[�h�ɕύX
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();//�s���������
		//�QD�̉�ʂ�ݒ�
		gluOrtho2D(mLeft, mRight, mBottom, mTop);
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
		CText::DrawString("TAKARA", 100, 250, 16, 16);
		CText::DrawString("ZANKI", 100, 220, 16, 16);

		
		char buf[10];//�X�R�A�̕`��
		sprintf(buf, "%d ", SCore);
		CText::DrawString(buf, -170, 250, 16, 16);

		//��̌��̕`��
		sprintf(buf, "%d/4", Treasure);
		CText::DrawString(buf, 300, 250, 16, 16);

		//�c�@
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


//���̃V�[���̎擾
CScene::EScene CSceneGame::GetNextScene() {
	return mScene;
}
//�f�X�g���N�^
CSceneGame::~CSceneGame() {
	//�S�ẴC���X�^���X���폜���܂�
	for (int i = 0; i < VectorRect.size(); i++) {
		//�C���X�^���X�̍폜
		delete VectorRect[i];
	}
	//�ϒ��z��̃N���A
	VectorRect.clear();
}
