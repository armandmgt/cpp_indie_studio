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

		enum type_t
		{
			ACTION,
			KEY
		};

		struct event_t
		{
			value_t value;
			type_t type;
		};

		class Event
		{
		public:
			explicit Event(gfx::Renderer &window);
			~Event();

			bool getKey(irr::EKEY_CODE &keyCode, event_t &event);
			bool getAction(event_t event);

			// Event *registerTimeoutItm(unsigned int time, eventAction type);
			bool pollEvent(irr::EKEY_CODE &keyCode, event_t &event);
		private:
			gfx::Renderer &renderer;
			std::queue<event_t> buffer;
		};
	}

#endif