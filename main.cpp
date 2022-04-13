#include <iostream>
#include <bitset>
#include <cmath>
#include <cstdlib>

#if defined(__linux__)
    #define CLEAR "clear"
#else
    #define CLEAR "cls"
#endif

/// Main port
#define PORT 0b10100

/// Number of port's lines
#define SIZE 5

/// Enumerate for user's choices
enum Choose {
    INV = 1, ///< Invert port's lines
    ON, ///< Turn ON port's lines
    OFF, ///< Turn OFF port's lines
    LINE, ///< Invert specific line
    SHIFT_L, ///< Shift left port's lines
    SHIFT_R, ///< Shift right port's lines
    EXIT = 9, ///< Exit
};

/*!
  \brief А сlass that allows you to work with an 5bit I/O port
*/
class Interface {
private:
    std::bitset<SIZE> val; //Input port, you can change it in #define PORT and #defile SIZE

public:
    /*!
        @brief Class constructor
    */
    explicit Interface(int port) {
        for(short i = 0; i<SIZE; i++){
            val.set(i,port/(short)(pow(2,i))%2);
        }
    }

    /*!
    @brief Method, which is turning val on
    */
    void turnOn() {
        val.set();
    }

    /*!
        @brief Method, which is turning val off
    */
    void turnOff() {
        val.reset();
    }

    /*!
        @brief Method, which inverts the val value
    */
    void invert() {
        val.flip();
    }

    /*!
        @brief Method, which allows to manage line manually
    */
    void lineManagment() {
        short a = 0;
        while (a != EXIT) {
            std::cout << val << "\n";
            for(short i = 0; i<SIZE; i++){
                std::cout << i+1 << " = " << val[SIZE - i - 1] << "\n";
            }
            std::cout << "9)back\n>";
            std::cin >> a;
            std::system(CLEAR);
            if (a == EXIT) return;
            if(a>SIZE||a<1){
                std::cout << "Wrong command, please try again\n";
                std::cin.clear();
                std::cin.ignore(4294967296, '\n');
            } else val[SIZE - a].flip();
        }
    }

    /*!
        @brief Method, which performs an arithmetic left shift
    */
    void Left_shift()
    {
        bool buf = val[SIZE-1];
        val.operator<<=(1);
        val[0] = buf;
    }

    /*!
        @brief Method, which performs an arithmetic right shift
    */
    void Right_shift()
    {
        bool buf = val[0];
        val.operator>>=(1);
        val[SIZE-1] = buf;
    }

    /*!
        @brief Getter of variable "val"
    */
    [[nodiscard]] const std::bitset<SIZE>& getVal() const {
        return val;
    }
};

short menu(std::bitset<SIZE> val) {
    short chosen = 0;
    std::cout
        << val << "\n"
        << "Choose an option:\n"
        << "1)invert\n"
        << "2)turnOn\n"
        << "3)turnOff\n"
        << "4)lineManagment\n"
        << "5)ShiftLeft\n"
        << "6)ShiftRight\n"
        << "9)exit\n>";
    std::cin >> chosen;
    std::system(CLEAR);
    return chosen;
}


int main() {
    Interface values(PORT);

    short chosen = 0;
    while (chosen != EXIT) {
        chosen = menu(values.getVal());

        if (chosen == ON) {
            values.turnOn();
            continue;
        }
        if (chosen == OFF) {
            values.turnOff();
            continue;
        }
        if (chosen == INV) {
            values.invert();
            continue;
        }
        if (chosen == LINE) {
            values.lineManagment();
            continue;
        }
        if (chosen == SHIFT_L) {
            values.Left_shift();
            continue;
        }
        if (chosen == SHIFT_R) {
            values.Right_shift();
            continue;
        }
        if(chosen == EXIT) continue;
        std::cout << "Wrong command, please try again\n";
        std::cin.clear();
        std::cin.ignore(4294967296, '\n');
    }
    return EXIT_SUCCESS;
}