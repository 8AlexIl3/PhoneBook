#pragma once
#include "Structures.h"
#include <atldbcli.h>
#define ACCESSOR_COUNT  2

#define ACCESSOR_0      0
#define ACCESSOR_1      1

#define REC_ID          1

#define UPDATE_COUNTER  2
#define CITY_NAME       3
#define TOWN_RESIDENCE  4

class CCitiesAccessor
{
protected:
    CITIES m_recCity;

    BEGIN_ACCESSOR_MAP(CCitiesAccessor, ACCESSOR_COUNT)
        BEGIN_ACCESSOR(ACCESSOR_0, true)
            COLUMN_ENTRY(REC_ID, m_recCity.lID)
        END_ACCESSOR()
       
        BEGIN_ACCESSOR(ACCESSOR_1, true)
            COLUMN_ENTRY(UPDATE_COUNTER, m_recCity.lUpdateCounter)
            COLUMN_ENTRY(CITY_NAME, m_recCity.szCityName)
            COLUMN_ENTRY(TOWN_RESIDENCE, m_recCity.szTownResidence)
        END_ACCESSOR()
    END_ACCESSOR_MAP()
};