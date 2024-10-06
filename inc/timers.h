#pragma once 
#include "bus.h"
#include "timers.h"


class TIMERS
{
public: 
	TIMERS();
	TIMERS(BUS* bus);
	void tick(uint8_t elapsed_t_cycles);


private: 
	BUS* bus;
	void update_div();
	void update_tima();
	bool is_tima_tick(uint8_t  timer_control);
	bool is_falling_edge();
};