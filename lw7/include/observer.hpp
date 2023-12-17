#pragma once
#include "npc.hpp"

// Text Observer
class TextObserver final : public Observer {
private:
    TextObserver() {};

public:
    static std::shared_ptr<Observer> get() {
        static TextObserver instance;
        return std::shared_ptr<Observer>(&instance, [](Observer*) {});
    }

    void on_fight(const std::shared_ptr<NPC> attacker, const std::shared_ptr<NPC> defender, bool win) override {
        if (win) {
            std::cout << "Murder --------" << std::endl;
            std::cout << "killer: ";
            attacker->print();
            std::cout << "victim: ";
            defender->print();
            std::cout << std::endl;
        }
    }
};


class FileObserver final : public Observer {
private:
    FileObserver() {};

public:
    static std::shared_ptr<Observer> get() {
        static FileObserver instance;
        return std::shared_ptr<Observer>(&instance, [](Observer*) {});
    }

    void on_fight(const std::shared_ptr<NPC> attacker, const std::shared_ptr<NPC> defender, bool win) override {
        if (win) {
            std::ofstream fs("log.txt", std::ios::app);
            fs << std::endl << "Murder --------" << std::endl << "killer: " << *attacker << std::endl << "victim: " << *defender;
            fs.close();
        }
    }
};

