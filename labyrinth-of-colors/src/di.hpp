//
//  di.hpp
//  labyrinth-of-colors
//
//  Created by Fiodar Navumenka on 11.09.21.
//

#ifndef di_hpp
#define di_hpp

#include <memory>
#include <optional>

class RenderList;
class RenderController;
class LevelKit;
class MapKit;
class CellKit;

class DI
{
private:
	static std::shared_ptr<RenderList> render_list;
	
	static std::shared_ptr<RenderController> render_controller;
	
	static CellKit* cell_kit;
	
	static MapKit* map_kit;
	
	static LevelKit* level_kit;
	
public:
	static std::shared_ptr<RenderList> get_render_list();
	
	static std::shared_ptr<RenderController> get_render_controller();
	
	static LevelKit* get_level_kit();
};

#endif /* di_hpp */