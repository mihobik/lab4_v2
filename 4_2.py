import random
import secrets
import sys
import io
sys.stdout = io.TextIOWrapper(sys.stdout.buffer, encoding='utf-8')

# генератор случайных чисел
gen = secrets.SystemRandom()

size1 = size2 = size3 = SIZE = 10

arr1 = [gen.randint(0, 100) for _ in range(size1)]  # массив arr1

print(f"Массив arr1 из {size1} случайных чисел [0, 100]:")
print(*arr1)

# поиск наибольшего и наименьшего элементов массива arr1
size1_max = arr1.index(max(arr1))
size1_min = arr1.index(min(arr1))

print("MAX:", arr1[size1_max])
print("MIN:", arr1[size1_min])

# сумма элементов между max и min
if size1_min > size1_max:
    size1_min, size1_max = size1_max, size1_min

sum_between = sum(arr1[i] for i in range(size1_min + 1, size1_max))
print("Сумма элементов между MIN и MAX:", sum_between)
print("-----------------------------------------")

# формирование arr2
arr2 = arr1[size1_min + 1:size1_max]
while len(arr2) < size1:
    rand_index = gen.randint(0, size1 - 1)
    if rand_index not in (size1_min, size1_max):
        arr2.append(arr1[rand_index])

print(f"Массив arr2 из {size1} элементов между min и max:")
print(*arr2)
print("-----------------------------------------")

# массив arr3
arr3 = [chr(gen.randint(ord('A'), ord('Z'))) for _ in range(size3)]

print("Массив arr3:")
print(*arr3)

# сбор символов на чётных позициях и сортировка
even_positions = sorted(arr3[i] for i in range(1, size3, 2))

# вставка отсортированных символов обратно в чётные позиции
index_arr3 = 0
for i in range(1, size3, 2):
    arr3[i] = even_positions[index_arr3]
    index_arr3 += 1

print("Массив arr3 после сортировки чётных позиций:")
print(*arr3)
print("-----------------------------------------")

# массив arr4
arr4 = [gen.randint(100, 900) for _ in range(SIZE)]
arr4.sort()

# массив arr5
arr5 = []
for num in arr4:
    digits = list(str(num))
    random.shuffle(digits)
    shuffled_num = int("".join(digits))
    arr5.append(shuffled_num if shuffled_num > num else 0)

print("Массив arr4 (отсортированный):")
print(*arr4)

print("Массив arr5 (перемешанный):")
print(*arr5)
