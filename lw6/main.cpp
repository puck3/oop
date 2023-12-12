#include "npc.hpp"
#include "factory.hpp"
#include "elf.hpp"
#include "bandit.hpp"
#include "squirrel.hpp"

// save array to file
void save(const set_t& array, const std::string& filename) {
    std::ofstream fs(filename);
    fs << array.size() << std::endl;
    for (auto& n : array)
        n->save(fs);
    fs.flush();
    fs.close();
}

set_t load(const std::string& filename) {
    set_t result;
    std::ifstream is(filename);
    if (is.good() && is.is_open()) {
        int count;
        is >> count;
        for (int i = 0; i < count; ++i)
            result.insert(Factory::CreateNPC(is));
        is.close();
    } else
        std::cerr << "Error: " << std::strerror(errno) << std::endl;
    return result;
}

// print to screen
std::ostream& operator<<(std::ostream& os, const set_t& array) {
    for (auto& n : array)
        n->print();
    return os;
}


// ВНИМАНИЕ: метод осуществляющий сражение написан неправильно!
// Переделайте его на использование паттерна Visitor
// То есть внутри цикла вместо кучи условий должно быть:
//
// success = defender->accept(attacker);
//
// В NPC методы типа is_dragon - станут не нужны

set_t fight(const set_t& array, size_t distance) {
    set_t dead_list;
    std::vector<std::shared_ptr<Visitor>> visitors({std::make_shared<ElfVisitor>(), std::make_shared<BanditVisitor>(), std::make_shared<SquirrelVisitor>()});
    for (const auto& attacker : array)
        for (const auto& defender : array)
            if ((attacker != defender) && (attacker->is_close(defender, distance))) {
                if (attacker->type) {
                    bool success = defender->accept(visitors[attacker->type - 1]);

                    attacker->fight_notify(defender, success);
                    if (success) dead_list.insert(defender);
                }
            }

    return dead_list;
}

int main() {
    set_t array; // монстры

    // Гененрируем начальное распределение монстров
    std::cout << "Generating ..." << std::endl;
    for (size_t i = 0; i < 10; ++i)
        array.insert(Factory::CreateNPC(NpcType(std::rand() % 3 + 1),
            std::rand() % 100,
            std::rand() % 100));
    std::cout << "Saving ..." << std::endl;

    save(array, "npc.txt");

    std::cout << "Loading ..." << std::endl;
    array = load("npc.txt");

    std::cout << "Fighting ..." << std::endl
        << array;

    for (size_t distance = 20; (distance <= 100) && !array.empty(); distance += 10) {
        auto dead_list = fight(array, distance);
        for (auto& d : dead_list)
            array.erase(d);
        std::cout << "Fight stats ----------" << std::endl
            << "distance: " << distance << std::endl
            << "killed: " << dead_list.size() << std::endl
            << std::endl << std::endl;

    }

    std::cout << "Survivors:" << array;

    return 0;
}