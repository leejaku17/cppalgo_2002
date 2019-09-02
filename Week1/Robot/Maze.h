// Maze.h: interface for the CMaze class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MAZE_H__FF364330_0858_4FE3_B923_01AF2381A471__INCLUDED_)
#define AFX_MAZE_H__FF364330_0858_4FE3_B923_01AF2381A471__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define MAZE_SIZE		19
#define CELL_SIZE		16		// 그림을 그릴때 한 블럭의 크기 

class CMaze  
{
public:
	CMaze();
	virtual ~CMaze();

public:
	void DrawShortedPath();
	void ShortestPath();
	void RightHandOnWall(int x, int y, int dir);
	void SetDrawWnd(CWnd* pwnd);
	bool DrawMaze();
	void SetMaze(int maze[][MAZE_SIZE]);
	enum {
		UP		= 1,
		RIGHT	= 2,
		DOWN	= 4,
		LEFT	= 8,
		NODIR	= 15
	};

protected:
	int DeletePath(int i, int j);
	void InitRecord();
	bool Record(int x, int y);
	void TurnLeft(int& dir);
	void TurnRight(int& dir);
	bool WallAhead(int x, int y, int dir);
	bool StillInMaze(int x, int y);
	void DrawMouse(int x, int y, int dir);
	void GoForward(int& x, int& y, int dir);
	int GetShape(int x, int y);
	int		m_arrayMaze[MAZE_SIZE][MAZE_SIZE];
	CWnd	*m_pwndDraw;
	int		m_arrayRecord[MAZE_SIZE*MAZE_SIZE*2];
	int		m_indexRecord;
};

#endif // !defined(AFX_MAZE_H__FF364330_0858_4FE3_B923_01AF2381A471__INCLUDED_)
