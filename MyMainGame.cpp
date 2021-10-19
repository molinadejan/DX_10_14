#include "MyMainGame.h"

MyMainGame::MyMainGame()
	: m_hBitmap(NULL)
	, m_vEye(0, 0, -5)
	, m_vLookAt(0, 0, 0)
	, m_vUp(0, 1, 0)
	, m_vPosition(0, 0, 0)
	, m_fBoxRotY(0.0f)
	, m_vBoxDirection(0, 0, 1)
	, m_fCameraDistance(5.0f)
	, m_isLButtonDown(false)
	, m_vCamRotAngle(0, 0, 0)
{ 
	m_ptPrevMouse.x = 0;
	m_ptPrevMouse.y = 0;
}

MyMainGame::~MyMainGame()
{
	SelectObject(m_MemDC, m_hOldBitmap);
	DeleteObject(m_hBitmap);
	DeleteDC(m_MemDC);
}

void MyMainGame::SetUp()
{
	HDC hdc = GetDC(g_hWnd);
	m_MemDC = CreateCompatibleDC(hdc);

	RECT rc;
	GetClientRect(g_hWnd, &rc);
	
	m_hBitmap = CreateCompatibleBitmap(hdc, rc.right, rc.bottom);
	m_hOldBitmap = (HBITMAP)SelectObject(m_MemDC, m_hBitmap);

	ReleaseDC(g_hWnd, hdc);

	m_vecVertex.push_back(MyVector3(-1.0f, -1.0f, -1.0f)); // 0
	m_vecVertex.push_back(MyVector3(-1.0f,  1.0f, -1.0f)); // 1
	m_vecVertex.push_back(MyVector3( 1.0f,  1.0f, -1.0f)); // 2
	m_vecVertex.push_back(MyVector3( 1.0f, -1.0f, -1.0f)); // 3

	m_vecVertex.push_back(MyVector3(-1.0f, -1.0f,  1.0f)); // 4
	m_vecVertex.push_back(MyVector3(-1.0f,  1.0f,  1.0f)); // 5
	m_vecVertex.push_back(MyVector3( 1.0f,  1.0f,  1.0f)); // 6
	m_vecVertex.push_back(MyVector3( 1.0f, -1.0f,  1.0f)); // 7

	// 앞
	m_vecIndex.push_back(0);
	m_vecIndex.push_back(1);
	m_vecIndex.push_back(2);

	m_vecIndex.push_back(0);
	m_vecIndex.push_back(2);
	m_vecIndex.push_back(3);

	// 뒤
	m_vecIndex.push_back(7);
	m_vecIndex.push_back(6);
	m_vecIndex.push_back(5);

	m_vecIndex.push_back(7);
	m_vecIndex.push_back(5);
	m_vecIndex.push_back(4);

	// 왼
	m_vecIndex.push_back(4);
	m_vecIndex.push_back(5);
	m_vecIndex.push_back(1);

	m_vecIndex.push_back(4);
	m_vecIndex.push_back(1);
	m_vecIndex.push_back(0);

	// 오
	m_vecIndex.push_back(3);
	m_vecIndex.push_back(2);
	m_vecIndex.push_back(6);

	m_vecIndex.push_back(3);
	m_vecIndex.push_back(6);
	m_vecIndex.push_back(7);

	// 위
	m_vecIndex.push_back(1);
	m_vecIndex.push_back(5);
	m_vecIndex.push_back(6);

	m_vecIndex.push_back(1);
	m_vecIndex.push_back(6);
	m_vecIndex.push_back(2);

	// 아래
	m_vecIndex.push_back(4);
	m_vecIndex.push_back(0);
	m_vecIndex.push_back(3);

	m_vecIndex.push_back(4);
	m_vecIndex.push_back(3);
	m_vecIndex.push_back(7);

	m_matWorld = MyMatrix::Identity(4);
	m_matView = MyMatrix::Identity(4);
	m_matProj = MyMatrix::Identity(4);
	m_matViewport = MyMatrix::Identity(4);

	SetGrid();
}

