#include "visitor.hpp"



bool ElfVisitor::visit(const std::shared_ptr<Elf>& other) const {
    return false;
}

bool ElfVisitor::visit(const std::shared_ptr<Bandit>& other) const {
    return true;
}

bool ElfVisitor::visit(const std::shared_ptr<Squirrel>& other) const {
    return false;
}

bool BanditVisitor::visit(const std::shared_ptr<Elf>& other) const {
    return false;
}

bool BanditVisitor::visit(const std::shared_ptr<Bandit>& other) const {
    return false;
}

bool BanditVisitor::visit(const std::shared_ptr<Squirrel>& other) const {
    return true;
}

bool SquirrelVisitor::visit(const std::shared_ptr<Elf>& other) const {
    return true;
}

bool SquirrelVisitor::visit(const std::shared_ptr<Bandit>& other) const {
    return false;
}

bool SquirrelVisitor::visit(const std::shared_ptr<Squirrel>& other) const {
    return false;
}
