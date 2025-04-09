def polynom(x, coeffs):
    return sum(c * x ** i for i, c in enumerate(reversed(coeffs)))
    # C0 * x^0 + C1 * x^1 + C2 * x^2 + ... + Cn * x^n
    # coeffs = 1 -1 -6
    # index  = 0  1  2  // поэтому инвертируем

def bisection(f, a, b, eps):
    if f(a) * f(b) > 0:
        return None # если на концах отрезка знаки разные => есть корень
    # делим пополам отрезок пока знаки функции на отрезке от a до mid не станут разными
    while (b - a) / 2 > eps:
        mid = (a + b) / 2
        if f(mid) == 0:
            return mid # точный корень
        elif f(a) * f(mid) < 0:
            b = mid # корень между a и mid
        else:
            a = mid # корень между mid и b
    return (a + b) / 2


def solve(x_range, epsilon, *coeffs):
    a, b = x_range
    step = epsilon * 100
    roots = []

    def f(x):
        return polynom(x, coeffs)

    x = a
    while x < b:
        x_next = x + step
        root = bisection(f, x, x_next, epsilon)
        if root is not None:
            root_rounded = round(root, 3)
            roots.append(root_rounded)
        x = x_next

    return roots

precision = 0.0001
print(solve([-5, 5], precision, 1, -1, -6))  # → [-2.0, 3.0]
print(solve([-5, 5], precision, 1, 0, 0, 0))  # → [0.0]
