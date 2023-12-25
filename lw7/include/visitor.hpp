#pragma once
#include "npc.hpp"

class Visitor {
public:
    virtual bool visit(const std::shared_ptr<NPC>&) const = 0;
};

class ElfVisitor final : public Visitor {
public:
    bool visit(const std::shared_ptr<NPC>& npc) const override {
        bool result{};
        switch (npc->get_type()) {
            case NpcType::ElfType:
                result = false;
                break;

            case NpcType::BanditType:
                result = true;
                break;

            case NpcType::SquirrelType:
                result = false;
                break;
        }
        return result;
    }
};

class BanditVisitor final : public Visitor {
    bool visit(const std::shared_ptr<NPC>& npc) const override {
        bool result{};
        switch (npc->get_type()) {
            case NpcType::ElfType:
                result = false;
                break;

            case NpcType::BanditType:
                result = false;
                break;

            case NpcType::SquirrelType:
                result = true;
                break;
        }
        return result;
    }
};

class SquirrelVisitor final : public Visitor {
    bool visit(const std::shared_ptr<NPC>& npc) const override {
        bool result{};
        switch (npc->get_type()) {
            case NpcType::ElfType:
                result = true;
                break;

            case NpcType::BanditType:
                result = false;
                break;

            case NpcType::SquirrelType:
                result = false;
                break;
        }
        return result;
    }
};

class VisitorFactory {
public:
    static std::shared_ptr<Visitor> CreateVisitor(const NpcType& type) {
        std::shared_ptr<Visitor> result;
        switch (type) {
            case NpcType::ElfType:
                result = std::static_pointer_cast<Visitor>(std::make_shared<ElfVisitor>());
                break;

            case NpcType::BanditType:
                result = std::static_pointer_cast<Visitor>(std::make_shared<BanditVisitor>());
                break;

            case NpcType::SquirrelType:
                result = std::static_pointer_cast<Visitor>(std::make_shared<SquirrelVisitor>());
                break;
            default:
                break;
        }
        return result;
    }
};
