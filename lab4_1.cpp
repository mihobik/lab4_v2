#include <iostream>
#include <cmath>
#include <iomanip>
#include <locale>
#include <vector>
using namespace std;

// функция уравнения: 2x + cos(x) = 0
double f(double x) {
    return 2 * x + cos(x);
}

// производная для метода Ньютона: f'(x) = 2 - sin(x)
double df(double x) {
    return 2 - sin(x);
}

// φ-функция для метода простых итераций: x = -0.5 * cos(x)
double phi(double x) {
    return -0.5 * cos(x);
}

// метод половинного деления
double bisection(double a, double b, double eps) {
    cout << "\nМетод половинного деления:\n";
    cout << "N\ta\tb\tb_n - a_n\n";
    int iter = 0;
    while (fabs(b - a) > eps) {
        double c = (a + b) / 2;
        cout << iter << "\t" << a << "\t" << b << "\t" << (b - a) << endl;
        if (f(c) == 0) return c;
        (f(a) * f(c) < 0) ? b = c : a = c;
        iter++;
    }
    return (a + b) / 2;
}

// метод ньютона
double newton(double x0, double eps) {
    cout << "\nМетод Ньютона:\n";
    cout << "N\tx_n\tx_n+1\tx_n+1 - x_n\n";
    int iter = 0;
    double x = x0;
    while (true) {
        double fx = f(x);
        double dfx = df(x);
        double x_new = x - fx / dfx;
        cout << iter << "\t" << x << "\t" << x_new << "\t" << fabs(x_new - x) << endl;
        if (fabs(x_new - x) < eps) return x_new;
        x = x_new;
        iter++;
    }
}

// метод простых итераций
double iteration(double x0, double eps, double (*phi)(double)) {
    cout << "\nМетод простых итераций:\n";
    cout << "N\tx_n\tx_n+1\tx_n+1 - x_n\n";
    int iter = 0;
    double x = x0;
    while (true) {
        double x_new = phi(x);
        cout << iter << "\t" << x << "\t" << x_new << "\t" << fabs(x_new - x) << endl;
        if (fabs(x_new - x) < eps) return x_new;
        x = x_new;
        iter++;
    }
}

int main() {
    setlocale(LC_ALL, "Russian");
    const double eps = 0.0001;
    cout << fixed << setprecision(4);

    cout << "Отделение корня:\n";
    vector<double> xs;
    for (double x = -0.6; x <= -0.4; x += 0.1) {
        xs.push_back(x);
    }
    for (double x : xs) {
        cout << "x = " << x << ", f(x) = " << f(x) << endl;
    }

    cout << "\n~~~ Корень уравнения 2x + cos(x) = 0 ~~~\n";

    double root_bis = bisection(-0.6, -0.4, eps);
    double root_newton = newton(-0.5, eps);
    double root_iter = iteration(-0.5, eps, phi);

    cout << "\n\nРезультаты (точность eps = " << eps << "):\n";
    cout << "Метод половинного деления: " << root_bis << endl;
    cout << "Метод Ньютона:             " << root_newton << endl;
    cout << "Метод простых итераций:    " << root_iter << endl;

    return 0;
}
