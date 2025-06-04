import sys
import io
sys.stdout = io.TextIOWrapper(sys.stdout.buffer, encoding='utf-8')
 # метод Борда: возвращает всех победителей
def borda_winners(votes, n):
    scores = [0] * n
    for vote in votes:
        for i in range(n):
            scores[vote[i]] += n - 1 - i

    max_score = max(scores)
    winners = [i for i, score in enumerate(scores) if score == max_score]
    return winners

# возвращает True, если кандидат A выигрывает у B в парном сравнении
def wins_against(votes, A, B):
    countA = 0
    countB = 0
    for vote in votes:
        posA = vote.index(A)
        posB = vote.index(B)
        if posA < posB:
            countA += 1
        elif posB < posA:
            countB += 1
    return countA > countB

# метод Кондорсе: возвращает индекс победителя или -1, если его нет
def condorce_winner(votes, n):
    for i in range(n):
        winner = True
        for j in range(n):
            if i != j and not wins_against(votes, i, j):
                winner = False
                break
        if winner:
            return i
    return -1

def main():
    print("Введите количество кандидатов: ", end='')
    n = int(input())
    print("Введите количество избирателей: ", end='')
    k = int(input())

    names = []
    print("Введите имена кандидатов:")
    for i in range(n):
        name = input(f"Кандидат {i}: ")
        names.append(name)

    votes = []
    print("\nВведите предпочтения избирателей (в виде имён через пробел от самого предпочтительного к наименее):")
    for i in range(k):
        while True:
            line = input(f"Избиратель {i + 1}: ").strip()
            input_names = line.split()

            if len(input_names) != n:
                print(f"Ошибка: введено не {n} имён. Повторите ввод.")
                continue

            valid = True
            vote_indices = []
            for name in input_names:
                if name not in names:
                    print(f"Ошибка: имя '{name}' не найдено. Повторите ввод.")
                    valid = False
                    break
                vote_indices.append(names.index(name))

            if valid:
                votes.append(vote_indices)
                break

    borda = borda_winners(votes, n)
    condorce = condorce_winner(votes, n)

    print("\n=== Результаты ===\n")

    print("Метод Борда: ", end='')
    if len(borda) == 1:
        print(f"победитель — {names[borda[0]]}")
    else:
        print("несколько победителей (ничья): ", end='')
        print(", ".join(names[i] for i in borda))

    if condorce != -1:
        print(f"Метод Кондорсе: победитель — {names[condorce]}")
    else:
        print("Метод Кондорсе: победителя не существует")

    if len(borda) != 1 or borda[0] != condorce:
        print("Методы дали разные результаты")

if __name__ == "__main__":
    main()