#pragma once
#include "Structures.h"
#include <atldbcli.h>

/////////////////////////////////////////////////////////////////////////////
// CCitiesAccessor

#define ACCESSOR_COUNT          2

#define ACCESSOR_IDENTITY       0
#define ACCESSOR_DATA           1

#define REC_ID                  1

#define CITY_UPDATE_COUNTER     2
#define CITY_NAME               3
#define TOWN_RESIDENCE          4

class CCitiesAccessor
{
protected:
    CITIES m_rec;

    BEGIN_ACCESSOR_MAP(CCitiesAccessor, ACCESSOR_COUNT)
        BEGIN_ACCESSOR(ACCESSOR_IDENTITY, true)
            COLUMN_ENTRY(REC_ID, m_rec.lID)
        END_ACCESSOR()
       
        BEGIN_ACCESSOR(ACCESSOR_DATA, true)
            COLUMN_ENTRY(CITY_UPDATE_COUNTER, m_rec.lUpdateCounter)
            COLUMN_ENTRY(CITY_NAME, m_rec.szCityName)
            COLUMN_ENTRY(TOWN_RESIDENCE, m_rec.szTownResidence)
        END_ACCESSOR()
    END_ACCESSOR_MAP()
};