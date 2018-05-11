
// extractBottomOsgDlg.h : 头文件
//

#pragma once
#include <string>
#include "traval.h"
#include "osg\Node"
#include <vector>
using namespace std;
// CextractBottomOsgDlg 对话框
class CextractBottomOsgDlg : public CDialogEx
{
// 构造
public:
	CextractBottomOsgDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_EXTRACTBOTTOMOSG_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButton1();
	CString mPath;
	afx_msg void OnBnClickedOk();
	void findBottomFile(osg::ref_ptr<osg::Node> node, vector<string> &VecBotFile);
	void findTexture(osg::ref_ptr<osg::Node> node,  std::string dir);
};
