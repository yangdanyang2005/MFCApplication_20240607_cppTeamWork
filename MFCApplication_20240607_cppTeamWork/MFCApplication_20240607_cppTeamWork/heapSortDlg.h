#pragma once
#include "afxdialogex.h"


// heapSortDlg 对话框

class heapSortDlg : public CDialogEx
{
	DECLARE_DYNAMIC(heapSortDlg)

public:
	heapSortDlg(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~heapSortDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG8 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	int m_nChooseSort;
	afx_msg void OnCbnSelchangeCombo1();
};
