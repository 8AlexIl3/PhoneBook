#include "pch.h"
#include "PhoneBook.h"
#include "afxdialogex.h"
#include "CitiesDlg.h"
#include "CitiesData.h"

#include <regex> //included because of edit control value

// CCitiesDlg dialog

IMPLEMENT_DYNAMIC(CCitiesDlg, CDialogEx)

CCitiesDlg::CCitiesDlg(CWnd* pParent)
	: CDialogEx(IDD_DLG_CITIES, pParent)
{
}
CCitiesDlg::CCitiesDlg(const CITIES & oCity, CWnd * pParent)
	: CDialogEx(IDD_DLG_CITIES, pParent),
	m_initialCityName(oCity.szCityName),
	m_initialTownResidence(oCity.szTownResidence)
{
}

CCitiesDlg::~CCitiesDlg()
{
}

void CCitiesDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDB_CITIES_NAME, m_EdbName);
	DDX_Control(pDX, IDC_EDB_CITIES_RESIDENCE, m_EdbResidence);
}

BEGIN_MESSAGE_MAP(CCitiesDlg, CDialogEx)
END_MESSAGE_MAP()

void CCitiesDlg::OnOK() {
	UpdateData(TRUE);

	m_EdbName.GetWindowTextW(m_szCityName);
	m_EdbResidence.GetWindowTextW(m_szTownResidence);
	if (!ValidateData()) {
		return;
	}

	CDialogEx::OnOK();
}

BOOL CCitiesDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	m_EdbResidence.SetLimitText(CITY_FIELD_SIZE);
	m_EdbName.SetLimitText(CITY_FIELD_SIZE);
	m_EdbName.SetWindowTextW(m_initialCityName);
	m_EdbResidence.SetWindowTextW(m_initialTownResidence);
	UpdateData(TRUE);

	return TRUE;
}

void CCitiesDlg::Capitalize(CString& oString)
{
	//Capitilize first letter
	if (oString.GetAt(0) > L'Я') {
		oString.SetAt(0, oString.GetAt(0) - 0x20);
	}
	//LowerCase all others
	for (int lIndexer(1); lIndexer < oString.GetLength(); lIndexer++) {
		if (oString.GetAt(lIndexer) < L'а') {
			oString.SetAt(lIndexer, oString.GetAt(lIndexer) + 0x20);
		}
	}
}
const CString& CCitiesDlg::GetCityName()
{
	return m_szCityName;
}
const CString& CCitiesDlg::GetTownResidence()
{
	return m_szTownResidence;
}
BOOL CCitiesDlg::ValidateData() {
	CArray<CString> oErrors;
	std::wstring oPatternChecker;

	//oPattern that allows only bulgarian and whitespaces
	std::wregex oPattern(L"^[\\u0410-\\u044F\\s]+$");

	m_szCityName.Trim();

	oPatternChecker = m_szCityName.GetString();
	if (m_szCityName.IsEmpty()) {
		oErrors.Add(L"Грешка: въведете град");
	}
	else if (!std::regex_match(oPatternChecker, oPattern)) {
		oErrors.Add(CITY_BULGARIAN_TEXT_ERROR);
	}
	Capitalize(m_szCityName);

	m_szTownResidence.Trim();
	oPatternChecker = m_szTownResidence.GetString();
	if (m_szTownResidence.IsEmpty()) {
		oErrors.Add(L"Грешка: въведете област");
	}
	else if (!std::regex_match(oPatternChecker, oPattern)) {
		oErrors.Add(L"Грешка: въведете полето на областта с бълграски текст");
	}
	else if (m_szCityName == m_initialCityName &&
		m_szTownResidence == m_initialTownResidence) {
		oErrors.Add(L"Грешка: полетата за корекция са еднакви с първоначалните. Въвдете различни имена");
	}
	Capitalize(m_szTownResidence);
	if (!oErrors.IsEmpty()) {
		for (int lIndexer(0); lIndexer < oErrors.GetCount(); lIndexer++) {
			AfxMessageBox(oErrors.GetAt(lIndexer), MB_OK | MB_ICONEXCLAMATION);
		}

		return FALSE;
	}

	return TRUE;

}
