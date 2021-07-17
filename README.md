# counter101
# **Подсчет максимальной последовательности едениц при удалении элемента**
 
###  Функция **maxOnesAfterRemoveItem_v3** является самой оптимальной реализацией подсчета

+ Реализация в main.cpp – с двумя счетками более продвинутая; 
+ Реализция one_couner — с одним счетчиком, приходится возвращатся к еденицам перед нулем;
+ Реализация state_machine — с использованием конечноего автомата;
+ Реализация two_counter – с двумя счетчками, кривая реализация.


[Задача о длиной цепочке единиц, ссылка на задание](https://gist.github.com/rusdevops/d85340e26aeac720c338874492adf637#file-21195-md)

> I Задача о длиной цепочке единиц ⭐⭐

Дана последоватльность 0 и 1
Нужно найти самую длинную последовательность из 1 (единиц) после удаления любого элемента

> func maxOnesAfterRemoveItem([]byte) uint\
> assert(maxOnesAfterRemoveItem[0,0] == 0)\
> assert(maxOnesAfterRemoveItem[0,1] == 1)\
> assert(maxOnesAfterRemoveItem[1,0] == 1)\
> assert(maxOnesAfterRemoveItem[1,1] == 1)\
> assert(maxOnesAfterRemoveItem[1, 1, 0, 1, 1] == 4)\
> assert(maxOnesAfterRemoveItem[1, 1, 0, 1, 1, 0, 1, 1, 1] == 5)\
> assert(maxOnesAfterRemoveItem[1, 1, 0, 1, 1, 0, 1, 1, 1, 0] == 5)

Что хочется увидеть:\
Алгоритм со сложностью O(N) по времени и O(1) по памяти
