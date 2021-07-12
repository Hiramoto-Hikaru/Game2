#include "CSceneGame.h"
//OpenGL
#include"glut.h"
#include "CVector.h"
#include"CTriangle.h"
#include "CKey.h"
#include"CModel.h"
#include<stdio.h> //�V�X�e���̃w�b�_�́����ň͂�
#include<string.h>
#include"CMatrix.h"
#include"CTransform.h"
#include"CPlayer.h"
#include"CTaskManager.h"
#include"CEnemy.h"
#include"CCollisionManager.h"
#include"CCollider.h"
#include"CBillBoard.h"
#include"CCamera.h"
#include"CColliderTriangle.h"
#include"CColliderMesh.h"
#include"CEnemy2.h"
#include"CWeapon.h"
void CSceneGame::Init()

{
    mBackGroundMatrix.Translate(0.0f, 0.0f, -500.0f);
    mModelc5.Load("Car.obj", "Car.mtl");

    int  map[10][10] =
    {
        {0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0},
        {0,1,1,1,1,1,1,1,1,0},
        {0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0},
    };
    for (int j = 0; j < 10; j++) {
        for (int i = 0; i < 10; i++) {
            if (map[i][j] == 1) {


               new CEnemy2(CVector(i*5.0f, 1.0f, j*10.0f) * mBackGroundMatrix,
                    CVector(), CVector(0.1f, 0.1f, 0.1f));

            }



        }
    }
    //�������E�E�E���炩���ߒl�������Ă�������
    mEye = CVector(1.0f, 2.0f, 3.0f);//X���AY���AZ���̏������i�E�΂ߏ�j
    //���f���t�@�C���̓���
    //���炩���ߏ������ꂽ�e�N�X�`���̃t�@�C����ݒ�
    mModel.Load("Player.obj", "Player.mtl");
    mBackGround.Load("sky.obj", "sky.mtl");

    CMatrix matrix;
    matrix.Print();
 //mBackGroundMatrix.Translate(0.0f, 0.0f, -500.0f);
   
    //�v���C���[���f��
    mPlayer.mpModel = &mModel;
    //�g��k���s��
   mPlayer.mScale = CVector(0.1f, 0.1f, 0.1f);
   //�ʒu���W
   mPlayer.mPosition = CVector(0.0f, 0.0f, 1.0f) *mBackGroundMatrix;
    //��]�s��
   mPlayer.mRotation = CVector(0.0f, 180.0f, 0.0f);

 
   //mModelc5.Load("Car.obj", "Car.mtl");
   //�G�@�̃C���X�^���X�쐬
   //CEnemy�i���f���A�ʒu�A��]�A�g�k)
   //&,,,�|�C���^�擾
   
   //�G�̐���
   new CEnemy(&mModelc5,
       CVector(-5.0f, 1.0f, -10.0f) * mBackGroundMatrix,
       CVector(), CVector(1.0f, 1.0f, 1.0f));
   
       new CEnemy2(CVector(-5.0f, 1.0f, -10.0f) * mBackGroundMatrix,
           CVector(), CVector(0.1f, 0.1f, 0.1f));
     
 
   new CEnemy2(CVector(5.0f, 1.0f, -10.0f) * mBackGroundMatrix,
       CVector(), CVector(0.1f, 0.1f, 0.1f));

   //�r���{�[�h�̐���
   new CBillBoard(CVector(-6.0f, 3.0f, -10.0f), 1.0f, 1.0f);


   //�O�p�R���C�_�̊m�F
   mColliderTriangle.Set(NULL, NULL
       , CVector(-50.0f, 0.0f, -50.0f)
       , CVector(-50.0f, 0.0f, 50.0f)
       , CVector(50.0f, 0.0f, -50.0f));

   mColliderTriangle2.Set(NULL, NULL
       , CVector(-50.0f, 0.0f, 50.0f)
       , CVector(50.0f, 0.0f, 50.0f)
       , CVector(50.0f, 0.0f, -50.0f));

   //�w�i���f������O�p�R���C�_�̐���
   //�e�C���X�^���X�Ɛe�s��͂Ȃ�
   mColliderMesh.Set(NULL, &mBackGroundMatrix , &mBackGround);

  
}

