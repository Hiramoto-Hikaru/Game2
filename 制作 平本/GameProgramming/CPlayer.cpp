//プレイヤークラス

#include"CPlayer.h"
#include"CKey.h"
#include"CBullet.h"
#include"CTaskManager.h"
#include"CTransform.h"
#include"CColliderLine.h"
#include"CTask.h"
#include"CUtil.h"
#include"CText.h"
#include"CEffect.h"
#define G 1.0f

CMatrix Matrix;
int CPlayer::mAction1 = 60;//１回目の攻撃の表示時間
int CPlayer::mAction2 = 60;//２回目の攻撃の表示時間
int CPlayer::mAction3 = 60;//３回目の攻撃の表示時間
int CPlayer::mSpaceCount1 = 0;//1回目攻撃後のクールタイム
int CPlayer::mSpaceCount2 = 0;//２回目攻撃後のクールタイム
int CPlayer::mSpaceCount3 = 0;//３回目攻撃後のクールタイム
int CPlayer::mStamina =   400;
int CPlayer::mWeaponCount = 0;
CPlayer::CPlayer()
//線分コライダの設定（親、親行列、頂点１、頂点２）
	:mLine(this, &mMatrix, CVector(0.0f, 9.0f, -7.0f), CVector(0.0f, 9.0f, 10.0f)) //前後の線分コライダ
	, mLine2(this, &mMatrix, CVector(0.0f, 12.0f, -4.0f), CVector(0.0f, 6.0f, -4.0f))  //上下の線分コライダ
	, mLine3(this, &mMatrix, CVector(7.0f, 9.0f, -4.0f), CVector(-7.0f, 9.0f, -4.0f))  //左右の線分コライダ
	,mCollider(this,&mMatrix,CVector(0.0f,9.0f,0.0f),1.0f)
	, mRotationCountFirst(1)
	,mRotationCount(0)
	,mRotationCount2(0)
	,mRotationCount3(0)
	,mRotationCount4(0)
	, mColliderCount(0)
	,mChild(this)
{
//テクスチャファイルの読み込み(１行６４列）
mText.LoadTexture("FontWhite.tga", 1, 64);
mCollider.mTag = CCollider::EPLAYERCOLLIDER;//タグの設定
mTag = EPLAYER;
mModelW.Load("Weapon.obj", "Weapon.mtl");
} 
void CPlayer::Update() {
	
	//スペースキー入力で武器
	if (CKey::Once(VK_SPACE)) {
		//最初の攻撃
 		if (mSpaceCount1 <= 0&& mSpaceCount3 <= 0) {
			mSpaceCount1 = 100;
			mAction1 = 0;

			
			
			
		}
		//２回目の攻撃
		else if (mSpaceCount2 <=0 && mAction1 <=50) {
			if (mAction1 < 100) {
				mSpaceCount2 = 100;
	     		mAction2 =0;

				mSpaceCount1 = 0;
				mAction1 = 60;
			
			}
			
		}
		//３回目の攻撃
		else if (mSpaceCount3 <=0 &&  mAction2 <=50) {
			if (mAction2 < 100) {
				mSpaceCount3 = 100;
  				mAction3 = 0;

				mAction2 = 60;
				mSpaceCount2 = 0;
			
			}
		}
	}
	//攻撃後のクールタイム
	if (mSpaceCount1 > 0) {
			mSpaceCount1--;
		}
		if (mSpaceCount2 > 0) {
			mSpaceCount2--;
		}
		if (mSpaceCount3 > 0) {
			mSpaceCount3--;
		}
		//スタミナ回復
	if (mStamina <= 400) {
    mStamina++;
	}
	if (mAction1 >= 60 && mAction2 >=60 && mAction3 >=60) {
		//前進
		if (CKey::Push('I')) {
			mWeaponCount = 0;
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
			//ダッシュ
			if (CKey::Push('C')) {
				if (mStamina > 0) {

					//Z軸方向に４進ませる
					mPosition = CVector(0.0f, 0.0f, 4.0f) * mMatrix;
					mStamina -= 2;
				}
				//スタミナ切れ
				else if (mStamina <= 2 || mStamina >= 0) {
					//Z軸方向に１進ませる
					mPosition = CVector(0.0f, 0.0f, 1.0f) * mMatrix;
					mStamina -= 2;
				}
			}
			else {
				//Z軸方向に２進ませる
				mPosition = CVector(0.0f, 0.0f, 2.0f) * mMatrix;
			}


		}
		//後退
		else if (CKey::Push('K')) {
			mWeaponCount = 1;
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
			//ダッシュ
			if (CKey::Push('C')) {
				if (mStamina > 0) {
					//Z軸方向に４進ませる
					mPosition = CVector(0.0f, 0.0f, 4.0f) * mMatrix;
					mStamina -= 2;
				}
				//スタミナ切れ
				else if (mStamina <= 2 || mStamina >= 0) {
					//Z軸方向に１進ませる
					mPosition = CVector(0.0f, 0.0f, 1.0f) * mMatrix;
					mStamina -= 2;
				}
			}
			else {
				//Z軸方向に２進ませる
				mPosition = CVector(0.0f, 0.0f, 2.0f) * mMatrix;
			}

		}
		//左折
		else if (CKey::Push('J')) {
			mWeaponCount = 2;
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
			//ダッシュ
			if (CKey::Push('C')) {
				if (mStamina > 0) {
					//Z軸方向に４進ませる
					mPosition = CVector(0.0f, 0.0f, 4.0f) * mMatrix;
					mStamina -= 2;
				}
				//スタミナ切れ
				else if (mStamina <= 2 || mStamina >= 0) {
					//Z軸方向に１進ませる
					mPosition = CVector(0.0f, 0.0f, 1.0f) * mMatrix;
					mStamina -= 2;
				}
			}
			else {
				//Z軸方向に２進ませる
				mPosition = CVector(0.0f, 0.0f, 2.0f) * mMatrix;
			}


		}
		//右折
		else if (CKey::Push('L')) {
		mWeaponCount = 3;
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
			//ダッシュ
			if (CKey::Push('C')) {
				if (mStamina > 0) {
					//Z軸方向に４進ませる
					mPosition = CVector(0.0f, 0.0f, 4.0f) * mMatrix;
					mStamina -= 2;
				}
				//スタミナ切れ
				else if (mStamina <= 2 || mStamina >= 0) {
					//Z軸方向に１進ませる
					mPosition = CVector(0.0f, 0.0f, 1.0f) * mMatrix;
					mStamina -= 2;
				}
			}
			else {
				//Z軸方向に２進ませる
				mPosition = CVector(0.0f, 0.0f, 2.0f) * mMatrix;
			}
		}
	}
    //左回転
	 if (CKey::Push('A')) {
		//Y軸の回転値を増加
		mRotation2.mY += 3;
		mRotation.mY += 3;
	 }
	//右回転
	if (CKey::Push('D')) {
		//Y軸の回転値を減算
		mRotation2.mY -= 3;
		mRotation.mY -= 3;
	}
	//上回転
	if (CKey::Push('S')) {
		//X軸の回転値を減算
		if (mRotation2.mX > -60) {

			mRotation2.mX -= 3;
		}
	}
	//下回転
	if (CKey::Push('W')) {
		//X軸の回転値を加算
		if (mRotation2.mX < 90) {

			mRotation2.mX += 3;
		}                 
	}
	//吹き飛ぶ
	if (mColliderCount > 0) {
		mColliderCount--;
		//mPosition.mZ -= mColliderCount;
		//mPosition.mY += mColliderCount;
	}
	//重力
	if (mPosition.mY > 0.0f) {
		mPosition.mY -= G;
	}
	//CCharacterの更新
	CTransform::Update();
}	
void CPlayer::Collision(CCollider* m, CCollider* o) {
	if (m->mType == CCollider::ESPHERE) {
		//プレイヤーのとき、
		if (m->mpParent->mTag == EPLAYER) {
			if (o->mTag == CCollider::EPLAYERCOLLIDER) {
				if (o->mpParent->mTag == EENEMY) {
					if (o->mTag == CCollider::EENEMYCOLLIDER) {

						//衝突しているとき
						if (CCollider::Collision(m, o)) {
							//mColliderCount = 10;
						}
					}
				}
				else if (o->mpParent->mTag == EENEMY2) {
					if (o->mTag == CCollider::EENEMY2COLLIDER) {
						//衝突しているとき
						if (CCollider::Collision(m, o)) {
							//mColliderCount = 10;
						}
					}




				}

			}
		}

	}
	//自身のコライダの設定
	switch (m->mType) {
	case CCollider::ELINE://線分コライダ
			//相手のコライダが三角コライダの場合
		if (o->mType == CCollider::ETRIANGLE) {
			CVector adjust;//調整用ベクトル
			//三角形と線分の衝突判定
			CCollider::CollisionTriangleLine(o, m, &adjust);
			//位置の更新（mPosition+adjust)
			mPosition = mPosition - adjust * -1;
			//行列の更新
			CTransform::Update();
		}
	case CCollider::ESPHERE:
		
		if (o->mType == CCollider::ESPHERE) {

			if (o->mpParent->mTag == EENEMY) {
				if (o->mTag == CCollider::EENEMYCOLLIDER) {
					//衝突しているとき
					CVector adjust;//調整用ベクトル
					if (CCollider::Collision(m, o)) {
						mColliderCount = 10;
					}
				}
	        }
			else if (o->mpParent->mTag == EENEMY2) {
				if (o->mTag == CCollider::EENEMY2COLLIDER) {
					//衝突しているとき
					CVector adjust;//調整用ベクトル
					if (CCollider::Collision(m, o)) {
						mColliderCount = 10;
					}
				}


			}

				

		}


	}
	


	
}

