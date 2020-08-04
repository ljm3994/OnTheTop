#pragma once
#include "Object/BulletManager.h"

enum FIRE_TYPE
{
	NORMAL_FIRE,
	AIMED_FIRE,
	N_WAY_FIRE,
	MULTI_FIRE,
	CIRCLE_FIRE,
	FIRE_TYPE_NUM
};

class EnemyBullet : public BulletManager
{
	FIRE_TYPE m_Type;
	bool		 m_bFirst;
	float		 m_fSec_count;
	float		m_Time;
	bool m_AimeFirst;
	D3DXVECTOR2 * m_PlayerPos;

public:
	EnemyBullet(D3DXVECTOR2 Pos, float BulletSize, float BulletSpeed, float FireSpeed, float Angle, float RotateAngle, FIRE_TYPE Type);
	EnemyBullet();
	~EnemyBullet() override;
	HRESULT init() override;
	void release() override;
	void update() override;
	void SetBullet(const float time);
	void FireFly();
	void FireBullet();
	void SetPlayerPos(D3DXVECTOR2 * pos);
	void CircleFireBullet();
	void AimedFireBullet(const float Time);
	void N_AwayFire(const float Time);
	void BulletSetting(D3DXVECTOR2 Pos, float BulletSize, float BulletSpeed, float FireSpeed, float Angle, float RotateAngle, FIRE_TYPE Type);
};

