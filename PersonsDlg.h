#pragma once
#include "afxdialogex.h"
#include "Person.h"
#include "PhoneNumbersDlg.h"
#include <regex>
// CPersonsDlg dialog

class CPersonsDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CPersonsDlg)
		DECLARE_MESSAGE_MAP()

public:
	/// <summary>
	/// Constructor
	/// </summary>
	/// <param name="oCitiesArray">Array of cities to be loaded</param>
	/// <param name="pPhoneTypesArray">Array of phone types  </param>
	/// <param name="pPerson">the person that will be edited/added</param>
	/// <param name="pParent">parent window</param>
	CPersonsDlg(CCitiesArray& oCitiesArray, CPhoneTypesArray* pPhoneTypesArray, CPerson* pPerson = nullptr, CWnd* pParent = nullptr);

	virtual ~CPersonsDlg();


	// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DLG_PERSONS };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual BOOL OnInitDialog() override;

private:
	CEdit m_EdbAddress;
	CEdit m_EdbSurname;
	CEdit m_EdbEGN;
	CEdit m_EdbLastName;
	CEdit m_EdbFirstName;
	CListCtrl m_LscPhoneNumbers;
	CComboBox m_CmbCities;

	CPhoneTypesArray* m_pPhoneTypes;
	CPerson* m_pPerson;
	CCitiesArray* m_pCitiesArray;
	CMap<long, long, CString, CString> m_oPhoneTypeToString;
	bool bAllocatedCity;

	/// <summary>
	/// Set Initial checkbox item list
	/// </summary>
	void SetCityComboboxItems();

	afx_msg void onInsertNumber();
	afx_msg void onUpdateNumber();
	afx_msg void onDeleteNumber();

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
	/// <summary>Called upon pressing cancel </summary>
	virtual void OnCancel();
	/// <summary>Called upon pressing ok</summary>

	virtual void OnOK();
public:
	void Capitalize(CString& oString);
	/// <summary>Getter for person </summary>
	/// <returns>a reference to the person object</returns>
	CPerson& GetPerson();
};
#define INDEX_NOT_FOUND		-1

#define PHONE_NUMBER_COLUMN 0
#define PHONE_TYPE_COLUMN	1

#define NAME_LENGTH			31
#define ADDRESS_LENGTH		63
#define EGN_LENGTH			10

#define PX250				250