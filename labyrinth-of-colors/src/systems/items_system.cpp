//
//  items_system.cpp
//  labyrinth-of-colors
//
//  Created by Fiodar Navumenka on 30.11.21.
//

#include "items_system.hpp"

#include <iostream>

#include "src/components/map_position.h"
#include "src/components/position.h"
#include "src/components/item.h"

#include "src/texture.h"

std::vector<entt::entity> ItemsSystem::get_items_at(const MapPosition& position)
{
    std::cout << "Getting items at " << position.i << ", " << position.j << std::endl;
    
    auto items = std::vector<entt::entity>{};
    
    for (const auto [e, item, pos] : registry.view<Item, MapPosition>().each())
    {
        if (pos != position)
        {
            continue;
        }
        
        items.push_back(e);
    }
    
    return items;
}

void ItemsSystem::remove_item_from_map(const entt::entity& item)
{
    registry.remove<MapPosition>(item);
    registry.remove<Position>(item);
}
