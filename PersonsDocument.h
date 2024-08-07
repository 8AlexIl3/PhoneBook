#pragma once


/////////////////////////////////////////////////////////////////////////////
// CPersonsDocument

#include "PersonsData.h"
#include "CitiesData.h"
#include "PhoneTypesData.h"
#include "Structures.h"
#include "Person.h"
class CPersonsDocument : public CDocument
{

    // Macros
    // ----------------
    DECLARE_DYNCREATE(CPersonsDocument)
    DECLARE_MESSAGE_MAP()


    // Constructor / Destructor
    // ----------------
public:
    CPersonsDocument();
    virtual ~CPersonsDocument();


    // Methods
    // ----------------
public:
    /// <param name="oPersons">Person to be inserted(its counter will be updated(so its not const)</param>
    /// <returns>true if successful, false otherwise</returns>
    bool InsertPerson(CPerson& oPersons);

    /// <param name="lID">Id to delete</param>
    /// <param name="lrowIndexer">index from listctrl</param>
    /// <returns>true if successful, false otherwise</returns>
    bool DeletePerson(const long lID, const long lrowIndexer);


    /// <param name="lID">Id to update</param>
    /// <param name="oPersons">Person that will get updated</param>
    /// <returns>true if successful, false otherwise</returns>
    bool UpdatePerson(const long lID, CPerson& oPersons);

    /// <param name="lID">Id to select</param>
    /// <param name="oPersons">Object that will get initilized</param>
    /// <returns>true if successful, false otherwise</returns>
    bool SelectPerson(const long lID, CPerson& oPersons);

    /// <summary>Get all Persons from table</summary>
    /// <returns>true if successful, false otherwise</returns>
    bool LoadPersons();

    /// <summary>Get all Cities from table</summary>
    /// <returns>true if successful, false otherwise</returns>
    bool LoadCities();

    /// <summary>Get all Phone types from table</summary>
   /// <returns>true if successful, false otherwise</returns>
    bool LoadPhoneTypes();

    /// <summary>Getter for personArray</summary>
    CPersonArray& GetPersonArray();

    /// <summary>Getter for CitiesArray</summary>
    CCitiesArray& GetCitiesArray();

    /// <summary>Getter for PhoneTypesArray</summary>
    CPhoneTypesArray& GetPhoneTypesArray();

    CMap<long, long, CString, CString>&GetStringCity();

private:
    void ClearPersonsArray();
    void ClearCitiesArray();
    void ClearPhoneTypesArray();


    // Overrides
    // ----------------
public:
    void SetTitle(LPCTSTR lpszTitle) override;
    virtual BOOL OnNewDocument() override;
    virtual void Serialize(CArchive& ar) override;


    // Members
    // ----------------
private:
    // Array to hold person records
    CPersonArray m_oPersonsArray;
    CCitiesArray m_oCitiesArray;
    CPhoneTypesArray m_oPhoneTypesArray;
    CMap<long, long, CString, CString> m_oCityIDtoString;

    // Implementation
    // ----------------
public:
#ifdef _DEBUG
    virtual void AssertValid() const;
    virtual void Dump(CDumpContext& dc) const;
#endif
};
