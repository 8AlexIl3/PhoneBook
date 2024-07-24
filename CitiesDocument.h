#include "CitiesData.h"

class CCitiesDocument : public CDocument
{
protected:
    CCitiesDocument() noexcept;
    DECLARE_DYNCREATE(CCitiesDocument)
///Members----------------------------------------------------------------------------------------------------
public:
    // Array to hold city records
    CAutoMemoryArray<CITIES> m_oCitiesArray;
private:
    //Data object to call functions from the data class
    CCitiesData oCitiesData;
///Member functions-------------------------------------------------------------------------------------------
public:
    BOOL InsertCity(CITIES& oCity);
    BOOL DeleteCityByID(const long lID, const long lrowIndexer);
    BOOL UpdateCityByID(const long lID, CITIES& oCity);
    BOOL SelectCityByID(const long lID, CITIES& oCity);
    BOOL LoadCities();
private:
    void ClearArray();
    // Overrides
public:
    virtual BOOL OnNewDocument();
    virtual void Serialize(CArchive& ar);

    // Implementation
public:
    virtual ~CCitiesDocument();
#ifdef _DEBUG
    virtual void AssertValid() const;
    virtual void Dump(CDumpContext& dc) const;
#endif

protected:
    DECLARE_MESSAGE_MAP()
};
