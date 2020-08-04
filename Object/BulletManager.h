#pragma once
#include "GameNode.h"

class BulletManager : public GameNode
{
private:
	FCIRCLE m_crBullet;
	D3DXVECTOR2    m_Pos;
	float m_BulletSpeed;			// �Ѿ��� �ʴ��̵��ϴ� �ȼ���
	float m_FireSpeed;				// �ʴ� �߻�ӵ�
	float  m_FireAngle;				// �߻簢, ����
	float m_FireAngle_rotate;		// �߻簢 ȸ���ӵ�, ����
	UINT m_CurrentFramX;
	bool m_IsFire;
	FRECT m_Stage;
public:
	BulletManager(D3DXVECTOR2 Pos, float BulletSize, float BulletSpeed, float FireSpeed, float Angle, float RotateAngle);
	BulletManager();
	~BulletManager() override;
	void render() override;
	//get,set �Լ�
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

