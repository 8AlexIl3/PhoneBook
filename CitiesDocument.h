// Add necessary includes and member variables
#include "CitiesData.h"

class CCitiesDocument : public CDocument
{
protected:
    CCitiesDocument() noexcept;
    DECLARE_DYNCREATE(CCitiesDocument)

public:
    // Array to hold city records
    CAutoArray<CITIES> m_oCitiesArray;
    BOOL InsertCity(CITIES& oCity);
    BOOL DeleteCityByID(const long lID, const long lrowIndexer);
    BOOL UpdateCityByID(const long lID, CITIES& oCity);
    BOOL SelectCityByID(const long lID, CITIES& oCity);
    BOOL LoadCities();
private:
    CCitiesData oCitiesData;
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
