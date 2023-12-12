#pragma once
#include "npc.hpp"
#include "observer.hpp"

class Factory {
public:
    static std::shared_ptr<NPC> CreateNPC(const NpcType& type, int x, int y) {
        std::shared_ptr<NPC> result;
        switch (type) {
            case NpcType::ElfType:
                result = static_pointer_cast<NPC>(std::make_shared<Elf>(x, y));
                break;

            case NpcType::BanditType:
                result = static_pointer_cast<NPC>(std::make_shared<Bandit>(x, y));
                break;

            case NpcType::SquirrelType:
                result = static_pointer_cast<NPC>(std::make_shared<Squirrel>(x, y));
                break;
            default:
                break;
        }

        if (result) {
            result->subscribe(TextObserver::get());
        }

        return result;
    }
    static std::shared_ptr<NPC> CreateNPC(std::istream& is) {
        std::shared_ptr<NPC> result;
        int type{0};
        if (is >> type) {
            switch (type) {
                case NpcType::ElfType:
                    result = static_pointer_cast<NPC>(std::make_shared<Elf>(is));
                    break;

                case NpcType::BanditType:
                    result = static_pointer_cast<NPC>(std::make_shared<Bandit>(is));
                    break;

                case NpcType::SquirrelType:
                    result = static_pointer_cast<NPC>(std::make_shared<Squirrel>(is));
                    break;
                default:
                    break;
            }
        } else {
            std::cerr << "unexpected NPC type:" << type << std::endl;
        }

        if (result) {
            result->subscribe(TextObserver::get());
        }

        return result;
    }
};


