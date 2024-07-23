 // CCitiesDlg.cpp : implementation file
//

#include "pch.h"
#include "PhoneBook.h"
#include "afxdialogex.h"
#include "CCitiesDlg.h"
#include "CitiesData.h"


// CCitiesDlg dialog

IMPLEMENT_DYNAMIC(CCitiesDlg, CDialogEx)

CCitiesDlg::CCitiesDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DLG_CITIES, pParent)
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
	DDX_Control(pDX, IDC_LSC_CITIES, m_ListControl);
}


BEGIN_MESSAGE_MAP(CCitiesDlg, CDialogEx)
END_MESSAGE_MAP()


// CCitiesDlg message handlers
void CCitiesDlg::OnOK() {
	UpdateData(TRUE);

	m_EdbName.GetWindowTextW(m_szCityName);
	m_EdbResidence.GetWindowTextW(m_szTownResidence);
	

	CDialogEx::OnOK();
}
BOOL CCitiesDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	m_EdbResidence.SetLimitText(CITY_FIELD_SIZE);
	m_EdbName.SetLimitText(CITY_FIELD_SIZE);
	m_EdbName.SetWindowTextW(L"Varna");
	m_EdbResidence.SetWindowTextW(L"Varna");
	UpdateData(TRUE);
	return TRUE;
}

