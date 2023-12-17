#pragma once
#include "npc.hpp"
#include "visitor.hpp"

class Squirrel final : public NPC {
public:
    Squirrel(const std::string&, int, int);
    Squirrel(std::istream&);

    virtual bool accept(const std::shared_ptr<NPC>&) const override;

    void print() override;
    void save(std::ostream&) override;

    friend std::ostream& operator<<(std::ostream&, Squirrel&);
};