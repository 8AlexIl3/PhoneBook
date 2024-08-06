// PersonsDlg.cpp : implementation file
//

#include "pch.h"
#include "PhoneBook.h"
#include "afxdialogex.h"
#include "PersonsDlg.h"

#include <regex>


// CPersonsDlg dialog

IMPLEMENT_DYNAMIC(CPersonsDlg, CDialogEx)
BEGIN_MESSAGE_MAP(CPersonsDlg, CDialogEx)
	ON_COMMAND(IDC_BTN_ADD_NUMBER, &CPersonsDlg::onInsertNumber)
	ON_COMMAND(IDC_BTN_UPDATE_NUMBER, &CPersonsDlg::onUpdateNumber)
	ON_COMMAND(IDC_BTN_DELETE_NUMBER, &CPersonsDlg::onDeleteNumber)
END_MESSAGE_MAP()

CPersonsDlg::CPersonsDlg( CCitiesArray& oCitiesArray, CPhoneTypesArray* pPhoneTypes,
	CPerson* pPerson /*nullptr*/, CWnd* pParent /*nullptr*/)
	: CDialogEx(IDD_DLG_PERSONS, pParent),
	m_pPerson(pPerson),
	m_pCitiesArray(&oCitiesArray),
	m_pPhoneTypes(pPhoneTypes)
	
{
	bAllocatedCity = false;
}

CPersonsDlg::~CPersonsDlg()
{
	m_pCitiesArray = nullptr;
	m_pPerson = nullptr;
}

bool CPersonsDlg::ValidateData()
{
	CArray<CString> oErrors;
	std::wstring oPatternChecker;
	CString strFirstName;
	CString strSurname;
	CString strLastName;
	CString strEGN;
	CString strAdress;
	m_EdbFirstName.GetWindowTextW(strFirstName);
	m_EdbSurname.GetWindowTextW(strSurname);
	m_EdbLastName.GetWindowTextW(strLastName);
	m_EdbEGN.GetWindowTextW(strEGN);
	m_EdbAddress.GetWindowTextW(strAdress);

	std::wregex oSymbolsOnly(L"^[\\u0410-\\u044F\\s]+$");
	std::wregex oNumbersOnly(L"^[\\u0030-\\u0039\\s]+$");
	std::wregex oPatternMixed(L"^[\\u0410-\\u044F\\u0030-\\u0039\\s\\.]+$");

	if (!IsStringValid(oSymbolsOnly, strFirstName)) {
		oErrors.Add(L"Въведете име на български");
		return false;
	}
	if(!IsStringValid(oSymbolsOnly, strSurname)) {
		oErrors.Add(L"Въведете презиме на български");
		return false;
	}
	if(!IsStringValid(oSymbolsOnly, strLastName)) {
		oErrors.Add(L"Въведете фамилия на български");
		return false;
	}
	if(!IsStringValid(oNumbersOnly, strEGN)) {
		oErrors.Add(L"Въведете егн");
		return false;
	}
	if(!IsStringValid(oPatternMixed, strAdress)) {
		oErrors.Add(L"Въведете адрес на български");
		return false;
	}

	if (!oErrors.IsEmpty()) {
		for (long lIndexer(0); (INT_PTR)lIndexer < oErrors.GetCount(); lIndexer++) {
			AfxMessageBox(oErrors.GetAt(lIndexer), MB_OK | MB_ICONEXCLAMATION);
		}

		return FALSE;
	}

	_tcscpy_s(m_pPerson->m_oRecPerson.szAddress, strAdress);
	_tcscpy_s(m_pPerson->m_oRecPerson.szEGN, strEGN);
	_tcscpy_s(m_pPerson->m_oRecPerson.szLastName, strLastName);
	_tcscpy_s(m_pPerson->m_oRecPerson.szSurname, strSurname);
	_tcscpy_s(m_pPerson->m_oRecPerson.szFirstName, strFirstName);

	int nCursel= m_CmbCities.GetCurSel();

	long lCityID= (long) m_CmbCities.GetItemData(nCursel);
	m_pPerson->m_oRecPerson.lCityID = lCityID;
	return TRUE;

}

