#pragma once
#include "afxdialogex.h"


// deldlg 对话框

class deldlg : public CDialogEx
{
	DECLARE_DYNAMIC(deldlg)

public:
	deldlg(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~deldlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG13 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CString name;
};
