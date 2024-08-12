#pragma once
#include "afxdialogex.h"
#include "Person.h"
#include "PhoneNumbersDlg.h"
#include <regex>
#include "PersonsCredentials.h"
// CPersonsDlg dialog

class CPersonsDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CPersonsDlg)
	DECLARE_MESSAGE_MAP()


	// Constructor / Destructor
	// ----------------
public:
	/// <param name="oCitiesArray">Array of cities to be loaded</param>
	/// <param name="pPhoneTypesArray">Array of phone types  </param>
	/// <param name="bEditPermission">view mode </param>
	/// <param name="pPerson">the person that will be edited/added</param>
	/// <param name="pParent">parent window</param>
	CPersonsDlg(CPersonsCredentials& oPersonsCredentials,bool bEditPermission=true, CPersonExtend* pPerson = nullptr, CWnd* pParent = nullptr);

	virtual ~CPersonsDlg();


	// Constants
	// ----------------
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DLG_PERSONS };
#endif
	

	// MFC Overrides
	// ----------------
protected:
	void DoDataExchange(CDataExchange* pDX) override;    // DDX/DDV support
	BOOL OnInitDialog() override;
	void OnCancel() override;
	void OnOK() override;


	//MFC message handlers
	// ----------------
private:
	afx_msg void onInsertNumber();
	afx_msg void onUpdateNumber();
	afx_msg void onDeleteNumber();


	//Methods
	// ----------------
public:
	/// <summary>Getter for person </summary>
	/// <returns>a reference to the person object</returns>
	CPersonExtend& GetPerson();
private:
	CEdit m_EdbAddress;
	CEdit m_EdbSurname;
	CEdit m_EdbEGN;
	CEdit m_EdbLastName;
	CEdit m_EdbFirstName;
	CListCtrl m_LscPhoneNumbers;
	CComboBox m_CmbCities;
	CPersonExtend* m_pPerson;
	CButton m_BtnAddNumber;
	CButton m_BtnUpdateNumber;
	CButton m_BtnDeleteNumber;

	CPersonsCredentials& m_oPersonsCredentials;
	//CMap<long, long, CString, CString> m_oPhoneTypeToString;
	bool m_bAllocatedPerson;
	bool m_bEditPermitted;

	/// <summary>
	/// Set Initial checkbox item list
	/// </summary>
	void SetCityComboboxItems();
	
	/// <summary>assign a string to the id of phonetypes</summary>
	void MapPhoneTypeIDToString();
	/// <summary>Checks all items in dialog to see if any changes are needed</summary>
	/// <returns>true if no changes are needed, false otherwise</returns>
	bool ValidateData();
	/// <summary>Display the persons' phone numbers</summary>
	void DisplayData();
	
	///<summary>Checks if the string is valid against the given pattern</summary>
	///<returns>true if no string matches pattern, false otherwise</returns>
	bool IsStringValid(const std::wregex& oPattern, CString& strArg);

	long GetRowIndex();

	void Capitalize(CString& oString);
	
};
#define INDEX_NOT_FOUND		-1

#define PHONE_NUMBER_COLUMN 0
#define PHONE_TYPE_COLUMN	1

#define NAME_LENGTH			NAME_SIZE-1
#define ADDRESS_LENGTH		ADDRESS_SIZE-1
#define EGN_LENGTH			10

#define PIXEL_WIDTH_250		250