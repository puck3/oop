#include "npc.hpp"

// Text Observer
class TextObserver : public Observer {
private:
    TextObserver() {};

public:
    static std::shared_ptr<Observer> get() {
        static TextObserver instance;
        return std::shared_ptr<Observer>(&instance, [](Observer*) {});
    }

    void on_fight(const std::shared_ptr<NPC> attacker, const std::shared_ptr<NPC> defender, bool win) override {
        if (win) {
            std::cout << std::endl
                << "Murder --------" << std::endl;
            attacker->print();
            defender->print();
        }
    }
};


class FileObserver : public Observer {
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
            fs << std::endl
                << "Murder --------" << std::endl;
            attacker->save(fs);
            defender->save(fs);
            fs.close();
        }
    }
};

