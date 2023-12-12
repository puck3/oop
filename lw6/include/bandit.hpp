#pragma once
#include "npc.hpp"
#include "visitor.hpp"

class Bandit : public NPC {
public:

    Bandit(int x, int y);
    Bandit(std::istream& is);

    virtual bool accept(const std::shared_ptr<Visitor>&) const override;

    void print() override;
    void save(std::ostream& os) override;

    friend std::ostream& operator<<(std::ostream& os, Bandit& bandit);
};