void CPlayer::TaskCollision() {
	//コライダの優先度変更
	mLine.ChangePriority();
	mLine2.ChangePriority();
	mLine3.ChangePriority();
	mCollider.ChangePriority();
	
	//	衝突処理を実行
	CCollisionManager::Get()->Collision(&mLine, COLLISIONRANGE);
	CCollisionManager::Get()->Collision(&mLine2, COLLISIONRANGE);
	CCollisionManager::Get()->Collision(&mLine3, COLLISIONRANGE);
	CCollisionManager::Get()->Collision(&mCollider, COLLISIONRANGE);
}
void CPlayer::Render() {
	//親の描画処理
	CCharacter::Render();
	//2Dの描画開始
	CUtil::Start2D(-400, 400, -300, 300);
	//描画色の設定（緑色の半透明）
	glColor4f(0.0f, 1.0f, 0.0f, 0.4f);
	//文字列編集エリアの作成
	char buf[64];

	//Y座標の表示
	//文字列の設定
	sprintf(buf, "ACTION1:%7.2d", mAction1);
	//文字列の描画
	mText.DrawString(buf, 100, 150, 8, 16);
	//文字列の設定
	sprintf(buf, "ACTION2:%7.2d", mAction2);
	//文字列の描画
	mText.DrawString(buf, 100, 120, 8, 16);
	//文字列の設定
	sprintf(buf, "ACTION3:%7.2d", mAction3);
	//文字列の描画
	mText.DrawString(buf, 100, 100, 8, 16);

	//文字列の設定
	sprintf(buf, "STAMINA:%7.2d", mStamina);
	//文字列の描画
	mText.DrawString(buf, 100, 70, 8, 16);
	//文字列の設定
	sprintf(buf, "SPACE:%7.2d", mSpaceCount1);
	//文字列の描画
	mText.DrawString(buf, 100, 40, 8, 16);

	//X座標の表示
	//文字列の設定
	sprintf(buf, "RX:%7.2f", mRotation2.mX);
	//文字列の描画
	mText.DrawString(buf, 100, 0, 8, 16);

	//Y軸回転値の表示
	//文字列の設定
	sprintf(buf, "RY:%7.2f", mRotation2.mY);
	//mText.DrawString(buf, 100, -100, 8, 16);
	//文字列の設定
	sprintf(buf, "%10d", mRotationCount);
	mText.DrawString(buf, 100, -100, 8, 16);

	//2Dの描画終了
	CUtil::End2D();


}