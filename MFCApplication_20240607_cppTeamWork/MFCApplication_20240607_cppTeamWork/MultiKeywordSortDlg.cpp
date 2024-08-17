// MultiKeywordSortDlg.cpp: 实现文件
//

#include "pch.h"
#include "MFCApplication_20240607_cppTeamWork.h"
#include "afxdialogex.h"
#include "MultiKeywordSortDlg.h"
#include "MFCApplication_20240607_cppTeamWorkDoc.h"
#include <vector>
using namespace std;

// MultiKeywordSortDlg 对话框

IMPLEMENT_DYNAMIC(MultiKeywordSortDlg, CDialogEx)

MultiKeywordSortDlg::MultiKeywordSortDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG24, pParent)
	, WantedSortRule(_T("x,y,z"))
{

}

MultiKeywordSortDlg::~MultiKeywordSortDlg()
{
}

void MultiKeywordSortDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, WantedSortRule);
	DDX_Control(pDX, IDC_LIST1, MultiKeywordSortOutcome);
	DDX_Control(pDX, IDC_COMBO1, wayFlag);
}


BEGIN_MESSAGE_MAP(MultiKeywordSortDlg, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON1, &MultiKeywordSortDlg::OnBnClickedButtonMultiKeywordSort)
END_MESSAGE_MAP()

template<typename T, typename... Keys>
/*模板声明，表示这是一个模板函数，
接受两种类型的参数：T 和 Keys...。
T 是一个类型参数，
而 Keys... 是一个可变参数模板，表示可以接受零个或多个类型参数。*/
// 自定义的比较函数模板
bool compare(int wayFlag, const Point& a, const Point& b, T(Point::* key)() const, Keys... keys)
//Keys... keys：这是一个可变参数模板参数，表示可以接受零个或多个成员函数指针参数。Keys... 是类型参数包，keys 是参数包的名称。
{
	switch (wayFlag)
	{
	case 1:
	{
		if ((a.*key)() < (b.*key)())/*比较 a 和 b 通过 key 成员函数指针调用的结果*/ {
			return true;
		}
		if ((a.*key)() > (b.*key)()) {
			return false;
		}
		if constexpr (sizeof...(keys) == 0) {
			return false;
		}
		else {
			return compare(wayFlag, a, b, keys...);
		}
	}
	case 2:
	{
		if ((a.*key)() > (b.*key)())/*比较 a 和 b 通过 key 成员函数指针调用的结果*/ {
			return true;
		}
		if ((a.*key)() < (b.*key)()) {
			return false;
		}
		if constexpr (sizeof...(keys) == 0) {
			return false;
		}
		else {
			return compare(wayFlag, a, b, keys...);
		}
	}
	}
}

// 快速排序的分区函数
template<typename... Keys>
int partition(int wayFlag, Point R[], int low, int high, Keys... keys) {
	Point pivot = R[high];
	int i = low - 1;

	for (int j = low; j <= high - 1; j++) {
		if (compare(wayFlag, R[j], pivot, keys...)) {
			i++;
			std::swap(R[i], R[j]);
		}
	}
	std::swap(R[i + 1], R[high]);
	return i + 1;
}
// 快速排序函数
template<typename... Keys>
void quickSort(int wayFlag, Point R[], int low, int high, Keys... keys) {
	if (low < high) {
		int pi = partition(wayFlag, R, low, high, keys...);
		quickSort(wayFlag, R, low, pi - 1, keys...);
		quickSort(wayFlag, R, pi + 1, high, keys...);
	}
}

