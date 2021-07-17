#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

enum StateCounter { SC_NULL = 0, SC_FIRST, SC_ONE, SC_ZERO, SC_ZERO_ONE, SC_ZEROZERO };

/**
 * @brief maxOnesAfterRemoveItemStateMachine - Функция с использованием конечного автомата
 * @param v
 */
unsigned maxOnesAfterRemoveItemStateMachine( const vector< unsigned char > &v)
{
    if( v.empty() )
        return 0;

    StateCounter state = SC_NULL;
    unsigned maxCount = 0;
    unsigned counter = 0, zero_one_counter = 0;
    state = SC_FIRST;

    unsigned index = 0;

    for( const auto& elem : v ) {
        switch (state) {
            case SC_FIRST:
                if( 1 == elem ) {
                    ++counter;
                    state = SC_ONE;
                } else {
                    continue;
                }
            break;

            case SC_ONE:
                if( 1 == elem ) {
                    ++counter;
                } else {
                    state = SC_ZERO;
                }
            break;

            case SC_ZERO:
                if( 1 == elem ) {
                    ++counter;
                    ++zero_one_counter;
                    state = SC_ZERO_ONE;
                } else {
                    maxCount = max( maxCount, counter );
                    counter = 0;
                    state = SC_ZEROZERO;
                }
            break;

            case SC_ZERO_ONE:
                if( 1 == elem ) {
                    ++counter;
                    ++zero_one_counter;
                } else {
                    maxCount = max( maxCount, counter );
                    counter = zero_one_counter;
                    zero_one_counter = 0;
                    state = SC_ZEROZERO;
                }
            break;

            case SC_ZEROZERO:
                if( 1 == elem ) {
                    ++counter;
                    ++zero_one_counter;
                    state = SC_ZERO_ONE;
                } else {
                    counter = 0;
                    zero_one_counter = 0;
                }
            break;
        }
        ++index;
    }

    maxCount = max( maxCount, counter );
    if( maxCount == v.size() ) --maxCount;
    return maxCount;
}
