#include <iostream>
#include <random>
#include <locale>
#include <algorithm>
#include <vector>
#include <string>
using namespace std;


int main() {
    setlocale(LC_ALL, "RU");
    // генератор случайных чисел
    random_device rd;
    uniform_int_distribution<> dist(0, 100);
    uniform_int_distribution<> dist2('A', 'Z');
    uniform_int_distribution<> dist3(100, 900);

    const int size1 = 10, size2 = 10, size3 = 10, SIZE = 10;

    int arr1[size1];
    int arr2[size2];
    vector<char> arr3(size3);
    vector<int> arr4(SIZE);
    vector<int> arr5;

    int index = 0; // для арр2
    int index_arr3 = 0; // для арр3

    // заполняем массив 1 (1-2 задание)

    for (int i = 0; i < size1; i++) {
        arr1[i] = dist(rd);
    }

    cout << "Массив arr1 из " << size1 << " случайных чисел [0, 100]:\n";
    for (int i = 0; i < size1; i++) {
        cout << arr1[i] << " ";
    }
    cout << endl;

    // наибольший и наим. элементы массива 1
    int size1_max = 0;
    int size1_min = 0;

    for (int i = 1; i < size1; i++) {
        if (arr1[i] > arr1[size1_max])
            size1_max = i;
    }
    cout << "MAX: " << arr1[size1_max] << endl;

    for (int i = 1; i < size1; i++) {
        if (arr1[i] < arr1[size1_min])
            size1_min = i;
    }
    cout << "MIN: " << arr1[size1_min] << endl;

    // сумма между наибольшим и наименьшим элементами массива 1
    int sum = 0;
    if (size1_min > size1_max) swap(size1_min, size1_max);
    for (int i = size1_min + 1; i < size1_max; i++) {
        sum += arr1[i];
    }
    cout << "Сумма элементов между MIN и MAX: " << sum << endl;
    cout << "-----------------------------------------" << endl;

    // массив arr2 (3 задание)

    // копируем элементы между min и max
    if (size1_min > size1_max) swap(size1_min, size1_max);
    for (int i = size1_min + 1; i < size1_max; i++) {
        arr2[index++] = arr1[i];
    }

    // дополнение arr2 случайными элементами из arr1
    while (index < size1) {
        int rand_index = dist(rd) % size1;
        if (rand_index != size1_min && rand_index != size1_max) {
            arr2[index++] = arr1[rand_index];
        }
    }

    cout << "Массив arr2 из " << size1 << " элементов между min и max:\n";
    for (int i = 0; i < size1; i++) {
        cout << arr2[i] << " ";
    }
    cout << endl;
    cout << "-----------------------------------------" << endl;

    //массив arr3 (4 задание)

    // заполнение массива случайными символами
    for (int i = 0; i < size3; ++i) {
        arr3[i] = static_cast<char>(dist2(rd));
    }

    cout << "Массив arr3: \n";
    for (char c : arr3) {
        cout << c << ' ';
    }
    cout << endl;

    // сбор символов на чётных местах
    vector<char> positions;
    for (int i = 1; i < size3; i += 2) {
        positions.push_back(arr3[i]);
    }

    // сортировка символов на чётных местах
    sort(positions.begin(), positions.end());

    // вставка отсортированных символов обратно
    for (int i = 1; i < size3; i += 2) {
        arr3[i] = positions[index_arr3++];
    }

    cout << "Массив arr3 после сортировки чётных позиций: \n";
    for (char c : arr3) {
        cout << c << ' ';
    }
    cout << endl;
    cout << "-----------------------------------------" << endl;

    // arr4, arr5 (5 задание)

    for (int& num : arr4) {
        num = dist3(rd);
    }

    // сортировка arr4 по возрастанию
    sort(arr4.begin(), arr4.end());

    // обработка каждого числа
    for (int num : arr4) {
        string digits = to_string(num);

        shuffle(digits.begin(), digits.end(), rd); // перемешивание цифр

        int shuffled_num = stoi(digits); // преобразование обратно в число

        if (shuffled_num > num) {
            arr5.push_back(shuffled_num);
        }
        else {
            arr5.push_back(0);
        }
    }

    cout << "Массив arr4 (отсортированный): ";
    for (int num : arr4) {
        cout << num << " ";
    }
    cout << endl;

    cout << "Массив arr5 (перемешанный): ";
    for (int num : arr5) {
        cout << num << " ";
    }
    cout << endl;

    return 0;
}