//对输入的字符串的处理函数
string removeCommas(const std::string& input) {
	std::string result;
	for (char c : input) {
		if (c != ',') {
			result += c;
		}
	}
	return result;
}
int convertStrtoNum(const std::string& input) {
	std::string result;
	for (char c : input) {
		if (c == 'x') {
			result += '1';
		}
		else if (c == 'y') {
			result += '2';
		}
		else if (c == 'z') {
			result += '3';
		}
		else {
			return -1;
		}
	}
	return std::stoi(result);  // 将结果字符串转换为整数
}
int chooseSortKeyword(int wayFlag, PointArr& arr, CString str1, int& n)
{
	MultiKeywordSortDlg dlg;
	string str;
	str = CT2A(str1);
	int chooseNum = convertStrtoNum(removeCommas(str));
	n = chooseNum;
	switch (chooseNum)
	{
	case -1:
	{
		AfxMessageBox(_T("请【按照格式要求】输入您想要的排序方式！"));
		return -1;
		break;
	}
	case 0:
	{
		AfxMessageBox(_T("请【先】按照格式要求【在下面的输入框中输入】您想要的排序方式！"));
		return -1;
		break;
	}
	case 1:
	{
		quickSort(wayFlag, arr.m_PointArr, 0, arr.m_Num - 1, &Point::getX);
		break;
	}
	case 2:
	{
		quickSort(wayFlag, arr.m_PointArr, 0, arr.m_Num - 1, &Point::getY);
		break;
	}
	case 3:
	{
		quickSort(wayFlag, arr.m_PointArr, 0, arr.m_Num - 1, &Point::getZ);
		break;
	}
	case 12:
	{
		quickSort(wayFlag, arr.m_PointArr, 0, arr.m_Num - 1, &Point::getX, &Point::getY);
		break;
	}
	case 13:
	{
		quickSort(wayFlag, arr.m_PointArr, 0, arr.m_Num - 1, &Point::getX, &Point::getZ);
		break;
	}
	case 23:
	{
		quickSort(wayFlag, arr.m_PointArr, 0, arr.m_Num - 1, &Point::getY, &Point::getZ);
		break;
	}
	case 21:
	{
		quickSort(wayFlag, arr.m_PointArr, 0, arr.m_Num - 1, &Point::getY, &Point::getX);
	}
	case 31:
	{
		quickSort(wayFlag, arr.m_PointArr, 0, arr.m_Num - 1, &Point::getZ, &Point::getX);
		break;
	}
	case 32:
	{
		quickSort(wayFlag, arr.m_PointArr, 0, arr.m_Num - 1, &Point::getZ, &Point::getY);
		break;
	case 123:
	{
		quickSort(wayFlag, arr.m_PointArr, 0, arr.m_Num - 1, &Point::getX, &Point::getY, &Point::getZ);
		break;
	}
	case 132:
	{
		quickSort(wayFlag, arr.m_PointArr, 0, arr.m_Num - 1, &Point::getX, &Point::getZ, &Point::getY);
		break;
	}
	case 231:
	{
		quickSort(wayFlag, arr.m_PointArr, 0, arr.m_Num - 1, &Point::getY, &Point::getZ, &Point::getX);
		break;
	}
	case 213:
	{
		quickSort(wayFlag, arr.m_PointArr, 0, arr.m_Num - 1, &Point::getY, &Point::getX, &Point::getZ);
		break;
	}
	case 312:
	{
		quickSort(wayFlag, arr.m_PointArr, 0, arr.m_Num - 1, &Point::getZ, &Point::getX, &Point::getY);
		break;
	}
	case 321:
	{
		quickSort(wayFlag, arr.m_PointArr, 0, arr.m_Num - 1, &Point::getZ, &Point::getY, &Point::getX);
		break;
	}
	default:
	{
		AfxMessageBox(_T("请【按照格式要求】输入您想要的排序方式！"));
		return -1;
		break;
	}
	return 0;
	}
	}
}

// MultiKeywordSortDlg 消息处理程序


