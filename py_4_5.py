import random
from typing import List, Tuple, Callable

def always_cooperate(round_number: int, self_choices: List[bool], enemy_choices: List[bool]) -> bool:
    """Всегда сотрудничает"""
    return True

def always_betray(round_number: int, self_choices: List[bool], enemy_choices: List[bool]) -> bool:
    """Всегда предает"""
    return False

def mirror_strategy(round_number: int, self_choices: List[bool], enemy_choices: List[bool]) -> bool:
    """Зеркальная стратегия: начинает с сотрудничества, затем повторяет последний ход противника"""
    if round_number == 0:
        return True
    return enemy_choices[-1]

def play_game(strategy1: Callable, strategy2: Callable, rounds: int) -> Tuple[int, int]:
    """Проведение игры между двумя стратегиями"""
    choices1, choices2 = [], []
    score1, score2 = 0, 0

    for round_num in range(rounds):
        choice1 = strategy1(round_num, choices1, choices2)
        choice2 = strategy2(round_num, choices2, choices1)

        choices1.append(choice1)
        choices2.append(choice2)

        if choice1 and choice2:  # сотрудничают
            score1 += 24
            score2 += 24
        elif choice1 and not choice2:  # первый сотрудничает, второй предает
            score1 += 0
            score2 += 20
        elif not choice1 and choice2:  # первый предает, второй сотрудничает
            score1 += 20
            score2 += 0
        else:  # предают
            score1 += 4
            score2 += 4

    return score1, score2

def main():
    random.seed()

    # массив всех стратегий
    strategies = [
        ("Всегда сотрудничает", always_cooperate),
        ("Всегда предаёт", always_betray),
        ("Зеркало", mirror_strategy)
    ]

    # хранение результатов
    results = [[(0, 0) for _ in range(3)] for _ in range(3)]

    # проведение матчей
    for i in range(len(strategies)):
        for j in range(i + 1, len(strategies)):
            rounds = random.randint(100, 200)
            score1, score2 = play_game(strategies[i][1], strategies[j][1], rounds)
            results[i][j] = (score1, score2)
            results[j][i] = (score2, score1)

            print(f"Игра: {strategies[i][0]} vs {strategies[j][0]} ({rounds} раундов)")
            print(f"Счёт: {score1} - {score2}\n")

    # подсчет количества очков
    total_scores = [0] * 3
    for i in range(3):
        for j in range(3):
            if i != j:
                total_scores[i] += results[i][j][0]

    # определение лучшей стратегии
    best_strategy = total_scores.index(max(total_scores))

    print("\nИтоговые результаты:")
    for i in range(3):
        print(f"{strategies[i][0]}: {total_scores[i]} очков")

    print(f"\nЛучшая стратегия: {strategies[best_strategy][0]} с {total_scores[best_strategy]} очков")

if __name__ == "__main__":
    main()