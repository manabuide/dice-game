#include <iostream>
#include <random>
#include <string>

class Dice {
    int64_t number;

   public:
    Dice() : number(1) {}
    Dice(int64_t number) : number(number) {}
    int64_t get_number() { return number; }
    void shake() {
        std::random_device rnd;
        std::mt19937 mt(rnd());
        std::uniform_int_distribution<> rand6(1, 6);
        number = rand6(mt);
    }
};

class Game {
    bool start_state;
    Dice dice1, dice2;
    bool result;  // true:Even false:Odd
    bool answer;  // true:Even false:Odd

   public:
    Game() {
        start_state = false;
        result = true;
        answer = true;
    }

    bool start_menu() {
        if (start_state) {
            std::cout << "Continue or end? (c/e):";
        } else {
            std::cout << "Start or end? (s/e):";
        }
        std::string ans;
        while (true) {
            std::cin >> ans;

            if (start_state) {
                if (ans == "c") {
                    return true;
                }
                if (ans == "e") {
                    return false;
                }
                std::cout << "Continue or end? (c/e):";
            } else {
                start_state = true;
                if (ans == "s") {
                    return true;
                }
                if (ans == "e") {
                    return false;
                }
                std::cout << "Start or end? (s/e):";
            }
        }
    }

    void start() {
        dice1.shake();
        dice2.shake();
    }

    bool judge() {
        result = (dice1.get_number() + dice2.get_number()) % 2 == 0;
        bool judge{true};

        if (result && answer) {
            judge = true;
        } else if (!result && answer) {
            judge = false;
        } else if (!result && !answer) {
            judge = true;
        } else if (result && !answer) {
            judge = false;
        }

        return judge;
    }

    void bet() {
        std::cout << "Odd or even? (o/e):";
        while (true) {
            std::string str;
            std::cin >> str;

            if (str == "e") {
                answer = true;
                break;
            } else if (str == "o") {
                answer = false;
                break;
            }

            std::cout << "Odd or even? (o/e):";
        }
    }

    void show_result() {
        std::cout << "Dice[1]:" << dice1.get_number()
                  << " Dice[2]:" << dice2.get_number() << '\n';
        std::cout << "Result:";
        if (result) {
            std::cout << "Even.\n";
        } else {
            std::cout << "Odd.\n";
        }
    }
};

int main() {
    Game game;
    while (game.start_menu()) {
        game.bet();
        game.start();

        if (game.judge()) {
            std::cout << "You are a winner.\n";
        } else {
            std::cout << "You are a loser.\n";
        }
        game.show_result();
    }

    return 0;
}
