// MySnackDlg.h: 头文件

#pragma once
#include "Resource.h"

// CMySnackDlg 对话框
class CMySnackDlg : public CDialogEx
{
	// 构造
public:
	CMySnackDlg(CWnd* pParent = nullptr);	// 标准构造函数

//=======================================================
//类
public:
	class Point {
	public:
		int x; int y;

		Point() {};

		Point(int x, int y) {
			this->x = x;
			this->y = y;
		}

		void operator=(const Point& other) {
			this->x = other.x;
			this->y = other.y;
		}

		bool operator == (const Point& other) {
			if (this->x == other.x && this->y == other.y) {
				return true;
			}
			return false;
		}

		//随机点
		void  GetRandPoint() {
			srand((int)time(NULL));
			x = rand() % 20;
			y = rand() % 20;
			this->x = x;
			this->y = y;
		}
	};

	class Snack {
	public:
		Point Body[400];
		int Length;
		void MoveUp() {
			for (int i = Length; i >= 1; i--) {
				Body[i] = Body[i - 1];
			}
			this->Body[0].y--;
		};
		void MoveDown() {
			for (int i = Length; i >= 1; i--) {
				Body[i] = Body[i - 1];
			}
			this->Body[0].y++;
		};
		void MoveLeft() {
			for (int i = Length; i >= 1; i--) {
				Body[i] = Body[i - 1];
			}
			this->Body[0].x--;
		};
		void MoveRight() {
			for (int i = Length; i >= 1; i--) {
				Body[i] = Body[i - 1];
			}
			this->Body[0].x++;
		};
	};

	//变量
	CDC* pdc;			
	CStatic* IdcStatic[6];		//控件		
	CFont StaticFont[3];		//字体
	CPen Border;				//边框
	//CBitmap MapBitmap;
	//CBrush MapBrush;//构造位图画刷
	//CBitmap FruitBitmap;
	//CBrush FruitBrush;
	//CBrush SnackBrush[10];
	CBitmap memBitmap[12];		//位图
	BITMAP BmInfo[12];			//位图信息
	CDC memDC[12];				//存储位图
	CRect Map[20][20];			//地图20*20
	CRect MapRect;				//地图窗口
	Snack s1;					//蛇对象
	Point Fruit;				//果实
	Point LastPos;				//存储贪吃蛇最后部分
	int Speed;					//速度
	int MoveSign;				//移动方向
	int GameStatus;				//游戏状态
	int Score;					//得分

	//方法
	//CSting转Int
	void C2I(int &a,CString b) {
		//a = atoi((LPCSTR)b);
		a = _ttoi(b);
	}

	//Int转CString
	CString I2C(int b) {
		CString temp;
		temp.Format(L"%d",b);
		return temp;
	}

	//初始化函数
	void OnInit() {
		//初始化地图
		InitMap(20, 20, 30, 20, 20); //Width,Height,Size,MarginTop,MarginLeft
		//初始化蛇
		InitSnack(3);
		// 初始化果实
		InitFruit(s1);
		InitMapBorder();
		InitMapBrush();
		InitSnackBrush();
		InitFruitBrush();
		InitGameStatus();
	}

	//绘制
	void Paint() {
		//绘制地图
		BrushMap();
		//绘制蛇
		BrushSnack();
		//绘制果实
		BrushFruit();
	}

	//初始化地图
	void InitMap(int Width, int Height, int BlockSize) {
		GetDlgItem(Main)->MoveWindow(0, 0, Height * BlockSize, Width * BlockSize, false);
		for (int i = 0; i < Width; i++) {
			for (int j = 0; j < Height; j++) {
				Map[i][j].left = i * BlockSize;
				Map[i][j].right = Map[i][j].left + BlockSize;
				Map[i][j].top = j * BlockSize;
				Map[i][j].bottom = Map[i][j].top + BlockSize;
			}
		}
	}

	void InitMap(int Width, int Height, int BlockSize, int MarginTop, int MarginLeft) {
		for (int i = 0; i < Width; i++) {
			for (int j = 0; j < Height; j++) {
				Map[i][j].left = i * BlockSize + MarginTop;
				Map[i][j].right = Map[i][j].left + BlockSize;
				Map[i][j].top = j * BlockSize + MarginLeft;
				Map[i][j].bottom = Map[i][j].top + BlockSize;
			}
		}
	}

