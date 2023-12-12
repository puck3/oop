#include "elf.hpp"
#include "bandit.hpp"
#include "squirrel.hpp"

Bandit::Bandit(int x, int y) : NPC(BanditType, x, y) {}
Bandit::Bandit(std::istream& is) : NPC(BanditType, is) {}

bool Bandit::accept(const std::shared_ptr<Visitor>& attacker_visitor) const {
    std::shared_ptr<Bandit> defender = std::dynamic_pointer_cast<Bandit>(std::const_pointer_cast<NPC>(shared_from_this()));
    bool result = attacker_visitor->visit(defender);
    return result;
}

void Bandit::print() {
    std::cout << *this;
}

void Bandit::save(std::ostream& os) {
    os << BanditType << std::endl;
    NPC::save(os);
}

std::ostream& operator<<(std::ostream& os, Bandit& bandit) {
    os << "bandit: " << *static_cast<NPC*>(&bandit) << std::endl;
    return os;
}