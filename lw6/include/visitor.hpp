#pragma once
#include "npc.hpp"

class Visitor {
public:
    virtual bool visit(const std::shared_ptr<Elf>&) const = 0;
    virtual bool visit(const std::shared_ptr<Bandit>&) const = 0;
    virtual bool visit(const std::shared_ptr<Squirrel>&) const = 0;
};

class ElfVisitor final : public Visitor {
public:
    virtual bool visit(const std::shared_ptr<Elf>&) const override;
    virtual bool visit(const std::shared_ptr<Bandit>&) const override;
    virtual bool visit(const std::shared_ptr<Squirrel>&) const override;
};

class BanditVisitor final : public Visitor {
    virtual bool visit(const std::shared_ptr<Elf>&) const override;
    virtual bool visit(const std::shared_ptr<Bandit>&) const override;
    virtual bool visit(const std::shared_ptr<Squirrel>&) const override;
};

class SquirrelVisitor final : public Visitor {
    virtual bool visit(const std::shared_ptr<Elf>&) const override;
    virtual bool visit(const std::shared_ptr<Bandit>&) const override;
    virtual bool visit(const std::shared_ptr<Squirrel>&) const override;
};