void MyMainGame::Update()
{
	Update_Rotation();
	Update_Move();

	RECT rc;
	GetClientRect(g_hWnd, &rc);

	MyMatrix matRX = MyMatrix::RotationX(m_vCamRotAngle.x);
	MyMatrix matRY = MyMatrix::RotationY(m_vCamRotAngle.y);
	MyMatrix matRC = matRX * matRY;


	m_vLookAt = m_vPosition;
	m_vEye = MyVector3(0.0f, m_fCameraDistance, -m_fCameraDistance);
	m_vEye = MyVector3::TransformCoord(m_vEye, matRC);
	m_vEye = m_vEye + m_vPosition;

	MyMatrix matR = MyMatrix::RotationY(m_fBoxRotY);
	MyMatrix matT = MyMatrix::Translation(m_vPosition);

	m_vBoxDirection = MyVector3(0, 0, 1);
	m_vBoxDirection = MyVector3::TransformNormal(m_vBoxDirection, matR);

	m_matWorld = matR * matT;
	m_matView = MyMatrix::View(m_vEye, m_vLookAt, m_vUp);
	m_matProj = MyMatrix::Projection(PI / 4.0f, (float)(rc.right / rc.bottom), 1.0f, 1000.0f);

	m_matViewport = MyMatrix::Viewport(0.0f, 0.0f, (float)rc.right, (float)rc.bottom, 0.0f, 1.0f);
}

void MyMainGame::Render(HDC hdc)
{
	RECT rc;
	GetClientRect(g_hWnd, &rc);

	PatBlt(m_MemDC, rc.left, rc.top, rc.right, rc.bottom, WHITENESS);

	// W V P
	MyMatrix matWVP = m_matWorld * m_matView * m_matProj;

	for (size_t i = 0; i < m_vecIndex.size(); i += 3)
	{
		MyVector3 v0 = m_vecVertex[m_vecIndex[i + 0]];
		MyVector3 v1 = m_vecVertex[m_vecIndex[i + 1]];
		MyVector3 v2 = m_vecVertex[m_vecIndex[i + 2]];

		v0 = MyVector3::TransformCoord(v0, matWVP);
		v1 = MyVector3::TransformCoord(v1, matWVP);
		v2 = MyVector3::TransformCoord(v2, matWVP);

		// To do someting ......

		v0 = MyVector3::TransformCoord(v0, m_matViewport);
		v1 = MyVector3::TransformCoord(v1, m_matViewport);
		v2 = MyVector3::TransformCoord(v2, m_matViewport);

		MoveToEx(m_MemDC, v0.x, v0.y, NULL);
		LineTo(m_MemDC, v1.x, v1.y);
		LineTo(m_MemDC, v2.x, v2.y);
		LineTo(m_MemDC, v0.x, v0.y);
	}

	DrawGrid();

	BitBlt(hdc, 0, 0, rc.right, rc.bottom, m_MemDC, 0, 0, SRCCOPY);
}

void MyMainGame::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
		case WM_LBUTTONDOWN:
		{
			m_ptPrevMouse.x = LOWORD(lParam);
			m_ptPrevMouse.y = HIWORD(lParam);
			m_isLButtonDown = true;
		}
		break;

		case WM_LBUTTONUP:
		{
			m_isLButtonDown = false;
		}
		break;

		case WM_MOUSEMOVE:
		{
			if (m_isLButtonDown)
			{
				POINT ptCurMouse;
				ptCurMouse.x = LOWORD(lParam);
				ptCurMouse.y = HIWORD(lParam);

				float fDeltaX = (float)ptCurMouse.x - m_ptPrevMouse.x;
				float fDeltaY = (float)ptCurMouse.y - m_ptPrevMouse.y;

				m_vCamRotAngle.y += (fDeltaX / 100.0f);
				m_vCamRotAngle.x += (fDeltaY / 100.0f);

				if (m_vCamRotAngle.x < -PI / 2.0f + 0.0001f)
					m_vCamRotAngle.x = -PI / 2.0f + 0.0001f;

				if (m_vCamRotAngle.y > PI / 2.0f + 0.0001f)
					m_vCamRotAngle.y = PI / 2.0f + 0.0001f;

				m_ptPrevMouse = ptCurMouse;
			}
		}
		break;

		case WM_MOUSEWHEEL:
		{
			m_fCameraDistance -= (GET_WHEEL_DELTA_WPARAM(wParam) / 30.f);

			if (m_fCameraDistance < 0.0001f)
				m_fCameraDistance = 0.0001f;
		}
		break;
	}

}

