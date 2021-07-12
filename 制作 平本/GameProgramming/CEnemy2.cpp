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
	:mCollider(this,&mMatrix,CVector(0.0f,0.0f,0.0f),1.0f)
	,mColSearch(this,&mMatrix,CVector(0.0f,0.0f,100.0f),200.0f)
	,mpPlayer(0)
	,mHp(HP)

{
	mTag = EENEMY2;
	//モデルが無いときは読み込む
	if (mModel.mTriangles.size() == 0) {
		mModel.Load(OBJ, MTL);
	}
	//モデルのポインタ設定
	mpModel = &mModel;
	mColSearch.mTag = CCollider::ESEARCH;//タグ設定
	mCollider.mTag = CCollider::EENEMY2COLLIDER;
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
	mPoint =mPosition + CVector(0.0f, 0.0f, 100.0f) * mMatrixRotate;
 
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
	
	//移動する
	mPosition = mPosition + CVector(0.0f, 0.0f, VELOCITY) * mMatrixRotate;
	CTransform::Update();//行列更新


	int r = rand() % 180; //rand()は整数の乱数を返す
	                     //%180は１８０で割った余りを求める
	if (r == 0) {
		if (mpPlayer) {
			mPoint = mpPlayer->mPosition;

		}
		else {
			mPoint = mPoint * CMatrix().RotateY(45);
		}
	}

	
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

	case CCollider::EWEAPON://
		//コライダのｍとｙが衝突しているか判定
		if (CCollider::Collision(m, o)) {
			new CEffect(o->mpParent->mPosition, 1.0f, 1.0f, "exp.tga", 4, 4, 2);
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
