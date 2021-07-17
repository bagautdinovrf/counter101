/**
 * @brief maxOnesAfterRemoveItem - Функция с одним счетчиком
 * Один счетчик, но возвращаемся назад к еденице каждый раз
 * @param v
 */
unsigned maxOnesAfterRemoveItem( const vector<unsigned char> &v )
{
    if( v.empty() )
        return 0;

    unsigned maxCount = 0;
    unsigned zero = 0;
    unsigned counter = 0;
    bool zero_flag = false;

    for( int i = 0; i < v.size(); ++i ) {
        if( 1 == v.at(i) ) {
            ++counter;
        } else {
            if( counter > 0 ) {
                if( zero_flag ) {
                    maxCount = max( maxCount, counter );
                    zero_flag = false;
                    counter = 0;
                    // Возвращаемся к прошлой последовательности
                    i = zero;
                } else {
                    zero_flag = true;
                    zero = i;
                }
            }
        }
    }

    if( counter == v.size() )
        maxCount = --counter;
    else
        maxCount = max( maxCount, counter );

return maxCount;
}
