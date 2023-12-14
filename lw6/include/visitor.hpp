#pragma once
#include "npc.hpp"
#include "elf.hpp"
#include "bandit.hpp"
#include "squirrel.hpp"

class Visitor {
public:
    virtual bool visit(const std::shared_ptr<Elf>&) const = 0;
    virtual bool visit(const std::shared_ptr<Bandit>&) const = 0;
    virtual bool visit(const std::shared_ptr<Squirrel>&) const = 0;
};

class ElfVisitor : public Visitor {
public:
    virtual bool visit(const std::shared_ptr<Elf>&) const override { return false; }
    virtual bool visit(const std::shared_ptr<Bandit>&) const override { return true; }
    virtual bool visit(const std::shared_ptr<Squirrel>&) const override { return false; }
};

class BanditVisitor : public Visitor {
    virtual bool visit(const std::shared_ptr<Elf>&) const override { return false; }
    virtual bool visit(const std::shared_ptr<Bandit>&) const override { return false; }
    virtual bool visit(const std::shared_ptr<Squirrel>&) const override { return true; }
};

class SquirrelVisitor : public Visitor {
    virtual bool visit(const std::shared_ptr<Elf>&) const override { return true; }
    virtual bool visit(const std::shared_ptr<Bandit>&) const override { return false; }
    virtual bool visit(const std::shared_ptr<Squirrel>&) const override { return false; }
};

class VisitorFactory {
public:
    static std::shared_ptr<Visitor> CreateVisitor(const NpcType& type) {
        std::shared_ptr<Visitor> result;
        switch (type) {
            case NpcType::ElfType:
                result = static_pointer_cast<Visitor>(std::make_shared<ElfVisitor>());
                break;

            case NpcType::BanditType:
                result = static_pointer_cast<Visitor>(std::make_shared<BanditVisitor>());
                break;

            case NpcType::SquirrelType:
                result = static_pointer_cast<Visitor>(std::make_shared<SquirrelVisitor>());
                break;
            default:
                break;
        }
        return result;
    }
};