// SignInDlg.cpp: 实现文件
//

#include "pch.h"
#include "MFCApplication_20240607_cppTeamWork.h"
#include "MFCApplication_20240607_cppTeamWorkDoc.h"
#include "afxdialogex.h"
#include "SignInDlg.h"
#include "BuyAccountDlg.h"
#include "IsRememberPasswordDlg.h"
#include <ctime>
#include <sstream>

// SignInDlg 对话框

IMPLEMENT_DYNAMIC(SignInDlg, CDialogEx)

SignInDlg::SignInDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG20, pParent)
	, m_username(rememberUsername.c_str())
	, m_password(rememberPassword.c_str())
	, isSignInOk(false)
{

}

SignInDlg::~SignInDlg()
{
}

void SignInDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_username);
	DDX_Text(pDX, IDC_EDIT2, m_password);
	DDX_Control(pDX, IDC_CHECK1, m_passwordcheck);
	DDX_Control(pDX, IDC_CHECK2, m_rememberPasswordCheck);
}


BEGIN_MESSAGE_MAP(SignInDlg, CDialogEx)
	ON_BN_CLICKED(IDOK, &SignInDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDC_CHECK1, &SignInDlg::OnBnClickedPasswordstyle)
	ON_BN_CLICKED(IDC_BUTTON1, &SignInDlg::OnBnClickedButtonBuyAccount)
	ON_BN_CLICKED(IDC_CHECK2, &SignInDlg::OnBnClickedRememberPasswordStyle)
END_MESSAGE_MAP()

//简单凯撒加密算法，将密码中的每个字符偏移一个随机数
string EncryptPassword(const string& password,int& n)
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
string DecryptPassword(const string& encryptedPassword,int n)
{
	string decrypted;
	for (char c : encryptedPassword)
	{
		decrypted += c - n; // 简单的字符偏移
	}
	return decrypted;
}
// 解析字符串并分别赋值给两个int引用
bool parseAndAssign(const std::string& str, int& num1, int& num2) {
	std::istringstream iss(str);
	if (!(iss >> num1 >> num2)) {
		// 如果解析失败，则返回false
		return false;
	}
	return true; // 解析成功，返回true
}

// SignInDlg 消息处理程序

BOOL SignInDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	CEdit* pmyEdit1 = (CEdit*)GetDlgItem(IDC_EDIT1); // 用户名编辑框控件的指针
	CEdit* pmyEdit2 = (CEdit*)GetDlgItem(IDC_EDIT2); // 密码编辑框控件的指针
	CButton* pCheckBox1 = (CButton*)GetDlgItem(IDC_CHECK1); // 是否显示密码的复选框控件的指针
	CButton* pCheckBox2 = (CButton*)GetDlgItem(IDC_CHECK2); // 获取是否记住密码的复选框控件的指针
	// 读取密码文件，如果存在则读取密码并解密

	pCheckBox2->SetCheck(BST_UNCHECKED);//默认不记住密码

	ifstream inFile("data/user_credentials.dat", ios::in | ios::binary);
	if (!inFile.is_open())
	{
		// 显示用户名和密码
		pmyEdit1->SetPasswordChar(0); // 显示格式为明文
		pmyEdit2->SetPasswordChar(0); // 显示格式为明文
	}
	else
	{
		// 隐藏用户名和密码
		pmyEdit1->SetPasswordChar('*'); // 用户名显示格式为原点
		pmyEdit2->SetPasswordChar('*'); // 密码显示格式为原点
		pCheckBox1->EnableWindow(FALSE);//禁用是否显示密码的复选框
		//pCheckBox2->EnableWindow(FALSE);//禁用是否记住密码的复选框
		pCheckBox2->SetCheck(BST_CHECKED);//如果已经有密码文件，则默认选中记住密码的复选框
	}
	pmyEdit1->SetFocus(); // 聚焦到用户名编辑框
	pmyEdit2->SetPasswordChar('*'); // 密码显示格式为原点

	if (inFile.is_open())
	{
		string getUsername;
		string getPassword;

		// 读取加密的用户名和密码
		string nEncryptString;
		getline(inFile, nEncryptString);
		getline(inFile, getUsername);
		getline(inFile, getPassword);

		inFile.close();

		// 解密用户名和密码
		parseAndAssign(nEncryptString, nEncryptUsername, nEncryptPassword);
		string decryptedUsername = DecryptPassword(getUsername, nEncryptUsername);
		string decryptedPassword = DecryptPassword(getPassword, nEncryptPassword);
		mainUsername = decryptedUsername;

		// 设置用户名和密码到编辑框
		pmyEdit1->SetWindowText(CA2T(decryptedUsername.c_str()));
		pmyEdit2->SetWindowText(CA2T(decryptedPassword.c_str()));

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


void SignInDlg::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	//CDialogEx::OnOK();
	UpdateData(TRUE); // 更新控件对应变量的值
	CEdit* pmyEdit1 = (CEdit*)GetDlgItem(IDC_EDIT1); // 用户名编辑框控件的指针
	CButton* pCheckBox1 = (CButton*)GetDlgItem(IDC_CHECK1); // 是否显示密码的复选框控件的指针
	CButton* pCheckBox2 = (CButton*)GetDlgItem(IDC_CHECK2); // 是否记住密码的复选框控件的指针
	if ((m_username == "杨丹阳" && m_password == "2023302131259")
		|| (m_username == "梁宇康" && m_password == "2023302131293")
		|| (m_username == "易星辰" && m_password == "2023302131197")
		|| (m_username == "赵启睿" && m_password == "2023302131175")
		|| (m_username == "曾泓源" && m_password == "2023302131235") 
		|| (m_username == "WHURSGIS" && m_password == "2023302131")//测试账号
		|| (m_username == "程悦彤" && m_password == "U202315620")
		)
	{
		// 进入主对话框界面
		MessageBox(_T("登录成功！欢迎您的使用！"), _T("登录成功提示"), MB_OK);
		CDialogEx::OnOK(); // 关闭登陆界面
		isSignInOk = true;//标志值更新
		return;//进入欢迎页
	}
	else
	{
		// 弹出窗口提示用户名或密码不正确
		MessageBox(_T("您输入的用户名或密码不正确！"), _T("登录失败提示"), MB_OK);
		// 清空用户名和密码，便于重新输入
		m_username = "";
		m_password = "";
		pCheckBox1->EnableWindow(TRUE);//启用是否显示密码的复选框
		pCheckBox2->EnableWindow(TRUE);//启用是否记住密码的复选框
		pCheckBox2->SetCheck(BST_UNCHECKED);
		pmyEdit1->SetPasswordChar(0); // 用户名显示格式为明文
		UpdateData(FALSE); // 更新编辑框控件的显示值
	}
}


