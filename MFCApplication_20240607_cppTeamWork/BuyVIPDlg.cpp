// BuyVIPDlg.cpp: 实现文件
//

#include "pch.h"
#include "MFCApplication_20240607_cppTeamWork.h"
#include "MFCApplication_20240607_cppTeamWorkDoc.h"
#include "afxdialogex.h"
#include "BuyVIPDlg.h"
#include "BuyAccountDlg.h"
#include "IsRememberVIPKeyDlg.h"
#include <ctime>


// BuyVIPDlg 对话框

IMPLEMENT_DYNAMIC(BuyVIPDlg, CDialogEx)

BuyVIPDlg::BuyVIPDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG22, pParent)
	, vipkey(_T(""))
	, isBeyVIPOk(false)
{

}

BuyVIPDlg::~BuyVIPDlg()
{
}

void BuyVIPDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT2, vipkey);
	DDX_Control(pDX, IDC_CHECK1, m_passwordcheck);
	DDX_Control(pDX, IDC_CHECK2, IsRememberVIPKeyCheckBox);
}


BEGIN_MESSAGE_MAP(BuyVIPDlg, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON1, &BuyVIPDlg::OnBnClickedButtonBuy)
	ON_BN_CLICKED(IDOK, &BuyVIPDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDC_CHECK1, &BuyVIPDlg::OnBnClickedVIPkeystyle)
	ON_BN_CLICKED(IDC_CHECK2, &BuyVIPDlg::OnBnClickedCheckIsRememberVIPKeyCheckBox)
END_MESSAGE_MAP()

//简单凯撒加密算法，将密码中的每个字符偏移一个随机数
string EncryptPassword(const string& password, int& n)
{
	srand(time(0)); // 初始化随机数种子
	string encrypted;
	n = rand() % 10; // 随机生成一个偏移量
	for (char c : password)
	{
		encrypted += c + n; // 简单的字符偏移
	}
	return encrypted;
}
//简单解密函数（与之前的加密函数对应）
string DecryptPassword(const string& encryptedPassword, int n)
{
	string decrypted;
	for (char c : encryptedPassword)
	{
		decrypted += c - n; // 简单的字符偏移
	}
	return decrypted;
}

// BuyVIPDlg 消息处理程序

BOOL BuyVIPDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	CEdit* pmyEdit = (CEdit*)GetDlgItem(IDC_EDIT2); // 密钥编辑框控件的指针
	CButton* pCheckBox1 = (CButton*)GetDlgItem(IDC_CHECK1); // 是否显示密钥的复选框控件的指针
	CButton* pCheckBox2 = (CButton*)GetDlgItem(IDC_CHECK2); // 获取是否记住密钥的复选框控件的指针

	pmyEdit->SetPasswordChar('*'); // 密钥显示格式为原点
	// 读取密钥文件，如果存在则读取密钥并解密
	pCheckBox2->SetCheck(BST_UNCHECKED);//默认选中不记住密码的复选框

	ifstream inFile("data/user_vipkey.dat", ios::in | ios::binary);
	if (inFile.is_open())
	{
		pCheckBox1->EnableWindow(FALSE);//禁用是否显示密钥的复选框
		//pCheckBox2->EnableWindow(FALSE);//禁用记住密钥的复选框
		pCheckBox2->SetCheck(BST_CHECKED);//如果已经有密钥文件，则默认选中记住密码的复选框
	}

	if (inFile.is_open())
	{
		string getVIPKey;

		// 读取加密存储的VIP密钥
		string nEncryptString;
		getline(inFile, nEncryptString);
		getline(inFile, getVIPKey);

		inFile.close();

		// 解密VIP密钥
		nEncryptVIPKey = atoi(nEncryptString.c_str());
		string decryptedVIPKey = DecryptPassword(getVIPKey, nEncryptVIPKey);

		// 设置VIP密钥到编辑框
		pmyEdit->SetWindowText(CA2T(decryptedVIPKey.c_str()));

		return TRUE;  // return TRUE unless you set the focus to a control
		// 异常: OCX 属性页应返回 FALSE
	}
	else
	{
		// 文件不存在
		return TRUE;
	}
	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}


void BuyVIPDlg::OnBnClickedButtonBuy()
{
	// TODO: 在此添加控件通知处理程序代码
	BuyAccountDlg dlg;
	dlg.DoModal();
}


