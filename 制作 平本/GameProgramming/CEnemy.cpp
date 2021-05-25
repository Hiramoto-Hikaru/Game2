#include"CEnemy.h"
#include"CVector.h"

#include"CTaskManager.h"
#include"CEffect.h"
#include"CBullet.h"
#include"CCollisionManager.h"
#define COLLISIONRANGE 30
#define VELOCITY 0.11f //マクロ
//コンストラクタ
//CEnemy（モデル、位置、回転、拡縮)
//&mMatrix=敵
CEnemy::CEnemy(CModel* model, CVector position, CVector rotation, CVector scale)
	:mCollider1(this, &mMatrix, CVector(0.0f, 5.0f, 0.0f), 0.8f)
	, mCollider2(this, &mMatrix, CVector(0.0f, 5.0f, 7.0f), 0.8f)
	, mCollider3(this, &mMatrix, CVector(0.0f, 5.0f, -7.0f), 0.8f)
	, mpPlayer(nullptr)
	, mFireCount(0)
	,mHp(10)
{

	//モデル、位置、回転、拡縮を設定（クラス内のみ適用）
	mpModel = model;//モデル
	mPosition = position;//位置
	mRotation = rotation;//回転
	mScale = scale; //拡縮
	//優先度を1に変更する
	mPriority = 1;
	CTaskManager::Get()->Remove(this);//削除して
	CTaskManager::Get()->Add(this);//追加する
	mPoint = mPosition + CVector(0.0f, 0.0f, 30.0f) * mMatrixRotate;
	CTransform::Update();//行列の更新

}
void CEnemy::Update() {
	//左向き（X軸）のベクトルを求める
	CVector vx = CVector(1.0f, 0.0f, 0.0f) * mMatrixRotate;
	//上向き（Y軸）のベクトルを求める
	CVector vy = CVector(0.0f, 1.0f, 0.0f) * mMatrixRotate;
	//前方向（Z軸）のベクトルを求める
	CVector vz = CVector(0.0f, 0.0f, 1.0f) * mMatrixRotate;
	//プレイヤーのポインタが０以外のとき
	if (mpPlayer) {
		//プレイヤーまでのベクトルを求める
		//プレイヤーと敵の座標の差
		CVector vp = mpPlayer->mPosition - mPosition;
		float dx = vp.Dot(vx);
		float dy = vp.Dot(vy);
		float dz = vp.Dot(vz);
		//X軸の-2～2の範囲に接触
		if (-2.0f < dx && dx < 2.0f) {
			//Y軸の-2～2の範囲に接触
			if (-2.0f < dy && dy < 2.0f) {
				
				//Z軸の0.0以上の範囲に接触
				if (0.0f <= dz) {
                   //停止
			    	mPosition = CVector(0.0f, 0.0f, 0.0f) * mMatrix;
					if (mFireCount <=0) {
						  //弾を発射
						CBullet* bullet = new CBullet();
						bullet->Set(0.1f, 1.5f);
						bullet->mPosition = CVector(0.0f, 0.0f, 10.0f) * mMatrix;
						bullet->mRotation = mRotation;
						bullet->Update();
						mFireCount += 60;
					}
					
				}

			}

		}
		else {
			//移動する
			mPosition = mPosition + CVector(0.0f, 0.0f, VELOCITY) * mMatrixRotate;

		}

	}
	if (mFireCount >= 0) {
		mFireCount--;
	}
	//目標地点までのベクトルを求める
	CVector vp = mPoint - mPosition;
	//左ベクトルとの内積を求める
	float dx = vp.Dot(vx);

	//上ベクトルとの内積を求める
	float dy = vp.Dot(vy);
	float margin = 0.1f;
	//左右方向へ回転

	if (dx > margin) {
		mRotation.mY += 5.0f;//左へ回転
	}
	else if (dx < -margin) {
		mRotation.mY -= 5.0f;//右へ回転
	}
	//上下方向に回転
	/*if (dy > margin) {
		mRotation.mX -= 5.0f;//上へ回転
	}
	else if (dy < -margin) {
		mRotation.mX += 5.0f;//下へ回転
	}*/
	
    //行列を更新
	CTransform:: Update();
	int r = rand() % 20; //rand()は整数の乱数を返す
						 //%180は１８０で割った余りを求める
	if (r == 0) {
		if (mpPlayer) {
			mPoint = mpPlayer->mPosition;
		}
		else {
			mPoint = mPoint * CMatrix().RotateY(30);
		}
	}
	mpPlayer = 0;
	if (mHp <= 0) {
		mHp--;
		//15フレームごとにエフェクト
		/*if (mHp % 15 == 0) {
			//エフェクト生成
			new CEffect(mPosition, 1.0f, 1.0f, "exp.tga", 4, 4, 2);
		}*/
		CTransform::Update();
		return;
	}
	//位置を移動(Z軸方向に0.9ずつ移動）
	//mPosition = CVector(0.0f, 0.0f, 0.9f) * mMatrix;
}
void CEnemy::Collision(CCollider* m, CCollider* o) {
	//相手がサーチのときは戻る
	if (o->mTag == CCollider::ESEARCH) {
		return;
	}
	//相手のコライダタイプの判定
	switch (o->mType) {
	case CCollider::ESPHERE://球コライダのとき
			//コライダのｍとｙが衝突しているか判定
			if (CCollider::Collision(m, o)) {
				//エフェクト生成
				new CEffect(o->mpParent->mPosition, 1.0f, 1.0f, "exp.tga", 4, 4, 2);
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
void CEnemy::TaskCollision() {

	//コライダの優先度変更
	mCollider1.ChangePriority();
	mCollider2.ChangePriority();
	mCollider3.ChangePriority();
	//衝突処理を実行
	CCollisionManager::Get()->Collision(&mCollider1, COLLISIONRANGE);
	CCollisionManager::Get()->Collision(&mCollider2, COLLISIONRANGE);
	CCollisionManager::Get()->Collision(&mCollider3, COLLISIONRANGE);
}