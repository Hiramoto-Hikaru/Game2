#ifndef CSCENEGAME_H
#define CSCENEGAME_H
#include "CScene.h"
#include"CVector.h"
#include"CModel.h"
#include"CCharacter.h"
#include "CPlayer.h"
#include"CEnemy.h"
#include"CCollisionManager.h"
#include"CItem.h"
#include"CBillBoard.h"
#include"CCamera.h"
#include"CColliderTriangle.h"
#include"CColliderMesh.h"
/*
ゲームのシーン
*/

class CSceneGame : public CScene {
public:
	
	CVector mEye; //カメラ視点の追加
	CModel mModel;//CModelクラスのインスタンス変数
	CModel mBackGround;//背景モデル
	CMatrix mMatrixRotate;//回転行列
	CMatrix mMatrix;//合成行列
	CMatrix mBackGroundMatrix;
	CPlayer mPlayer;
	
	//モデルからコライダ生成
      CColliderMesh mColliderMesh;
	  int mMapCount;
	//敵モデルのインスタンス（クラスと同じものは使えない）
	CModel mModelC5;
	CModel mModelc5;
	CModel mModelI;
	
	//三角コライダの作成
	CColliderTriangle mColliderTriangle;
	CColliderTriangle mColliderTriangle2;

	

	//初期化処理のオーバーライド

	void Init();
	
	//更新処理のオーバーライド
	void Update();
};

#endif