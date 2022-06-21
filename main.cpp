#include <iomanip>
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

class User {
    bool answer;  // true:Even false:Odd
    bool winner;
    int64_t wins;
    int64_t games;

   public:
    User() {
        answer = true;
        winner = true;
        wins = 0;
        games = 0;
    }

    void set_answer(bool is_even) { answer = is_even; }
    void set_winner(bool is_win) { winner = is_win; }
    void add_win() { ++wins; }
    void add_game() { ++games; }
    const bool& get_answer() { return answer; }
    const bool& get_winner() { return winner; }
    const int64_t& get_wins() { return wins; }
    const int64_t& get_games() { return games; }
};

class Game {
    bool start_state;
    Dice dice1, dice2;
    bool result;  // true:Even false:Odd
    User user;

   public:
    Game() {
        start_state = false;
        result = true;
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

    void judge() {
        result = (dice1.get_number() + dice2.get_number()) % 2 == 0;

        if (result && user.get_answer()) {
            user.set_winner(true);
            user.add_win();
        } else if (!result && user.get_answer()) {
            user.set_winner(false);
        } else if (!result && !user.get_answer()) {
            user.set_winner(true);
            user.add_win();
        } else if (result && !user.get_answer()) {
            user.set_winner(false);
        }

        user.add_game();
    }

    void bet() {
        std::cout << "Odd or even? (o/e):";
        while (true) {
            std::string str;
            std::cin >> str;

            if (str == "e") {
                user.set_answer(true);
                break;
            } else if (str == "o") {
                user.set_answer(false);
                break;
            }

            std::cout << "Odd or even? (o/e):";
        }
    }

    double get_winning_percentage() {
        return static_cast<double>(user.get_wins()) / user.get_games();
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

        if (user.get_winner()) {
            std::cout << "You are a winner!\n";
        } else {
            std::cout << "You are a loser!\n";
        }

        std::cout << "Games:" << user.get_games() << " Wins:" << user.get_wins()
                  << '\n';
        std::cout << std::fixed << std::setprecision(3)
                  << "Winning percentage:" << get_winning_percentage() << '\n';
    }
};

int main() {
    Game game;
    while (game.start_menu()) {
        game.bet();
        game.start();
        game.judge();
        game.show_result();
    }

    return 0;
}
