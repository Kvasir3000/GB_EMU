#include "timers.h"

TIMERS::TIMERS()
{
	system_counter = 0xABCC;
	tima = 0x00;
	tma = 0x00;
	timer_control = 0xF8;
	last_falling_edge_state = false;

}

bool TIMERS::tick(uint8_t elapsed_t_cycles)
{
	bool request_timer_interrupt = false;
	for (int i = 0; i < elapsed_t_cycles; i++)
	{
		update_div();
		if (update_tima())
		{
			request_timer_interrupt = true;
		};
	}
	return request_timer_interrupt;
}

void TIMERS::update_div()
{
	system_counter++;
}

bool TIMERS::update_tima()
{
	uint8_t  timer_counter = tima;
	bool     falling_edge = false;
	bool     request_timer_interrupt = false;
	falling_edge = is_falling_edge();
	if (falling_edge && (timer_counter == 0xFF))
	{
		request_timer_interrupt = true;
		tima = tma;
	}
	else if (falling_edge)
	{
		tima++;
	}
	return request_timer_interrupt;
}

bool TIMERS::is_falling_edge()
{
	bool tima_tick = false;
	tima_tick = is_tima_tick(timer_control);
	tima_tick &= ((timer_control & TAC_ENABLE_MASK) >> 2);
	bool result = last_falling_edge_state == 1 && tima_tick == 0;
	last_falling_edge_state = tima_tick;
	return result;
}

bool TIMERS::is_tima_tick(uint8_t  timer_control)
{
	bool tima_tick = false;

	if (timer_control & TAC_CLOCK_00_4096_HZ)
	{
		tima_tick = system_counter & TAC_CLOCK_00_SYSTEM_COUNTER_BIT;
	}
	else if (timer_control & TAC_CLOCK_01_262144_HZ)
	{
		tima_tick = system_counter & TAC_CLOCK_01_SYSTEM_COUNTER_BIT;
	}
	else if (timer_control & TAC_CLOCK_10_65536_HZ)
	{
		tima_tick = system_counter & TAC_CLOCK_10_SYSTEM_COUNTER_BIT;
	}
	else if (timer_control & TAC_CLOCK_11_16384_HZ)
	{
		tima_tick = system_counter & TAC_CLOCK_11_SYSTEM_COUNTER_BIT;
	}

	return tima_tick;
}

uint8_t TIMERS::read_div()
{
	return (system_counter & 0xF0) >> 8;
}

uint8_t TIMERS::read_tac()
{
	return timer_control;
}

uint8_t TIMERS::read_tima()
{
	return tima;
}

uint8_t TIMERS::read_tma()
{
	return tma;
}

void TIMERS::reset_div()
{
	system_counter = 0;
}

void TIMERS::write_tima(uint8_t tima)
{
	this->tima = tima;
}

void TIMERS::write_timer_control(uint8_t tac)
{
	last_falling_edge_state &= ((tac & TAC_ENABLE_MASK) >> 2);
	timer_control = tac;
}

void TIMERS::write_tma(uint8_t tma)
{
	this->tma = tma;
}


