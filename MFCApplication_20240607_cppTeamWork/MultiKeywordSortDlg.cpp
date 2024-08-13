// MultiKeywordSortDlg.cpp: 实现文件
//

#include "pch.h"
#include "MFCApplication_20240607_cppTeamWork.h"
#include "afxdialogex.h"
#include "MultiKeywordSortDlg.h"
#include "MFCApplication_20240607_cppTeamWorkDoc.h"
#include <vector>
using namespace std;

//使用快速排序——
////快速排序的分区函数
//int partitionX(Point arr[], int low, int high) {
//	// 选择最右侧的元素作为基准
//	Point pivot = arr[high];
//	int i = (low - 1);
//
//	for (int j = low; j <= high - 1; j++) {
//		// 如果当前元素小于或等于基准
//		if (arr[j].getX() <= pivot.getX()) {
//			i++;
//			// 交换 arr[i] 和 arr[j]
//			swap(arr[i], arr[j]);
//		}
//	}
//	// 交换 pivot 到它最终的位置
//	swap(arr[i + 1], arr[high]);
//	return (i + 1);
//}
//int partitionY(Point arr[], int low, int high) {
//	// 选择最右侧的元素作为基准
//	Point pivot = arr[high];
//	int i = (low - 1);
//
//	for (int j = low; j <= high - 1; j++) {
//		// 如果当前元素小于或等于基准
//		if (arr[j].getY() <= pivot.getY()) {
//			i++;
//			// 交换 arr[i] 和 arr[j]
//			swap(arr[i], arr[j]);
//		}
//	}
//	// 交换 pivot 到它最终的位置
//	swap(arr[i + 1], arr[high]);
//	return (i + 1);
//}
//int partitionZ(Point arr[], int low, int high) {
//	// 选择最右侧的元素作为基准
//	Point pivot = arr[high];
//	int i = (low - 1);
//
//	for (int j = low; j <= high - 1; j++) {
//		// 如果当前元素小于或等于基准
//		if (arr[j].getZ() <= pivot.getZ()) {
//			i++;
//			// 交换 arr[i] 和 arr[j]
//			swap(arr[i], arr[j]);
//		}
//	}
//	// 交换 pivot 到它最终的位置
//	swap(arr[i + 1], arr[high]);
//	return (i + 1);
//}
////快速排序
//void quickSort(Point R[], int low, int high, int m) {
//	int n = high + 1;
//	switch (m) {
//	case 1:
//	{
//		if (low < high) {
//			// pi 是分区索引，arr[pi] 现在处在正确的位置
//			int pi = partitionX(R, low, high);
//
//			// 分别对左右分区进行排序
//			quickSort(R, low, pi - 1, m);
//			quickSort(R, pi + 1, high, m);
//		}
//		break;
//	}
//	case 2:
//	{
//		if (low < high) {
//			// pi 是分区索引，arr[pi] 现在处在正确的位置
//			int pi = partitionY(R, low, high);
//
//			// 分别对左右分区进行排序
//			quickSort(R, low, pi - 1, m);
//			quickSort(R, pi + 1, high, m);
//		}
//		break;
//	}
//	case 3:
//	{
//		if (low < high) {
//			// pi 是分区索引，arr[pi] 现在处在正确的位置
//			int pi = partitionZ(R, low, high);
//
//			// 分别对左右分区进行排序
//			quickSort(R, low, pi - 1, m);
//			quickSort(R, pi + 1, high, m);
//		}
//		break;
//	}
//	case 12:
//	{
//		if (low < high) {
//			// 使用按 x 和 y 的多关键字排序
//			int pi = partitionXY(R, low, high);
//
//			// 分别对左右分区进行排序
//			quickSort(R, low, pi - 1, m);
//			quickSort(R, pi + 1, high, m);
//		}
//		break;
//	}
//	}
//}
//// 辅助函数，用于合并两个已排序的数组
//void mergeX(PointArr& arr, int l, int m, int r, int kk) {
//	int n1 = m - l + 1;
//	int n2 = r - m;
//
//	// 创建临时数组
//	vector<Point> L(n1), R(n2);
//
//	// 复制数据到临时数组
//	for (int i = 0; i < n1; i++) {
//		L[i] = arr.m_PointArr[l + i];
//	}
//	for (int j = 0; j < n2; j++) {
//		R[j] = arr.m_PointArr[m + 1 + j];
//	}
//
//	// 合并临时数组
//	int i = 0, j = 0;
//	int k = l;
//	while (i < n1 && j < n2) {
//		if (L[i].getX() <= R[j].getX()) {
//			arr.m_PointArr[k] = L[i];
//			i++;
//		}
//		else {
//			arr.m_PointArr[k] = R[j];
//			j++;
//		}
//		k++;
//	}
//
//	// 复制剩余的元素
//	while (i < n1) {
//		arr.m_PointArr[k] = L[i];
//		i++;
//		k++;
//	}
//
//	while (j < n2) {
//		arr.m_PointArr[k] = R[j];
//		j++;
//		k++;
//	}
//}
//void mergeY(PointArr& arr, int l, int m, int r, int kk) {
//	int n1 = m - l + 1;
//	int n2 = r - m;
//
//	// 创建临时数组
//	vector<Point> L(n1), R(n2);
//
//	// 复制数据到临时数组
//	for (int i = 0; i < n1; i++) {
//		L[i] = arr.m_PointArr[l + i];
//	}
//	for (int j = 0; j < n2; j++) {
//		R[j] = arr.m_PointArr[m + 1 + j];
//	}
//
//	// 合并临时数组
//	int i = 0, j = 0;
//	int k = l;
//	while (i < n1 && j < n2) {
//		if (L[i].getY() <= R[j].getY()) {
//			arr.m_PointArr[k] = L[i];
//			i++;
//		}
//		else {
//			arr.m_PointArr[k] = R[j];
//			j++;
//		}
//		k++;
//	}
//
//	// 复制剩余的元素
//	while (i < n1) {
//		arr.m_PointArr[k] = L[i];
//		i++;
//		k++;
//	}
//
//	while (j < n2) {
//		arr.m_PointArr[k] = R[j];
//		j++;
//		k++;
//	}
//}
//void mergeZ(PointArr& arr, int l, int m, int r, int kk) {
//	int n1 = m - l + 1;
//	int n2 = r - m;
//
//	// 创建临时数组
//	vector<Point> L(n1), R(n2);
//
//	// 复制数据到临时数组
//	for (int i = 0; i < n1; i++) {
//		L[i] = arr.m_PointArr[l + i];
//	}
//	for (int j = 0; j < n2; j++) {
//		R[j] = arr.m_PointArr[m + 1 + j];
//	}
//
//	// 合并临时数组
//	int i = 0, j = 0;
//	int k = l;
//	while (i < n1 && j < n2) {
//		if (L[i].getZ() <= R[j].getZ()) {
//			arr.m_PointArr[k] = L[i];
//			i++;
//		}
//		else {
//			arr.m_PointArr[k] = R[j];
//			j++;
//		}
//		k++;
//	}
//
//	// 复制剩余的元素
//	while (i < n1) {
//		arr.m_PointArr[k] = L[i];
//		i++;
//		k++;
//	}
//
//	while (j < n2) {
//		arr.m_PointArr[k] = R[j];
//		j++;
//		k++;
//	}
//}
// 通用的排序函数模板

