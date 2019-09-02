// Maze.cpp: implementation of the CMaze class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Robot.h"
#include "Maze.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CMaze::CMaze()
{
	// 멤버변수들의 초기화 
	m_pwndDraw = 0;
	memset(m_arrayMaze, 0, sizeof(m_arrayMaze));
	InitRecord();
}

CMaze::~CMaze()
{
}

void CMaze::SetMaze(int maze[][MAZE_SIZE])
{
	memcpy(m_arrayMaze, maze, sizeof(m_arrayMaze));
}

int CMaze::GetShape(int x, int y)
{
	int shape = 0;
	
	if (m_arrayMaze[y][x] != 0) 	// 벽이 있는 경우에만 경우의 수를 따진다. 
	{			
		if (y > 0 && m_arrayMaze[y-1][x])		// 위쪽에 벽이 있나?
			shape |= UP;
		if (y < MAZE_SIZE - 1 && m_arrayMaze[y+1][x])	// 아랫쪽에 벽이 있나?
			shape |= DOWN;
		if (x > 0 && m_arrayMaze[y][x-1])		// 왼쪽에 벽이 있나?
			shape |= LEFT;
		if (x < MAZE_SIZE - 1 && m_arrayMaze[y][x+1])	// 오른쪽에 벽이 있나?
			shape |= RIGHT;
	}

	return shape;
}

bool CMaze::DrawMaze()
{
	// assertion
	if (!m_pwndDraw) 
		return false;

	// DC를 얻는다. 
	CDC *pdc = m_pwndDraw->GetDC();
	if (!pdc) 
		return false;

	// 벽 이미지를 로드하여 메모리DC에 넣는다. 
	CDC dcMem;
	dcMem.CreateCompatibleDC(pdc);
	CBitmap bmpWall;
	CBitmap *pbmpOld;
	bmpWall.LoadBitmap(IDB_WALL);
	pbmpOld = dcMem.SelectObject(&bmpWall);

	// 미로를 그린다. 
	int i, j;
	for (j = 0; j < MAZE_SIZE; j++) {
		for (i = 0; i < MAZE_SIZE; i++) {
			int shape = GetShape(i, j);
			pdc->BitBlt(i * 16, j * 16, 16, 16, &dcMem, shape*16, 0, SRCCOPY);		
		}
	}

	// 사용한 리소스들을 정리한다. 
	dcMem.SelectObject(pbmpOld);
	bmpWall.DeleteObject();
	m_pwndDraw->ReleaseDC(pdc);
	m_pwndDraw->ReleaseDC(&dcMem);
	return false;
}


void CMaze::SetDrawWnd(CWnd *pwnd)
{
	m_pwndDraw = pwnd;
}

void CMaze::GoForward(int &x, int &y, int dir)
{
	// 좌표 이동 
	x = (dir == LEFT ? --x : dir == RIGHT ? ++x : x);
	y = (dir == UP ? --y : dir == DOWN ? ++y : y);
}

void CMaze::DrawMouse(int x, int y, int dir)
{
	// dir이 0이면 지우고, 1,2,4,8 이면 해당 모양으로 그린다. 
	if (!m_pwndDraw)
		return;

	CDC *pdc = m_pwndDraw->GetDC();
	if (!pdc) 
		return;

	// 지우는 모드 (dir == 0)이면 그냥 지우고 리턴 
	if (dir == 0) {
		pdc->FillSolidRect(x*16, y*16, 16, 16, RGB(255, 255, 255));
		return;
	}

	// 모양 선택 
	int shape = (dir == UP ? 0 : dir == RIGHT ? 1 : dir == DOWN ? 2 : dir == LEFT ? 3 : dir == NODIR ? 4 : -1);
	if (shape < 0) 
		return;

	// 마우스 이미지를 로드하여 메모리DC에 넣는다. 
	CDC dcMem;
	dcMem.CreateCompatibleDC(pdc);
	CBitmap bmpMouse;
	CBitmap *pbmpOld;
	bmpMouse.LoadBitmap(IDB_MOUSE);
	pbmpOld = dcMem.SelectObject(&bmpMouse);
	
	// 마우스를 그린다. 
	pdc->BitBlt(x * 16, y * 16, 16, 16, &dcMem, shape*16, 0, SRCCOPY);		

	// 사용한 리소스들을 정리한다. 
	dcMem.SelectObject(pbmpOld);
	bmpMouse.DeleteObject();
	m_pwndDraw->ReleaseDC(pdc);
	m_pwndDraw->ReleaseDC(&dcMem);
}