void MyMainGame::SetGrid()
{
	int nNumHalfTile = 5;
	float fInterval = 1.0f;
	float fMax = nNumHalfTile * fInterval;
	float fMin = -nNumHalfTile * fInterval;

	for (int i = 1; i <= nNumHalfTile; ++i)
	{
		m_vecLineVertex.push_back(MyVector3(fMin, 0, i * fInterval));
		m_vecLineVertex.push_back(MyVector3(fMax, 0, i * fInterval));

		m_vecLineVertex.push_back(MyVector3(fMin, 0, -i * fInterval));
		m_vecLineVertex.push_back(MyVector3(fMax, 0, -i * fInterval));

		m_vecLineVertex.push_back(MyVector3(i * fInterval, 0, fMin));
		m_vecLineVertex.push_back(MyVector3(i * fInterval, 0, fMax));

		m_vecLineVertex.push_back(MyVector3(-i * fInterval, 0, fMin));
		m_vecLineVertex.push_back(MyVector3(-i * fInterval, 0, fMax));
	}

	m_vecLineVertex.push_back(MyVector3(0, 0, fMin));
	m_vecLineVertex.push_back(MyVector3(0, 0, fMax));

	m_vecLineVertex.push_back(MyVector3(fMin, 0, 0));
	m_vecLineVertex.push_back(MyVector3(fMax, 0, 0));

	m_vAxisXTextPosition = MyVector3(fMax, 0, 0);
	m_vAxisZTextPosition = MyVector3(0, 0, fMax);
}

void MyMainGame::DrawGrid()
{
	MyMatrix mat = m_matView * m_matProj * m_matViewport;

	for (size_t i = 0; i < m_vecLineVertex.size(); i += 2)
	{
		MyVector3 v1 = m_vecLineVertex[i];
		MyVector3 v2 = m_vecLineVertex[i + 1];

		v1 = MyVector3::TransformCoord(v1, mat);
		v2 = MyVector3::TransformCoord(v2, mat);
	
		MoveToEx(m_MemDC, v1.x, v1.y, NULL);
		LineTo(m_MemDC, v2.x, v2.y);
	}

	MyVector3 textX = MyVector3::TransformCoord(m_vAxisXTextPosition, mat);
	MyVector3 textZ = MyVector3::TransformCoord(m_vAxisZTextPosition, mat);


}

void MyMainGame::Update_Rotation()
{
	if (GetKeyState('A') & 0x8000)
		m_fBoxRotY -= 0.1f;

	if (GetKeyState('D') & 0x8000)
		m_fBoxRotY += 0.1f;
}

void MyMainGame::Update_Move()
{
	if (GetKeyState('W') & 0x8000)
		m_vPosition = m_vPosition + (m_vBoxDirection * 0.1f);

	if (GetKeyState('S') & 0x8000)
		m_vPosition = m_vPosition - (m_vBoxDirection * 0.1f);
}

bool MyMainGame::IsBackFace(MyVector3 & v1, MyVector3 & v2, MyVector3 & v3)
{
	MyVector3 v12 = v2 - v1;
	MyVector3 v13 = v3 - v1;
	MyVector3 n = MyVector3::Cross(v12, v13);

	if (MyVector3::Dot(n, MyVector3(0, 0, 1)) > 0)
		return true;

	return false;
}
