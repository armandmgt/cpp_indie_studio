/*
** EPITECH PROJECT, 2018
** Event
** File description:
** none
*/

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
	static std::unordered_map<eventKey, player_t> const eventType = {
		{NONE, {0, NOTHING}}, {UP, {1, MOVEUP}}, {DOWN, {1, MOVEDOWN}},
		{RIGHT, {1, MOVERIGHT}}, {LEFT, {1, MOVELEFT}},
		{A, {2, PUTBOMB}}, {B, {1, NOTHING}}, {C, {2, NOTHING}},
		{D, {2, MOVERIGHT}}, {E, {2, PUTITEM}}, {F, {2, NOTHING}},
		{G, {2, NOTHING}}, {H, {1, NOTHING}}, {I, {1, NOTHING}},
		{J, {1, NOTHING}}, {K, {1, NOTHING}}, {L, {1, NOTHING}},
		{M, {1, NOTHING}}, {N, {1, NOTHING}}, {O, {1, NOTHING}},
		{P, {1, NOTHING}}, {Q, {2, MOVELEFT}}, {R, {2, NOTHING}},
		{S, {2, MOVEDOWN}}, {T, {2, NOTHING}}, {U, {1, NOTHING}},
		{V, {2, NOTHING}}, {W, {2, NOTHING}}, {X, {2, NOTHING}},
		{Y, {1, NOTHING}}, {Z, {2, MOVEUP}}, {SPACE, {1, PAUSE}},
		{DELE, {1, RESTART}}, {ESCAPE, {1, MENU}}, {MOUSE, {1, CLICK}}
	};

	for (auto it = eventType.begin(); it != eventType.end(); it++) {
		if (it->first == event.player.value.key) {
			tmp.player.value.action = it->second->value;
			tmp.player.player = it->second->player;
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
			tmp.player.value.key = it->second;
			tmp.type = KEY;
			buffer.push(tmp);
			getAction(tmp);
			return true;
		}
	}
	return false;
}

void ids::Event::getBackEnd(event_t event, int player)
{
	auto head;

	for (auto it : buffer) {
		if (event.player.player == player)
			;
		else if (event.player.player != player && *it == NULL) {
			head = *it;
			buffer.push(event);
		} else if (event.player.player != player && *it == head) {
			buffer.push(event);
		}
	}
	buffer = buffer.end() - 1;
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