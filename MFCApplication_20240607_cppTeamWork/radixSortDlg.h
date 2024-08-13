#pragma once
#include "afxdialogex.h"


// radixSortDlg 对话框

class radixSortDlg : public CDialogEx
{
	DECLARE_DYNAMIC(radixSortDlg)

public:
	radixSortDlg(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~radixSortDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG12 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	int m_nChooseSort;
	afx_msg void OnCbnSelchangeCombo1();
};