	//初始化蛇
	void InitSnack(int Length) {    //Lenght不包括头
		s1.Body[0].GetRandPoint();
		s1.Length = Length;
		if (s1.Body[0].x - Length >= 0) {
			for (int i = 1; i <= Length; i++) {
				Point p1 = s1.Body[i - 1];
				p1.x--;
				s1.Body[i] = p1;
			}
		}
		else if (s1.Body[0].x + Length <= 20) {
			for (int i = 1; i <= Length; i++) {
				Point p1 = s1.Body[i - 1];
				p1.x++;
				s1.Body[i] = p1;
			}
		}
		else if (s1.Body[0].y - Length >= 0) {
			for (int i = 1; i <= Length; i++) {
				Point p1 = s1.Body[i - 1];
				p1.y--;
				s1.Body[i] = p1;
			}
		}
		else {
			for (int i = 1; i <= Length; i++) {
				Point p1 = s1.Body[i - 1];
				p1.y++;
				s1.Body[i] = p1;
			}
		}
		for (int i = Length+1; i < 400; i++) {
			s1.Body[i].x = -100;
			s1.Body[i].y = -100;
		}
	}

	//初始化果实
	void InitFruit(Snack s1) {
		//找到不重复的点
		Point arr1[400];
		int cnt = 0;
		for (int i = 0; i < 20; i++) {
			for (int j = 0; j < 20; j++) {
				Point p1(i, j);
				for (int k = 1; k <= s1.Length; k++) {
					if (p1 == s1.Body[k]) {
						break;
					}
					if (k == s1.Length) {
						arr1[cnt] = p1;
						cnt++;
					}
				}
			}
		}

		srand((int)time(NULL));
		Fruit = arr1[rand() % cnt];
	}


	//初始化位图
	void InitBmInfo(CBitmap &ItemBitmap, BITMAP &BmInfo) {
		ItemBitmap.GetObjectW(sizeof(BmInfo), &BmInfo);	//Get Bitmap attribute
	}

	//初始化边框画笔
	void InitMapBorder() {
		Border.CreatePen(PS_SOLID, 5, RGB(88, 88, 88));
	}

	//初始化地图画笔
	void InitMapBrush() {
		memBitmap[0].LoadBitmapW(IDB_BITMAP2);				//初试化位图对象
		//MapBrush.CreatePatternBrush(&MapBitmap);		// 创建位图画刷
		InitBmInfo(memBitmap[0],BmInfo[0]);
		memDC[0].CreateCompatibleDC(pdc);
		memDC[0].SelectObject(&memBitmap[0]);
	}

	//初始化蛇画笔
	void InitSnackBrush() {
		//SnackBrush[0].CreateSolidBrush(RGB(155, 155, 155));
		//SnackBrush[4].CreateSolidBrush(RGB(50, 50, 50));
		memBitmap[2].LoadBitmapW(IDB_BITMAP4);					//初试化位图对象
		memBitmap[3].LoadBitmapW(IDB_BITMAP5);					//初试化位图对象
		memBitmap[4].LoadBitmapW(IDB_BITMAP6);					//初试化位图对象
		memBitmap[5].LoadBitmapW(IDB_BITMAP7);					//初试化位图对象
		memBitmap[6].LoadBitmapW(IDB_BITMAP8);					//初试化位图对象
		memBitmap[7].LoadBitmapW(IDB_BITMAP10);					//初试化位图对象
		memBitmap[8].LoadBitmapW(IDB_BITMAP11);					//初试化位图对象
		memBitmap[9].LoadBitmapW(IDB_BITMAP12);					//初试化位图对象
		memBitmap[10].LoadBitmapW(IDB_BITMAP13);				//初试化位图对象
		memBitmap[11].LoadBitmapW(IDB_BITMAP14);				//初试化位图对象

		InitBmInfo(memBitmap[2], BmInfo[2]);
		InitBmInfo(memBitmap[3], BmInfo[3]);
		InitBmInfo(memBitmap[4], BmInfo[4]);
		InitBmInfo(memBitmap[5], BmInfo[5]);
		InitBmInfo(memBitmap[6], BmInfo[6]);
		InitBmInfo(memBitmap[7], BmInfo[7]);
		InitBmInfo(memBitmap[8], BmInfo[8]);
		InitBmInfo(memBitmap[9], BmInfo[9]);
		InitBmInfo(memBitmap[10], BmInfo[10]);
		InitBmInfo(memBitmap[11], BmInfo[11]);

		//FruitBitmap.GetObjectW(sizeof(BmInfo), &FruitBmInfo);	//Get Bitmap attribute
		memDC[2].CreateCompatibleDC(pdc);
		memDC[3].CreateCompatibleDC(pdc);
		memDC[4].CreateCompatibleDC(pdc);
		memDC[5].CreateCompatibleDC(pdc);
		memDC[6].CreateCompatibleDC(pdc);
		memDC[7].CreateCompatibleDC(pdc);
		memDC[8].CreateCompatibleDC(pdc);
		memDC[9].CreateCompatibleDC(pdc);
		memDC[10].CreateCompatibleDC(pdc);
		memDC[11].CreateCompatibleDC(pdc);

		memDC[2].SelectObject(memBitmap[2]);
		memDC[3].SelectObject(memBitmap[3]);
		memDC[4].SelectObject(memBitmap[4]);
		memDC[5].SelectObject(memBitmap[5]);
		memDC[6].SelectObject(memBitmap[6]);
		memDC[7].SelectObject(memBitmap[7]);
		memDC[8].SelectObject(memBitmap[8]);
		memDC[9].SelectObject(memBitmap[9]);
		memDC[10].SelectObject(memBitmap[10]);
		memDC[11].SelectObject(memBitmap[11]);
	}

