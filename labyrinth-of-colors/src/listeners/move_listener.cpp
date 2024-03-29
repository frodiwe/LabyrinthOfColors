//
//  move_listener.cpp
//  labyrinth-of-colors
//
//  Created by Fiodar Navumenka on 5.12.21.
//

#include "move_listener.hpp"

#include "src/events/exit_event.h"
#include "src/events/move_event.h"
#include "src/events/move_in_event.h"
#include "src/events/move_out_event.h"
#include "src/events/item_given_event.h"
#include "src/events/event.h"

#include "src/components/map_position.h"
#include "src/tags/player.h"

#include "src/level/tags/cell.h"
#include "src/level/components/exit.h"

#include "src/systems/movement_system.hpp"
#include "src/systems/render_system.hpp"
#include "src/systems/items_system.hpp"
#include "src/systems/inventory_system.hpp"
#include "src/systems/player_system.hpp"

#include "src/events_queue.hpp"

void MoveListener::operator()(Event *event)
{
    MoveEvent* e = dynamic_cast<MoveEvent*>(event);
    
    auto player = player_system->get_player();
    auto to = get_target_pos(registry.get<MapPosition>(player), get_abs_diff(e->i_diff, e->j_diff), e->i_diff < 0 or e->j_diff < 0);
    
    auto cell = get_cell(to);
    
    if (cell == entt::null)
    {
        return;
    }
    
    if (
        not movement_system->can_move(cell) or
        not inventory_system->has_color(player, registry.get<CellColor>(cell))
    )
    {
        return;
    }
    
    auto from_cell = get_cell(registry.get<MapPosition>(player));
    
    events_queue->publish<MoveOutEvent>(from_cell);
    movement_system->move(player, get_cell(registry.get<MapPosition>(player)), cell);
    events_queue->publish<MoveInEvent>(cell);
}
                           
entt::entity MoveListener::get_cell(const MapPosition& at) const
{
   for (const auto [entity, map_position] : registry.view<Cell, MapPosition>().each())
   {
       if (map_position.i == at.i and map_position.j == at.j) {
           return entity;
       }
   }
   
   return entt::null;
}

MapPosition MoveListener::get_target_pos(MapPosition curr_pos, MapPosition abs_diff, bool backward)
{
    return backward ? curr_pos - abs_diff : curr_pos + abs_diff;
}

MapPosition MoveListener::get_abs_diff(int32_t i_diff, int32_t j_diff)
{
    return {
        static_cast<size_t>(std::abs(i_diff)),
        static_cast<size_t>(std::abs(j_diff))
    };
}
