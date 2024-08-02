#pragma once


/////////////////////////////////////////////////////////////////////////////
// CPersonsDocument

#include "PersonsData.h"
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
    bool InsertPerson(PERSONS& oPersons);

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

    /// <summary>Getter for m_oCitiesArray</summary>
    const CPersonArray& GetPersonArray();
private:
    void ClearArray();


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


    // Implementation
    // ----------------
public:
#ifdef _DEBUG
    virtual void AssertValid() const;
    virtual void Dump(CDumpContext& dc) const;
#endif
};
