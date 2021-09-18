//
//  listener.hpp
//  labyrinth-of-colors
//
//  Created by Fiodar Navumenka on 9.08.21.
//

#ifndef listener_hpp
#define listener_hpp

#include <functional>

#include "events_queue.hpp"

enum class Event;

struct Listener
{
private:
	ListenerId listener_id;
	
	Event event;

public:
	Listener(Event, std::function<void()>);
	
	~Listener();
};

#endif /* listener_hpp */