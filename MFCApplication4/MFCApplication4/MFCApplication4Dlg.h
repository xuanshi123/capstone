
// MFCApplication4Dlg.h : 头文件
//

#pragma once
#include "resource.h"		// 主符号

// CMFCApplication4Dlg 对话框
class CMFCApplication4Dlg : public CDialogEx
{
// 构造
public:
	CMFCApplication4Dlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_MFCAPPLICATION4_DIALOG };

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
