#pragma once


/////////////////////////////////////////////////////////////////////////////
// CPersonsDocument

#include "PersonsData.h"
#include "CitiesData.h"
#include "PhoneTypesData.h"
#include "Structures.h"
#include "Person.h"
#include "PersonsCredentials.h"
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
    bool InsertPerson(CPersonExtend& oPersons);

    /// <param name="lID">Id to delete</param>
    /// <param name="lrowIndexer">index from listctrl</param>
    /// <returns>true if successful, false otherwise</returns>
    bool DeletePerson(const long lID, const long lrowIndexer);

    /// <param name="lID">Id to update</param>
    /// <param name="oPersons">Person that will get updated</param>
    /// <returns>true if successful, false otherwise</returns>
    bool UpdatePerson(const long lID, CPersonExtend& oPersons);

    /// <param name="lID">Id to select</param>
    /// <param name="oPersons">Object that will get initilized</param>
    /// <returns>true if successful, false otherwise</returns>
    bool SelectPerson(const long lID, CPersonExtend& oPersons);

    /// <summary>Get all Persons from table</summary>
    /// <returns>true if successful, false otherwise</returns>
    bool LoadPersons();

    CPersonsCredentials& GetCredentials();

    /// <summary>Getter for personArray</summary>
    CPersonArray& GetPersonArray();

   
private:
    void ClearPersonsArray();
    


    // Overrides
    // ----------------
public:
    void SetTitle(LPCTSTR lpszTitle) override;
    BOOL OnNewDocument() override;
    void Serialize(CArchive& ar) override;


    // Members
    // ----------------
private:
    // Array to hold person records
    CPersonArray m_oPersonsArray;
    CPersonsCredentials m_oCredentials;
    //CMap<long, long, CString, CString> m_oCityIDtoString;

    // Implementation
    // ----------------
public:
#ifdef _DEBUG
    virtual void AssertValid() const;
    virtual void Dump(CDumpContext& dc) const;
#endif
};
