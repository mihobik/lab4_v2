#include <iostream>
#include <vector>
#include <random>
#include <ctime>
#include <algorithm>
#include <locale>

using namespace std;

// всегда сотрудничает
bool AlwaysCooperate(int32_t round_number, const vector<bool>& self_choices, const vector<bool>& enemy_choices) {
    return true;
}

// всегда предает
bool AlwaysBetray(int32_t round_number, const vector<bool>& self_choices, const vector<bool>& enemy_choices) {
    return false;
}

// зеркало
bool MirrorStrategy(int32_t round_number, const vector<bool>& self_choices, const vector<bool>& enemy_choices) {
    if (round_number == 0) {
        return true;
    }
    return enemy_choices.back();
}

// функция для проведения игры
pair<int, int> PlayGame(bool (*strategy1)(int32_t, const vector<bool>&, const vector<bool>&),
    bool (*strategy2)(int32_t, const vector<bool>&, const vector<bool>&),
    int rounds) {
    vector<bool> choices1, choices2;
    int score1 = 0, score2 = 0;

    for (int round = 0; round < rounds; ++round) {
        bool choice1 = strategy1(round, choices1, choices2);
        bool choice2 = strategy2(round, choices2, choices1);

        choices1.push_back(choice1);
        choices2.push_back(choice2);

        // подсчет очков
        if (choice1 && choice2) { // сотрудничают
            score1 += 24;
            score2 += 24;
        }
        else if (choice1 && !choice2) { // первый сотрудничает, второй предает
            score1 += 0;
            score2 += 20;
        }
        else if (!choice1 && choice2) { // первый предает, второй сотрудничает
            score1 += 20;
            score2 += 0;
        }
        else { // предают
            score1 += 4;
            score2 += 4;
        }
    }

    return { score1, score2 };
}

int main() {
    setlocale(LC_ALL, "Russian");
    mt19937 gen(time(0));
    uniform_int_distribution<> rounds_dist(100, 200);

    // массив всех стратегий
    vector<pair<string, bool (*)(int32_t, const vector<bool>&, const vector<bool>&)>> strategies = {
        {"Всегда сотрудничает", AlwaysCooperate},
        {"Всегда предаёт", AlwaysBetray},
        {"Зеркало", MirrorStrategy}
    };

    // хранение результатов
    vector<vector<pair<int, int>>> results(3, vector<pair<int, int>>(3));

    // проведение всех матчей
    for (int i = 0; i < strategies.size(); ++i) {
        for (int j = i + 1; j < strategies.size(); ++j) {
            int rounds = rounds_dist(gen);
            auto result = PlayGame(strategies[i].second, strategies[j].second, rounds);
            int score1 = result.first;
            int score2 = result.second;
            results[i][j] = { score1, score2 };
            results[j][i] = { score2, score1 };

            cout << "Игра: " << strategies[i].first << " vs " << strategies[j].first
                << " (" << rounds << " раундов)\n";
            cout << "Счёт: " << score1 << " - " << score2 << "\n\n";
        }
    }

    // подсчет общего количества очков для каждой стратегии
    vector<int> total_scores(3, 0);
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            if (i != j) {
                total_scores[i] += results[i][j].first;
            }
        }
    }

    // определение лучшей стратегии
    int best_strategy = max_element(total_scores.begin(), total_scores.end()) - total_scores.begin();

    cout << "\nИтоговые результаты:\n";
    for (int i = 0; i < 3; ++i) {
        cout << strategies[i].first << ": " << total_scores[i] << " очков\n";
    }

    cout << "\nЛучшая стратегия: " << strategies[best_strategy].first
        << " с " << total_scores[best_strategy] << " очков\n";

    return 0;
}