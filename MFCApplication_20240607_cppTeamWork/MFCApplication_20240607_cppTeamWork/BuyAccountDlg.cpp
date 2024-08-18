// BuyAccountDlg.cpp: 实现文件
//

#include "pch.h"
#include "MFCApplication_20240607_cppTeamWork.h"
#include "afxdialogex.h"
#include "BuyAccountDlg.h"


// BuyAccountDlg 对话框

IMPLEMENT_DYNAMIC(BuyAccountDlg, CDialogEx)

BuyAccountDlg::BuyAccountDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG21, pParent)
{

}

BuyAccountDlg::~BuyAccountDlg()
{
}

void BuyAccountDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(BuyAccountDlg, CDialogEx)
	ON_WM_PAINT()
END_MESSAGE_MAP()


// BuyAccountDlg 消息处理程序


void BuyAccountDlg::OnPaint()
{
	//CPaintDC dc(this); // device context for painting
	// TODO: 在此处添加消息处理程序代码
	// 不为绘图消息调用 CDialogEx::OnPaint()
	
	//CImage* m_sLogInPic;//新建一个CImage的对象 用于储存图片
	//m_sLogInPic = new CImage;
	//m_sLogInPic->Load(L"D://weixinzhifu.png");//使用m_sLogInPic读取图片引号中添加图片地址及图片名
	//CPaintDC dc(this); // 建立一个矩形在矩形中画图
	//CRect rect;
	//GetDlgItem(IDC_STATIC)->GetWindowRect(&rect);//规定矩形为你所创建的图片控件（括号内为控件ID）若是为整个窗口添加背景将矩形设为整个窗口即可
	//ScreenToClient(&rect);
	//dc.SetStretchBltMode(HALFTONE);
	//m_sLogInPic->Draw(dc.m_hDC, rect);//通过画图 将图片paint出来 
	//CImage* m_sLogInPic1;//新建一个CImage的对象 用于储存图片
	//m_sLogInPic1 = new CImage;
	//m_sLogInPic1->Load(L"D://zhifubaozhifu.jpg");//使用m_sLogInPic读取图片引号中添加图片地址及图片名
	//CPaintDC dc1(this); // 建立一个矩形在矩形中画图
	//CRect rect1;
	//GetDlgItem(IDC_STATIC)->GetWindowRect(&rect1);//规定矩形为你所创建的图片控件（括号内为控件ID）若是为整个窗口添加背景将矩形设为整个窗口即可
	//ScreenToClient(&rect1);
	//dc.SetStretchBltMode(HALFTONE);
	//m_sLogInPic1->Draw(dc.m_hDC, rect1);//通过画图 将图片paint出来 

	// https://blog.csdn.net/wangyongjie1231/article/details/117076619

	CStatic* pStatic = (CStatic*)GetDlgItem(IDC_STATIC1); // 得到 Picture Control 句柄   
	CImage image;
	image.Load(TEXT("images/weixinzhifu.png"));//加载图片
	//HBITMAP bitmap = image.Detach();
	//pStatic->ModifyStyle(0xF, SS_BITMAP | SS_CENTERIMAGE);
	//pStatic->SetBitmap(bitmap);
	//以下为根据MFC控件大小CImage类实例图片显示
	CRect zcRect;
	pStatic->GetClientRect(&zcRect);   //得到尺寸
	image.Draw(pStatic->GetDC()->m_hDC,
		zcRect.left,
		zcRect.top,
		zcRect.Width(),
		zcRect.Height());
	image.Destroy();

	CStatic* pStatic1 = (CStatic*)GetDlgItem(IDC_STATIC2); // 得到 Picture Control 句柄   
	CImage image1;
	image1.Load(TEXT("images/zhifubaozhifu.jpg"));
	/*HBITMAP bitmap1 = image1.Detach();
	pStatic1->ModifyStyle(0xF, SS_BITMAP | SS_CENTERIMAGE);
	pStatic1->SetBitmap(bitmap1);*/
	//以下为根据MFC控件大小CImage类实例图片显示
	CRect zcRect1;
	pStatic1->GetClientRect(&zcRect1);   //得到尺寸
	image1.Draw(pStatic1->GetDC()->m_hDC,
		zcRect1.left,
		zcRect1.top,
		zcRect1.Width(),
		zcRect1.Height());
	image1.Destroy();

	CDialogEx::OnPaint();
}
