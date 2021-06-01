#include "CSceneGame.h"
//OpenGL
#include"glut.h"
#include "CVector.h"
#include"CTriangle.h"
#include "CKey.h"
#include"CModel.h"
#include<stdio.h> //システムのヘッダは＜＞で囲む
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

void CSceneGame::Init() {
    //初期化・・・あらかじめ値を代入しておくこと
    mEye = CVector(1.0f, 2.0f, 3.0f);//X軸、Y軸、Z軸の初期化（右斜め上）
    //モデルファイルの入力
    //あらかじめ準備されたテクスチャのファイルを設定
    mModel.Load("Player.obj", "Player.mtl");
    mBackGround.Load("sky.obj", "sky.mtl");

    CMatrix matrix;
    matrix.Print();
 mBackGroundMatrix.Translate(0.0f, 0.0f, -500.0f);
   
    //プレイヤーモデル
    mPlayer.mpModel = &mModel;
    //拡大縮小行列
   mPlayer.mScale = CVector(0.1f, 0.1f, 0.1f);
   //位置座標
   mPlayer.mPosition = CVector(0.0f, 0.0f, 1.0f) *mBackGroundMatrix;
    //回転行列
   mPlayer.mRotation = CVector(0.0f, 180.0f, 0.0f);

   //objとmtlの読み込み
   //C5モデルの読み込み
   mModelW.Load("Weapon.obj", "Weapon.mtl");
   new CWeapon(&mModelW,
       CVector(0.0f, 3.0f, 1.0f) * mBackGroundMatrix,
       CVector(), CVector(1.0f, 1.0f, 1.0f));
   mModelc5.Load("Car.obj", "Car.mtl");
   //敵機のインスタンス作成
   //CEnemy（モデル、位置、回転、拡縮)
   //&,,,ポインタ取得
 // new CWeapon(&mModelW, mPlayer.mPosition,
    //  CVector(), CVector(0.1f, 0.1f, 0.1f));

   //敵の生成
   new CEnemy(&mModelc5,
       CVector(-5.0f, 3.0f, -10.0f) * mBackGroundMatrix,
       CVector(), CVector(1.0f, 1.0f, 1.0f));

   new CEnemy2(CVector(-5.0f, 3.0f, -10.0f) * mBackGroundMatrix,
       CVector(), CVector(0.1f, 0.1f, 0.1f));
   new CEnemy2(CVector(5.0f, 3.0f, -10.0f) * mBackGroundMatrix,
       CVector(), CVector(0.1f, 0.1f, 0.1f));

   //ビルボードの生成
   new CBillBoard(CVector(-6.0f, 3.0f, -10.0f), 1.0f, 1.0f);


   //三角コライダの確認
   mColliderTriangle.Set(NULL, NULL
       , CVector(-50.0f, 0.0f, -50.0f)
       , CVector(-50.0f, 0.0f, 50.0f)
       , CVector(50.0f, 0.0f, -50.0f));

   mColliderTriangle2.Set(NULL, NULL
       , CVector(-50.0f, 0.0f, 50.0f)
       , CVector(50.0f, 0.0f, 50.0f)
       , CVector(50.0f, 0.0f, -50.0f));

   //背景モデルから三角コライダの生成
   //親インスタンスと親行列はなし
   mColliderMesh.Set(NULL, &mBackGroundMatrix , &mBackGround);

  
}

//頂点１，頂点２，頂点３，法線データの作成
void CSceneGame::Update() { 
    //タスクマネージャー（弾）の更新
  CTaskManager::Get()->Update();


  //コリジョンマネージャの衝突処理(タスクマネージャの衝突処理に変更）
   // CCollisionManager::Get()->Collision();
    CTaskManager::Get()->TaskCollision();

    CVector v0, v1, v2, n;
    //法線を上向きで設定する
    n.mX = 0.0f; n.mY = 1.0f; n.mZ = 0.0f;
    //頂点0の座標の設定
    v0.mX = 0.0f; v0.mY = 0.0f; v0.mZ = 0.5f;
    //頂点1の座標の設定
    v1.mX = 1.0f; v1.mY = 0.0f; v1.mZ = 0.0f;
    //頂点２の座標を設定
    v2.mX = 0.0f; v2.mY = 0.0f; v2.mZ = -0.5f;

    //視点を設定する前に操作方法を設定
    //入力した方向に視点が移動する
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
    //視点の設定
  //ｍEyeを付け加えて操作可能にする
    //glutLookAt(視点X,視点Y,視点Z,中心X,中心Y，中心Z,上向X,上向Y,上向Z,）
    //上から下を見下ろすような視点になる
    
//transモデル
   /* CTransform trans;//変換行列インスタンスの作成
    trans.mPosition = CVector(0.5f, 1.8f, 0.5f);//位置の設定
    trans.mRotation = CVector(-10.0f, -20.0f, -30.0f);//回転の設定
    trans.mScale = CVector(0.1f, 0.1f, 0.1f);//拡大縮小の設定
    trans.Update(); // 行列の更新
    mModel.Render(trans.mMatrix);*/
   
  
    //カメラのパラメータ作成
    CVector e, c, u;//視点　注視点　上方向
    //視点(合成行列*座標）
    //CVectorをつけないと何の座標かわからない
    //mPlayerをつける
    //CMatrix().RotateY(Camera.mRotation.mY)
    e = mPlayer.mPosition+ CVector(0.0f, 5.0f, 10.0f) * mPlayer.mMatrixRotate2;
    //注視点（位置座標）
    c = mPlayer.mPosition;
    //上方向（回転行列*座標）
    u = CVector(0, 1, 0) * mPlayer.mMatrixRotate;

    //カメラの設定
   //mX,mY,mZ＝（）内の数字の代入
    //カメラクラスで処理
   // gluLookAt(e.mX, e.mY, e.mZ, c.mX, c.mY, c.mZ, u.mX, u.mY, u.mZ);
    //カメラクラスの設定(視点、注視点、上方向)
    Camera.Set(e, c, u); 
    Camera.Render();
    
  //タスクリストの削除
  CTaskManager::Get()->Delete();
  
    //背景の描画
    mBackGround.Render(mBackGroundMatrix);
    //Scale（拡大縮小）


  //コライダの描画 （コライダの最後のタスクがNULLになればいい）
    CCollisionManager::Get()->Render();
    //タスクマネージャーの描画
  CTaskManager::Get()->Render();
}
