
#include "pch.h"
#include "PhoneBook.h"
#include "afxdialogex.h"
#include "PhoneTypesDlg.h"
#include <regex>

/////////////////////////////////////////////////////////////////////////////
// CPhoneTypesDlg

IMPLEMENT_DYNAMIC(CPhoneTypesDlg, CDialogEx)
BEGIN_MESSAGE_MAP(CPhoneTypesDlg, CDialogEx)
END_MESSAGE_MAP()


// Constructor / Destructor
// ----------------
CPhoneTypesDlg::CPhoneTypesDlg(bool editPermission/*=true*/, CWnd* pParent/*=nullptr*/)
	: CDialogEx(IDD_DLG_PHONE_TYPES, pParent),
	m_bEditPermission(editPermission)
{
	m_pPhoneType = &m_oPhoneType;
}

CPhoneTypesDlg::CPhoneTypesDlg(PHONE_TYPES& oPhoneTypes,bool bEditPermission, CWnd* pParent/*=nullptr*/)
	: CDialogEx(IDD_DLG_PHONE_TYPES, pParent),
	m_pPhoneType(&oPhoneTypes),
	m_oPhoneType(oPhoneTypes),
	m_bEditPermission(bEditPermission)
{
}

CPhoneTypesDlg::~CPhoneTypesDlg()
{
}

void CPhoneTypesDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDB_PHONE_TYPE, m_EdbPhoneType);
}


//MFC Overrides
// ----------------
void CPhoneTypesDlg::OnOK()
{
	if (!m_bEditPermission);

	else if (!ValidateData())
		return;

	CDialogEx::OnOK();
}

BOOL CPhoneTypesDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	if (!m_bEditPermission) {
		m_EdbPhoneType.EnableWindow(false);
	}
	m_EdbPhoneType.SetLimitText(PHONE_TYPE_SIZE);
	m_EdbPhoneType.SetWindowTextW(m_oPhoneType.szPhoneType);

	return TRUE;
}
//MFC Methods
// ----------------
bool CPhoneTypesDlg::ValidateData() {
	std::wstring oPatternChecker;
	CString strPhoneTypeGetter;
	m_EdbPhoneType.GetWindowTextW(strPhoneTypeGetter);

	//oPattern that allows only bulgarian and whitespaces
	std::wregex oPattern(L"^[\\u0410-\\u044F\\s]+$");

	strPhoneTypeGetter.Trim();

	oPatternChecker = strPhoneTypeGetter.GetString();
	if (strPhoneTypeGetter.IsEmpty()) {
		AfxMessageBox(EMPTY_PHONE_TYPE_FIELD);
		return FALSE;
	}

	else if (!std::regex_match(oPatternChecker, oPattern)) {
		AfxMessageBox(USE_PHONE_TYPE_FIELD_WITH_BULGARIAN_TEXT);
		return FALSE;
	}
	else if (!_tcscmp(m_pPhoneType->szPhoneType, strPhoneTypeGetter)) {
		AfxMessageBox(SAME_TEXT_AS_INITIAL);
		return FALSE;

	}

	Capitalize(strPhoneTypeGetter);

	_tcscpy_s(m_pPhoneType->szPhoneType, strPhoneTypeGetter);

	return TRUE;

}

void CPhoneTypesDlg::Capitalize(CString& oString)
{
	//Capitilize first letter
	if (oString.GetAt(0) > L'ß')
		oString.SetAt(0, oString.GetAt(0) - 0x20);
	//LowerCase all others
	for (long lIndexer(1); (int)lIndexer < oString.GetLength(); lIndexer++)
		if (oString.GetAt(lIndexer) < L'à')
			oString.SetAt(lIndexer, oString.GetAt(lIndexer) + 0x20);

}

PHONE_TYPES* CPhoneTypesDlg::GetPhoneType()
{
	return m_pPhoneType;
}