void CPersonsDlg::DisplayData()
{

	for (INT_PTR nIndexer(0); nIndexer < m_pPerson->m_oPhoneNumbersArray.GetCount(); ++nIndexer)
	{
		PHONE_NUMBERS oPhoneNumber = *m_pPerson->GetPhoneNumbers().GetAt(nIndexer);
			CString strID;
			strID.Format(_T("%ld"), oPhoneNumber.lPhoneTypeID);
			m_LscPhoneNumbers.InsertItem((int)nIndexer, strID);
			m_LscPhoneNumbers.SetItemText((int)nIndexer, 0, oPhoneNumber.szPhone);
		
	}
}

bool CPersonsDlg::IsStringValid(const std::wregex& oPattern, CString& strArg)
{
	strArg.Trim();

	if (strArg.IsEmpty()) {
		return false;
	}

	std::wstring oPatternChecker = strArg.GetString();

	if (!std::regex_match(oPatternChecker, oPattern)) {
		return false;
	}

	return true;
}

void CPersonsDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDB_ADDRESS, m_EdbAddress);
	DDX_Control(pDX, IDC_EDB_SURNAME, m_EdbSurname);
	DDX_Control(pDX, IDC_EDB_EGN, m_EdbEGN);
	DDX_Control(pDX, IDC_EDB_LAST_NAME, m_EdbLastName);
	DDX_Control(pDX, IDC_EDB_FIRST_NAME, m_EdbFirstName);
	DDX_Control(pDX, IDC_LSC_PHONE_NUMBERS, m_LscPhoneNumbers);
	DDX_Control(pDX, IDC_CMB_CITIES, m_CmbCities);
}

// CPersonsDlg message handlers

void CPersonsDlg::onInsertNumber()
{
	CPhoneNumbersDlg oPhoneNumbersdlg(m_pPhoneTypes);

	if (oPhoneNumbersdlg.DoModal() == IDCANCEL) {
		return;
	}
	PHONE_NUMBERS oPhoneNumbers;

	oPhoneNumbers = oPhoneNumbersdlg.GetNumber();

	int nCount= m_LscPhoneNumbers.GetItemCount();

	m_LscPhoneNumbers.InsertItem(nCount, oPhoneNumbers.szPhone);

	CString strPhoneType;

	strPhoneType.Format(L"%d", oPhoneNumbers.lPhoneTypeID);
	m_LscPhoneNumbers.SetItemText(nCount, 1, strPhoneType);
	
	PHONE_NUMBERS* pPhoneNumbers = new PHONE_NUMBERS(oPhoneNumbers);

	m_pPerson->m_oPhoneNumbersArray.Add(pPhoneNumbers);

}

void CPersonsDlg::onUpdateNumber()
{
	POSITION pos = m_LscPhoneNumbers.GetFirstSelectedItemPosition();
	if (!pos)
		return;

	int lIndexer = m_LscPhoneNumbers.GetNextSelectedItem(pos);
	if (lIndexer == -1)
		return;

	PHONE_NUMBERS* pPhoneNumbers= m_pPerson->
		m_oPhoneNumbersArray.GetAt((INT_PTR)lIndexer);

	CPhoneNumbersDlg oPhoneNumbersdlg(m_pPhoneTypes, pPhoneNumbers);
	if (oPhoneNumbersdlg.DoModal() == IDCANCEL) {
		return;
	}

	pPhoneNumbers = &oPhoneNumbersdlg.GetNumber();

	m_LscPhoneNumbers.SetItemText(lIndexer, 0, pPhoneNumbers->szPhone);

	CString strPhoneType;
	strPhoneType.Format(_T("%d"), pPhoneNumbers->lPhoneTypeID);
	m_LscPhoneNumbers.SetItemText(lIndexer, 1, strPhoneType);

	m_LscPhoneNumbers.Update(lIndexer);

}
void CPersonsDlg::onDeleteNumber()
{
	
	POSITION pos = m_LscPhoneNumbers.GetFirstSelectedItemPosition();
	if (!pos)
		return;

	int nIndexer = m_LscPhoneNumbers.GetNextSelectedItem(pos);
	if (nIndexer == -1)
		return;

	int nCount = m_LscPhoneNumbers.GetItemCount();
	if (nCount == 1) {
		AfxMessageBox(L"Трябва да има поне един телефон");
		return;
	}

	CString strNumberToDelete = m_LscPhoneNumbers.GetItemText(nIndexer, 0);

	for (long lIndexer(0); lIndexer < m_pPerson->m_oPhoneNumbersArray.GetCount(); lIndexer++) {
		PHONE_NUMBERS A=*m_pPerson->m_oPhoneNumbersArray.GetAt(lIndexer);
		if (!_tcscmp(A.szPhone, strNumberToDelete)) {
			_tcscpy_s(m_pPerson->m_oPhoneNumbersArray.GetAt(lIndexer)->szPhone,EMPTY_NUMBER);
		}
	}
	m_LscPhoneNumbers.DeleteItem(nIndexer);
}