void BuyVIPDlg::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	//CDialogEx::OnOK();
	UpdateData(TRUE); // 更新控件对应变量的值
	CEdit* pmyEdit = (CEdit*)GetDlgItem(IDC_EDIT2); // 密钥编辑框控件的指针
	CButton* pCheckBox1 = (CButton*)GetDlgItem(IDC_CHECK1); // 是否显示密钥的复选框控件的指针
	CButton* pCheckBox2 = (CButton*)GetDlgItem(IDC_CHECK2); // 获取是否记住密钥的复选框控件的指针
	if ((vipkey == "2023302131259")
		|| (vipkey == "2023302131293")
		|| (vipkey == "2023302131197")
		|| (vipkey == "2023302131175")
		|| (vipkey == "2023302131235")
		|| (vipkey == "wudayaoganshijiediyi")//测试密钥
		|| (vipkey == "U202315620")
		)
	{
		// 进入主对话框界面
		MessageBox(_T("VIP激活成功！感谢您的支持！"), _T("VIP激活成功提示"), MB_OK);
		CDialogEx::OnOK(); // 关闭登陆界面
		isBeyVIPOk = true;//标志值更新
		return;//进入欢迎页
	}
	else
	{
		// 弹出窗口提示用户名或密码不正确
		MessageBox(_T("您输入的VIP激活密钥不正确！"), _T("VIP激活失败提示"), MB_OK);
		// 清空用户名和密码，便于重新输入
		vipkey = "";
		pCheckBox1->EnableWindow(TRUE);//启用是否显示密钥的复选框
		pCheckBox2->EnableWindow(TRUE);//启用是否显示密钥的复选框
		pCheckBox2->SetCheck(BST_UNCHECKED);
		//pmyEdit->SetPasswordChar('*'); // 密钥显示格式为密文
		UpdateData(FALSE); // 更新编辑框控件的显示值
	}
}


void BuyVIPDlg::OnBnClickedVIPkeystyle()
{
	// TODO: 在此添加控件通知处理程序代码
	// 若在显示密码前打勾，则密码显示为明文，默认为密文（星号）
	UpdateData(TRUE); // 更新控件对应变量的值
	CEdit* pmyEdit = (CEdit*)GetDlgItem(IDC_EDIT2); // 密码编辑框控件的指针

	if (isRememberVIPKey)
	{
		// TODO: 保存密钥到一个文件（如果之前已经保存了文件则将其覆盖），并且加密存储
		string VIPKeyRemember = CT2A(vipkey.GetBuffer());

		// 对密钥进行简单加密（可以使用更复杂的加密算法）
		string encryptedVIPKey = EncryptPassword(VIPKeyRemember, nEncryptVIPKey);

		// 保存到文件
		ofstream outFile("data/user_vipkey.dat", ios::out | ios::trunc | ios::binary);
		if (outFile.is_open())
		{
			outFile << nEncryptVIPKey << "\n" << encryptedVIPKey;
			outFile.close();
		}
	}
	else
	{
		remove("data/uesr_vipkey.dat");//删除密钥文件
	}

	if (m_passwordcheck.GetCheck() == 1)
	{
		pmyEdit->SetPasswordChar(0); // 显示格式为明文
		/*ASSERT(!(pmyEdit->GetStyle() & ES_PASSWORD));
		SetDlgItemText(IDC_EDIT2, vipkey);
		UpdateData(FALSE);*/
	}
	else
	{
		pmyEdit->SetPasswordChar('*'); // 密文显示格式为原点
		/*SetDlgItemText(IDC_EDIT2, vipkey);
		UpdateData(FALSE);*/
	}
	//GetDlgItem(IDC_EDIT2)->SetFocus();
	pmyEdit->SetFocus();
	//只保留这个SetFocus，防止出现“光标会聚焦在输入框的开始位置，而不是最后”的bug
	// https://blog.csdn.net/D_daytime/article/details/107871386
}



void BuyVIPDlg::OnBnClickedCheckIsRememberVIPKeyCheckBox()

{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE); // 更新控件对应变量的值
	CButton* pCheckBox2 = (CButton*)GetDlgItem(IDC_CHECK2); // 获取是否记住密钥的复选框控件的指针
	int state = pCheckBox2->GetCheck();
	if (state == BST_CHECKED)
	{
		// TODO: 记住密码功能
		IsRememberVIPKeyDlg dlg;
		dlg.DoModal();
		if (isRememberVIPKey)
		{
			// TODO: 保存密钥到一个文件（如果之前已经保存了文件则将其覆盖），并且加密存储
			string VIPKeyRemember = CT2A(vipkey.GetBuffer());

			// 对密钥进行简单加密（可以使用更复杂的加密算法）
			string encryptedVIPKey = EncryptPassword(VIPKeyRemember, nEncryptVIPKey);

			// 保存到文件
			ofstream outFile("data/user_vipkey.dat", ios::out | ios::trunc | ios::binary);
			if (outFile.is_open())
			{
				outFile << nEncryptVIPKey << "\n" << encryptedVIPKey;
				outFile.close();
			}
		}
		else
		{
			remove("data/uesr_vipkey.dat");//删除密钥文件
			pCheckBox2->SetCheck(BST_UNCHECKED); // 取消选中复选框
		}
	}
	return;
}
