#pragma once
#include "afxdialogex.h"


// MultiKeywordSortDlg 对话框

class MultiKeywordSortDlg : public CDialogEx
{
	DECLARE_DYNAMIC(MultiKeywordSortDlg)

public:
	MultiKeywordSortDlg(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~MultiKeywordSortDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG24 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	// 用户输入的字符串，用于表示用户想要的排序规则
	CString WantedSortRule;
	afx_msg void OnBnClickedButtonMultiKeywordSort();
	// 多关键字排序输出的排序结果
	CListCtrl MultiKeywordSortOutcome;
	virtual BOOL OnInitDialog();
};
