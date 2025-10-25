# include <iostream>

bool is_Pyth (unsigned a, unsigned b, unsigned c);

int main () {
    using u_t = unsigned;
    u_t a = 0;
    u_t a = 0, b = 0, c = 0;
    size_t count = 0;


    //std::cin >> a;
    while (std::cin >> a) {
        count++;
        count += is_Pyth(a, b, c);
    }

    if (std::cin.eof()) {
        std::cout << count;
        std::cout << "\n";
    } else if (std::cin.fail()) {
        std::cerr << "Input error\n";
        return 1;
    }
}