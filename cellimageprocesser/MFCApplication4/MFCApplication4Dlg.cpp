
// MFCApplication4Dlg.cpp : 实现文件
//

#include "stdafx.h"
#include "MFCApplication4.h"
#include "MFCApplication4Dlg.h"
#include "afxdialogex.h"
#include <opencv2/opencv.hpp>  
#include <iostream>
#include <time.h> 
#include <string.h> 
#include <opencv2\core\core.hpp>
#include <opencv2\highgui\highgui.hpp>
#include <opencv2\core\core.hpp>
#include <opencv2\highgui\highgui.hpp>

using namespace std;
using namespace cv;
int min_area;
#ifdef _DEBUG
#define new DEBUG_NEW
#endif

IplImage *g_pGrayImage = NULL;
int maxthe;


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

void on_trackbar(int, void*)
{
	pl1->minarea = min_area;
	pl1->UpdateData(FALSE);
}

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


// CMFCApplication4Dlg 对话框


CMFCApplication4Dlg::CMFCApplication4Dlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CMFCApplication4Dlg::IDD, pParent)
	, headline(_T(""))
	, maxx(0)
	, minx(0)
	, maxy(0)
	, miny(0)
	, ct(0)
	, multiratio(0)
	, concentration(0)
	, maxarea(0)
	, minarea(0)
	, m_radiogroup1(0)
	, number(0)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMFCApplication4Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT5, headline);
	DDX_Text(pDX, IDC_EDIT1, maxx);
	DDV_MinMaxInt(pDX, maxx, 0, 1280);
	DDX_Text(pDX, IDC_EDIT2, minx);
	DDV_MinMaxInt(pDX, minx, 0, 1280);
	DDX_Text(pDX, IDC_EDIT3, maxy);
	DDV_MinMaxInt(pDX, maxy, 0, 720);
	DDX_Text(pDX, IDC_EDIT4, miny);
	DDV_MinMaxInt(pDX, miny, 0, 720);
	DDX_Text(pDX, IDC_EDIT6, ct);
	DDX_Text(pDX, IDC_EDIT8, multiratio);
	DDX_Text(pDX, IDC_EDIT7, concentration);
	DDX_Text(pDX, IDC_EDIT9, maxarea);
	DDV_MinMaxInt(pDX, maxarea, 0, 930000);
	DDX_Text(pDX, IDC_EDIT10, minarea);
	DDV_MinMaxInt(pDX, minarea, 0, 930000);
	DDX_Radio(pDX, IDC_RADIO1, m_radiogroup1);
	DDX_Text(pDX, IDC_EDIT11, number);
	DDV_MinMaxInt(pDX, number, 0, 719);
}

BEGIN_MESSAGE_MAP(CMFCApplication4Dlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, &CMFCApplication4Dlg::OnBnClickedOpen)
	ON_EN_CHANGE(IDC_EDIT5, &CMFCApplication4Dlg::OnEnChangeEdit5)
	ON_BN_CLICKED(IDOK, &CMFCApplication4Dlg::OnBnClickedUPDATE)
	ON_BN_CLICKED(IDC_BUTTON2, &CMFCApplication4Dlg::OnBnClickedUPDATE)
	ON_NOTIFY(UDN_DELTAPOS, IDC_SPIN1, &CMFCApplication4Dlg::OnDeltaposSpin1)
	ON_NOTIFY(UDN_DELTAPOS, IDC_SPIN2, &CMFCApplication4Dlg::OnDeltaposSpin2)
	ON_BN_CLICKED(IDC_RADIO1, &CMFCApplication4Dlg::OnBnClickedRadio1)
	ON_BN_CLICKED(IDC_RADIO2, &CMFCApplication4Dlg::OnBnClickedRadio1)
	ON_EN_CHANGE(IDC_EDIT11, &CMFCApplication4Dlg::OnEnChangeEdit11)
	ON_BN_CLICKED(IDC_BUTTON3, &CMFCApplication4Dlg::OnBnClickedlog)
END_MESSAGE_MAP()


// CMFCApplication4Dlg 消息处理程序

BOOL CMFCApplication4Dlg::OnInitDialog()
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
	maxx=960;
	minx=320;
	maxy=620;
	miny=100;
	multiratio = 0.2;
	maxarea = 930000;
	cvNamedWindow("binary", CV_WINDOW_AUTOSIZE);
	cvNamedWindow("contours", CV_WINDOW_AUTOSIZE);
	createTrackbar("Max thresh", "binary", &maxthe, 254, NULL);
	cvSetTrackbarPos("Max thresh", "binary", 0);
	createTrackbar("Min area", "contours", &min_area, 150, on_trackbar);
	cvSetTrackbarPos("Min area", "contours", 0);

	UpdateData(FALSE);
	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CMFCApplication4Dlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CMFCApplication4Dlg::OnPaint()
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
HCURSOR CMFCApplication4Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CMFCApplication4Dlg::OnBnClickedOpen()
{
	UpdateData(TRUE);
//TODO: Add your command handler code here 
	LPCTSTR lpszFilter = _T("JPGFiles(*.jpg)|*.jpg|All Files(*.*)|*.*||");
	CFileDialog dlg(TRUE, lpszFilter, NULL, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT| OFN_NOCHANGEDIR, lpszFilter, NULL);
	CString filepath;  CFile file;     //打开文件对话框  
	dlg.m_ofn.lpstrInitialDir = _T(".");
	if (dlg.DoModal() == IDOK)
	{
		filepath = dlg.GetPathName();
		IplImage *pSrcImage = cvLoadImage(CT2CA(filepath), CV_LOAD_IMAGE_UNCHANGED);
		FILE *out=fopen("1213.txt", "w");
		headline = filepath;
		cvNamedWindow("original", CV_WINDOW_AUTOSIZE);
		cvShowImage("original", pSrcImage);
		if (g_pGrayImage!=NULL)
		   cvReleaseImage(&g_pGrayImage);
		g_pGrayImage = cvCreateImage(cvGetSize(pSrcImage), IPL_DEPTH_8U, 1);
		cvCvtColor(pSrcImage, g_pGrayImage, CV_BGR2GRAY);
		

	}


	UpdateData(FALSE);
}


