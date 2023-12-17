#include "bandit.hpp"

Bandit::Bandit(const std::string& name, int x, int y) : NPC(BanditType, name, x, y) {
    move_distance = 10;
    kill_distance = 10;
}

Bandit::Bandit(std::istream& is) : NPC(BanditType, is) {
    move_distance = 10;
    kill_distance = 10;
}

bool Bandit::accept(const std::shared_ptr<NPC>& attacker) const {
    std::shared_ptr<Visitor> attacker_visitor = VisitorFactory::CreateVisitor(attacker->get_type());
    std::shared_ptr<Bandit> defender = std::dynamic_pointer_cast<Bandit>(std::const_pointer_cast<NPC>(shared_from_this()));
    bool result = attacker_visitor->visit(defender);
    attacker->fight_notify(defender, result);
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
    os << "bandit " << *static_cast<NPC*>(&bandit) << std::endl;
    return os;
}
