
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
 * @brief maxOnesAfterRemoveItem_v3 - Упрощенная функция с двумя счетчиками
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


int main()
{
    vector<unsigned char> v = {1, 1, 0, 1, 1};
//    vector<unsigned char> v = {0,0,0,1,0,0,0,0, 1, 0, 1,0,0, 1, 0, 1, 1, 1,0,1,0,1,1,0,0};
//    vector<unsigned char> v = {0, 1, 1, 0, 1, 1, 0, 0, 1, 1, 1, 0, 1, 1, 1, 0,1,1,1,1,0};
//    vector<unsigned char> v = {0, 1, 1, 0, 1, 1, 0, 1, 1, 1, 0, 1, 1, 1};
    cout << maxOnesAfterRemoveItem(v) << endl;
    cout << maxOnesAfterRemoveItemStateMachine(v) << endl;
    cout << maxOnesAfterRemoveItem_v3(v) << endl;

//    unsigned size = 94'967'290;
//    vector<unsigned char> v(size);

//    for( auto &item : v ) {
//        item = rand() % 2;
//    }

//    unsigned int t1 =  clock(); // начальное время
//    cout << maxOnesAfterRemoveItem(v) << endl;
//    cout << maxOnesAfterRemoveItem_v2(v) << endl;
//    cout << maxOnesAfterRemoveItemStateMachine(v) << endl;
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

    assert(maxOnesAfterRemoveItemStateMachine({0,0}) == 0);
    assert(maxOnesAfterRemoveItemStateMachine({0,1}) == 1);
    assert(maxOnesAfterRemoveItemStateMachine({1,0}) == 1);
    assert(maxOnesAfterRemoveItemStateMachine({1,1}) == 1);
    assert(maxOnesAfterRemoveItemStateMachine({1,1,1}) == 2);
    assert(maxOnesAfterRemoveItemStateMachine({1, 1, 0, 1, 1}) == 4);
    assert(maxOnesAfterRemoveItemStateMachine({1, 1, 0, 1, 1, 0, 1, 1, 1}) == 5);
    assert(maxOnesAfterRemoveItemStateMachine({1, 1, 0, 1, 1, 0, 1, 1, 1, 0}) == 5);
    assert(maxOnesAfterRemoveItemStateMachine({0, 0, 1, 1, 0, 1, 1, 0, 1, 1, 1, 0}) == 5);

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
