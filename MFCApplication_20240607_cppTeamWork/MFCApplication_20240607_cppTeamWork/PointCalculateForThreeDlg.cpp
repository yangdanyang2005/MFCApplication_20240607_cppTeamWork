// PointCalculateForThreeDlg.cpp: 实现文件
//
#include "pch.h"
#include "MFCApplication_20240607_cppTeamWork.h"
#include "afxdialogex.h"
#include "PointCalculateForThreeDlg.h"
#include "MFCApplication_20240607_cppTeamWorkDoc.h"

// PointCalculateForThreeDlg 对话框

IMPLEMENT_DYNAMIC(PointCalculateForThreeDlg, CDialogEx)

PointCalculateForThreeDlg::PointCalculateForThreeDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG18, pParent)
	, vertexName(_T(""))
	, vertexX(0)
	, vertexY(0)
	, vertexZ(0)
	, aName(_T(""))
	, aX(0)
	, aY(0)
	, aZ(0)
	, bName(_T(""))
	, bX(0)
	, bY(0)
	, bZ(0)
	, angDlg(0)
	, angDlgDegree(0)
	, angDlgMinute(0)
	, angDlgSecond(0)
	, prjangDlg(0)
	, prjangDlgDegree(0)
	, prjangDlgMinute(0)
	, angprjDlgSecond(0)
{

}

PointCalculateForThreeDlg::~PointCalculateForThreeDlg()
{
}

void PointCalculateForThreeDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, vertexName);
	DDX_Text(pDX, IDC_EDIT2, vertexX);
	DDX_Text(pDX, IDC_EDIT3, vertexY);
	DDX_Text(pDX, IDC_EDIT4, vertexZ);
	DDX_Text(pDX, IDC_EDIT5, aName);
	DDX_Text(pDX, IDC_EDIT6, aX);
	DDX_Text(pDX, IDC_EDIT7, aY);
	DDX_Text(pDX, IDC_EDIT8, aZ);
	DDX_Text(pDX, IDC_EDIT9, bName);
	DDX_Text(pDX, IDC_EDIT10, bX);
	DDX_Text(pDX, IDC_EDIT11, bY);
	DDX_Text(pDX, IDC_EDIT12, bZ);
	DDX_Text(pDX, IDC_EDIT14, angDlg);
	DDX_Text(pDX, IDC_EDIT16, angDlgDegree);
	DDX_Text(pDX, IDC_EDIT19, angDlgMinute);
	DDX_Text(pDX, IDC_EDIT17, angDlgSecond);
	DDX_Text(pDX, IDC_EDIT13, prjangDlg);
	DDX_Text(pDX, IDC_EDIT22, prjangDlgDegree);
	DDX_Text(pDX, IDC_EDIT21, prjangDlgMinute);
	DDX_Text(pDX, IDC_EDIT20, angprjDlgSecond);
}


BEGIN_MESSAGE_MAP(PointCalculateForThreeDlg, CDialogEx)
	ON_EN_CHANGE(IDC_EDIT8, &PointCalculateForThreeDlg::OnEnChangeEdit8)
	ON_EN_CHANGE(IDC_EDIT10, &PointCalculateForThreeDlg::OnEnChangeEdit10)
	ON_BN_CLICKED(IDC_BUTTON1, &PointCalculateForThreeDlg::OnBnClickedButtonCalculateForThree)
	ON_BN_CLICKED(IDOK, &PointCalculateForThreeDlg::OnBnClickedOk)
END_MESSAGE_MAP()


// PointCalculateForThreeDlg 消息处理程序


void PointCalculateForThreeDlg::OnEnChangeEdit8()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
}


void PointCalculateForThreeDlg::OnEnChangeEdit10()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
}


