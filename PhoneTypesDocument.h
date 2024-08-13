#pragma once
#include "PhoneTypesData.h"
#include "Structures.h"


/////////////////////////////////////////////////////////////////////////////
// CPhoneTypesDocument

class CPhoneTypesDocument : public CDocument
{

    // Macros
    // ----------------
    DECLARE_DYNCREATE(CPhoneTypesDocument)
        DECLARE_MESSAGE_MAP()


    // Constructor / Destructor
    // ----------------
public:
    CPhoneTypesDocument();
    virtual ~CPhoneTypesDocument();


    // Methods
    // ----------------
public:
    /// <param name="oPhoneTypes">City to be inserted(its counter will be updated(so its not const)</param>
    /// <returns>true if successful, false otherwise</returns>
    bool InsertPhoneType(PHONE_TYPES& oPhoneTypes);

    /// <param name="lID">id to delete</param>
    /// <param name="lrowIndexer">index from listctrl</param>
    /// <returns>true if successful, false otherwise</returns>
    bool DeletePhoneType(const long lID, const long lrowIndexer);

    /// <param name="lID">id to update</param>
    /// <param name="oPhoneTypes">Object that will update</param>
    /// <returns>true if successful, false otherwise</returns>
    bool UpdatePhoneType(const long lID, PHONE_TYPES& oPhoneTypes);

    /// <param name="lID">id to select</param>
    /// <param name="oPhoneTypes">Object that will get initilized</param>
    /// <returns>true if successful, false otherwise</returns>
    bool SelectPhoneType(const long lID, PHONE_TYPES& oPhoneTypes);

    /// <summary>Get all PhoneTypes from table</summary>
    /// <returns>true if successful, false otherwise</returns>
    bool LoadPhoneTypes();

    /// <summary>Getter for m_oPhoneTypesArray</summary>
    const CPhoneTypesArray& GetPhoneTypeArray();
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
    // Array to hold PhoneType records
    CPhoneTypesArray m_oPhoneTypesArray;


    // Implementation
    // ----------------
public:
#ifdef _DEBUG
    virtual void AssertValid() const;
    virtual void Dump(CDumpContext& dc) const;
#endif
};
