#ifndef ARMSTRONG_H
#define ARMSTRONG_H

#include <QString>
#include <QTextStream>
#include <cmath>

class Numbers {
private:
    int arm;

public:
    Numbers() : arm(0) {}

    explicit Numbers(int value) : arm(value) {}

    int nod(const Numbers& other){
        int x = arm;
        int y = other.arm;
        while (x != 0 && y != 0) {
            if (x > y) {
                x %= y;
            } else {
                y %= x;
            }
        }
        return x + y;
    }
    int nod(int y){
        int x = arm;
        while (x != 0 && y != 0) {
            if (x > y) {
                x %= y;
            } else {
                y %= x;
            }
        }
        return x + y;
    }

    int nok(const Numbers& other) const {
        int x = arm;
        int y = other.arm;
        int product = x * y;
        while (x != 0 && y != 0) {
            if (x > y) {
                x %= y;
            } else {
                y %= x;
            }
        }
        return product / (x + y);
    }

    int nok(int y) const {
        int x = arm;
        int product = x * y;
        while (x != 0 && y != 0) {
            if (x > y) {
                x %= y;
            } else {
                y %= x;
            }
        }
        return product / (x + y);
    }

    bool isPrime() const {
        if (arm < 2) {
            return false;
        }
        for (int i = 2; i <= std::sqrt(arm); ++i) {
            if (arm % i == 0) {
                return false;
            }
        }
        return true;
    }

    unsigned int countDigits() const {
        unsigned int x = std::abs(arm);
        unsigned int result = 0;
        if (x == 0) {
            return 1;
        }
        while (x != 0) {
            x /= 10;
            result++;
        }
        return result;
    }

    bool isArmstrong() const {
        unsigned int sum = 0;
        unsigned int temp = std::abs(arm);
        unsigned int original = temp;
        unsigned int digits = countDigits();
        while (temp != 0) {
            unsigned int digit = temp % 10;
            sum += static_cast<unsigned int>(std::pow(digit, digits));
            temp /= 10;
        }
        if (arm == 0) sum = 0;
        return sum == original;
    }

    void set(int x){
        arm = x;
    }

    friend QTextStream& operator>>(QTextStream& in, Numbers& number) {
        in >> number.arm;
        return in;
    }

    friend QTextStream& operator<<(QTextStream& out, const Numbers& number) {
        out << number.arm;
        return out;
    }
};

#endif // ARMSTRONG_H
