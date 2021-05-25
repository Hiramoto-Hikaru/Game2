#include"CEnemy2.h"
#include"CEffect.h"
#include"CCollisionManager.h"
#include"CBullet.h"
#define OBJ "f14.obj"//モデルのファイル
#define MTL "f14.mtl"//モデルのマテリアルファイル
#define HP 3
#define VELOCITY 0.11f //マクロ

CModel CEnemy2::mModel;//モデルデータ作成

//デフォルトコンストラクタ
CEnemy2::CEnemy2()
//コライダの設定
	:mCollider(this,&mMatrix,CVector(0.0f,0.0f,0.0f),0.1f)
	,mColSearch(this,&mMatrix,CVector(0.0f,0.0f,100.0f),30.0f)
	,mpPlayer(0)
	,mHp(HP)

{
	//モデルが無いときは読み込む
	if (mModel.mTriangles.size() == 0) {
		mModel.Load(OBJ, MTL);
	}
	//モデルのポインタ設定
	mpModel = &mModel;
	mColSearch.mTag = CCollider::ESEARCH;//タグ設定

}

//CEnemy(位置、回転、拡縮）
CEnemy2::CEnemy2(const CVector& position, const CVector& rotation, const CVector& scale)
:CEnemy2()

{
	//位置、回転、拡縮を設定する
	mPosition = position;//位置の設定
	mRotation = rotation;//回転の設定
	mScale = scale;//拡縮の設定
	CTransform::Update();//行列の更新
	//目標地点の設定
	mPoint =mPosition + CVector(0.0f, 0.0f, 30.0f) * mMatrixRotate;
 
	//優先度を１に変更する
	mPriority = 1;
	CTaskManager::Get()->Remove(this);//削除して
	CTaskManager::Get()->Add(this);//追加する
}
//更新処理
void CEnemy2::Update() {
	//左向き（X軸）のベクトルを求める
	CVector vx = CVector(1.0f, 0.0f, 0.0f)*mMatrixRotate;
	//上向き（Y軸）のベクトルを求める
	CVector vy = CVector(0.0f, 1.0f, 0.0f) * mMatrixRotate;
	//前方向（Z軸）のベクトルを求める
	CVector vz = CVector(0.0f, 0.0f, 5.0f) * mMatrixRotate;

	//プレイヤーのポインタが０以外のとき
	if (mpPlayer) {
		//プレイヤーまでのベクトルを求める
		//プレイヤーと敵の座標の差
		CVector vp = mpPlayer->mPosition - mPosition;
		float dx = vp.Dot(vx);
		float dy = vp.Dot(vy);
		float dz = vp.Dot(vz);
		//X軸の-2～2の範囲に接触
		
				//Y軸の-2～2の範囲に接触
			if (-10.0f < dy && dy < 10.0f) {
				//位置を移動(Z軸方向に0.9ずつ移動）
				mPosition = CVector(0.0f, 0.0f, 0.9f) * mMatrix;

				//Z軸の0.0以上の範囲に接触
				if (0.0f <= dz) {

                //弾を発射

				/*CBullet* bullet = new CBullet();
				bullet->Set(0.1f, 1.5f);
				bullet->mPosition = CVector(0.0f, 0.0f, 10.0f) * mMatrix;
				bullet->mRotation = mRotation;
				bullet->Update();*/
				}
				
			}

		

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
		mRotation.mY += 1.0f;//左へ回転
	}
		else if (dx < -margin) {
		mRotation.mY -= 1.0f;//右へ回転
        }
	//上下方向に回転
	/*if (dy > margin) {
		mRotation.mX  -= 1.0f;//上へ回転
	}
	else if (dy < -margin) {
		mRotation.mX += 1.0f;//下へ回転
	}*/
	//移動する
	mPosition = mPosition + CVector(0.0f, 0.0f, VELOCITY) * mMatrixRotate;
	CTransform::Update();//行列更新


	int r = rand() % 20; //rand()は整数の乱数を返す
	                     //%180は１８０で割った余りを求める
	if (r == 0) {
		if (mpPlayer) {
			mPoint = mpPlayer->mPosition;

		}
		else {
			mPoint = mPoint * CMatrix().RotateY(45);
		}
	}

	mpPlayer =0;
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

}
//Collision(コライダ１，コライダ２，）
void CEnemy2::Collision(CCollider* m, CCollider* o) {
	//相手がサーチのときは戻る
	if (o->mTag == CCollider::ESEARCH) {
		
		return;
	}
	//自分がサーチ用のとき
	if (m->mTag == CCollider::ESEARCH) {
		//相手が弾コライダのとき
		if (o->mType == CCollider::ESPHERE) {
			//相手がプレイヤーのとき、
			if (o->mpParent->mTag == EPLAYER) {
				//衝突しているとき
				if (CCollider::Collision(m, o)) {
					//プレイヤーのポインタ設定
					mpPlayer = o->mpParent;
				}
			}
		}
		return;
	}


	//相手のコライダタイプの判定
	switch (o->mType) {
	case CCollider::ESPHERE://球コライダのとき
			//コライダのｍとｙが衝突しているか判定
		if (CCollider::Collision(m, o)) {
			//エフェクト生成
			new CEffect(o->mpParent->mPosition, 1.0f, 1.0f, "exp.tga", 4, 4, 2);
			mHp--;
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
				//撃破で地面に衝突すると無効
			if (mHp <= 0) {
			
				 //mEnabled = false;
			}
		}
	
		break;
	}
}
void CEnemy2::TaskCollision() {
	mColSearch.ChangePriority();
	//衝突処理を実行
	CCollisionManager::Get()->Collision(&mColSearch, COLLISIONRANGE);
	//コライダの優先度変更
	mCollider.ChangePriority();
	//衝突処理を実行
	CCollisionManager::Get()->Collision(&mCollider, COLLISIONRANGE);
}
