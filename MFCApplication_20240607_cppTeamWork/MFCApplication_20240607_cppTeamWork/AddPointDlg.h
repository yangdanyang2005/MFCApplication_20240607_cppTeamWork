#pragma once
#include "afxdialogex.h"


// AddPointDlg 对话框

class AddPointDlg : public CDialogEx
{
	DECLARE_DYNAMIC(AddPointDlg)

public:
	AddPointDlg(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~AddPointDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG2 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	// 用户在“添加点坐标”对话框中输入的点名
	CString name;
	// 用户在“添加点坐标”对话框中输入的x坐标
	double x;
	// 用户在“添加点坐标”对话框中输入的y坐标
	double y;
	// 用户在“添加点坐标”对话框中输入的z坐标
	double z;
	afx_msg void OnEnChangeEdit1();
};
