#include "pch.h"
#include "PhoneBook.h"
#include "afxdialogex.h"
#include "CCitiesDlg.h"
#include "CitiesData.h"

#include <regex> //included because of edit control value

// CCitiesDlg dialog

IMPLEMENT_DYNAMIC(CCitiesDlg, CDialogEx)

CCitiesDlg::CCitiesDlg(CWnd* pParent /*=nullptr*/, const CString& cityName, const CString& townResidence)
	: CDialogEx(IDD_DLG_CITIES, pParent), m_initialCityName(cityName), m_initialTownResidence(townResidence)
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
BOOL CCitiesDlg::ValidateData() {
	CArray<CString> oErrors;
	std::wstring oPatternChecker;

	//oPattern that allows only bulgarian and whitespaces
	std::wregex oPattern(L"^[\\u0400-\\u04FF\\s]+$");

	m_szCityName.Trim();

	oPatternChecker = m_szCityName.GetString();
	if (m_szCityName.IsEmpty()) {
		oErrors.Add(L"Грешка: въведете град");
	}
	else if (!std::regex_match(oPatternChecker, oPattern)) {
		oErrors.Add(L"Грешка: въведете полето на града с бълграски текст");
	}

	m_szTownResidence.Trim();

	oPatternChecker = m_szTownResidence.GetString();
	if (m_szTownResidence.IsEmpty()) {
		oErrors.Add(L"Грешка: въведете област");
	}
	else if (!std::regex_match(oPatternChecker, oPattern)) {
		oErrors.Add(L"Грешка: въведете полето на областта с бълграски текст");
	}
	else if (m_szCityName== m_initialCityName &&
		m_szTownResidence == m_initialTownResidence) {
		oErrors.Add(L"Грешка: полетата за корекция са еднакви с първоначалните. Въвдете различни имена");
	}

	if (!oErrors.IsEmpty()) {
		for (int indexer(0); indexer < oErrors.GetSize(); indexer++) {
			AfxMessageBox(oErrors.GetAt(indexer), MB_OK | MB_ICONEXCLAMATION);
		}

		return FALSE;
	}

	return TRUE;

}
