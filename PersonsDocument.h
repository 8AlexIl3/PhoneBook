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
    /// <param name="oPersons">City to be inserted(its counter will be updated(so its not const)</param>
    /// <returns>true if successful, false otherwise</returns>
    bool InsertPerson(CPerson& oPersons);

    /// <param name="lID">id to delete</param>
    /// <param name="lrowIndexer">index from listctrl</param>
    /// <returns>true if successful, false otherwise</returns>
    bool DeletePerson(const long lID, const long lrowIndexer);


    /// <param name="lID">id to update</param>
    /// <param name="oPersons">Object that will update</param>
    /// <returns>true if successful, false otherwise</returns>
    bool UpdatePerson(const long lID, CPerson& oPersons);

    /// <param name="lID">id to select</param>
    /// <param name="oPersons">Object that will get initilized</param>
    /// <returns>true if successful, false otherwise</returns>
    bool SelectPerson(const long lID, CPerson& oPersons);

    /// <summary>Get all persons from table</summary>
    /// <returns>true if successful, false otherwise</returns>
    bool LoadPersons();

    bool LoadCities();

    bool LoadPhoneTypes();

    /// <summary>Getter for m_oCitiesArray</summary>
    CPersonArray& GetPersonArray();
    CCitiesArray& GetCitiesArray();
    CPhoneTypesArray& GetPhoneTypesArray();
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
public:
    CMap<long, long, CString, CString> cityIDtoString;

    // Implementation
    // ----------------
public:
#ifdef _DEBUG
    virtual void AssertValid() const;
    virtual void Dump(CDumpContext& dc) const;
#endif
};
