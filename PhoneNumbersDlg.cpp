// PhoneNumbersDlg.cpp : implementation file
//

#include "pch.h"
#include "PhoneBook.h"
#include "afxdialogex.h"
#include "PhoneNumbersDlg.h"


// CPhoneNumbersDlg dialog

IMPLEMENT_DYNAMIC(CPhoneNumbersDlg, CDialogEx)

CPhoneNumbersDlg::CPhoneNumbersDlg(CPhoneTypesArray* oPhoneTypeArray,PHONE_NUMBERS* oPhoneNumbers/*=nullptr*/, CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DLG_PHONE_NUMBERS, pParent),
	m_pPhoneNumbers(oPhoneNumbers),
	m_pPhoneTypeArray(oPhoneTypeArray)
{

}

CPhoneNumbersDlg::~CPhoneNumbersDlg()
{
	m_pPhoneNumbers = nullptr;
	m_pPhoneTypeArray = nullptr;
}

void CPhoneNumbersDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDB_PHONE_NUMBER, m_EdbPhoneNumber);
	DDX_Control(pDX, IDC_CMB_PHONE_TYPE, m_CmbPhoneType);
}


BEGIN_MESSAGE_MAP(CPhoneNumbersDlg, CDialogEx)
END_MESSAGE_MAP()


// CPhoneNumbersDlg message handlers


PHONE_NUMBERS& CPhoneNumbersDlg::GetNumber()
{
	return *m_pPhoneNumbers;
}

BOOL CPhoneNumbersDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	m_EdbPhoneNumber.SetLimitText(10);
	m_EdbPhoneNumber.SetCueBanner(L"0987654321",1);
	for (INT_PTR nIndexer(0); nIndexer < m_pPhoneTypeArray->GetCount(); nIndexer++) {
		PHONE_TYPES oPhoneTypes= *m_pPhoneTypeArray->GetAt(nIndexer);
		m_CmbPhoneType.AddString(oPhoneTypes.szPhoneType);
		m_CmbPhoneType.SetItemData((int)nIndexer, oPhoneTypes.lID);

		if(m_pPhoneNumbers!=nullptr)

		if (oPhoneTypes.lID == m_pPhoneNumbers->lPhoneTypeID) {
			m_CmbPhoneType.SetCurSel((int)nIndexer);
		}
	}

	return TRUE;
}


void CPhoneNumbersDlg::OnOK()
{
	CString strPhoneNumber;	
	m_EdbPhoneNumber.GetWindowTextW(strPhoneNumber);
	if (strPhoneNumber.IsEmpty()) {
		//prompt user to enter a phone number
		return;
	}
	int nIndexer=m_CmbPhoneType.GetCurSel();

	if (nIndexer == CB_ERR) {
		//prompt user to select a phone nubmer
		return;
	}
	
	//in case we are trying to write to null
	//(happens when we call the constructor with nullptr)
	bool bAllocated=false;
	if (!m_pPhoneNumbers) {
		m_pPhoneNumbers = new PHONE_NUMBERS;
		bAllocated = true;
	}
	_tcscpy_s(m_pPhoneNumbers->szPhone, strPhoneNumber);
	if (m_pPhoneNumbers->szPhone[0] != L'0') {
		return;
	}
	m_pPhoneNumbers->lPhoneTypeID = (int)m_CmbPhoneType.GetItemData(nIndexer);

	CDialogEx::OnOK();
}
