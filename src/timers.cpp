#include "timers.h"

TIMERS::TIMERS()
{

}

TIMERS::TIMERS(BUS* bus)
{
	this->bus = bus;
}

void TIMERS::tick(uint8_t elapsed_t_cycles)
{
	for (int i = 0; i < elapsed_t_cycles; i++)
	{
		update_div();
		update_tima();
	}
}

void TIMERS::update_div()
{
	bus->increment_system_counter();
}

void TIMERS::update_tima()
{
	uint8_t  timer_counter = bus->read_memory(TIMA);
	bool     falling_edge = false;

	falling_edge = is_falling_edge();
	if (falling_edge && (timer_counter == 0xFF))
	{
		uint8_t interrupt_flag = bus->read_memory(IF);
		bus->write_memory(IF, interrupt_flag | IF_TIMER_MASK);
		bus->write_memory(TIMA, bus->read_memory(TMA));
	}
	else if (falling_edge)
	{
		bus->write_memory(TIMA, ++timer_counter);
	}
}

bool TIMERS::is_falling_edge()
{
	uint8_t  timer_control = bus->read_memory(TAC);
	bool     last_falling_edge_state = bus->read_falling_edge_state();
	bool     tima_tick = false;
	tima_tick = is_tima_tick(timer_control);
	tima_tick &= ((timer_control & TAC_ENABLE_MASK) >> 2);
	bus->write_falling_edge_state(tima_tick);
	return last_falling_edge_state == 1 && tima_tick == 0;
}

bool TIMERS::is_tima_tick(uint8_t  timer_control)
{
	uint16_t system_counter = bus->read_system_counter();
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
