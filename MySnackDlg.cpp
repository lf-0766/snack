
//MySnack.cpp
#include "pch.h"
#include "framework.h"
#include "MySnack.h"
#include "MySnackDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


CMySnackDlg::CMySnackDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_MYSNACK_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMySnackDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CMySnackDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON2, &CMySnackDlg::OnBnClickedButton2)
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_BUTTON1, &CMySnackDlg::OnBnClickedButton1)
	ON_CBN_SELCHANGE(IDC_COMBO1, &CMySnackDlg::OnCbnSelchangeCombo1)
END_MESSAGE_MAP()


// CMySnackDlg 消息处理程序

BOOL CMySnackDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码
	pdc = GetDC();
	StaticFont[0].CreatePointFont(150, _T("华文中宋"), NULL);
	StaticFont[1].CreatePointFont(100, _T("新宋体"), NULL);
	StaticFont[2].CreatePointFont(200, _T("华文中宋"), NULL);
	//CStatic* p;   //p->GetDlgItem(Main)
	//GetDlgItem(Main)->GetClientRect(&MapRect);
	//GetDlgItem(Main)->MoveWindow(10, 10, 410, 410);
	GetDlgItem(Main)->MoveWindow(20, 20, 600, 600, false);
	(this->GetDlgItem(Main))->GetWindowRect(&MapRect);
	ScreenToClient(MapRect);
	int TitleHeight = GetSystemMetrics(SM_CYCAPTION);	//标题栏高度
	//获取按钮尺寸
	CRect ButtonRect;

	IdcStatic[0] = (CStatic*)GetDlgItem(IDC_BUTTON2);
	IdcStatic[1] = (CStatic*)GetDlgItem(IDC_BUTTON1);
	IdcStatic[2] = (CStatic*)GetDlgItem(IDC_STATIC4);
	IdcStatic[3] = (CStatic*)GetDlgItem(IDC_COMBO1);
	IdcStatic[4] = (CStatic*)GetDlgItem(IDC_STATIC2);
	IdcStatic[5] = (CStatic*)GetDlgItem(IDC_STATIC3);

	IdcStatic[0]->GetWindowRect(&ButtonRect);
	IdcStatic[0]->MoveWindow(MapRect.right + (ButtonRect.right - ButtonRect.left) / 2, MapRect.top + (ButtonRect.bottom - ButtonRect.top) / 2, ButtonRect.right - ButtonRect.left, ButtonRect.bottom - ButtonRect.top, false);
	IdcStatic[1]->MoveWindow(MapRect.right + (ButtonRect.right - ButtonRect.left) / 2, MapRect.top + (ButtonRect.bottom - ButtonRect.top) * 2 / 2 + (ButtonRect.bottom - ButtonRect.top), ButtonRect.right - ButtonRect.left, ButtonRect.bottom - ButtonRect.top, false);

	CRect Static1;
	IdcStatic[2]->GetWindowRect(Static1);
	IdcStatic[2]->MoveWindow(MapRect.right + (ButtonRect.right - ButtonRect.left) / 2, MapRect.top + (ButtonRect.bottom - ButtonRect.top) * 4 / 2 + (ButtonRect.bottom - ButtonRect.top) * 2, Static1.right - Static1.left, Static1.bottom - Static1.top);


	CRect Static2;
	IdcStatic[3]->GetWindowRect(Static2);
	IdcStatic[3]->MoveWindow(MapRect.right + 3 * (Static1.right - Static1.left) / 2 + (ButtonRect.right - ButtonRect.left) / 2, MapRect.top + (ButtonRect.bottom - ButtonRect.top) * 4 / 2 + (ButtonRect.bottom - ButtonRect.top) * 2, Static2.right - Static2.left, Static2.bottom - Static2.top);
	//IdcStatic[3]->SetDlgItemTextW(1, L"1");
	CComboBoxEx* comboboxCtr = (CComboBoxEx*)GetDlgItem(IDC_COMBO1);
	comboboxCtr->SetCurSel(0);

	IdcStatic[4]->MoveWindow(MapRect.right + (ButtonRect.right - ButtonRect.left) / 2, MapRect.top + (ButtonRect.bottom - ButtonRect.top) * 4 / 2 + (ButtonRect.bottom - ButtonRect.top) * 5, ButtonRect.right - ButtonRect.left, ButtonRect.bottom - ButtonRect.top, false);

	IdcStatic[5]->MoveWindow(MapRect.right + (ButtonRect.right - ButtonRect.left) * 2 / 2, MapRect.top + (ButtonRect.bottom - ButtonRect.top) * 5 / 2 + (ButtonRect.bottom - ButtonRect.top) * 6, ButtonRect.right - ButtonRect.left, ButtonRect.bottom - ButtonRect.top, false);
	IdcStatic[5]->SetWindowTextW(L"0");

	MoveWindow(0, 0, MapRect.right + MapRect.left + 20 + 2 * (ButtonRect.right - ButtonRect.left), MapRect.bottom + MapRect.top + TitleHeight + 20, false);

	IdcStatic[0]->SetFont(&StaticFont[0]);
	IdcStatic[1]->SetFont(&StaticFont[0]);
	IdcStatic[2]->SetFont(&StaticFont[1]);
	IdcStatic[4]->SetFont(&StaticFont[2]);
	IdcStatic[5]->SetFont(&StaticFont[2]);

	CString a;
	IdcStatic[3]->GetWindowTextW(a);
	C2I(Speed, a);
	//GetDlgItem(IDC_BUTTON2)->MoveWindow(MapRect.right,)
	OnInit();
	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CMySnackDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	//if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	//{
	//	CAboutDlg dlgAbout;
	//	dlgAbout.DoModal();
	//}
	//else
	//{
	CDialogEx::OnSysCommand(nID, lParam);
	//}
}

void CMySnackDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
	Paint();
}

HCURSOR CMySnackDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

//捕获按键
BOOL CMySnackDlg::PreTranslateMessage(MSG* pMsg) {
	if (pMsg->message == WM_KEYDOWN)
		if (GameStatus == 1 || pMsg->wParam == ' ')
		{
			switch (pMsg->wParam) {
			case VK_RETURN:				// 屏蔽回车
				return TRUE;
			case VK_UP:
			case 'W':
			case 'w':
				if(MoveSign != 2)
				MoveSign = 1;
				return TRUE;
				break;
			case VK_DOWN:
			case 'S':
			case's':
				if (MoveSign != 1)
					MoveSign = 2;
				return TRUE;
				break;
			case VK_LEFT:
			case 'A':
			case 'a':
				if(MoveSign != 4)
				MoveSign = 3;
				return TRUE;
				break;
			case VK_RIGHT:
			case 'D':
			case 'd':
				if(MoveSign != 3)
				MoveSign = 4;
				return TRUE;
				break;
			default:
				break;
			}
		}else if (GameStatus == -1) {
		MessageBox(_T("请重新开始游戏！"), _T("提示"));
	}
	return CDialogEx::PreTranslateMessage(pMsg);
}

BOOL CMySnackDlg::OnEraseBkgnd(CDC* pDC)
{
	return TRUE;
	//return CView::OnEraseBkgnd(pDC);
}

//开始游戏
void CMySnackDlg::OnBnClickedButton2()
{
	// TODO: 在此添加控件通知处理程序代码
	switch (GameStatus)
	{
	case 0:
		IdcStatic[0]->SetWindowTextW(_T("暂停"));
		GameStatus = 1;
		SetTimer(1, 500 / Speed, NULL);
		break;
	case 1:
		IdcStatic[0]->SetWindowTextW(_T("继续"));
		GameStatus = 0;
		KillTimer(1);
		break;
	case -1:
		IdcStatic[0]->SetWindowTextW(_T("暂停"));
		InitMap(20, 20, 30, 20, 20); //Width,Height,Size,MarginTop,MarginLeft
		//初始化蛇
		InitSnack(3);
		// 初始化果实
		InitFruit(s1);
		InitGameStatus();
		GameStatus = 1;
		IdcStatic[5]->SetWindowTextW(I2C(Score));
		Paint();
		SetTimer(1, 500 / Speed, NULL);
		break;
	default:
		break;
	}
}


void CMySnackDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	SnackMove();
	CDialogEx::OnTimer(nIDEvent);
}

//重置按钮
void CMySnackDlg::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码
	//初始化地图
	InitMap(20, 20, 30, 20, 20); //Width,Height,Size,MarginTop,MarginLeft
	//初始化蛇
	InitSnack(3);
	// 初始化果实
	InitFruit(s1);
	InitGameStatus();
	Paint();
	IdcStatic[0]->SetWindowTextW(_T("开始游戏"));
	IdcStatic[5]->SetWindowTextW(I2C(Score));
}

//选择速度
void CMySnackDlg::OnCbnSelchangeCombo1()
{
	// TODO: 在此添加控件通知处理程序代码
	if (GameStatus) {
		KillTimer(1);
		CString Temp;
		IdcStatic[3]->GetWindowTextW(Temp);
		C2I(Speed, Temp);
		SetTimer(1, 500 / Speed, NULL);
	}
	else {
		CString Temp;
		IdcStatic[3]->GetWindowTextW(Temp);
		C2I(Speed, Temp);
	}
}

