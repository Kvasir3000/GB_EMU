#pragma once 
#include <stdint.h>

#include "timers.h"
#include "common/timers_defs.h"


class TIMERS
{
public: 
	TIMERS();
	bool tick(uint8_t elapsed_t_cycles);
    void reset_div();
	uint8_t read_div();
	uint8_t read_tima();
	uint8_t read_tac();

	void write_timer_control(uint8_t tac);


private: 
	uint16_t system_counter;
	uint8_t  timer_control;
	uint8_t  tma;
	uint8_t  tima;
	bool     falling_edge_state;
	bool     last_falling_edge_state;
	void     update_div();
	bool     update_tima();
	bool     is_tima_tick(uint8_t  timer_control);
	bool     is_falling_edge();
};