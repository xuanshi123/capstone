
// MFCApplication4Dlg.h : ͷ�ļ�
//

#pragma once
#include "resource.h"		// ������

// CMFCApplication4Dlg �Ի���
class CMFCApplication4Dlg : public CDialogEx
{
// ����
public:
	CMFCApplication4Dlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_MFCAPPLICATION4_DIALOG };

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
	afx_msg void OnBnClickedOpen();
	afx_msg void OnEnChangeEdit5();
	CString headline;
	
	afx_msg void OnBnClickedUPDATE();
	int maxx;
	int minx;
	int maxy;
	int miny;
	int ct;
	double multiratio;
	double concentration;
	int maxarea;
	afx_msg void OnDeltaposSpin1(NMHDR *pNMHDR, LRESULT *pResult);
	int minarea;
	afx_msg void OnDeltaposSpin2(NMHDR *pNMHDR, LRESULT *pResult);
	int m_radiogroup1;
	afx_msg void OnBnClickedRadio1();
	afx_msg void OnEnChangeEdit11();
	int number;
	afx_msg void OnBnClickedlog();
};
