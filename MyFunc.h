#pragma once
//�Լ� ���� ����� ���ĵ� ok �Լ� �ʹ� ������ ������ �ٸ������ �־ ok
#define PI 3.141592654f
#define TORADIAN 0.017435f  // PI/180.0f
//float �� ����ü
typedef struct tagFRECT
{
	float left;
	float top;
	float right;
	float bottom;
} FRECT, *PFRECT;

typedef struct tagFCIRCLE
{
	float  x;
	float  y;
	float  r;
} FCIRCLE, *PFCIRCLE;

//����
template <typename T>
static void CustomSwap(T &a, T &b)
{
	T temp;
	temp = a;
	a = b;
	b = temp;

}
//����
template <typename T>
static void CustomShuffle(T a[], unsigned int time, unsigned int range)
{
	for (UINT i = 0; i < time; i++)
	{
		unsigned int dest = rand() % range;
		unsigned int sour = rand() % range;
		T temp = a[dest];
		a[dest] = a[sour];
		a[sour] = temp;
	}
}
//�� ������ �Ÿ� ���ϱ�
static float GetDistance(float x1, float y1, float x2, float y2)
{
	float x = x2 - x1;
	float y = y2 - y1;

	return sqrtf(x * x + y * y);
}
//���� ���ϱ�
static float GetRadian(float x1, float y1, float x2, float y2)
{
	float x = x2 - x1;
	float distance = GetDistance(x1, y1, x2, y2);
	float angle = acosf(x / distance);
	if (y2 < y1)
	{
		angle = PI + (PI - angle);
		//angle += PI;
	}
	return angle;
}
static float GetDegree(float x1, float y1, float x2, float y2)
{
	float angle = GetRadian(x1, y1, x2, y2);
	angle /= TORADIAN;
	return angle;
}
//���� ������ �Լ�
static void ReverseAngle(float &angle, bool isRadian, bool AxisX, bool AxisY)
{
	float angle180;
	//���׿�����
	(isRadian) ? angle180 = PI : angle180 = 180.0f;
	if (AxisX)angle = angle180 - angle;
	if (AxisY)angle = angle180 + angle180 - angle;
}


//�׸� �����
static FRECT RectMake(const float x, const float y, const float width, const float height)
{
	FRECT rc = { x , y + height , x + width , y };
	return rc;
}
//�����߽� �׸� �����

static FRECT RectMakeCenter(const float x, const float y, const float width, const float height)
{
	float HalfWidth = width / 2.0f;
	float HalfHeight = height / 2.0f;
	FRECT rc = { x - HalfWidth ,y + HalfHeight ,x + HalfWidth ,y - HalfHeight };
	return rc;
}
//�� �����
static FCIRCLE CircleMake(const float x, const float y, const float r)
{
	FCIRCLE cc = { x,y,r };
	return cc;
}
//�浹 �Լ�(�� �����)
//�簢��,�簢��
static bool IntersectRect(FRECT rc1, FRECT rc2)
{
	if (rc1.right >= rc2.left &&
		rc1.left <= rc2.right &&
		rc1.top >= rc2.bottom &&
		rc1.bottom <= rc2.top)
	{
		return true;
	}
	return false;
}
//�簢��,��
static bool PtInRect( FRECT Rect, D3DXVECTOR2 InPt)
{
	if (Rect.left <= InPt.x && InPt.x <= Rect.right &&
		Rect.top >= InPt.y && InPt.y >= Rect.bottom)
	{
		return true;
	}
	return false;
}
static bool PtInRect(FRECT Rect, D3DXVECTOR2 InPt, float radian)
{
	D3DXVECTOR2 pos{ Rect.right - ((Rect.right - Rect.left) / 2.0f), Rect.top - ((Rect.top - Rect.bottom) / 2.0f) };
	D3DXMATRIX R;
	D3DXMatrixRotationZ(&R, -radian);
	FRECT tempRc{ Rect.left - pos.x ,Rect.top - pos.y,Rect.right - pos.x,Rect.bottom - pos.y };
	D3DXVECTOR2 tempPt{ InPt.x - pos.x ,InPt.y - pos.y };
	D3DXVec2TransformCoord(&tempPt, &tempPt, &R);
	return PtInRect(tempRc, tempPt);
}
//��,��
static bool PtInCircle(FCIRCLE cc, D3DXVECTOR2 InPt)
{
	if (cc.r >= GetDistance(cc.x, cc.y, InPt.x, InPt.y))
	{
		return true;
	}
	return false;
}
//��,��
static bool IntersectCircle(FCIRCLE cc1, FCIRCLE cc2)
{
	if (cc1.r + cc2.r >= GetDistance(cc1.x, cc1.y, cc2.x, cc2.y))
	{
		return true;
	}
	return false;
}
//�簢��,��
static bool IntersectRectCircle(FRECT rc, FCIRCLE cc)
{
	//�𼭸� ���� �׸� ���浹
	FRECT temp{ rc.left ,rc.top + cc.r,rc.right,rc.bottom - cc.r };
	if (PtInRect(temp, D3DXVECTOR2(cc.x, cc.y))) return true;
	FRECT temp2{ rc.left - cc.r,rc.top,rc.right + cc.r,rc.bottom };
	if (PtInRect(temp2, D3DXVECTOR2(cc.x, cc.y))) return true;

	//�𼭸� �浹
	if (PtInCircle(cc, D3DXVECTOR2(rc.left, rc.top))) return true;
	if (PtInCircle(cc, D3DXVECTOR2(rc.left, rc.bottom))) return true;
	if (PtInCircle(cc, D3DXVECTOR2(rc.right, rc.top))) return true;
	if (PtInCircle(cc, D3DXVECTOR2(rc.right, rc.bottom))) return true;
	return false;
}
static bool IntersectRectCircle(FRECT rc, FCIRCLE cc, float radian)
{
	D3DXVECTOR2 pos{ rc.right - ((rc.right - rc.left) / 2.0f), rc.top - ((rc.top - rc.bottom) / 2.0f) };
	D3DXMATRIX R;
	D3DXMatrixRotationZ(&R, -radian);
	FRECT tempRc{ rc.left - pos.x ,rc.top - pos.y,rc.right - pos.x,rc.bottom - pos.y };
	D3DXVECTOR2 tempPt{ cc.x - pos.x ,cc.y - pos.y };
	D3DXVec2TransformNormal(&tempPt, &tempPt, &R);
	FCIRCLE tempcc{ tempPt.x,tempPt.y,cc.r };
	return IntersectRectCircle(tempRc, tempcc);
}

//���� ���

//	0 ���� ���� int �� ��������
static int GetInt(int num)
{
	return rand() % num;
}
//	������ ���� int �� ��������
static int GetFromIntTo(int fromNum, int toNum)
{
	return rand() % (toNum - fromNum + 1) + fromNum;
}
//	0 ���� ���� float �� ��������
static float GetFloat(float num)
{
	return (static_cast<float>(rand()) / static_cast<float>(RAND_MAX)) * num;
}
//	������ ���� float �� ��������
static float GetFromFloatTo(float fromNum, float toNum)
{
	float rnd = static_cast<float>(rand()) / static_cast<float>(RAND_MAX);
	return (rnd * (toNum - fromNum) + fromNum);
}