#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <algorithm>
#include <locale>
using namespace std;

//метод Борда: возвращает всех победителей
vector<int> borda_winners(const vector<vector<int>>& votes, int n) {
    vector<int> scores(n, 0);
    for (const auto& vote : votes) {
        for (int i = 0; i < n; ++i) {
            scores[vote[i]] += n - 1 - i;
        }
    }

    int max_score = *max_element(scores.begin(), scores.end());
    vector<int> winners;
    for (int i = 0; i < n; ++i) {
        if (scores[i] == max_score) {
            winners.push_back(i);
        }
    }
    return winners;
}

//возвращает true, если кандидат A выигрывает у B в парном сравнении
bool wins_against(const vector<vector<int>>& votes, int A, int B) {
    int countA = 0, countB = 0;
    for (const auto& vote : votes) {
        int posA = find(vote.begin(), vote.end(), A) - vote.begin();
        int posB = find(vote.begin(), vote.end(), B) - vote.begin();
        if (posA < posB) ++countA;
        else if (posB < posA) ++countB;
    }
    return countA > countB;
}

//метод кондорсе: возвращает индекс победителя или -1, если его нет
int condorce_winner(const vector<vector<int>>& votes, int n) {
    for (int i = 0; i < n; ++i) {
        bool winner = true;
        for (int j = 0; j < n; ++j) {
            if (i != j && !wins_against(votes, i, j)) {
                winner = false;
                break;
            }
        }
        if (winner) return i;
    }
    return -1;
}

int main() {
    setlocale(LC_ALL, "Russian");
    int n, k;
    cout << "Введите количество кандидатов: ";
    cin >> n;
    cout << "Введите количество избирателей: ";
    cin >> k;
    cin.ignore();

    vector<string> names(n);
    cout << "Введите имена кандидатов:\n";
    for (int i = 0; i < n; ++i) {
        cout << "Кандидат " << i << ": ";
        getline(cin, names[i]);
    }

    vector<vector<int>> votes(k, vector<int>(n));
    cout << "\nВведите предпочтения избирателей (в виде имён через пробел от самого предпочтительного к наименее):\n";
    for (int i = 0; i < k; ++i) {
        cout << "Избиратель " << i + 1 << ": ";
        string line;
        getline(cin, line);

        vector<string> input_names;
        string name;
        for (char ch : line) {
            if (ch == ' ') {
                if (!name.empty()) {
                    input_names.push_back(name);
                    name.clear();
                }
            }
            else {
                name += ch;
            }
        }
        if (!name.empty()) input_names.push_back(name);

        if (input_names.size() != n) {
            cout << "Ошибка: введено не " << n << " имён. Повторите ввод.\n";
            --i;
            continue;
        }

        bool valid = true;
        for (int j = 0; j < n; ++j) {
            auto it = find(names.begin(), names.end(), input_names[j]);
            if (it == names.end()) {
                cout << "Ошибка: имя '" << input_names[j] << "' не найдено. Повторите ввод.\n";
                valid = false;
                break;
            }
            votes[i][j] = it - names.begin();
        }

        if (!valid) {
            --i;
            continue;
        }
    }


    vector<int> borda = borda_winners(votes, n);

    int condorce = condorce_winner(votes, n);


    cout << "\n=== Результаты ===\n";


    cout << "Метод Борда: ";
    if (borda.size() == 1)
        cout << "победитель — " << names[borda[0]] << endl;
    else {
        cout << "несколько победителей (ничья): ";
        for (int i = 0; i < borda.size(); ++i) {
            cout << names[borda[i]];
            if (i != borda.size() - 1) cout << ", ";
        }
        cout << endl;
    }


    if (condorce != -1)
        cout << "Метод Кондорсе: победитель — " << names[condorce] << endl;
    else
        cout << "Метод Кондорсе: победителя не существует\n";

    if (borda.size() != 1 || borda[0] != condorce)
        cout << "Методы дали разные результаты\n";

    return 0;
}