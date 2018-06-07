/*
** EPITECH PROJECT, 2018
** Event
** File description:
** none
*/

#ifndef EVENT_HPP_
	#define EVENT_HPP_

	#include <map>
	#include <queue>
	#include "enum/EventEnum.hpp"
	#include "gfx/Renderer.hpp"

	namespace ids {

		struct eventType
		{
			eventAction action;
			eventKey key;
		};

		class Event
		{
		public:
			explicit Event(gfx::Renderer &window) noexcept;
			~Event() = default;
			bool pollEvent();
			std::queue<ids::eventType> getEvent(std::size_t index);
		private:
			bool _fillKey(irr::EKEY_CODE &keyCode);
			gfx::Renderer &renderer;
			std::multimap<std::size_t, eventType> buffer;
		};
	}

#endif