	//初始化果实画刷
	void InitFruitBrush() {
		memBitmap[1].LoadBitmapW(IDB_BITMAP3);					//初试化位图对象
		InitBmInfo(memBitmap[1], BmInfo[1]);
		//FruitBitmap.GetObjectW(sizeof(BmInfo), &FruitBmInfo);	//Get Bitmap attribute
		memDC[1].CreateCompatibleDC(pdc);
		memDC[1].SelectObject(memBitmap[1]);
	}

	//初始化游戏参数
	void InitGameStatus() {
		GameStatus = 0;
		MoveSign = -1;
		Score = 0;
	};

	//绘制地图
	void BrushMap() {
		//绘制边框
		BrushBorder();
		for (int i = 0; i < 20; i++) {
			for (int j = 0; j < 20; j++) {
				//pdc->FillRect(Map[i][j], &MapBrush);
				pdc->StretchBlt(Map[i][j].left, Map[i][j].top, 30, 30, &memDC[0], 0, 0, BmInfo[0].bmWidth, BmInfo[0].bmHeight, SRCCOPY);
			}
		}
	}

	//绘制边框
	void BrushBorder() {
		CPen* OldPen = pdc->SelectObject(&Border);
		CRect Temp = MapRect;
		Temp.top -= 5; Temp.bottom += 5; Temp.left -= 5; Temp.right += 5;
		pdc->Rectangle(&Temp);
		pdc->SelectObject(&OldPen);
	}

