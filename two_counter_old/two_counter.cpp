#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

/**
 * @brief maxOnesAfterRemoveItem_v2 - Фунция с двумя счетчиками
 * Два счетчика без возвратов по массиву.
 * Почти не быстрей. Не быстрее чем maxOnesAfterRemoveItem
 * @param v
 */
unsigned maxOnesAfterRemoveItem_v2( const vector<unsigned char> &v )
{
    if( v.empty() )
        return 0;
    // Счетчик
    unsigned maxCount = 0;
    // Счетчик для каждой последовательности
    unsigned c1 = 0, c2 = 0;
    // Флаги для обнаруженияя нуля
    bool zf1 = false, zf2 =  false;

    for( const auto &item : v ) {
        if( 1 == item ) {
            if( 0 == c2 || zf2 || (false == zf2 && c2 > 0 ) )
                ++c1;
            if( zf1 || ( 0 == c1 && 0 != c2 ) || ( zf2 && c1 > 0) )
                ++c2;
        } else {
            // Сброс второго нуля
            if( c1 > 0 || c2 > 0 ) {
                if( zf1 ) {
                    maxCount = max( maxCount, c1 );
                    zf1 = false;
                    c1 = 0;
                } else if( c1 > 0)
                    zf1 = true;

                if( zf2 ) {
                    maxCount = max( maxCount, c2 );
                    zf2 = false;
                    c2 = 0;
                } else if( c2 > 0 )
                    zf2 = true;
            }
        }
    }

    maxCount = max( maxCount, max(c1, c2) );
    if( maxCount == v.size() ) --maxCount;

return maxCount;
}
