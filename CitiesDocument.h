#pragma once


/////////////////////////////////////////////////////////////////////////////
// CCitiesDocument

#include "CitiesData.h"
#include "Structures.h"

class CCitiesDocument : public CDocument
{

// Macros
// ----------------
    DECLARE_DYNCREATE(CCitiesDocument)
    DECLARE_MESSAGE_MAP()


// Constructor / Destructor
// ----------------
public:
    CCitiesDocument();
    virtual ~CCitiesDocument();


// Methods
// ----------------
public:
    /// <param name="oCities">City to be inserted(its counter will be updated(so its not const)</param>
    /// <returns>true if successful, false otherwise</returns>
    bool InsertCity(CITIES& oCities);

    /// <param name="lID">id to delete</param>
    /// <param name="lrowIndexer">index from listctrl</param>
    /// <returns>true if successful, false otherwise</returns>
    bool DeleteCity(const long lID, const long lrowIndexer);

    /// <param name="lID">id to update</param>
    /// <param name="oCities">Object that will update</param>
    /// <returns>true if successful, false otherwise</returns>
    bool UpdateCity(const long lID,CITIES& oCities);

    /// <param name="lID">id to select</param>
    /// <param name="oCities">Object that will get initilized</param>
    /// <returns>true if successful, false otherwise</returns>
    bool SelectCity(const long lID, CITIES& oCities);

    /// <summary>Get all cities from table</summary>
    /// <returns>true if successful, false otherwise</returns>
    bool LoadCities();

    /// <summary>Getter for m_oCitiesArray</summary>
    const CCitiesArray& GetCityArray();
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
    // Array to hold city records
    CCitiesArray m_oCitiesArray;


// Implementation
// ----------------
public:
#ifdef _DEBUG
    virtual void AssertValid() const;
    virtual void Dump(CDumpContext& dc) const;
#endif
};
