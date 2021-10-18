#include "MyMainGame.h"

MyMainGame::MyMainGame()
	: m_hBitmap(NULL), m_vEye(0, 0, -5), m_vLookAt(0, 0, 0), m_vUp(0, 1, 0)
{ }

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

	m_vecVertext.push_back(MyVector3(-1.0f, -1.0f, -1.0f)); // 0
	m_vecVertext.push_back(MyVector3(-1.0f,  1.0f, -1.0f)); // 1
	m_vecVertext.push_back(MyVector3( 1.0f,  1.0f, -1.0f)); // 2
	m_vecVertext.push_back(MyVector3( 1.0f, -1.0f, -1.0f)); // 3

	m_vecVertext.push_back(MyVector3(-1.0f, -1.0f,  1.0f)); // 4
	m_vecVertext.push_back(MyVector3(-1.0f,  1.0f,  1.0f)); // 5
	m_vecVertext.push_back(MyVector3( 1.0f,  1.0f,  1.0f)); // 6
	m_vecVertext.push_back(MyVector3( 1.0f, -1.0f,  1.0f)); // 7

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
}

void MyMainGame::Update()
{
	RECT rc;
	GetClientRect(g_hWnd, &rc);

	m_vLookAt = MyVector3(0.0f, 0.0f, 0.0f);
	m_vEye = MyVector3(0.0f, 5.0f, -5.0f);

	m_matView = MyMatrix::View(m_vEye, m_vLookAt, m_vUp);
	m_matProj = MyMatrix::Projection(PI / 4.0f, (float)(rc.right / rc.bottom), 1.0f, 1000.0f);

	m_matViewport = MyMatrix::Viewport(0.0f, 0.0f, (float)rc.right, (float)rc.bottom, 0.0f, 1.0f);
}

void MyMainGame::Render(HDC hdc)
{
	RECT rc;
	GetClientRect(g_hWnd, &rc);

	PatBlt(m_MemDC, rc.left, rc.top, rc.right, rc.bottom, WHITENESS);

	MyMatrix matWVP = m_matWorld * m_matView * m_matProj;

	for (size_t i = 0; i < m_vecIndex.size(); i += 3)
	{
		MyVector3 v0 = m_vecVertext[m_vecIndex[i + 0]];
		MyVector3 v1 = m_vecVertext[m_vecIndex[i + 1]];
		MyVector3 v2 = m_vecVertext[m_vecIndex[i + 2]];

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

	BitBlt(hdc, 0, 0, rc.right, rc.bottom, m_MemDC, 0, 0, SRCCOPY);
}

void MyMainGame::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{

}
