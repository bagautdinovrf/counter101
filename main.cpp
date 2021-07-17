
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
#include <algorithm>

using namespace std;


/**
 * @brief maxOnesAfterRemoveItem_v3 - Упрощенная функция с двумя счетчиками
 * По идее самая быстрая из всех моих реализаций.
 * @param v
 */
unsigned maxOnesAfterRemoveItem_v3( const vector<unsigned char> &v )
{
    if( v.empty() )
        return 0;

    // Счетчик
    unsigned maxCount = 0;
    // Счетчик для каждой последовательности
    unsigned counter = 0, second = 0;
    // Флаги для обнаруженияя нуля
    bool zero_flag = false;

    for( const auto &item : v ) {
         if( 1 == item ) {
             ++counter;
             if( zero_flag )
                 ++second;
         } else {
             if( zero_flag ) {
                 maxCount = max( maxCount, counter );
                 counter = second;
                 second = 0;
             }
             zero_flag = true;
         }
    }

    maxCount = max( maxCount, counter );
    if( maxCount == v.size() ) --maxCount;

return maxCount;
}


int main()
{
//    vector<unsigned char> v = {1, 1, 0, 1, 1};
//    vector<unsigned char> v = {0,0,0,1,0,0,0,0, 1, 0, 1,0,0, 1, 0, 1, 1, 1,0,1,0,1,1,0,0};
//    vector<unsigned char> v = {0, 1, 1, 0, 1, 1, 0, 0, 1, 1, 1, 0, 1, 1, 1, 0,1,1,1,1,0};
//    vector<unsigned char> v = {0, 1, 1, 0, 1, 1, 0, 1, 1, 1, 0, 1, 1, 1};
//    cout << maxOnesAfterRemoveItem(v) << endl;
//    cout << maxOnesAfterRemoveItemStateMachine(v) << endl;
//    cout << maxOnesAfterRemoveItem_v3(v) << endl;

//    unsigned size = 94'967'290;
//    vector<unsigned char> v(size);

//    srand( clock() );
//    for( auto &item : v ) {
//        item = rand() % 2;
//    }

//    for( int i = 0; i < 100; ++i ) {
//        v[i] = 1;
//    }

//    unsigned int t1 =  clock(); // начальное время
//    cout << maxOnesAfterRemoveItem(v) << endl;
//    cout << maxOnesAfterRemoveItem_v3(v) << endl;
//    cout << maxOnesAfterRemoveItemStateMachine(v) << endl;
//    unsigned int t2 = clock(); // конечное время
//    std::cout << "Executed in " << t2-t1 << endl;

//    auto t1 = std::chrono::high_resolution_clock::now();
////    maxOnesAfterRemoveItem_v2(v);
////    maxOnesAfterRemoveItem(v);
//    maxOnesAfterRemoveItem_v3(v);
//    auto t2 = std::chrono::high_resolution_clock::now();
//    auto time_took = std::chrono::duration_cast<std::chrono::duration<double>>(t2 - t1);

    /**************************************************************************************/

    assert(maxOnesAfterRemoveItem_v3({0,0}) == 0);
    assert(maxOnesAfterRemoveItem_v3({0,1}) == 1);
    assert(maxOnesAfterRemoveItem_v3({1,0}) == 1);
    assert(maxOnesAfterRemoveItem_v3({1,1}) == 1);
    assert(maxOnesAfterRemoveItem_v3({1,1,1}) == 2);
    assert(maxOnesAfterRemoveItem_v3({1, 1, 0, 1, 1}) == 4);
    assert(maxOnesAfterRemoveItem_v3({1, 1, 0, 1, 1, 0, 1, 1, 1}) == 5);
    assert(maxOnesAfterRemoveItem_v3({1, 1, 0, 1, 1, 0, 1, 1, 1, 0}) == 5);
    assert(maxOnesAfterRemoveItem_v3({0, 0, 1, 1, 0, 1, 1, 0, 1, 1, 1, 0}) == 5);

    return 0;
}
