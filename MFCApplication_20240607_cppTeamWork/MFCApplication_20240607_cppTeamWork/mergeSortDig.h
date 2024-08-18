#pragma once
#include "afxdialogex.h"


// mergeSortDig 对话框

class mergeSortDig : public CDialogEx
{
	DECLARE_DYNAMIC(mergeSortDig)

public:
	mergeSortDig(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~mergeSortDig();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG11 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	int m_nChooseSort;
	afx_msg void OnCbnSelchangeCombo1();
};
