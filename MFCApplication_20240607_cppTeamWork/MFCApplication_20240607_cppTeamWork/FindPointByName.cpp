// FindPointByName.cpp: 实现文件
//

#include "pch.h"
#include "MFCApplication_20240607_cppTeamWork.h"
#include "afxdialogex.h"
#include "FindPointByName.h"
#include "MFCApplication_20240607_cppTeamWorkDoc.h"



// FindPointByName 对话框

IMPLEMENT_DYNAMIC(FindPointByName, CDialogEx)
FindPointByName::FindPointByName(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG15, pParent)
	, ptName(defaultPointName.c_str())
{

}

FindPointByName::~FindPointByName()
{
}

void FindPointByName::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, ptName);
	DDX_Control(pDX, IDC_LIST1, m_listCtrl);
}


BEGIN_MESSAGE_MAP(FindPointByName, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON1, &FindPointByName::OnBnClickedButtonFindPointByName)
END_MESSAGE_MAP()


// FindPointByName 消息处理程序


BOOL FindPointByName::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化


	/*大一下 《遥感信息处理C++基础》 P209
	列表内添加五列表头，每列宽度为列表控件的1/5*/
	CRect rc; m_listCtrl.GetClientRect(&rc);
	m_listCtrl.InsertColumn(0, _T("点的序号"), LVCFMT_LEFT);
	m_listCtrl.InsertColumn(1, _T("点的名称"), LVCFMT_LEFT);
	m_listCtrl.InsertColumn(2, _T("x坐标"), LVCFMT_LEFT);
	m_listCtrl.InsertColumn(3, _T("y坐标"), LVCFMT_LEFT);
	m_listCtrl.InsertColumn(4, _T("z坐标"), LVCFMT_LEFT);
	m_listCtrl.SetColumnWidth(0, rc.Width() / 5);
	m_listCtrl.SetColumnWidth(1, rc.Width() / 5);
	m_listCtrl.SetColumnWidth(2, rc.Width() / 5);
	m_listCtrl.SetColumnWidth(3, rc.Width() / 5);
	m_listCtrl.SetColumnWidth(4, rc.Width() / 5);
	ListView_SetExtendedListViewStyle(m_listCtrl.m_hWnd, LVS_EX_GRIDLINES);

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}

void FindPointByName::OnBnClickedButtonFindPointByName()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);
	CFrameWnd* pMainFrame = (CFrameWnd*)AfxGetMainWnd();
	CFrameWnd* pActiveFrame = pMainFrame->GetActiveFrame();
	CDocument* pActiveDocument = pActiveFrame->GetActiveDocument();
	CMFCApplication20240607cppTeamWorkDoc* pDoc = dynamic_cast<CMFCApplication20240607cppTeamWorkDoc*>(pActiveDocument);//从文档读取变量数据到对话框中

	if (pDoc == nullptr)
	{
		MessageBox(NULL, _T("发生错误：未关联文档！"), MB_OK | MB_ICONWARNING);
		return;
	}
	else
	{
		//大一下 《遥感信息处理C++基础》 BP208图10-36
		
		//先清空上一次按照点名查找的数据
		POSITION pos = m_listCtrl.GetFirstSelectedItemPosition();

		while (pos != NULL)
		{
			m_listCtrl.DeleteItem(m_listCtrl.GetNextSelectedItem(pos));
			pos = m_listCtrl.GetFirstSelectedItemPosition();
		}
		
		//再来向表格输入这次按照点名查找的数据
		string strFindName;
		strFindName = CT2A(ptName.GetBuffer());
		defaultPointName = (CStringA)ptName;
		if (!GetPt1(strFindName, pDoc->arr, pDoc->arrFind))
		{
			return;
		}

		CString str;
		int n = pDoc->arrFind.m_Num;
		int item = m_listCtrl.GetItemCount();
		/*item是插入的行号。
		GetItemCount()：这是CListCtrl类的另一个成员函数，用于获取当前列表视图中的项目数量。返回值是一个整数，表示列表中的项目总数。
		上面这一行操作往往用于向列表视图中续接式地添加新的项目。*/
		for(int i=0;i<n;i++)
		{
			m_listCtrl.InsertItem(item + i, str);

			str.Format(_T("%d"), pDoc->arrFind.m_PointArr[i].getSerialNum());
			m_listCtrl.SetItemText(item, 0, str);

			str = pDoc->arrFind.m_PointArr[i].getName().c_str();
			m_listCtrl.SetItemText(item + i, 1, str);

			str.Format(_T("%1f"), pDoc->arrFind.m_PointArr[i].getX());
			m_listCtrl.SetItemText(item + i, 2, str);

			str.Format(_T("%1f"), pDoc->arrFind.m_PointArr[i].getY());
			m_listCtrl.SetItemText(item + i, 3, str);

			str.Format(_T("%1f"), pDoc->arrFind.m_PointArr[i].getZ());
			m_listCtrl.SetItemText(item + i, 4, str);
		}
		UpdateData(FALSE);
	}
}
