#include "src/window.hpp"
#include "src/game.hpp"
#include "src/events/event.h"
#include "src/coord.hpp"
#include "src/consts.h"
#include "src/di.hpp"
#include "src/key_handler.hpp"

#include <chrono>
#include <thread>

using namespace std::literals;

std::ostream& operator<<(std::ostream& os, Event* e)
{
    os << e->get_name();
    
	return os;
}

int main(int argc, char *argv[])
{
	Coord::start_x = 400;
	Coord::start_y = 300;
	
    auto window = Window{800, 600, new KeyHandler{DI::get_events_queue()}};
	auto game = Game(&window, DI::get_events_queue());
    
    constexpr std::chrono::milliseconds ms_per_frame = 1s / Consts::fps;
	
	while (not window.is_quited())
	{
        const auto start = std::chrono::steady_clock::now();
        
		window.process_events();
		game.render(window.get_renderer());
        
        std::this_thread::sleep_until(start + ms_per_frame);
	}
	
	return EXIT_SUCCESS;
}