void SignInDlg::OnBnClickedPasswordstyle()
{
	// TODO: 在此添加控件通知处理程序代码
	// 若在显示密码前打勾，则密码显示为明文，默认为密文（星号）
	UpdateData(TRUE); // 更新控件对应变量的值
	CEdit* pmyEdit = (CEdit*)GetDlgItem(IDC_EDIT2); // 密码编辑框控件的指针

	if (isRememberPassword)
	{
		// TODO: 保存密码到一个文件（如果之前已经保存了文件则将其覆盖），并且加密存储
		string usernameRemember = CT2A(m_username.GetBuffer());
		string passwordRemember = CT2A(m_password.GetBuffer());

		// 对用户名和密码进行简单加密（可以使用更复杂的加密算法）
		string encryptedUsername = EncryptPassword(usernameRemember, nEncryptUsername);
		string encryptedPassword = EncryptPassword(passwordRemember, nEncryptPassword);

		// 保存到文件
		ofstream outFile("data/user_credentials.dat", ios::out | ios::trunc | ios::binary);
		if (outFile.is_open())
		{
			outFile << nEncryptUsername << " " << nEncryptPassword << "\n" << encryptedUsername << "\n" << encryptedPassword;
			outFile.close();
		}
	}
	else
	{
		remove("data/user_credentials.dat");//删除密码文件
	}

	if (m_passwordcheck.GetCheck() == 1)
	{
		pmyEdit->SetPasswordChar(0); // 显示格式为明文
		//ASSERT(!(pmyEdit->GetStyle() & ES_PASSWORD));
		//SetDlgItemText(IDC_EDIT2, m_password);
		//UpdateData(FALSE);
		//通过SetFocus让上面改动生效且聚焦在edit最后位置，不需要UpdateData(FALSE)
	}
	else
	{
		pmyEdit->SetPasswordChar('*'); // 密文显示格式为原点
		//SetDlgItemText(IDC_EDIT2, m_password);
		//UpdateData(FALSE);
		//通过SetFocus让上面改动生效且聚焦在edit最后位置，不需要UpdateData(FALSE)
	}
	//GetDlgItem(IDC_EDIT2)->SetFocus();
	pmyEdit->SetFocus();
	//只保留这个SetFocus，防止出现“光标会聚焦在输入框的开始位置，而不是最后”的bug
	// https://blog.csdn.net/D_daytime/article/details/107871386
}


void SignInDlg::OnBnClickedButtonBuyAccount()
{
	// TODO: 在此添加控件通知处理程序代码
	BuyAccountDlg dlg;
	dlg.DoModal();
}


void SignInDlg::OnBnClickedRememberPasswordStyle()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE); // 更新控件对应变量的值
	CButton* pCheckBox2 = (CButton*)GetDlgItem(IDC_CHECK2); // 获取是否记住密码的复选框控件的指针
	int state = pCheckBox2->GetCheck();
	if (state == BST_CHECKED)
	{
		// TODO: 记住密码功能
		IsRememberPasswordDlg dlg;
		dlg.DoModal();
		if (isRememberPassword)
		{
			// TODO: 保存密码到一个文件（如果之前已经保存了文件则将其覆盖），并且加密存储
			string usernameRemember = CT2A(m_username.GetBuffer());
			string passwordRemember = CT2A(m_password.GetBuffer());

			// 对用户名和密码进行简单加密（可以使用更复杂的加密算法）
			string encryptedUsername = EncryptPassword(usernameRemember,nEncryptUsername);
			string encryptedPassword = EncryptPassword(passwordRemember,nEncryptPassword);

			// 保存到文件
			ofstream outFile("data/user_credentials.dat", ios::out | ios::trunc | ios::binary);
			if (outFile.is_open())
			{
				outFile << nEncryptUsername << " " << nEncryptPassword << "\n" << encryptedUsername << "\n" << encryptedPassword;
				outFile.close();
			}
		}
		else
		{
			remove("data/user_credentials.dat");//删除密码文件
			pCheckBox2->SetCheck(BST_UNCHECKED); // 取消选中复选框
		}
	}
	return;
}
