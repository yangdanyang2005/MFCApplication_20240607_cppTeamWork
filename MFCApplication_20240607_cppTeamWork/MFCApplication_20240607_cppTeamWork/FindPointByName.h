#pragma once
#include "afxdialogex.h"
#include "MFCApplication_20240607_cppTeamWorkDoc.h"

// FindPointByName 对话框

class FindPointByName : public CDialogEx
{
	DECLARE_DYNAMIC(FindPointByName)

public:
	FindPointByName(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~FindPointByName();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG15 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	// 用户输入的点的名称，用于查找点
	CString ptName;
	// 显示按照点名查找到的高程点数据
	CListCtrl m_listCtrl;
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedButtonFindPointByName();
	//按照点名进行查找的函数
	bool GetPt1(string ptName, PointArr arr, PointArr& arrFind)//一定要引用传入
	{
		//输入点名进行查找
		int i = 0;
		int j = 0;
		int count = 0;
		int arrNum[1024];
		for (i = 0; i < arr.m_Num; i++)
		{
			if (ptName == arr.m_PointArr[i].getName())
			{
				count++;
				arrNum[j] = i; j++;
			}
		}
		arrFind.m_Num = count;
		if (count == 0)
		{
			AfxMessageBox(_T("没有查找到符合查找条件的点！"));
			return false;
		}
		arrFind.m_PointArr = new Point[count];//一定要分配内存
		for (j = 0; j < count; j++)
		{
			arrFind.m_PointArr[j] = arr.m_PointArr[arrNum[j]];
		}
		return true;
	}

};
