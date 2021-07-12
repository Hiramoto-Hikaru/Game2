#include"CWeapon.h"
#include"CVector.h"

#include"CTaskManager.h"
#include"CEffect.h"
#include"CCollisionManager.h"
#define OBJ "Weapon.obj"//モデルのファイル
#define MTL "Weapon.mtl"//モデルのマテリアルファイル
#include"CCharacter.h"
#include"CMatrix.h"
#include"CsceneGame.h"
#include"CKey.h"

CWeapon::CWeapon(CModel* model, CVector position, CVector rotation, CVector scale) 
	
	: mCollider(this, &mMatrix, CVector(0.0f, 8.0f, 0.0f), 1.5f)
	, mRotationCountFirst(1)
	, mRotationCount(0)
	, mRotationCount2(0)
	, mRotationCount3(0)
	, mRotationCount4(0)
	,mStamina2(400)

{
	//モデル、位置、回転、拡縮を設定（クラス内のみ適用）
	mpModel = model;//モデル
	mPosition = position;//位置
	mRotation = rotation;//回転
	mScale = scale; //拡縮
	mCollider.mTag = CCollider::EWEAPON;
	mModelW.Load("Weapon.obj", "Weapon.mtl");
	CTaskManager::Get()->Remove(this);//削除して
	CTaskManager::Get()->Add(this);//追加する

	CTransform::Update();//行列の更新
}
CWeapon::CWeapon( 
)
	
{

}
void CWeapon::Update(){
	//前進
	if (CKey::Push('I')) {
		if (mRotationCount <= 0) {
			mRotationCount += 1;
			if (mRotationCountFirst > 0) {
				mRotationCountFirst--;
			}
		}
		else if (mRotationCount2 > 0) {//右を向いていたとき
			mRotation.mY += 90;
			mRotationCount2 -= 1;
		}
		else if (mRotationCount3 > 0) {//後ろを向いていたとき
			mRotation.mY += 180;
			mRotationCount3 -= 1;
		}
		else if (mRotationCount4 > 0) {//左を向いていたとき
			mRotation.mY -= 90;
			mRotationCount4 -= 1;
		}
		
	}
	//後退
	else if (CKey::Push('K')) {
		if (mRotationCount3 <= 0) {
			mRotationCount3 += 1;
			if (mRotationCountFirst > 0) {
				mRotation.mY += 180;
				mRotationCountFirst--;
			}
		}
		else if (mRotationCount2 > 0) {//右を向いていたとき
			mRotation.mY -= 90;
			mRotationCount2 -= 1;
		}
		else if (mRotationCount > 0) {//正面を向いていたとき
			mRotation.mY += 180;
			mRotationCount -= 1;
		}
		else if (mRotationCount4 > 0) {//左を向いていたとき
			mRotation.mY += 90;
			mRotationCount4 -= 1;
		}
	
	}
	//左折
	else if (CKey::Push('J')) {
		if (mRotationCount4 <= 0) {
			mRotationCount4 += 1;
			if (mRotationCountFirst > 0) {
				mRotation.mY += 90;
				mRotationCountFirst--;
			}
		}
		else if (mRotationCount2 > 0) {//右を向いていたとき
			mRotation.mY += 180;
			mRotationCount2 -= 1;
		}
		else if (mRotationCount3 > 0) {//後ろを向いていたとき
			mRotation.mY -= 90;
			mRotationCount3 -= 1;
		}
		else if (mRotationCount > 0) {//正面を向いていたとき
			mRotation.mY += 90;
			mRotationCount -= 1;
		}
		
	}
	//右折
	else if (CKey::Push('L')) {
		if (mRotationCount2 <= 0) {
			mRotationCount2 += 1;
			if (mRotationCountFirst > 0) {
				mRotation.mY -= 90;
				mRotationCountFirst--;
			}
		}
		else if (mRotationCount > 0) {//正面を向いていたとき
			mRotation.mY -= 90;
			mRotationCount -= 1;
		}
		else if (mRotationCount3 > 0) {//後ろを向いていたとき
			mRotation.mY += 90;
			mRotationCount3 -= 1;
		}
		else if (mRotationCount4 > 0) {//左を向いていたとき
			mRotation.mY += 180;
			mRotationCount4 -= 1;
		}
		
	}
	//左向き
	if (CKey::Push('A')) {
		mRotation.mY += 3;
	}
	//右向き
	if (CKey::Push('D')) {
		mRotation.mY -= 3;
	}

		if (CPlayer::mAction1 <100) {
			if (mPosition.mY <= 3.0f) {
				mPosition.mY += 3;
			}
            mRotation.mX += 20.0f;
           CPlayer::mAction1++;
		}
		else if (CPlayer::mAction2 <100) {
		if (mRotation.mX < 90) {
        	mRotation.mX += 90.0f;
		}
			mRotation.mY += 20.0f;
			CPlayer::mAction2++;
		}
 		else if (CPlayer::mAction3 <100) {
			mRotation.mZ += 20.0f;
			CPlayer::mAction3++;
		}
    	
		else {

			mEnabled = false;
		}
	    
		CTransform::Update();
}
void CWeapon::Collision(CCollider* m, CCollider* o) {

	switch (o->mType) {
	case CCollider::ESPHERE://球コライダのとき
			//コライダのｍとｙが衝突しているか判定
		if (CCollider::Collision(m, o)) {
			if (o->mpParent->mTag ==CCollider::EENEMYCOLLIDER1 || o->mpParent->mTag == CCollider::EENEMY2COLLIDER) {
				//エフェクト生成
				new CEffect(o->mpParent->mPosition, 1.0f, 1.0f, "Attack.tga", 2, 6, 2);
				//衝突しているときは無効
				//mEnabled=false;
			}
		}
		break;
	case CCollider::EENEMYCOLLIDER1:
		if (CCollider::Collision(m, o)) {
			new CEffect(o->mpParent->mPosition, 1.0f, 1.0f, "Attack.tga", 2, 6, 2);
		}
	case CCollider::ETRIANGLE://三角コライダのとき
		CVector adjust;//調整値
		//三角コライダと球コライダの衝突判定
		//adjust、、、調整値
		if (CCollider::CollisionTriangleSphere(o, m, &adjust))
		{
			//衝突しない位置まで戻す
			mPosition = mPosition + adjust;
		}
		break;
	}
}

void CWeapon::TaskCollision()
{

	//コライダの優先度変更
	mCollider.ChangePriority();
	
	//衝突処理を実行
	CCollisionManager::Get()->Collision(&mCollider, COLLISIONRANGE);
	

}

