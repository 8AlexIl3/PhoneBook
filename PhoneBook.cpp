
// PhoneBook.cpp : Defines the class behaviors for the application.
//

#include "pch.h"
#include "framework.h"
#include "afxwinappex.h"
#include "afxdialogex.h"
#include "PhoneBook.h"
#include "MainFrm.h"
#include "ChildFrm.h"
#include "CitiesDocument.h"
#include "PersonsDocument.h"
#include "CitiesView.h"
#include "PersonsView.h"
#include "CitiesTable.h"
#include "CitiesDlg.h"
#include "PhoneTypesDocument.h"
#include "PhoneTypesView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CPhoneBookApp

BEGIN_MESSAGE_MAP(CPhoneBookApp, CWinAppEx)
	ON_COMMAND(ID_APP_ABOUT, &CPhoneBookApp::OnAppAbout)
	ON_COMMAND(ID_FILE_NEW_PERSONS, &CPhoneBookApp::OnFileNewPersons)
	ON_COMMAND(ID_FILE_NEW_CITIES, &CPhoneBookApp::OnFileNewCities)
	ON_COMMAND(ID_FILE_NEW_PHONE_TYPES, &CPhoneBookApp::OnFileNewPhoneTypes)
	ON_COMMAND(ID_FILE_OPEN, &CWinAppEx::OnFileOpen)
	ON_COMMAND(ID_FILE_NEW, &CWinAppEx::OnFileNew)

END_MESSAGE_MAP()


// CPhoneBookApp construction

CPhoneBookApp::CPhoneBookApp() noexcept
{
	pPersonsTemplate=nullptr;
	pCitiesTemplate= nullptr;
	pPhoneTypesTemplate= nullptr;

	m_bHiColorIcons = TRUE;
	
	m_nAppLook = 0;
	// TODO: replace application ID string below with unique ID string; recommended
	// format for string is CompanyName.ProductName.SubProduct.VersionInformation
	SetAppID(_T("PhoneBook.AppID.NoVersion"));

	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}

// The one and only CPhoneBookApp object

CPhoneBookApp theApp;


// CPhoneBookApp initialization

BOOL CPhoneBookApp::InitInstance()
{
	// InitCommonControlsEx() is required on Windows XP if an application
	// manifest specifies use of ComCtl32.dll version 6 or later to enable
	// visual styles.  Otherwise, any window creation will fail.
	INITCOMMONCONTROLSEX InitCtrls;
	InitCtrls.dwSize = sizeof(InitCtrls);
	// Set this to include all the common control classes you want to use
	// in your application.
	InitCtrls.dwICC = ICC_WIN95_CLASSES;
	InitCommonControlsEx(&InitCtrls);

	CWinAppEx::InitInstance();


	// Initialize OLE libraries
	if (!AfxOleInit())
	{
		AfxMessageBox(IDP_OLE_INIT_FAILED);
		return FALSE;
	}

	AfxEnableControlContainer();

	EnableTaskbarInteraction();

	// AfxInitRichEdit2() is required to use RichEdit control
	// AfxInitRichEdit2();

	// Standard initialization
	// If you are not using these features and wish to reduce the size
	// of your final executable, you should remove from the following
	// the specific initialization routines you do not need
	// Change the registry key under which our settings are stored
	// TODO: You should modify this string to be something appropriate
	// such as the name of your company or organization
	SetRegistryKey(_T("Local AppWizard-Generated Applications"));
	LoadStdProfileSettings(4);  // Load standard INI file options (including MRU)


	InitContextMenuManager();

	InitKeyboardManager();

	InitTooltipManager();
	CMFCToolTipInfo ttParams;
	ttParams.m_bVislManagerTheme = TRUE;
	theApp.GetTooltipManager()->SetTooltipParams(AFX_TOOLTIP_TYPE_ALL,
		RUNTIME_CLASS(CMFCToolTipCtrl), &ttParams);

	// Register the application's document templates.  Document templates
	//  serve as the connection between documents, frame windows and views
	pPersonsTemplate = new CMultiDocTemplate(IDR_PersonsTYPE,
			RUNTIME_CLASS(CPersonsDocument),
			RUNTIME_CLASS(CChildFrame),
			RUNTIME_CLASS(CPersonsView));

	 pCitiesTemplate = new CMultiDocTemplate(IDR_CitiesTYPE,
		RUNTIME_CLASS(CCitiesDocument),
		RUNTIME_CLASS(CChildFrame),
		RUNTIME_CLASS(CCitiesView));

	pPhoneTypesTemplate = new CMultiDocTemplate(IDR_PhoneTypesTYPE,
		RUNTIME_CLASS(CPhoneTypesDocument),
		RUNTIME_CLASS(CChildFrame),
		RUNTIME_CLASS(CPhoneTypesView));

	if (!pPersonsTemplate || !pCitiesTemplate || !pPhoneTypesTemplate)
		return FALSE;

	AddDocTemplate(pPersonsTemplate);
	AddDocTemplate(pCitiesTemplate);
	AddDocTemplate(pPhoneTypesTemplate);

	// create main MDI Frame window
	CMainFrame* pMainFrame = new CMainFrame;
	if (!pMainFrame || !pMainFrame->LoadFrame(IDR_MAINFRAME))
	{
		delete pMainFrame;
		return FALSE;
	}
	m_pMainWnd = pMainFrame;

	if (pPersonsTemplate)
	{
		pPersonsTemplate->OpenDocumentFile(NULL);
	}
	

	// The main window has been initialized, so show and update it
	pMainFrame->ShowWindow(m_nCmdShow);
	pMainFrame->UpdateWindow();

	return TRUE;
}

int CPhoneBookApp::ExitInstance()
{
	//TODO: handle additional resources you may have added
	AfxOleTerm(FALSE);

	return CWinAppEx::ExitInstance();
}

// CPhoneBookApp message handlers


// CAboutDlg dialog used for App About

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg() noexcept;

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() noexcept : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()

// App command to run the dialog
void CPhoneBookApp::OnAppAbout()
{
	CAboutDlg oAboutDlg;
	oAboutDlg.DoModal();
}

void CPhoneBookApp::OnFileNewPersons()
{
	if (pPersonsTemplate)
	{
		pPersonsTemplate->OpenDocumentFile(NULL);
	}
}

void CPhoneBookApp::OnFileNewCities()
{
	if (pCitiesTemplate)
	{
		pCitiesTemplate->OpenDocumentFile(NULL);
	}
}

void CPhoneBookApp::OnFileNewPhoneTypes()
{
	if (pPhoneTypesTemplate)
	{
		pPhoneTypesTemplate->OpenDocumentFile(NULL);
	}
}

// CPhoneBookApp customization load/save methods

void CPhoneBookApp::PreLoadState()
{
	BOOL bNameValid;
	CString strName;
	bNameValid = strName.LoadString(IDS_EDIT_MENU);
	ASSERT(bNameValid);
	GetContextMenuManager()->AddMenu(strName, IDR_POPUP_EDIT);
}

void CPhoneBookApp::LoadCustomState()
{
}

void CPhoneBookApp::SaveCustomState()
{
}

// CPhoneBookApp message handlers



