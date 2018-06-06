/*
** EPITECH PROJECT, 2018
** Event
** File description:
** none
*/

#ifndef EVENT_HPP_
	#define EVENT_HPP_

	#include <unordered_map>
	#include <queue>
	#include "enum/EventEnum.hpp"
	#include "gfx/Renderer.hpp"

	namespace ids {

		union value_t
		{
			eventKey key;
			eventAction action;
		};

		struct player_t
		{
			int player;
			value_t value;
		}

		struct event_t
		{
			type_t type;
			player_t player;
		};

		class Event
		{
		public:
			explicit Event(gfx::Renderer &window);
			~Event();
			bool pollEvent(irr::EKEY_CODE &keyCode, event_t &event);
			void getBackEnd(event_t event, int player);
		private:
			bool getKey(irr::EKEY_CODE &keyCode);
			bool getAction(event_t event);
			gfx::Renderer &renderer;
			std::queue<event_t> buffer;
		};
	}

#endif