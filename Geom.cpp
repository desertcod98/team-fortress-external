#include "Geom.h"
#include <Windows.h>
#include <iostream>

int screenX = GetSystemMetrics(SM_CXSCREEN);
int screenY = GetSystemMetrics(SM_CYSCREEN);
#define EnemyPen 0x000000FF
HBRUSH EnemyBrush = CreateSolidBrush(0x000000FF);
HDC hdc = GetDC(FindWindowA(NULL, "Team Fortress 2"));

RECT getRect() {
	RECT tempRect;
	GetWindowRect(FindWindowA(NULL, "Team Fortress 2"), &tempRect);
	return tempRect;
}

RECT rect = getRect();

Vec3 WorldToScreen(const Vec3 pos, view_matrix_t matrix) {
	int width = rect.right - rect.left;
	int height = rect.bottom - rect.top;
	float screenX = (matrix[0][0] * pos.x) + (matrix[0][1] * pos.y) + (matrix[0][2] * pos.z) + matrix[0][3];
	float screenY = (matrix[1][0] * pos.x) + (matrix[1][1] * pos.y) + (matrix[1][2] * pos.z) + matrix[1][3];
	float screenW = (matrix[3][0] * pos.x) + (matrix[3][1] * pos.y) + (matrix[3][2] * pos.z) + matrix[3][3];

	if (screenW < 0.001f) return { 0,0,0 };

	//camera position (eye level/middle of screen)
	float camX = width / 2.f;
	float camY = height / 2.f;

	//convert to homogeneous position
	float x = camX + (camX * screenX / screenW);
	float y = camY - (camY * screenY / screenW);

	return { x,y,0 };

}

void DrawFilledRect(int x, int y, int w, int h)
{
	RECT rect = { x, y, x + w, y + h };
	FillRect(hdc, &rect, EnemyBrush);
}

void DrawBorderBox(int x, int y, int w, int h, int thickness)
{
	DrawFilledRect(x, y, w, thickness); //Top horiz line
	DrawFilledRect(x, y, thickness, h); //Left vertical line
	DrawFilledRect((x + w), y, thickness, h); //right vertical line
	DrawFilledRect(x, y + h, w + thickness, thickness); //bottom horiz line
}

void DrawLine(float StartX, float StartY, float EndX, float EndY)
{
	int a, b = 0;
	HPEN hOPen;
	HPEN hNPen = CreatePen(PS_SOLID, 2, EnemyPen);// penstyle, width, color
	hOPen = (HPEN)SelectObject(hdc, hNPen);
	MoveToEx(hdc, StartX, StartY, NULL); //start
	a = LineTo(hdc, EndX, EndY); //end
	DeleteObject(SelectObject(hdc, hOPen));
}

float Vec3SquareDistance(Vec3 v, Vec3 w) {
	Vec3 difference = v - w;
	return (difference.x * difference.x + difference.y * difference.y + difference.z * difference.z);
}