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
#include"CWeapon.h"
CMatrix Matrix;
CPlayer::CPlayer()
//線分コライダの設定（親、親行列、頂点１、頂点２）
	:mLine(this, &mMatrix, CVector(0.0f, 9.0f, -7.0f), CVector(0.0f, 9.0f, 10.0f)) //前後の線分コライダ
	, mLine2(this, &mMatrix, CVector(0.0f, 12.0f, -4.0f), CVector(0.0f, 6.0f, -4.0f))  //上下の線分コライダ
	, mLine3(this, &mMatrix, CVector(7.0f, 9.0f, -4.0f), CVector(-7.0f, 9.0f, -4.0f))  //左右の線分コライダ
	,mCollider(this,&mMatrix,CVector(0.0f,9.0f,0.0f),0.1f)
	, mRotationCountFirst(1)
	,mRotationCount(0)
	,mRotationCount2(0)
	,mRotationCount3(0)
	,mRotationCount4(0)
	, mSpaceCount(0)
	, mStamina(400)
{
//テクスチャファイルの読み込み(１行６４列）
mText.LoadTexture("FontWhite.tga", 1, 64);
mTag = EPLAYER;//タグの設定

}
void CPlayer::Update() {
	

	//スペースキー入力で弾発射
	if (CKey::Once(VK_SPACE)) {

		
		//Weapon = new CWeapon();

/*
		if (mSpaceCount <= 0) {
         mSpaceCount += 60;
          Weapon->mAction1 += 60;
      
		}
		else if (mSpaceCount > 0&& Weapon->mAction1>0) {
			mSpaceCount += 60;
			Weapon->mAction2 += 60;
		}
		else if (mSpaceCount > 0&& Weapon->mAction2 > 0) {
			mSpaceCount += 60;
			Weapon->mAction3 += 60;
		}*/

		/*//Y軸の回転値を増加
		mRotation.mY += 50;
		//CBulletをbulletに変換
		CBullet* bullet = new CBullet();
		//mPlayerの視点と同じ方向に飛ぶ
		bullet->Set(0.1f, 1.5f);
        bullet->mPosition = CVector(0.0f, 0.0f, 10.0f) * mMatrix;
        bullet->mRotation = mRotation;
		bullet->Update();
		//弾クラスのインスタンスをタスクリストに追加
		//TaskManager.Add(bullet);*/

	}
	if (mSpaceCount > 0) {
		mSpaceCount--;
	}
	
	if (mStamina <= 400) {
    mStamina++;
	}
	
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
			 mRotation.mY +=180;
				mRotationCount3 -= 1;
	     }
		 else if (mRotationCount4 > 0) {//左を向いていたとき
			 mRotation.mY -=90;
				mRotationCount4 -= 1;
	     }
		if (CKey::Push('C')) {
			if (mStamina > 0) {
				
				//X軸方向に-１進んだ値を回転移動させる
				mPosition = CVector(0.0f, 0.0f, 4.0f) * mMatrix;
				mStamina -= 2;
			}
			else if (mStamina <= 2 || mStamina >= 0) {
				//X軸方向に-１進んだ値を回転移動させる
				mPosition = CVector(0.0f, 0.0f, 1.0f) * mMatrix;
				mStamina -= 2;
			}
		}
		else {
			//X軸方向に-１進んだ値を回転移動させる
			mPosition = CVector(0.0f, 0.0f, 2.0f) * mMatrix;
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
			 mRotation.mY -=90;
			 mRotationCount2 -= 1;
		 }
		 else if (mRotationCount > 0) {//正面を向いていたとき
			 mRotation.mY+=180;
			 mRotationCount -= 1;
		 }
		 else if (mRotationCount4 >0) {//左を向いていたとき
			 mRotation.mY += 90;
			 mRotationCount4 -= 1;
		 }
		if (CKey::Push('C')) {
			if (mStamina > 0) {
				//X軸方向に-１進んだ値を回転移動させる
				mPosition = CVector(0.0f, 0.0f, 4.0f) * mMatrix;
				mStamina -= 2;
			}
			else if (mStamina <= 2 || mStamina >= 0) {
				//X軸方向に-１進んだ値を回転移動させる
				mPosition = CVector(0.0f, 0.0f, 1.0f) * mMatrix;
				mStamina -= 2;
			}
		}
		else {
			//X軸方向に-１進んだ値を回転移動させる
			mPosition = CVector(0.0f, 0.0f, 2.0f) * mMatrix;
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
			 mRotation.mY +=180;
			 mRotationCount2 -= 1;
		 }
		 else if (mRotationCount3 > 0) {//後ろを向いていたとき
			 mRotation.mY -=90;
			 mRotationCount3 -= 1;
		 }
		 else if (mRotationCount > 0) {//正面を向いていたとき
			 mRotation.mY += 90;
			 mRotationCount -= 1;
		 }
		if (CKey::Push('C')) {
			if (mStamina > 0) {
				//X軸方向に-１進んだ値を回転移動させる
				mPosition = CVector(0.0f, 0.0f, 4.0f) * mMatrix;
				mStamina -= 2;
			}
			else if (mStamina <= 2 || mStamina >= 0) {
				//X軸方向に-１進んだ値を回転移動させる
				mPosition = CVector(0.0f, 0.0f, 1.0f) * mMatrix;
				mStamina -= 2;
			}
		}
		else {
			//X軸方向に-１進んだ値を回転移動させる
			mPosition = CVector(0.0f, 0.0f, 2.0f) * mMatrix;
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
			 mRotation.mY +=180;
			 mRotationCount4 -= 1;
		 }
		if (CKey::Push('C')) {
			if (mStamina > 0) {
				//X軸方向に-１進んだ値を回転移動させる
				mPosition = CVector(0.0f, 0.0f, 4.0f) * mMatrix;
				mStamina -= 2;
			}
			else if (mStamina <= 2 || mStamina >= 0) {
				//X軸方向に-１進んだ値を回転移動させる
				mPosition = CVector(0.0f, 0.0f, 1.0f) * mMatrix;
				mStamina -= 2;
			}
		}
		else {
        //X軸方向に-１進んだ値を回転移動させる
		mPosition = CVector(0.0f, 0.0f, 2.0f) * mMatrix;
		}
	}
	
    //左向き
	 if (CKey::Push('A')) {
		//Y軸の回転値を増加
		mRotation2.mY += 3;
		mRotation.mY += 3;
	 }
	//右向き
	if (CKey::Push('D')) {
		//Y軸の回転値を減算
		mRotation2.mY -= 3;
		mRotation.mY -= 3;
	}
	//上向き
	if (CKey::Push('S')) {
		//X軸の回転値を減算
		if (mRotation2.mX > -60) {

			mRotation2.mX -= 3;
		}
	}
	//下向き
	if (CKey::Push('W')) {
		//X軸の回転値を加算
		if (mRotation2.mX < 90) {

			mRotation2.mX += 3;
		}
	}
	//CCharacterの更新
	CTransform::Update();
}	
void CPlayer::Collision(CCollider* m, CCollider* o) {
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
			break;
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
	sprintf(buf, "PY:%7.2f", mPosition.mY);
	//文字列の描画
	mText.DrawString(buf, 100, 30, 8, 16);

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