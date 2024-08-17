#pragma once
#include "afxdialogex.h"


// UseMySQLDlg 对话框

class UseMySQLDlg : public CDialogEx
{
	DECLARE_DYNAMIC(UseMySQLDlg)

public:
	UseMySQLDlg(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~UseMySQLDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG27 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButtonMySQLToArr();

	MySQLInterface SQL;
	virtual BOOL OnInitDialog();
	// 在对接MySQL数据库中使用到的ListCtrl变量
	CListCtrl CUseMySQLListCtrl;
	afx_msg void OnBnClickedButtonAddToMySQL();
	void UpdateCControlList();
	afx_msg void OnBnClickedButtonFileToMySQL();
	afx_msg void OnBnClickedButtonDelInMySQL();
	afx_msg void OnBnClickedButtonUpdateInMySQL();
	afx_msg void OnBnClickedButtonFindPointInMySQL();

	// 选择排序规则的下拉框
	CComboBox m_CComboBoxSort;
	// 用户选择的对数据库中的数据的排序顺序
	CComboBox m_CComboBoxSortOrder;

	afx_msg void OnBnClickedButtonAnalyze();
	afx_msg void OnBnClickedButtonSort();

};
