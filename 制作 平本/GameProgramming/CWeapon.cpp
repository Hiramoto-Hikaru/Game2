#include"CWeapon.h"
#include"CVector.h"

#include"CTaskManager.h"
#include"CEffect.h"
#include"CCollisionManager.h"
#define OBJ "Weapon.obj"//モデルのファイル
#define MTL "Weapon.mtl"//モデルのマテリアルファイル
#include"CCharacter.h"

CWeapon::CWeapon(CModel* model, CVector position, CVector rotation, CVector scale) 
	
	: mCollider(this, &mMatrix, CVector(0.0f, 5.0f, 0.0f), 1.0f)
{
	//モデル、位置、回転、拡縮を設定（クラス内のみ適用）
	mpModel = model;//モデル
	mPosition = position;//位置
	mRotation = rotation;//回転
	mScale = scale; //拡縮
	
	
	CTaskManager::Get()->Remove(this);//削除して
	CTaskManager::Get()->Add(this);//追加する

	CTransform::Update();//行列の更新
}
CWeapon::CWeapon() 
:mAction1(0)
	,mAction2(0)
	,mAction3(0)
{

}
void CWeapon::Update(){
	mPosition = mpPlayer->mPosition;

		if (mAction1 > 0) {
			mRotation.mX += 3.0f;
			mAction1--;
		}
		else if (mAction2 > 0) {
			mRotation.mY += 3.0f;
			mAction2--;
		}
		else if (mAction3 > 0) {
			mRotation.mZ += 3.0f;
			mAction3--;
		}
    	else {
		mEnabled = false;
	    }
		
	

}
void CWeapon::Collision(CCollider* m, CCollider* o) {


	switch (o->mType) {
	case CCollider::ESPHERE://球コライダのとき
			//コライダのｍとｙが衝突しているか判定
		if (CCollider::Collision(m, o)) {
			//エフェクト生成
			new CEffect(o->mpParent->mPosition, 1.0f, 1.0f, "Attack.tga", 2, 6, 2);
			//衝突しているときは無効
			//mEnabled=false;
		}
		break;
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

