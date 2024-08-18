#pragma once
#include "afxdialogex.h"


// chaDlg 对话框

class chaDlg : public CDialogEx
{
	DECLARE_DYNAMIC(chaDlg)

public:
	chaDlg(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~chaDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG14 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CString name1;
	CString name2;
	double x;
	double y;
	double z;
};