bool CMaze::StillInMaze(int x, int y)
{
	if (x > 0 && x < MAZE_SIZE - 1 && y > 0 && y < MAZE_SIZE - 1)
		return true;
	else
		return false;
}

bool CMaze::WallAhead(int x, int y, int dir)
{
	// 좌표를 한칸 이동하여 벽인지 아닌지를 체크한다. 
	x = (dir == LEFT ? --x : dir == RIGHT ? ++x : x);
	y = (dir == UP ? --y : dir == DOWN ? ++y : y);

	return m_arrayMaze[y][x] != 0;
}


void CMaze::TurnRight(int &dir)
{
	dir <<= 1;
	dir = (dir > LEFT ? UP : dir);
}

void CMaze::TurnLeft(int &dir)
{
	dir >>= 1;
	dir = (dir == 0 ? LEFT : dir);
}

#define DELAY	100		// 100 msec
void CMaze::RightHandOnWall(int x, int y, int dir)
{
	InitRecord();

	// 생쥐 그리기 
	DrawMouse(x, y, dir);
	Sleep(DELAY);		// 시간 지연 
	Record(x, y);

//	GoForward(x, y, dir);		// 앞으로 간다.
	while (StillInMaze(x, y)) {		// 아직도 미로 안이면. 
		TurnRight(dir);		// 오른쪽으로 틀기 
		DrawMouse(x, y, dir);
		Sleep(DELAY);
		while (WallAhead(x, y, dir)) {		// 앞에 벽이 있으면 계속 
			TurnLeft(dir);			// 왼쪽으로 튼다. 
			DrawMouse(x, y, dir);
			Sleep(DELAY);
		}
		// 이전거 지우고. 
		DrawMouse(x, y, 0);

		// 이동 
		GoForward(x, y, dir);
		Record(x, y);		// 새로운 좌표 기록 
		DrawMouse(x, y, dir);
		Sleep(DELAY);
	}

	// 탐색 끝. 
	Record(-1, -1);
}

bool CMaze::Record(int x, int y)
{
	if (m_indexRecord > MAZE_SIZE*MAZE_SIZE*2 - 3)	// 오버플로우 방지. 
		return false;

	m_arrayRecord[m_indexRecord++] = x;
	m_arrayRecord[m_indexRecord++] = y;
	return true;
}

void CMaze::InitRecord()
{
	// 초기화 
	memset(m_arrayRecord, -1, sizeof(m_arrayRecord));
	m_indexRecord = 0;
}

int CMaze::DeletePath(int i, int j)
{
	int k = i;
	while (m_arrayRecord[j] >= 0)
		m_arrayRecord[i++] = m_arrayRecord[j++];
	m_arrayRecord[i] = -1;
	m_arrayRecord[i+1] = -1;
	return k;		// k는 삭제되고 난 뒤, j가 가져야 할 값. 
}

void CMaze::ShortestPath()
{
	int i = 0;
	int x, y;
	int j;
	int x1, y1;

	while (m_arrayRecord[i] >= 0) {
		x = m_arrayRecord[i];
		y = m_arrayRecord[i+1];
		j = i + 2;		// 한 좌표가 두개의 정수이므로 다음 좌표는 +2이다. 

		while (m_arrayRecord[j] >= 0) {
			x1 = m_arrayRecord[j];
			y1 = m_arrayRecord[j+1];
			if (x == x1 && y == y1)		// 같은 좌표 발견되면 
				j = DeletePath(i, j);		// 중복 경로 삭제 
			j += 2;
		}
		i += 2;
	}
}

void CMaze::DrawShortedPath()
{
	int i = 0;
	int x, y;
	while (m_arrayRecord[i] >= 0) {
		x = m_arrayRecord[i++];
		y = m_arrayRecord[i++];

		DrawMouse(x, y, NODIR);
		Sleep(DELAY);
		DrawMouse(x, y, 0);
	}
}