void CMFCApplication4Dlg::OnEnChangeEdit5()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
}



void CMFCApplication4Dlg::OnBnClickedUPDATE()
{
	// TODO:  在此添加控件通知处理程序代码
	 
	 UpdateData(TRUE);
	 ct = 0;
     	Mat image;
		IplImage *pBinaryImage = cvCreateImage(cvGetSize(g_pGrayImage), IPL_DEPTH_8U, 1);
		if(m_radiogroup1==0)
			cvThreshold(g_pGrayImage, pBinaryImage, maxthe, 255, CV_THRESH_BINARY);
		else
		{
			if (number >= 3)
			{
				int thresh = number % 2 - 1 + number;
				cvAdaptiveThreshold(g_pGrayImage, pBinaryImage, 255, CV_ADAPTIVE_THRESH_MEAN_C, CV_THRESH_BINARY, thresh, maxthe);
			}
		}
		// 显示二值图  
		cvShowImage("binary", pBinaryImage);


		image = Mat(pBinaryImage, true);
		cvReleaseImage(&pBinaryImage);

	
	// Get the contours of the connected components
	vector<vector<Point>> contours;
	findContours(image,
		contours, // a vector of contours 
		CV_RETR_EXTERNAL, // retrieve the external contours
		CV_CHAIN_APPROX_SIMPLE); // retrieve all pixels of each contours



	Mat result(image.size(), CV_8UC3, Scalar(255, 255, 255));

	std::vector<std::vector<cv::Point>>::const_iterator itc = contours.begin();
	while (itc != contours.end()) {
		double tmparea = fabs(contourArea(*itc));

		if (tmparea < minarea || tmparea>maxarea)
		{
			//删除面积小于设定值的轮廓  
			itc = contours.erase(itc);
			//cout << "delete a small area" << std::endl;
			continue;
		}


		//计算轮廓的直径宽高  

		RotatedRect rRect = minAreaRect(*itc);
		if (rRect.center.x >= minx&&rRect.center.x <= maxx&&rRect.center.y <= maxy&&rRect.center.y >= miny)

		{
			ct++;
			Point2f vertices[4];
			rRect.points(vertices);

			for (int i = 0; i < 4; i++)
				line(result, vertices[i], vertices[(i + 1) % 4], Scalar(0, 0, 255), 2);


		}
		++itc;
	}


	/// Draw contours


	drawContours(result, contours,
		-1, // draw all contours
		Scalar(255, 0, 0), // in black
		1);
	// Create Window  
	if (minarea<=150)
		cvSetTrackbarPos("Min area", "contours", minarea);
	imshow("contours", result);
	concentration = multiratio*ct;
	UpdateData(FALSE);
	
}


void CMFCApplication4Dlg::OnDeltaposSpin1(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMUPDOWN pNMUpDown = reinterpret_cast<LPNMUPDOWN>(pNMHDR);
	// TODO:  在此添加控件通知处理程序代码
	if (pNMUpDown->iDelta == 1) // 如果此值为1 , 说明点击了Spin的往下箭头 
	{
		maxarea--; //增加编辑框中的数字值 
	}
	else if (pNMUpDown->iDelta == -1) // 如果此值为-1 , 说明点击了Spin的往上箭头 
	{
		maxarea++;
	}
	UpdateData(FALSE);
	*pResult = 0;
}


void CMFCApplication4Dlg::OnDeltaposSpin2(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMUPDOWN pNMUpDown = reinterpret_cast<LPNMUPDOWN>(pNMHDR);
	// TODO:  在此添加控件通知处理程序代码
	if (pNMUpDown->iDelta == 1) // 如果此值为1 , 说明点击了Spin的往下箭头 
	{
		minarea--; //增加编辑框中的数字值 
	}
	else if (pNMUpDown->iDelta == -1) // 如果此值为-1 , 说明点击了Spin的往上箭头 
	{
		minarea++;
	}
	UpdateData(FALSE);
	*pResult = 0;
}


void CMFCApplication4Dlg::OnBnClickedRadio1()
{
	// TODO:  在此添加控件通知处理程序代码
}




void CMFCApplication4Dlg::OnBnClickedlog()
{
	char x[100][100];
	int y[100];
	double z[100];
	int j, n = 0;
	FILE *fp;
	int flag = 1;
	fp = fopen("log.csv", "r");
	while (1){
		fscanf(fp, "%[^\n],%d,%lf",x[n], &y[n], &z[n]);
		if (feof(fp))break;
		if (strcmp(x[n], CT2CA(headline)) == 0)
		{   
			y[n] = ct;
			z[n] = concentration;
			flag = 0;
		}
		n++;
	}
	fclose(fp);
	fp = fopen("log.csv", "w");
	for (j = 0; j<n; j++){
		
		fprintf(fp, "%s,%d,%lf\n",x[n],y[n],z[n]);
	}
	if (flag)
	{ 
		fprintf(fp, "%s,%d,%lf\n", CT2CA(headline), ct, concentration);
	}
}
