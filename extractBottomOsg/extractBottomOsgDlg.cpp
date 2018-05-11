
// extractBottomOsgDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "extractBottomOsg.h"
#include "extractBottomOsgDlg.h"
#include "afxdialogex.h"
#include "osgDB/WriteFile"
#include "OsgStateDynamicSetter.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#endif
using namespace std;

// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CextractBottomOsgDlg 对话框



CextractBottomOsgDlg::CextractBottomOsgDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CextractBottomOsgDlg::IDD, pParent)
	, mPath(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CextractBottomOsgDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, mPath);
}

BEGIN_MESSAGE_MAP(CextractBottomOsgDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, &CextractBottomOsgDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDOK, &CextractBottomOsgDlg::OnBnClickedOk)
END_MESSAGE_MAP()


// CextractBottomOsgDlg 消息处理程序

BOOL CextractBottomOsgDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
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

	// TODO:  在此添加额外的初始化代码

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CextractBottomOsgDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CextractBottomOsgDlg::OnPaint()
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
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CextractBottomOsgDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CextractBottomOsgDlg::OnBnClickedButton1()
{
	// TODO:  在此添加控件通知处理程序代码
	CFileDialog dlg(FALSE, NULL, NULL, OFN_HIDEREADONLY, _T("osgb (*.osgb)|*.osgb|osg (*.osg)|*.osg|所有文件 (*.*)|*.*||"), NULL);
	if (dlg.DoModal() == IDOK)
		mPath = dlg.GetPathName();
	else
		mPath = _T("");
	UpdateData(FALSE);
}


void CextractBottomOsgDlg::OnBnClickedOk()
{
	// TODO:  在此添加控件通知处理程序代码
	USES_CONVERSION;
	
	//CDialogEx::OnOK();
	if (mPath.IsEmpty())
	{
		return;
	}
	string s = W2A(mPath);
	int pos = s.find_last_of(".");
	string outFilePath = s.substr(0,pos);
	int pos1 = s.find_last_of("\\");

	osg::ref_ptr<osg::Node> mainNode = osgDB::readNodeFile(s);
	findTexture(mainNode,s.substr(0,pos1+1));
	vector<string> vecFileName;
	findBottomFile(mainNode, vecFileName);
	osg::ref_ptr<osg::Node> group = osgDB::readNodeFiles(vecFileName);
	
	osg::ref_ptr<osgDB::Options> spOptions = new osgDB::Options;
	spOptions->setPluginStringData("WriteImageHint", "IncludeFile");
	osgDB::writeNodeFile(*group,outFilePath + ".obj",spOptions.get());
	osgDB::writeNodeFile(*group, outFilePath + "_bottom.osgb", spOptions.get());
	MessageBox(_T("完成"));
}

void CextractBottomOsgDlg::findBottomFile(osg::ref_ptr<osg::Node> node, vector<string> &VecBotFile)
{
	COsgPagedLodBottomLevelFinder ive(&VecBotFile);
	node->accept(ive);

	return;
}

void CextractBottomOsgDlg::findTexture(osg::ref_ptr<osg::Node> node,std::string dir)
{
	COsgStateDynamicSetter sds(dir);
	node->accept(sds);

	return;
}