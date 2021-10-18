#pragma once

#include "framework.h"
#include "MyVector3.h"

class MyMainGame
{
public:
	
	MyMainGame();
	~MyMainGame();

private:

	HDC m_MemDC;
	HBITMAP m_hOldBitmap, m_hBitmap;

	std::vector<MyVector3> m_vecVertext;
	std::vector<DWORD> m_vecIndex;
	std::vector<MyVector3> m_vecLineVertex;

	MyMatrix m_matWorld;
	MyMatrix m_matView;
	MyMatrix m_matProj;
	MyMatrix m_matViewport;
	
	MyVector3 m_vEye;
	MyVector3 m_vLookAt;
	MyVector3 m_vUp;

public:

	void SetUp();
	void Update();
	void Render(HDC hdc);
	void WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

};

