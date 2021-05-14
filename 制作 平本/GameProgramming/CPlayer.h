#ifndef CPLAYER_H
#define CPLAYER_H
#include"CBullet.h"
#include"CCharacter.h"
#include"CColliderLine.h"
#include"CBullet.h"
#include"CText.h"
#include"CText.h"
class CPlayer : public CCharacter {
public:

    CPlayer();
    CColliderLine mLine;//線分コライダ
    CColliderLine mLine2;//線分コライダ
    CColliderLine mLine3;//線分コライダ
    CBullet bullet();
    void Update();
   //衝突処理
    void Collision(CCollider* m, CCollider* o);
    void TaskCollision();
    CText mText;
    void Render();
    CCollider mCollider;//本体用コライダ
    int mRotationCount1;
    int mRotationCount2;
    int mRotationCount3;
    int mRotationCount4;
    int mStamina;
};
#endif
  
