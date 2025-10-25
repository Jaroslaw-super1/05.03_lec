# include <iostream>
# include <limits>

bool oversize_multiplise(size_t a, size_t b) {

    const size_t lim_size_t = std::numeric_limits<size_t>::max();
    if (lim_size_t / a < b) {
        return 0;
    }
    return 1;
}

bool oversize_plise(size_t a, size_t b) {

    const size_t lim_size_t = std::numeric_limits<size_t>::max();
    if (lim_size_t < a || lim_size_t - a < b) {
        return 0;
    }
    return 1;
}

bool all_good(size_t a, size_t b, size_t c) {

    bool fl1 = oversize_multiplise(a, a);
    fl1 = fl1 && oversize_multiplise(b, b);
    fl1 = fl1 && oversize_multiplise(c, c);

    if (fl1) {
        bool fl2 = oversize_plise(b * b, c * c);
        fl2 = fl2 && oversize_plise(a * a, c * c);
        fl2 = fl2 && oversize_plise(b * b, a * a);
        if (fl2) {
            return 1;
        }
    }
    return 0;
}

bool is_Pyth (size_t a, size_t b, size_t c) {

    if (all_good(a, b, c)) {
        bool p = a * a == b * b + c * c;
        p = p || b * b == a * a + c * c;
        p = p || c * c == a * a + b * b;

        return p;
    }
    return 0;
}

int main () {
    size_t a = 0, b = 0, c = 0;
    size_t count = 0;
    bool Pyth = 0;

    std::cin >> c >> b;
    while (std::cin >> a) {
        Pyth = is_Pyth(a, b, c);
        if (!Pyth && !all_good(a, b, c)) {
            return 2;
        }
        count += Pyth ? 1 : 0;
        c = b;
        b = a;
    }

    if (std::cin.eof()) {
        std::cout << count;
        std::cout << "\n";
    } else if (std::cin.fail()) {
        std::cerr << "Input error\n";
        return 1;
    }
}