template<typename T, typename... Keys>
bool compare(const Point& a, const Point& b, T(Point::* key)() const, Keys... keys) {
	if ((a.*key)() < (b.*key)()) {
		return true;
	}
	if ((a.*key)() > (b.*key)()) {
		return false;
	}
	if constexpr (sizeof...(keys) == 0) {
		return false;
	}
	else {
		return compare(a, b, keys...);
	}
}
// 快速排序的分区函数
template<typename... Keys>
int partition(Point R[], int low, int high, Keys... keys) {
	Point pivot = R[high];
	int i = low - 1;

	for (int j = low; j <= high - 1; j++) {
		if (compare(R[j], pivot, keys...)) {
			i++;
			std::swap(R[i], R[j]);
		}
	}
	std::swap(R[i + 1], R[high]);
	return i + 1;
}
// 快速排序函数
template<typename... Keys>
void quickSort(Point R[], int low, int high, Keys... keys) {
	if (low < high) {
		int pi = partition(R, low, high, keys...);
		quickSort(R, low, pi - 1, keys...);
		quickSort(R, pi + 1, high, keys...);
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
int chooseSortKeyworf(PointArr& arr, CString str1,int& n)
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
		quickSort(arr.m_PointArr, 0, arr.m_Num - 1, &Point::getX);
		break;
	}
	case 2:
	{
		quickSort(arr.m_PointArr, 0, arr.m_Num - 1, &Point::getY);
		break;
	}
	case 3:
	{
		quickSort(arr.m_PointArr, 0, arr.m_Num - 1, &Point::getZ);
		break;
	}
	case 12:
	{
		quickSort(arr.m_PointArr, 0, arr.m_Num - 1, &Point::getX, &Point::getY);
		break;
	}
	case 13:
	{
		quickSort(arr.m_PointArr, 0, arr.m_Num - 1, &Point::getX, &Point::getZ);
		break;
	}
	case 23:
	{
		quickSort(arr.m_PointArr, 0, arr.m_Num - 1, &Point::getY, &Point::getZ);
		break;
	}
	case 21:
	{
		quickSort(arr.m_PointArr, 0, arr.m_Num - 1, &Point::getY, &Point::getX);
	}
	case 31:
	{
		quickSort(arr.m_PointArr, 0, arr.m_Num - 1, &Point::getZ, &Point::getX);
		break;
	}
	case 32:
	{
		quickSort(arr.m_PointArr, 0, arr.m_Num - 1, &Point::getZ, &Point::getY);
		break;
	case 123:
	{
		quickSort(arr.m_PointArr, 0, arr.m_Num - 1, &Point::getX, &Point::getY, &Point::getZ);
		break;
	}
	case 132:
	{
		quickSort(arr.m_PointArr, 0, arr.m_Num - 1, &Point::getX, &Point::getZ, &Point::getY);
		break;
	}
	case 231:
	{
		quickSort(arr.m_PointArr, 0, arr.m_Num - 1, &Point::getY, &Point::getZ, &Point::getX);
		break;
	}
	case 213:
	{
		quickSort(arr.m_PointArr, 0, arr.m_Num - 1, &Point::getY, &Point::getX, &Point::getZ);
		break;
	}
	case 312:
	{
		quickSort(arr.m_PointArr, 0, arr.m_Num - 1, &Point::getZ, &Point::getX, &Point::getY);
		break;
	}
	case 321:
	{
		quickSort(arr.m_PointArr, 0, arr.m_Num - 1, &Point::getZ, &Point::getY, &Point::getX);
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
}


BEGIN_MESSAGE_MAP(MultiKeywordSortDlg, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON1, &MultiKeywordSortDlg::OnBnClickedButtonMultiKeywordSort)
END_MESSAGE_MAP()


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

		//再来处理输入的表示排序规则的字符串
		if (chooseSortKeyworf(pDoc->arr, WantedSortRule, pDoc->arrMultiSortRuleCode)==-1)
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
