#include "CitiesData.h"
#include "Structures.h"
class CCitiesDocument : public CDocument
{
public:
    CCitiesDocument() noexcept;
    virtual ~CCitiesDocument();
protected:
    DECLARE_DYNCREATE(CCitiesDocument)
    DECLARE_MESSAGE_MAP()

///Members----------------------------------------------------------------------------------------------------
private:
    //Data object to call functions from the data class
    CCitiesData oCitiesData;
    // Array to hold city records
    CCitiesArray m_oCitiesArray;

///Methods-------------------------------------------------------------------------------------------
public:
    BOOL InsertCity(CITIES& oCity);
    BOOL DeleteCity(const long lID, const long lrowIndexer);
    BOOL UpdateCity(CITIES& oCity);
    BOOL SelectCity(const long lID, CITIES& oCity);
    BOOL LoadCities();
    CITIES& GetCity(long lIndexer);
    const CCitiesArray& GetCityArray();
private:
    void ClearArray();
    // Overrides
public:
    void SetTitle(LPCTSTR lpszTitle) override;
    virtual BOOL OnNewDocument() override;
    virtual void Serialize(CArchive& ar) override;

    // Implementation
public:
#ifdef _DEBUG
    virtual void AssertValid() const;
    virtual void Dump(CDumpContext& dc) const;
#endif

protected:
};
