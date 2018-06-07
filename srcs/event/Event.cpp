/*
** EPITECH PROJECT, 2018
** Event
** File description:
** none
*/

#include <chrono>
#include <thread>
#include <iterator>
#include <irrlicht/Keycodes.h>
#include "event/Event.hpp"

ids::Event::Event(gfx::Renderer &window) : renderer(window)
{
}

ids::Event::~Event()
{
}

bool ids::Event::getAction(event_t event)
{
	event_t tmp{};
	static std::unordered_map<eventKey, eventAction> const eventType = {
		{NONE, NOTHING}, {UP, MOVEUP}, {DOWN, MOVEDOWN},
		{RIGHT, MOVERIGHT}, {LEFT, MOVELEFT}, {A, PUTBOMB},
		{B, NOTHING}, {C, NOTHING}, {D, MOVERIGHT}, {E, PUTITEM},
		{F, NOTHING}, {G, NOTHING}, {H, NOTHING}, {I, NOTHING},
		{J, NOTHING}, {K, NOTHING}, {L, NOTHING}, {M, NOTHING},
		{N, NOTHING}, {O, NOTHING}, {P, NOTHING}, {Q, MOVELEFT},
		{R, NOTHING}, {S, MOVEDOWN}, {T, NOTHING}, {U, NOTHING},
		{V, NOTHING}, {W, NOTHING}, {X, NOTHING}, {Y, NOTHING},
		{Z, MOVEUP}, {SPACE, PAUSE}, {DELE, RESTART}, {ESCAPE, MENU},
		{MOUSE, CLICK}
	};
	for (auto it = eventType.begin(); it != eventType.end(); it++) {
		if (it->first == event.value.key) {
			tmp.value.action = it->second;
			tmp.type = ACTION;
			buffer.push(tmp);
			return true;
		}
	}
	return false;
}

bool ids::Event::getKey(irr::EKEY_CODE &keyCode)
{
	event_t tmp{};
	static std::unordered_map<irr::EKEY_CODE, eventKey> const key = {
		{irr::KEY_UP, UP}, {irr::KEY_DOWN, DOWN},
		{irr::KEY_RIGHT, RIGHT}, {irr::KEY_LEFT, LEFT},
		{irr::KEY_KEY_A, A}, {irr::KEY_KEY_B, B}, {irr::KEY_KEY_C, C},
		{irr::KEY_KEY_D, D}, {irr::KEY_KEY_E, E}, {irr::KEY_KEY_F, F},
		{irr::KEY_KEY_G, G}, {irr::KEY_KEY_H, H}, {irr::KEY_KEY_I, I},
		{irr::KEY_KEY_J, J}, {irr::KEY_KEY_K, K}, {irr::KEY_KEY_L, L},
		{irr::KEY_KEY_M, M}, {irr::KEY_KEY_N, N}, {irr::KEY_KEY_O, O},
		{irr::KEY_KEY_P, P}, {irr::KEY_KEY_Q, Q}, {irr::KEY_KEY_R, R},
		{irr::KEY_KEY_S, S}, {irr::KEY_KEY_T, T}, {irr::KEY_KEY_U, U},
		{irr::KEY_KEY_V, V}, {irr::KEY_KEY_W, W}, {irr::KEY_KEY_X, X},
		{irr::KEY_KEY_Y, Y}, {irr::KEY_KEY_Z, Z},
		{irr::KEY_SPACE, SPACE}, {irr::KEY_DELETE, DELE},
		{irr::KEY_ESCAPE, ESCAPE}, {irr::KEY_LBUTTON, MOUSE}
	};

	for (auto it : key) {
		if (keyCode == it.first) {
			tmp.value.key = it.second;
			tmp.type = KEY;
			buffer.push(tmp);
			getAction(tmp);
			return true;
		}
	}
	return false;
}

bool ids::Event::pollEvent(irr::EKEY_CODE &keyCode, event_t &event)
{
	event_t tmp{};

	if (renderer.getKeyPressed(keyCode))
		getKey(keyCode);
	if (buffer.empty())
		return false;
	tmp = buffer.front();
	if (tmp.type == ACTION)
		event.type = ACTION;
	else
		event.type = KEY;
	event.value = tmp.value;
	buffer.pop();
	return true;
}