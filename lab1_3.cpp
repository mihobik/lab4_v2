#include <iostream> 
#include <vector>
#include <locale>
#include <random>

using namespace std;

int main() {
    setlocale(LC_ALL, "RU");
    int j, k, k0, k1, m, n;

    cout << "Введите параметры j и k (j, k >= 1) через пробел: ";
    cin >> j >> k;
    cout << "Введите значение m (m >= 2): ";
    cin >> m;
    cout << "Введите первые члены последовательности k0 и k1 (k0, k1 принадлежат [0, m-1]) через пробел: ";
    cin >> k0 >> k1;
    cout << "Введите количество вычисляемых членов n (n >= 2): ";
    cin >> n;

    vector<int> S;
    S.push_back(k0);
    S.push_back(k1);

    if (j < 1 || k < 1) {
        cout << "Ошибка: j и k должны быть >= 1\n";
        return 1;
    }

    if (m < 2) {
        cout << "Ошибка: m должно быть >= 2\n";
        return 1;
    }

    if (n < 1) {
        cout << "Ошибка: n должно быть >= 1\n";
        return 1;
    }

    for (int i = 2; i < n + 2; ++i) {
        if (i - j < 0 || i - k < 0) {
            cout << "Ошибка: j и k слишком велики для длины последовательности\n";
            return 1;
        }
        int next = (S[i - j] + S[i - k]) % m;
        S.push_back(next);
    }

    for (int i = 2; i < S.size(); ++i) {
        cout << S[i] << " ";
    }

    return 0;
}