void PointCalculateForThreeDlg::OnBnClickedButtonCalculateForThree()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);
	//if (isFindFail)
	//{
	//	return;
	//}
	CFrameWnd* pMainFrame = (CFrameWnd*)AfxGetMainWnd();
	CFrameWnd* pActiveFrame = pMainFrame->GetActiveFrame();
	CDocument* pActiveDocument = pActiveFrame->GetActiveDocument();
	CMFCApplication20240607cppTeamWorkDoc* pDoc = dynamic_cast<CMFCApplication20240607cppTeamWorkDoc*>(pActiveDocument);//从文档读取变量数据到对话框中
	if (pDoc != nullptr)
	{
		Point vertex, a, b;
		int i = 0; bool isFind = false;
		if (vertexName == "" && vertexX != 0 && vertexY != 0 && vertexZ != 0)
		{
			vertex.setX(vertexX); vertex.setY(vertexY); vertex.setZ(vertexZ);
		}
		else if (vertexName != "" && vertexX == 0 && vertexY == 0 && vertexZ == 0)
		{
			for (i = 0; i < pDoc->arr.m_Num; i++)
			{
				if (vertexName == pDoc->arr.m_PointArr[i].getName().c_str())
				{
					vertex = pDoc->arr.m_PointArr[i];
					isFind = true;
					break;
				}
			}
			if (!isFind)
			{
				CString strVertex;
				strVertex.Format(_T("没有查找到您输入的点名对应的点“%s”！"), vertexName);
				if (isAfxMessageBoxOn)
				{
					AfxMessageBox(strVertex);
				}
				isAfxMessageBoxOn=false;
				return;
			}
		}
		else
		{
			AfxMessageBox(_T("请按照要求输入顶点数据！")); return;
		}

		if (aName == "" && aX != 0 && aY != 0 && aZ != 0)
		{
			a.setX(aX); a.setY(aY); a.setZ(aZ);
		}
		else if (aName != "" && aX == 0 && aY == 0 && aZ == 0)
		{
			for (i = 0; i < pDoc->arr.m_Num; i++)
			{
				if (aName == pDoc->arr.m_PointArr[i].getName().c_str())
				{
					a = pDoc->arr.m_PointArr[i];
					isFind = true;
					break;
				}
			}
			if (!isFind)
			{
				CString strA;
				strA.Format(_T("没有查找到您输入的点名对应的点“%s”！"), aName);
				if (isAfxMessageBoxOn)
				{
					AfxMessageBox(strA);
				}
				isAfxMessageBoxOn = false;
				isFind = true;
				return;
			}
		}
		else
		{
			AfxMessageBox(_T("请按照要求输入角的第一条边上的点的数据！")); return;
		}

		if (bName == "" && bX != 0 && bY != 0 && bZ != 0)
		{
			b.setX(bX); b.setY(bY); b.setZ(bZ);
		}
		else if (bName != "" && bX == 0 && bY == 0 && bZ == 0)
		{
			for (i = 0; i < pDoc->arr.m_Num; i++)
			{
				if (bName == pDoc->arr.m_PointArr[i].getName().c_str())
				{
					b = pDoc->arr.m_PointArr[i];
					isFind = true;
					break;
				}
			}
			if (!isFind)
			{
				CString strB;
				strB.Format(_T("没有查找到您输入的点名对应的点“%s”！"), bName); 
				if (isAfxMessageBoxOn)
				{
					AfxMessageBox(strB);
				}
				isAfxMessageBoxOn = false;
				//isFindFail = true;
				isFind = true;
				return;
			}
		}
		else
		{
			AfxMessageBox(_T("请按照要求输入角的第二条边上的点的数据！")); return;
		}

		GetProjectAng(vertex, a, b);
		GetAng(vertex, a, b);


		// 对话框中显示的空间角的度
		angDlgDegree = degree1;
		// 对话框中显示的空间角的分
		angDlgMinute = minute1;
		// 对话框中显示的空间角的秒
		angDlgSecond = second1;


		// 对话框中显示的水平投影角的度
		prjangDlgDegree = degree2;
		// 对话框中显示的水平投影角的分
		prjangDlgMinute = minute2;
		// 对话框中显示的水平投影角的秒
		angprjDlgSecond = second2;


		UpdateData(FALSE);
	}
}


void PointCalculateForThreeDlg::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	CDialogEx::OnOK();

}