	//绘制蛇头
	void DrawHead() {
		//pdc->FillRect(Map[s1.Body[0].x][s1.Body[0].y], &SnackBrush[0]);
		switch (MoveSign) {
		case 1:
			pdc->StretchBlt(Map[s1.Body[0].x][s1.Body[0].y].left, Map[s1.Body[0].x][s1.Body[0].y].top, 30, 30, &memDC[2], 0, 0, BmInfo[2].bmWidth, BmInfo[2].bmHeight, SRCCOPY);
			break;
		case 2:
			pdc->StretchBlt(Map[s1.Body[0].x][s1.Body[0].y].left, Map[s1.Body[0].x][s1.Body[0].y].top, 30, 30, &memDC[3], 0, 0, BmInfo[3].bmWidth, BmInfo[3].bmHeight, SRCCOPY);
			break;
		case 3:
			pdc->StretchBlt(Map[s1.Body[0].x][s1.Body[0].y].left, Map[s1.Body[0].x][s1.Body[0].y].top, 30, 30, &memDC[4], 0, 0, BmInfo[4].bmWidth, BmInfo[4].bmHeight, SRCCOPY);
			break;
		case 4:
			pdc->StretchBlt(Map[s1.Body[0].x][s1.Body[0].y].left, Map[s1.Body[0].x][s1.Body[0].y].top, 30, 30, &memDC[5], 0, 0, BmInfo[5].bmWidth, BmInfo[5].bmHeight, SRCCOPY);
			break;
		default:
			switch (s1.Body[0].x - s1.Body[1].x) {
			case 1:
				pdc->StretchBlt(Map[s1.Body[0].x][s1.Body[0].y].left, Map[s1.Body[0].x][s1.Body[0].y].top, 30, 30, &memDC[5], 0, 0, BmInfo[5].bmWidth, BmInfo[5].bmHeight, SRCCOPY);
				break;
			case -1:
				pdc->StretchBlt(Map[s1.Body[0].x][s1.Body[0].y].left, Map[s1.Body[0].x][s1.Body[0].y].top, 30, 30, &memDC[4], 0, 0, BmInfo[4].bmWidth, BmInfo[4].bmHeight, SRCCOPY);
				break;
			default:
				switch (s1.Body[0].y - s1.Body[1].y) {
				case 1:
					pdc->StretchBlt(Map[s1.Body[0].x][s1.Body[0].y].left, Map[s1.Body[0].x][s1.Body[0].y].top, 30, 30, &memDC[3], 0, 0, BmInfo[3].bmWidth, BmInfo[3].bmHeight, SRCCOPY);
					break;
				case -1:
					pdc->StretchBlt(Map[s1.Body[0].x][s1.Body[0].y].left, Map[s1.Body[0].x][s1.Body[0].y].top, 30, 30, &memDC[2], 0, 0, BmInfo[2].bmWidth, BmInfo[2].bmHeight, SRCCOPY);
					break;
				}
			}
		}
	}

	//绘制蛇身
	void DrawBody() {
		for (int i = 0; i <= s1.Length; i++) {
			//pdc->FillRect(Map[s1.Body[i].x][s1.Body[i].y], &SnackBrush[4]);
			switch (s1.Body[i].x-s1.Body[i+2].x)
			{
				case 0:
					pdc->StretchBlt(Map[s1.Body[i+1].x][s1.Body[i+1].y].left, Map[s1.Body[i+1].x][s1.Body[i+1].y].top, 30, 30, &memDC[6], 0, 0, BmInfo[7].bmWidth, BmInfo[7].bmHeight, SRCCOPY);
					break;
				case 2:
				case -2:
					pdc->StretchBlt(Map[s1.Body[i+1].x][s1.Body[i+1].y].left, Map[s1.Body[i+1].x][s1.Body[i+1].y].top, 30, 30, &memDC[7], 0, 0, BmInfo[6].bmWidth, BmInfo[6].bmHeight, SRCCOPY);
					break;
				case 1:
					switch (s1.Body[i].y - s1.Body[i + 2].y)
					{
						case 1:
							if (s1.Body[i + 1].x + 1 != s1.Body[i].x) {
								pdc->StretchBlt(Map[s1.Body[i + 1].x][s1.Body[i + 1].y].left, Map[s1.Body[i + 1].x][s1.Body[i + 1].y].top, 30, 30, &memDC[10], 0, 0, BmInfo[10].bmWidth, BmInfo[10].bmHeight, SRCCOPY);

							}
							else {
								pdc->StretchBlt(Map[s1.Body[i + 1].x][s1.Body[i + 1].y].left, Map[s1.Body[i + 1].x][s1.Body[i + 1].y].top, 30, 30, &memDC[9], 0, 0, BmInfo[9].bmWidth, BmInfo[9].bmHeight, SRCCOPY);

							}
							break;
						case -1:
							if (s1.Body[i + 1].y - 1 != s1.Body[i].y) {
								pdc->StretchBlt(Map[s1.Body[i + 1].x][s1.Body[i + 1].y].left, Map[s1.Body[i + 1].x][s1.Body[i + 1].y].top, 30, 30, &memDC[11], 0, 0, BmInfo[11].bmWidth, BmInfo[11].bmHeight, SRCCOPY);
							}
							else {
								pdc->StretchBlt(Map[s1.Body[i + 1].x][s1.Body[i + 1].y].left, Map[s1.Body[i + 1].x][s1.Body[i + 1].y].top, 30, 30, &memDC[8], 0, 0, BmInfo[8].bmWidth, BmInfo[8].bmHeight, SRCCOPY);

							}
							break;
					}
					break;
				case -1:
					switch (s1.Body[i].y - s1.Body[i + 2].y)
					{
						case 1:
							if (s1.Body[i + 1].y + 1 != s1.Body[i].y) {
							pdc->StretchBlt(Map[s1.Body[i+1].x][s1.Body[i+1].y].left, Map[s1.Body[i+1].x][s1.Body[i+1].y].top, 30, 30, &memDC[8], 0, 0, BmInfo[8].bmWidth, BmInfo[8].bmHeight, SRCCOPY);
							}
							else {
								pdc->StretchBlt(Map[s1.Body[i + 1].x][s1.Body[i + 1].y].left, Map[s1.Body[i + 1].x][s1.Body[i + 1].y].top, 30, 30, &memDC[11], 0, 0, BmInfo[11].bmWidth, BmInfo[11].bmHeight, SRCCOPY);
							}
							break;
						case -1:
							if (s1.Body[i + 1].x - 1 != s1.Body[i].x) {
								pdc->StretchBlt(Map[s1.Body[i+1].x][s1.Body[i+1].y].left, Map[s1.Body[i+1].x][s1.Body[i+1].y].top, 30, 30, &memDC[9], 0, 0, BmInfo[9].bmWidth, BmInfo[9].bmHeight, SRCCOPY);
							}
							else {
								pdc->StretchBlt(Map[s1.Body[i + 1].x][s1.Body[i + 1].y].left, Map[s1.Body[i + 1].x][s1.Body[i + 1].y].top, 30, 30, &memDC[10], 0, 0, BmInfo[10].bmWidth, BmInfo[10].bmHeight, SRCCOPY);
							}
							break;
						}
					break;
			}
		}
	}

