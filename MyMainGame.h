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

	std::vector<MyVector3> m_vecVertex;
	std::vector<DWORD> m_vecIndex;
	std::vector<MyVector3> m_vecLineVertex;

	MyMatrix m_matWorld;
	MyMatrix m_matView;
	MyMatrix m_matProj;
	MyMatrix m_matViewport;
	
	MyVector3 m_vEye;
	MyVector3 m_vLookAt;
	MyVector3 m_vUp;
	MyVector3 m_vBoxDirection;

	MyVector3 m_vPosition;
	float m_fBoxRotY;

	// grid
	//std::vector<MyVector3> m_vecLineVertex;
	MyVector3 m_vAxisXTextPosition;
	MyVector3 m_vAxisZTextPosition;

	// camera
	POINT m_ptPrevMouse;
	bool m_isLButtonDown;
	float m_fCameraDistance;
	MyVector3 m_vCamRotAngle;

	float m_fScale;

public:

	void SetUp();
	void Update();
	void Render(HDC hdc);
	void WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

	void SetGrid();
	void DrawGrid();

	void Update_Rotation();
	void Update_Move();
	void Update_Scale();

	bool IsBackFace(MyVector3 &v1, MyVector3 &v2, MyVector3 &v3);
};

