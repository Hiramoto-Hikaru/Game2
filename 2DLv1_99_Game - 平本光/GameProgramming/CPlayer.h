#ifndef CPLAYER_H
#define CPLAYER_H
#include "CRectangle.h"
#include"CSound.h"
class CPlayer : public CRectangle {
public:
	static CPlayer* spInstance;
	//変数の定義
	int mFx, mFy;
	static int DamageCount;//ライフが減ると増える
	int FireCount;
	
     CPlayer();//コンストラクタ
	void Update();
		//更新処理
	void Render();//描画処理
	int mJump;//ジャンプフラグ
	int mVj;//ジャンプ用速度
	int mDj;//ノックバック
	int mjumpcount;//ジャンプできるようにする
	int mWorkCount;//徐々に速度を加算する
	int Count;// DamageCountをへらすタイミングを決める
	CSound Se;
	CSound Se2;
	CSound Se3;
	//衝突処理
	void Collision(CRectangle *i, CRectangle *y);
	int mAniCount;//アニメーション用カウンタ
	
};

#endif