//���_�P�C���_�Q�C���_�R�C�@���f�[�^�̍쐬
void CSceneGame::Update() { 
    //�^�X�N�}�l�[�W���[�i�e�j�̍X�V
  CTaskManager::Get()->Update();


  //�R���W�����}�l�[�W���̏Փˏ���(�^�X�N�}�l�[�W���̏Փˏ����ɕύX�j
   // CCollisionManager::Get()->Collision();
    CTaskManager::Get()->TaskCollision();

    CVector v0, v1, v2, n;
    //�@����������Őݒ肷��
    n.mX = 0.0f; n.mY = 1.0f; n.mZ = 0.0f;
    //���_0�̍��W�̐ݒ�
    v0.mX = 0.0f; v0.mY = 0.0f; v0.mZ = 0.5f;
    //���_1�̍��W�̐ݒ�
    v1.mX = 1.0f; v1.mY = 0.0f; v1.mZ = 0.0f;
    //���_�Q�̍��W��ݒ�
    v2.mX = 0.0f; v2.mY = 0.0f; v2.mZ = -0.5f;

    //���_��ݒ肷��O�ɑ�����@��ݒ�
    //���͂��������Ɏ��_���ړ�����
    if (CKey::Push('J'))
    {
        mEye.mX -= 0.1f;
    }
    if (CKey::Push('L'))
    {
        mEye.mX += 0.1f;
    }
    if (CKey::Push('I'))
    {
        mEye.mZ -= 0.1f;
    }
    if (CKey::Push('K'))
    {
        mEye.mZ += 0.1f;
    }
    if (CKey::Push('O'))
    {
        mEye.mY += 0.1f;
    }
    if (CKey::Push('M'))
    {
        mEye.mY -= 0.1f;
    }
    //���_�̐ݒ�
  //��Eye��t�������đ���\�ɂ���
    //glutLookAt(���_X,���_Y,���_Z,���SX,���SY�C���SZ,���X,���Y,���Z,�j
    //�ォ�牺�������낷�悤�Ȏ��_�ɂȂ�
    
//trans���f��
   /* CTransform trans;//�ϊ��s��C���X�^���X�̍쐬
    trans.mPosition = CVector(0.5f, 1.8f, 0.5f);//�ʒu�̐ݒ�
    trans.mRotation = CVector(-10.0f, -20.0f, -30.0f);//��]�̐ݒ�
    trans.mScale = CVector(0.1f, 0.1f, 0.1f);//�g��k���̐ݒ�
    trans.Update(); // �s��̍X�V
    mModel.Render(trans.mMatrix);*/
   
  
    //�J�����̃p�����[�^�쐬
    CVector e, c, u;//���_�@�����_�@�����
    //���_(�����s��*���W�j
    //CVector�����Ȃ��Ɖ��̍��W���킩��Ȃ�
    //mPlayer������
    //CMatrix().RotateY(Camera.mRotation.mY)
    e = mPlayer.mPosition+ CVector(0.0f, 5.0f, 10.0f) * mPlayer.mMatrixRotate2;
    //�����_�i�ʒu���W�j
    c = mPlayer.mPosition;
    //������i��]�s��*���W�j
    u = CVector(0, 1, 0) * mPlayer.mMatrixRotate;

    //�J�����̐ݒ�
   //mX,mY,mZ���i�j���̐����̑��
    //�J�����N���X�ŏ���
   // gluLookAt(e.mX, e.mY, e.mZ, c.mX, c.mY, c.mZ, u.mX, u.mY, u.mZ);
    //�J�����N���X�̐ݒ�(���_�A�����_�A�����)
    Camera.Set(e, c, u); 
    Camera.Render();
    
  //�^�X�N���X�g�̍폜
  CTaskManager::Get()->Delete();
  
    //�w�i�̕`��
    mBackGround.Render(mBackGroundMatrix);
    //Scale�i�g��k���j


  //�R���C�_�̕`�� �i�R���C�_�̍Ō�̃^�X�N��NULL�ɂȂ�΂����j
    CCollisionManager::Get()->Render();
    //�^�X�N�}�l�[�W���[�̕`��
  CTaskManager::Get()->Render();
}
