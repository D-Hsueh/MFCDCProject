
// MFCDCProgectDlg.h : ͷ�ļ�
//

#pragma once
#include "ProjectCreat.h"


// CMFCDCProgectDlg �Ի���
class CMFCDCProgectDlg : public CDialogEx
{
// ����
public:
	CMFCDCProgectDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MFCDCPROGECT_DIALOG };
#endif

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
	int Maze_Length;
	int Maze_Width;
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton2();
	MazeProject *m;
};
