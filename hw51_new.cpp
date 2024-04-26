#include <iostream>
#include <vector>
#include <thread>
#include <chrono>

using namespace std;

int findmax(int n[]) {
    int num_max = 0;
    int index_max = -1;
    for (int i = 0; i < 100; i++) {
        if (n[i] > num_max) {
            index_max = i;
            num_max = n[i];
        }
    }
    n[index_max] = 0;
    std::cout << num_max << "\n";
    return num_max;
}

int main()  
{
    int s1;
    int s2;
    int s3;
    int nums1[100]; //Создаём массив
    srand(time(0));
    for (int i = 0; i < 100; i++) { //Заполняем его случайными числами от 1 до 1000
        int x = rand() % 1000 + 1;
        nums1[i] = x;
    }
    //Разделяем код на три потока. С выводом чисел в терминале у него, конечно, не очень хорошо,
    // но функции по расчёту суммы код свои выполняет.
    std::thread t1([&](){
        s1 = findmax(nums1);    
    });
    std::thread t2([&](){
        s2 = findmax(nums1); 
    });
    std::thread t3([&](){
        s3 = findmax(nums1); 
    });
    t1.join();
    t2.join();
    t3.join();
    std::cout << s1 + s2 + s3;
    return 0;
}