//
//  give_base_inventory_listener.cpp
//  labyrinth-of-colors
//
//  Created by Fiodar Navumenka on 4.02.22.
//

#include "give_base_inventory_listener.hpp"

#include "src/events/player_created_event.h"
#include "src/events/item_given_event.h"

#include "src/events_queue.hpp"

#include "src/systems/movement_system.hpp"
#include "src/systems/render_system.hpp"
#include "src/systems/items_system.hpp"
#include "src/systems/inventory_system.hpp"

#include "src/items_kit.hpp"
#include "src/category.h"

#include "src/level/cell_color.h"

void GiveBaseInventoryListener::operator()(Event *event)
{
    PlayerCreatedEvent* e = dynamic_cast<PlayerCreatedEvent*>(event);\
    
    auto items = std::vector{
        items_kit->create_item("yellow_paint", Category::Paint, CellColor::YELLOW),
        items_kit->create_item("yellow_paint_bucket", Category::Bucket, CellColor::YELLOW),
        
        items_kit->create_item("rainbow_paint", Category::Paint, CellColor::RAINBOW),
    };
    
    for (const auto& item : items)
    {
        inventory_system->give_item(e->player, item);
        events_queue->publish<ItemGivenEvent>(item);
    }
}
