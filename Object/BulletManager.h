#pragma once
#include "GameNode.h"

class BulletManager : public GameNode
{
private:
	FCIRCLE m_crBullet;
	D3DXVECTOR2    m_Pos;
	float m_BulletSpeed;			// 총알이 초당이동하는 픽셀값
	float m_FireSpeed;				// 초당 발사속도
	float  m_FireAngle;				// 발사각, 라디안
	float m_FireAngle_rotate;		// 발사각 회전속도, 라디안
	UINT m_CurrentFramX;
	bool m_IsFire;
	FRECT m_Stage;
public:
	BulletManager(D3DXVECTOR2 Pos, float BulletSize, float BulletSpeed, float FireSpeed, float Angle, float RotateAngle);
	BulletManager();
	~BulletManager() override;
	void render() override;
	//get,set 함수
	void SetSpeed(float Speed);
	void SetFireSpeed(float Speed);
	void SetAngle(float Angle);
	void SetRotateAngle(float Angle);
	void SetStage(FRECT Stage);
	float GetRotateAngle();
	float GetAngle();;
	float GetSpeed();
	float GetBulletSpeed();
	void SetPos(D3DXVECTOR2 pos);
	bool GetFire();
	void SetFire(bool Fire);
	void SetSize(float Size);
	bool OnDisplay();
	bool CharColide(FRECT Object);
	FCIRCLE GetBullet();
	D3DXVECTOR2 GetPos();
	MAKEGETSET(UINT, m_CurrentFramX);
};

