#pragma once
#include "npc.hpp"
#include "elf.hpp"
#include "bandit.hpp"
#include "squirrel.hpp"
#include "observer.hpp"

class Factory {
public:
    static std::shared_ptr<NPC> CreateNPC(const NpcType& type, const std::string& name, int x, int y) {
        std::shared_ptr<NPC> result;
        if (type > NpcType::UnknownType && type < NpcType::Max) {

            switch (type) {
                case NpcType::ElfType:
                    result = std::static_pointer_cast<NPC>(std::make_shared<Elf>(name, x, y));
                    break;

                case NpcType::BanditType:
                    result = std::static_pointer_cast<NPC>(std::make_shared<Bandit>(name, x, y));
                    break;

                case NpcType::SquirrelType:
                    result = std::static_pointer_cast<NPC>(std::make_shared<Squirrel>(name, x, y));
                    break;
                default:
                    break;
            }
        } else {
            std::string err = "unexpected NPC type: " + type;
            throw std::runtime_error(err);
        }

        if (result) {
            result->subscribe(TextObserver::get());
            result->subscribe(FileObserver::get());
        }

        return result;
    }

    static std::shared_ptr<NPC> CreateNPC(std::istream& is) {
        std::shared_ptr<NPC> result;
        int type{0};
        if (is >> type && type > NpcType::UnknownType && type < NpcType::Max) {
            switch (type) {
                case NpcType::ElfType:
                    result = std::static_pointer_cast<NPC>(std::make_shared<Elf>(is));
                    break;

                case NpcType::BanditType:
                    result = std::static_pointer_cast<NPC>(std::make_shared<Bandit>(is));
                    break;

                case NpcType::SquirrelType:
                    result = std::static_pointer_cast<NPC>(std::make_shared<Squirrel>(is));
                    break;
                default:
                    break;
            }
        } else {
            std::string err = "unexpected NPC type: " + type;
            throw std::runtime_error(err);
        }

        if (result) {
            result->subscribe(TextObserver::get());
            result->subscribe(FileObserver::get());
        }

        return result;
    }
};




