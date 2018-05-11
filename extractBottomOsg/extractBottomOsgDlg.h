
// extractBottomOsgDlg.h : ͷ�ļ�
//

#pragma once
#include <string>
#include "traval.h"
#include "osg\Node"
#include <vector>
using namespace std;
// CextractBottomOsgDlg �Ի���
class CextractBottomOsgDlg : public CDialogEx
{
// ����
public:
	CextractBottomOsgDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_EXTRACTBOTTOMOSG_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
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