void MultiKeywordSortDlg::OnBnClickedButtonMultiKeywordSort()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);
	CFrameWnd* pMainFrame = (CFrameWnd*)AfxGetMainWnd();
	CFrameWnd* pActiveFrame = pMainFrame->GetActiveFrame();
	CDocument* pActiveDocument = pActiveFrame->GetActiveDocument();
	CMFCApplication20240607cppTeamWorkDoc* pDoc = dynamic_cast<CMFCApplication20240607cppTeamWorkDoc*>(pActiveDocument);//从文档读取变量数据到对话框中

	MultiKeywordSortDlg dlg;
	string str;
	str = CT2A(WantedSortRule);
	//strcpy(pDoc->arrMultiSortRuleName , str.c_str());//容易出现乱码

	if (pDoc == nullptr)
	{
		MessageBox(NULL, _T("发生错误：未关联文档！"), MB_OK | MB_ICONWARNING);
		return;
	}
	else
	{
		//大一下 《遥感信息处理C++基础》 BP208图10-36

		//先清空上一次输入的表示排序规则的字符串
		POSITION pos = MultiKeywordSortOutcome.GetFirstSelectedItemPosition();

		while (pos != NULL)
		{
			MultiKeywordSortOutcome.DeleteItem(MultiKeywordSortOutcome.GetNextSelectedItem(pos));
			pos = MultiKeywordSortOutcome.GetFirstSelectedItemPosition();
		}

		//再来处理输入的表示排序规则的字符串，同时调用快速排序函数
		int wayFlagNum = wayFlag.GetCurSel();
		if (chooseSortKeyword(wayFlagNum, pDoc->arr, WantedSortRule, pDoc->arrMultiSortRuleCode)==-1)
		{
			return;
		}

		CString str;
		int n = pDoc->arr.m_Num;
		int item = MultiKeywordSortOutcome.GetItemCount();
		/*GetItemCount()：这是CListCtrl类的另一个成员函数，用于获取当前列表视图中的项目数量。返回值是一个整数，表示列表中的项目总数。
		这往往用于向列表视图中续接式地添加新的项目。*/
		for (int i = 0; i < n; i++)
		{
			MultiKeywordSortOutcome.InsertItem(item + i, str);//申请空间
			/*InsertItem是CListCtrl类的一个成员函数，用于在列表视图中插入一个新的项目。
			item + i是插入的行号。
			str是一个CString对象，包含了要插入到新项目中的文本内容。*/

			str.Format(_T("%d"), pDoc->arr.m_PointArr[i].getSerialNum());
			/*这段代码是C++语言中使用Windows平台下的字符串处理函数`str.Format`进行字符串格式化的一个例子。
			`str.Format`函数是`CString`类的一部分，这是Microsoft Foundation Class (MFC)库中的一个类，用于处理Windows应用程序中的Unicode和ANSI字符串。

			1. `str`：这是一个`CString`类型的对象，它是MFC库中的一个类，用于表示和处理字符串。
			2. `.Format`：这是`CString`类的一个成员函数，用于根据格式字符串和参数生成一个新的字符串。
			3. `_T("%1f")`：这是一个格式字符串，用于指定如何格式化要插入到字符串中的数据。
				- `%`：是一个格式指示符的前缀，它告诉`str.Format`函数接下来的是一个格式规范。
				 - `1`：这个数字指定了宽度，即输出字符串的最小宽度。如果实际数据不足这个宽度，会用空格填充。
				 - `f`：表示浮点数的格式。它告诉`str.Format`函数，要将一个浮点数格式化为字符串。
			4. `m_X`：这是某个类的成员变量，很可能是`float`或`double`类型的变量，它要被格式化为字符串并插入到`str`对象中。

			所以，整个表达式的意思是：将`m_X`变量的值格式化为一个浮点数，并且确保这个浮点数的字符串表示至少有1位宽度，不足的部分用空格填充。
			然后，这个格式化后的浮点数字符串将被插入到`str`对象中，最终返回一个新的字符串。
			例如，如果`m_X`的值是3.14159，那么`str`对象最终会包含字符串" 3.14159"。注意，输出字符串的前面有一个空格，这是因为格式字符串中有宽度为1的要求。*/
			MultiKeywordSortOutcome.SetItemText(item + i, 0, str);//设置（修改）列表项的文本内容

			str = pDoc->arr.m_PointArr[i].getName().c_str();
			/*`m_Operator`是一个`CString`类型的字符串，如果想要将其内容作为字符串输出应该使用`_T("%s")`作为格式指示符，因为`%s`用于格式化字符串。
			这样，`str.Format`会直接将`m_Operator`的内容复制到输出字符串中，而不进行任何格式化。
			下面示例代码：
			```cpp
			// 假设m_Operator是一个CString类型的变量
			CString m_Operator = _T("some text");
			// ...
			// 使用_T("%s")来格式化字符串
			str.Format(_T("%s"), m_Operator);
			```
			这段代码会将`m_Operator`的内容作为字符串输出到`str`对象中。例如，如果`m_Operator`的值是`_T("some text")`，那么`str`最终会包含字符串`"some text"`。

			请注意，如果使用的编译器或工具版本支持C++11或更高版本，你可以使用更简洁的方式来进行字符串连接，例如：
			```cpp
			str = m_Operator; // 直接将m_Operator的内容赋值给str
			```
			或者，如果你想要在字符串前面加上一些前缀或后缀，你可以这样做：
			```cpp
			str = _T("Prefix ") + m_Operator + _T(" Suffix");
			```
			这将会在`m_Operator`的内容前后分别加上"Prefix "和" Suffix"。*/	
			MultiKeywordSortOutcome.SetItemText(item + i, 1, str);

			str.Format(_T("%1f"), pDoc->arr.m_PointArr[i].getX());		
			MultiKeywordSortOutcome.SetItemText(item + i, 2, str);

			str.Format(_T("%1f"), pDoc->arr.m_PointArr[i].getY());		
			MultiKeywordSortOutcome.SetItemText(item + i, 3, str);

			str.Format(_T("%1f"), pDoc->arr.m_PointArr[i].getZ());
			MultiKeywordSortOutcome.SetItemText(item + i, 4, str);
		}
		UpdateData(FALSE);
	}
}


BOOL MultiKeywordSortDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
		
	wayFlag.SetCurSel(0);//下拉框默认选中某个选项,这里设置默认为第一个选项

	/*大一下 《遥感信息处理C++基础》 P209
	列表内添加五列表头，每列宽度为列表控件的1/5*/
	CRect rc; MultiKeywordSortOutcome.GetClientRect(&rc);
	MultiKeywordSortOutcome.InsertColumn(0, _T("点的序号"), LVCFMT_LEFT);
	MultiKeywordSortOutcome.InsertColumn(1, _T("点的名称"), LVCFMT_LEFT);
	MultiKeywordSortOutcome.InsertColumn(2, _T("x坐标"), LVCFMT_LEFT);
	MultiKeywordSortOutcome.InsertColumn(3, _T("y坐标"), LVCFMT_LEFT);
	MultiKeywordSortOutcome.InsertColumn(4, _T("z坐标"), LVCFMT_LEFT);
	MultiKeywordSortOutcome.SetColumnWidth(0, rc.Width() / 5);
	MultiKeywordSortOutcome.SetColumnWidth(1, rc.Width() / 5);
	MultiKeywordSortOutcome.SetColumnWidth(2, rc.Width() / 5);
	MultiKeywordSortOutcome.SetColumnWidth(3, rc.Width() / 5);
	MultiKeywordSortOutcome.SetColumnWidth(4, rc.Width() / 5);
	ListView_SetExtendedListViewStyle(MultiKeywordSortOutcome.m_hWnd, LVS_EX_GRIDLINES);

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}
