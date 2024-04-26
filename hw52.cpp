#include <iostream>
#include <cmath>
#include <chrono>
#include <thread>

using namespace std;

template<typename Cont> Cont filling(Cont cont) { //Заполнитель контейнеров (точно работает на последовательных контейнерах)
    srand(time(0));
    for (unsigned i = 0; i < 10000; i++) {
        cont.push_back(rand() % 10001);
    }
    return cont;
}

// Разделение с использованием схемы разделения Хоара
int partition(int mas[], int low, int high)
{
    int pivot = mas[low];
    int i = low - 1;
    int j = high + 1;
    while (1)
    {
        do {
            i++;
        } while (mas[i] < pivot);
 
        do {
            j--;
        } while (mas[j] > pivot);
 
        if (i >= j) {
            return j;
        }
 
        swap(mas[i], mas[j]);
    }
}
 
// Процедура быстрой сортировки
void hoar5sort(int mas[], int low, int high)
{
    // базовое условие
    if (low >= high) {
        return;
    }
 
    // Переставляем элементы относительно опорной точки
    int pivot = partition(mas, low, high);

    // Делим на два потока, первый сортирует то, что меньше опорной точки, второй другую половину.

    // Повторяем подмассив, содержащий элементы, меньшие опорной точки
    std::thread t1(hoar5sort, mas, low, pivot);
 
    // Повторяем подмассив, содержащий элементы, превышающие точку опоры
    std::thread t2(hoar5sort, mas, pivot + 1, high);

    t1.join();
    t2.join();
}

int main()  
{
    int nums1[10]; //Создаём массив
    srand(time(0));
    for (int i = 0; i < 10; i++) { //Заполняем его случайными числами
        int x = rand() % 100 + 1;
        nums1[i] = x;
        std::cout << nums1[i] << " ";
    }
    std::cout << "\n";
    hoar5sort(nums1, 0, 9); //Проводим сортировку Хоара, распараллеливая потоки внутри
    for (int i = 0; i < 10; i++) { //Проверяем сортировку
        std::cout << nums1[i] << " ";
    }
    return 0;
}