void CPersonsDlg::OnOK()
{
	if (!ValidateData()) {
		return;
	}
	if (!m_LscPhoneNumbers.GetItemCount()) {
		AfxMessageBox(L"Абонатът трябва да има поне един номер");
		return;
	}
	CDialogEx::OnOK();
}

CPerson& CPersonsDlg::GetPerson()
{
	return *m_pPerson;
}


BOOL CPersonsDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	m_LscPhoneNumbers.ModifyStyle(0, LVS_REPORT | LVS_SINGLESEL);
	m_LscPhoneNumbers.SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
	m_LscPhoneNumbers.InsertColumn(0, _T("Телефон"), LVCFMT_CENTER, 250);
	m_LscPhoneNumbers.InsertColumn(1, _T("План"), LVCFMT_LEFT, 250);

	if (!m_pPerson) {
		bAllocatedCity = true;
		m_pPerson = new CPerson;
	}
	if (!m_pPerson) {
		AfxMessageBox(L"Не може да се зареди диалог за човек");
	}
		m_EdbAddress.SetWindowTextW(m_pPerson->m_oRecPerson.szAddress);
		m_EdbSurname.SetWindowTextW(m_pPerson->m_oRecPerson.szSurname);
		m_EdbEGN.SetWindowTextW(m_pPerson->m_oRecPerson.szEGN);
		m_EdbLastName.SetWindowTextW(m_pPerson->m_oRecPerson.szLastName);
		m_EdbFirstName.SetWindowTextW(m_pPerson->m_oRecPerson.szFirstName);


		for (INT_PTR nIndexer(0); nIndexer < m_pCitiesArray->GetCount(); nIndexer++) {

			CITIES oCities = *m_pCitiesArray->GetAt(nIndexer);

			CString strCityName = oCities.szCityName;
			CString strResidenceName = oCities.szTownResidence;

			CString strCityOption;
			strCityOption.Format(L"%s (област %s)", strCityName, strResidenceName);
			m_CmbCities.AddString(strCityOption);
			m_CmbCities.SetItemData((int)nIndexer, oCities.lID);

			if (oCities.lID == m_pPerson->m_oRecPerson.lCityID) {
				m_CmbCities.SetCurSel((int)nIndexer);
			}
		}

		for (INT_PTR nIndexer(0); nIndexer < m_pPerson->m_oPhoneNumbersArray.GetCount(); nIndexer++) {

			PHONE_NUMBERS oPhoneNumbers = *m_pPerson->m_oPhoneNumbersArray.GetAt(nIndexer);

			m_LscPhoneNumbers.InsertItem((int)nIndexer, oPhoneNumbers.szPhone);

			CString strTypeID;
			strTypeID.Format((L"%d"), oPhoneNumbers.lPhoneTypeID);
			m_LscPhoneNumbers.SetItemText((int)nIndexer, 1, strTypeID);


		}
	return TRUE;
}


void CPersonsDlg::OnCancel()
{
	if (bAllocatedCity) {
		delete m_pPerson;
	}
	CDialogEx::OnCancel();
}
