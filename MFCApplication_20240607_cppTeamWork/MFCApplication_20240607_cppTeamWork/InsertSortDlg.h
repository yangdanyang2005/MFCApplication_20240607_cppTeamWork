#pragma once
#include "afxdialogex.h"


// InsertSortDlg 对话框

class InsertSortDlg : public CDialogEx
{
	DECLARE_DYNAMIC(InsertSortDlg)

public:
	InsertSortDlg(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~InsertSortDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG4 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	// 用户选择下拉菜单中给x,y,z中的一个做排序
	int m_nChooseSort;
	afx_msg void OnCbnSelchangeCombo1();
};
