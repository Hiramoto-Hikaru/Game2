#ifndef CPLAYER_H
#define CPLAYER_H
#include"CBullet.h"
#include"CCharacter.h"
#include"CColliderLine.h"
#include"CBullet.h"
#include"CText.h"
#include"CText.h"
#include"CParent.h"
class CWeapon;
class CPlayer : public CCharacter {
public:

    CPlayer();
    CColliderLine mLine;//線分コライダ
    CColliderLine mLine2;//線分コライダ
    CColliderLine mLine3;//線分コライダ

    //CBullet bullet();
    CModel mModelW;
    void Update();
   //衝突処理
    void Collision(CCollider* m, CCollider* o);
    void TaskCollision();
    CText mText;
    void Render();
    CCollider mCollider;//本体用コライダ
    int mColliderCount;
    int mRotationCountFirst;
    int mRotationCount;
    int mRotationCount2;
    int mRotationCount3;
    int mRotationCount4;
    static  int mStamina;
    static int mSpaceCount1;
    static int mSpaceCount2;
    static int mSpaceCount3;
    static int mWeaponCount;
    CVector mCollisionEnemy;
    int mCount;
    static int mAction1;
    static int mAction2;
    static int mAction3;
    int mHp;
    //子のインスタンス
    CChild mChild;
   // CWeapon* Weapon;
};
#endif
  
