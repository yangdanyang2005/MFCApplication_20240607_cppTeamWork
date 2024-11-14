// PointCalculateForTwoDlg.cpp: 实现文件
//

#include "pch.h"
#include "MFCApplication_20240607_cppTeamWork.h"
#include "afxdialogex.h"
#include "PointCalculateForTwoDlg.h"
#include "MFCApplication_20240607_cppTeamWorkDoc.h"


// PointCalculateForTwoDlg 对话框

IMPLEMENT_DYNAMIC(PointCalculateForTwoDlg, CDialogEx)

PointCalculateForTwoDlg::PointCalculateForTwoDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG17, pParent)
	, a_x(0)
	, a_y(0)
	, a_z(0)
	, closeName(_T(""))
	, closeX(0)
	, closeY(0)
	, closeZ(0)
	, closeSlantDis(0)
	, prjDis(0)
	, hDiff(0)
	, altitudeAng(0)
	, zenithAng(0)
	, aDegree(0)
	, aMinute(0)
	, aSecond(0)
	, zDegree(0)
	, zMinute(0)
	, zSecond(0)
{

}

PointCalculateForTwoDlg::~PointCalculateForTwoDlg()
{
}

void PointCalculateForTwoDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, a_x);
	DDX_Text(pDX, IDC_EDIT2, a_y);
	DDX_Text(pDX, IDC_EDIT3, a_z);
	DDX_Text(pDX, IDC_EDIT4, closeName);
	DDX_Text(pDX, IDC_EDIT5, closeX);
	DDX_Text(pDX, IDC_EDIT6, closeY);
	DDX_Text(pDX, IDC_EDIT7, closeZ);
	DDX_Text(pDX, IDC_EDIT8, closeSlantDis);
	DDX_Text(pDX, IDC_EDIT9, prjDis);
	DDX_Text(pDX, IDC_EDIT10, hDiff);
	DDX_Text(pDX, IDC_EDIT11, altitudeAng);
	DDX_Text(pDX, IDC_EDIT12, zenithAng);
	DDX_Text(pDX, IDC_EDIT17, aDegree);
	DDX_Text(pDX, IDC_EDIT18, aMinute);
	DDX_Text(pDX, IDC_EDIT16, aSecond);
	DDX_Text(pDX, IDC_EDIT15, zDegree);
	DDX_Text(pDX, IDC_EDIT19, zMinute);
	DDX_Text(pDX, IDC_EDIT13, zSecond);
}


BEGIN_MESSAGE_MAP(PointCalculateForTwoDlg, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON1, &PointCalculateForTwoDlg::OnBnClickedButtonPointCalculateForTwo)
	ON_EN_CHANGE(IDC_EDIT6, &PointCalculateForTwoDlg::OnEnChangeEdit6)
	ON_EN_CHANGE(IDC_EDIT3, &PointCalculateForTwoDlg::OnEnChangeEdit3)
END_MESSAGE_MAP()


// PointCalculateForTwoDlg 消息处理程序


void PointCalculateForTwoDlg::OnBnClickedButtonPointCalculateForTwo()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);
	CFrameWnd* pMainFrame = (CFrameWnd*)AfxGetMainWnd();
	CFrameWnd* pActiveFrame = pMainFrame->GetActiveFrame();
	CDocument* pActiveDocument = pActiveFrame->GetActiveDocument();
	CMFCApplication20240607cppTeamWorkDoc* pDoc = dynamic_cast<CMFCApplication20240607cppTeamWorkDoc*>(pActiveDocument);//从文档读取变量数据到对话框中
	if (pDoc != nullptr)
	{
		Point a;
		a.setX(a_x); a.setY(a_y); a.setZ(a_z);

		GetMinDis(a, pDoc->arr, pDoc->closePoint);//求最小斜距的函数
		closeSlantDis = minSlantDis;// 所求的最小斜距

		closeName =pDoc->closePoint.getName().c_str();
		closeX = pDoc->closePoint.getX();
		closeY = pDoc->closePoint.getY();
		closeZ = pDoc->closePoint.getZ();
		
		hDiff = GetHeightDifference(a, pDoc->closePoint);//高差

		prjDis = GetHorizontalDis(a, pDoc->closePoint);//水平距离

		GetAltitude(a, pDoc->closePoint);//高度角
		GetZenithAngle(a, pDoc->closePoint);//天顶距

		// 高度角的度
		aDegree = degree1;
		// 高度角的分
		aMinute= minute1;
		// 高度角的秒
		aSecond= second1;
		// 天顶距的度
		zDegree = degree2;
		// 天顶距的分
		zMinute = minute2;
		// 天顶距的秒
		zSecond = second2;

		UpdateData(FALSE);
	}
	else 
	{
		MessageBox(NULL, _T("发生错误：未关联文档！"), MB_OK | MB_ICONWARNING);
	}
}


void PointCalculateForTwoDlg::OnEnChangeEdit6()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
}


void PointCalculateForTwoDlg::OnEnChangeEdit3()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
}
