
/**
 * 16.07.2021
 * Ruslan Bagautdinov
 *      bagautdinovrf@ya.ru
 *      bagautdinovrf@gmail.com
 * */


/*
I Задача о длиной цепочке единиц ⭐⭐

Дана последоватльность 0 и 1
Нужно найти самую длинную последовательность из 1 (единиц) после удаления любого элемента

func maxOnesAfterRemoveItem([]byte) uint
assert(maxOnesAfterRemoveItem[0,0] == 0)
assert(maxOnesAfterRemoveItem[0,1] == 1)
assert(maxOnesAfterRemoveItem[1,0] == 1)
assert(maxOnesAfterRemoveItem[1,1] == 1)
assert(maxOnesAfterRemoveItem[1, 1, 0, 1, 1] == 4)
assert(maxOnesAfterRemoveItem[1, 1, 0, 1, 1, 0, 1, 1, 1] == 5)
assert(maxOnesAfterRemoveItem[1, 1, 0, 1, 1, 0, 1, 1, 1, 0] == 5)
Что хочется увидеть:

Алгоритм со сложностью O(N) по времени и O(1) по памяти
*/

#include <iostream>
#include <vector>
#include <cassert>
#include <ctime>
#include <chrono>

using namespace std;


/**
 * @brief maxOnesAfterRemoveItem_v2 - Фунция с двумя счетчиками
 * Два счетчика без возвратов по массиву.
 * Почти не быстрей.
 * @param v
 */
unsigned maxOnesAfterRemoveItem_v2( const vector<unsigned char> &v )
{
    // Счетчик
    unsigned maxC = 0;
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
                    maxC = max( maxC, c1 );
                    zf1 = false;
                    c1 = 0;
                } else if( c1 > 0)
                    zf1 = true;

                if( zf2 ) {
                    maxC = max( maxC, c2 );
                    zf2 = false;
                    c2 = 0;
                } else if( c2 > 0 )
                    zf2 = true;
            }
        }
    }

    maxC = max( maxC, max(c1, c2) );
    if( maxC == v.size() ) --maxC;

return maxC;
}


/**
 * @brief maxOnesAfterRemoveItem - Функция с одним счетчиком
 * Один счетчик, но возвращаемся назад к еденице каждый раз
 * @param v
 */
unsigned maxOnesAfterRemoveItem( const vector<unsigned char> &v )
{
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


int main()
{
//    vector<char> v = {1,1};
//    vector<char> v = {1, 1, 0, 1, 1, 0, 1, 1, 1};
//    cout << maxOnesAfterRemoveItem_v2(v) << endl;

//    unsigned size = 294'967'290;
//    vector<char> v(size);

//    for( auto &item : v ) {
//        item = rand() % 2;
//    }

//    unsigned int t1 =  clock(); // начальное время
////    cout << maxOnesAfterRemoveItem_v2(v) << endl;
////    cout << maxOnesAfterRemoveItem(v) << endl;
//    unsigned int t2 = clock(); // конечное время
//    std::cout << "Executed in " << t2-t1 << endl;

//    auto t1 = std::chrono::high_resolution_clock::now();
////    maxOnesAfterRemoveItem_v2(v);
////    maxOnesAfterRemoveItem(v);
//    auto t2 = std::chrono::high_resolution_clock::now();
//    auto time_took = std::chrono::duration_cast<std::chrono::duration<double>>(t2 - t1);
//    std::cout << "Executed in " << time_took.count() << endl;

    assert(maxOnesAfterRemoveItem({0,0}) == 0);
    assert(maxOnesAfterRemoveItem({0,1}) == 1);
    assert(maxOnesAfterRemoveItem({1,0}) == 1);
    assert(maxOnesAfterRemoveItem({1,1}) == 1);
    assert(maxOnesAfterRemoveItem({1,1,1}) == 2);
    assert(maxOnesAfterRemoveItem({1, 1, 0, 1, 1}) == 4);
    assert(maxOnesAfterRemoveItem({1, 1, 0, 1, 1, 0, 1, 1, 1}) == 5);
    assert(maxOnesAfterRemoveItem({1, 1, 0, 1, 1, 0, 1, 1, 1, 0}) == 5);
    assert(maxOnesAfterRemoveItem({0, 0, 1, 1, 0, 1, 1, 0, 1, 1, 1, 0}) == 5);

    /**************************************************************************************/

    assert(maxOnesAfterRemoveItem_v2({0,0}) == 0);
    assert(maxOnesAfterRemoveItem_v2({0,1}) == 1);
    assert(maxOnesAfterRemoveItem_v2({1,0}) == 1);
    assert(maxOnesAfterRemoveItem_v2({1,1}) == 1);
    assert(maxOnesAfterRemoveItem_v2({1,1,1}) == 2);
    assert(maxOnesAfterRemoveItem_v2({1, 1, 0, 1, 1}) == 4);
    assert(maxOnesAfterRemoveItem_v2({1, 1, 0, 1, 1, 0, 1, 1, 1}) == 5);
    assert(maxOnesAfterRemoveItem_v2({1, 1, 0, 1, 1, 0, 1, 1, 1, 0}) == 5);
    assert(maxOnesAfterRemoveItem_v2({0, 0, 1, 1, 0, 1, 1, 0, 1, 1, 1, 0}) == 5);

    return 0;
}
