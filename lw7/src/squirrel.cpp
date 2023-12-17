#include "squirrel.hpp"

Squirrel::Squirrel(const std::string& name, int x, int y) : NPC(SquirrelType, name, x, y) {
    move_distance = 5;
    kill_distance = 5;
}

Squirrel::Squirrel(std::istream& is) : NPC(SquirrelType, is) {
    move_distance = 5;
    kill_distance = 5;
}

bool Squirrel::accept(const std::shared_ptr<NPC>& attacker) const {
    std::shared_ptr<Visitor> attacker_visitor = VisitorFactory::CreateVisitor(attacker->get_type());
    std::shared_ptr<Squirrel> defender = std::dynamic_pointer_cast<Squirrel>(std::const_pointer_cast<NPC>(shared_from_this()));
    bool result = attacker_visitor->visit(defender);
    attacker->fight_notify(defender, result);
    return result;
}

void Squirrel::print() {
    std::cout << *this;
}

void Squirrel::save(std::ostream& os) {
    os << SquirrelType << std::endl;
    NPC::save(os);
}

std::ostream& operator<<(std::ostream& os, Squirrel& squirrel) {
    os << "squirrel " << *static_cast<NPC*>(&squirrel) << std::endl;
    return os;
}
