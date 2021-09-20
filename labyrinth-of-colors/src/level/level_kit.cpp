//
//  level_kit.cpp
//  labyrinth-of-colors
//
//  Created by Fiodar Navumenka on 13.09.21.
//

#include "level_kit.hpp"

#include <SDL2/SDL.h>

#include <memory>

#include "src/level/level.hpp"
#include "src/level/map.hpp"
#include "src/level/cell.hpp"
#include "src/level/map_position_controller.hpp"
#include "src/player.hpp"
#include "src/entity.h"
#include "src/texture.h"
#include "src/render_component.h"
#include "src/level/map_kit.hpp"
#include "src/level/level_config.h"
#include "src/coord.hpp"

LevelKit::LevelKit(MapKit* map_kit):
	map_kit{map_kit}
{ }

Level LevelKit::create_level(SDL_Renderer* renderer, LevelConfig config) const
{
	auto map = map_kit->create_map(renderer, config.labyrinth);
	auto player = new Player{
		std::unique_ptr<RenderComponent>{
			new Texture{
				renderer,
				"/Volumes/Development/gamedev/projects/labyrinth-of-colors/labyrinth-of-colors/assets/wizard-idle.png",
				{0, 0, 32, 32}
			}
		},
		{Coord::start_x + map->at(0, 0)->x(), Coord::start_y + map->at(0, 0)->y(), 100, 100}
	};
	
	return Level{player, map, new MapPositionController{player, map}};
}
