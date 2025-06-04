import math
import sys
import io
sys.stdout = io.TextIOWrapper(sys.stdout.buffer, encoding='utf-8')

# функция уравнения
def f(x):
    return 2 * x + math.cos(x)

# производная для метода ньютона
def df(x):
    return 2 - math.sin(x)

# ф-функция для метода простых итераций
def phi(x):
    return -0.5 * math.cos(x)

# метод половинного деления
def bisection(a, b, eps):
    print("\nМетод половинного деления:")
    print("N\ta\t\tb\t\tb_n - a_n")
    iter = 0
    while abs(b - a) > eps:
        c = (a + b) / 2
        print(f"{iter}\t{a:.4f}\t{b:.4f}\t{(b - a):.4f}")
        if f(c) == 0:
            return c
        if f(a) * f(c) < 0:
            b = c
        else:
            a = c
        iter += 1
    return (a + b) / 2

# метод ньютона
def newton(x0, eps):
    print("\nМетод Ньютона:")
    print("N\tx_n\t\tx_n+1\t\tx_n+1 - x_n")
    iter = 0
    x = x0
    while True:
        fx = f(x)
        dfx = df(x)
        x_new = x - fx / dfx
        print(f"{iter}\t{x:.4f}\t{x_new:.4f}\t{abs(x_new - x):.4f}")
        if abs(x_new - x) < eps:
            return x_new
        x = x_new
        iter += 1

# метод простых итераций
def iteration(x0, eps, phi_func):
    print("\nМетод простых итераций:")
    print("N\tx_n\t\tx_n+1\t\tx_n+1 - x_n")
    iter = 0
    x = x0
    while True:
        x_new = phi_func(x)
        print(f"{iter}\t{x:.4f}\t{x_new:.4f}\t{abs(x_new - x):.4f}")
        if abs(x_new - x) < eps:
            return x_new
        x = x_new
        iter += 1

def main():
    eps = 0.0001
    print("Отделение корня:")
    xs = []
    x = -0.6
    while x <= -0.4 + 1e-9:
        xs.append(x)
        x += 0.1
    for x in xs:
        print(f"x = {x:.1f}, f(x) = {f(x):.4f}")

    print("\n~~~ Корень уравнения 2x + cos(x) = 0 ~~~")

    root_bis = bisection(-0.6, -0.4, eps)
    root_newton = newton(-0.5, eps)
    root_iter = iteration(-0.5, eps, phi)

    print(f"\n\nРезультаты (точность eps = {eps}):")
    print(f"Метод половинного деления: {root_bis:.4f}")
    print(f"Метод Ньютона:             {root_newton:.4f}")
    print(f"Метод простых итераций:    {root_iter:.4f}")

if __name__ == "__main__":
    main()
