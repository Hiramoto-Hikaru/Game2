#include "CParent.h"
#include "Ckey.h"

#define INIT_POSE CVector(20.0f, 0.0f, 0.0f) //初期の姿勢
#define VELOCITY CVector(0.0f, 0.0f, 2.0f) //移動速度
#define ROTATE_V CVector(0.0f, 2.0f, 0.0f) //回転速度
#define COLLIDER_POS CVector(0.0f, 1.7f, 0.0f) //コライダの位置
#define PARENT_MODEL "Weapon.obj","Weapon.mtl"

CModel CParent::mModel;
int CParent::sCount = 0;

CParent::CParent()
	
{
	/*if (sCount == 0)
	{
		mModel.Load(PARENT_MODEL);
		
	}*/
	mpModel = &mModel;
	sCount++;
	mScale = CVector(1.0f, 1.0f, 1.0f);
	CTransform::Update();
}


void CParent::Update()
{
	// J L で回転
	if (CKey::Push('J'))
	{
		mRotation = mRotation + ROTATE_V;
	}
	if (CKey::Push('L'))
	{
		mRotation = mRotation - ROTATE_V;
	}
	//W S で移動
	if (CKey::Push('W'))
	{
		mPosition = mPosition + VELOCITY * mMatrixRotate;
	}
	if (CKey::Push('S'))
	{
		mPosition = mPosition - VELOCITY * mMatrixRotate;
	}
	//親の行列の更新
	CTransform::Update();
}

/*****************************************************/
/*  CChild                                           */
/*****************************************************/

CModel CChild::sModel;
int CChild::sCount = 0;

CChild::CChild(CCharacter* parent)
	: mCollider(this, &mMatrix, COLLIDER_POS, 1.0f)
{
	//親のインスタンスの退避
	mpParent = parent;

	if (sCount == 0)
	{
		
		sModel.Load(PARENT_MODEL);
	}
	mpModel = &sModel;
	//sCount++;
	mScale = CVector(0.5f, 5.5f, 0.5f);
	mPosition = CVector(0.0f, 1.0f, 0.0f);
	mRotation = INIT_POSE;
	CTransform::Update();
}


void CChild::Update()
{
	// I で攻撃
	if (CKey::Push('I'))
	{
		mRotation.mX = 90.0f;
	}
	else
	{
		mRotation = INIT_POSE;
	}
	//子の行列の更新
	CTransform::Update();
	//自分の行列に親の行列を掛けて、最終的な合成行列にする
	mMatrix = mMatrix * mpParent->mMatrix;
}