	//绘制蛇
	void BrushSnack() {
		DrawHead();
		DrawBody();
	}

	//绘制果实
	void BrushFruit() {
		//pdc->FillRect(Map[Fruit.x][Fruit.y], &FruitBrush);
		//CBitmap FruitBitmap;
		pdc->StretchBlt(Map[Fruit.x][Fruit.y].left, Map[Fruit.x][Fruit.y].top, 30,30,&memDC[1], 0, 0, BmInfo[1].bmWidth, BmInfo[1].bmHeight, SRCCOPY);
		//pdc->StretchBlt(Map[Fruit.x][Fruit.y].left, Map[Fruit.x][Fruit.y].top,30,30,pdc,0,0,32,32,SRCCOPY);
	}

	//蛇移动
	void SnackMove() {
		LastPos = s1.Body[s1.Length];
		switch (MoveSign)
		{
		case 1:
			s1.MoveUp();
			break;
		case 2:
			s1.MoveDown();
			break;
		case 3:
			s1.MoveLeft();
			break;
		case 4:
			s1.MoveRight();
			break;
		default:
			break;
		}
		Check();
		//Brush
		BrushMap();
		BrushSnack();
		BrushFruit();
	}

	//检查是否吃到果实
	void Check() {
		if (s1.Body[0] == Fruit) {
			s1.Length++;
			s1.Body[s1.Length] = LastPos;
			InitFruit(s1);
			Score++;
			IdcStatic[5]->SetWindowTextW(I2C(Score));
			BrushFruit();
		}
		if (s1.Body[0].x < 0 || s1.Body[0].x > 19 || s1.Body[0].y < 0 || s1.Body[0].y > 19) {
			KillTimer(1);
			IdcStatic[0]->SetWindowTextW(_T("重新开始"));
			GameStatus = -1;
			MessageBox(_T("游戏结束,您的得分是") + I2C(Score), _T("提示"));
		}
		for (int i = 3; i <= s1.Length; i++) {
			if (s1.Body[0] == s1.Body[i]) {
				KillTimer(1);
				IdcStatic[0]->SetWindowTextW(_T("重新开始"));
				GameStatus = -1;
				MessageBox(_T("游戏结束,您的得分是") + I2C(Score), _T("提示"));
			}
		}
	}

	//=======================================================

	// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MYSNACK_DIALOG };
#endif
protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持
// 实现
protected:
	HICON m_hIcon;
	// 生成的消息映射函数
	BOOL CMySnackDlg::PreTranslateMessage(MSG* pMsg);
	BOOL CMySnackDlg::OnEraseBkgnd(CDC* pDC);
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButton2();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnBnClickedButton1();
	afx_msg void OnCbnSelchangeCombo1();
};
