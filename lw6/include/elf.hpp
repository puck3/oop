#pragma once
#include "npc.hpp"
#include "visitor.hpp"

class Elf : public NPC {
public:
    Elf(int x, int y);
    Elf(std::istream& is);

    virtual bool accept(const std::shared_ptr<Visitor>&) const override;

    void print() override;
    void save(std::ostream& os) override;

    friend std::ostream& operator<<(std::ostream& os, Elf& elf);
};