/*
** EPITECH PROJECT, 2018
** cpp_indie_studio
** File description:
** EventReceiver
*/
#ifndef CPP_INDIE_STUDIO_EVENTRECEIVER_HPP
#define CPP_INDIE_STUDIO_EVENTRECEIVER_HPP

#include <irrlicht/irrlicht.h>
#include <queue>
#include <map>
#include "enum/EventEnum.hpp"

namespace evt {
	struct eventType
	{
		eventAction action;
		eventKey key;
	};

	class MyEventReceiver : public irr::IEventReceiver
	{
	public:
		struct MouseState
		{
			MouseState() : leftButtonDown(false) {};

			irr::core::position2di position;
			bool leftButtonDown;
		} mouseState;

		MyEventReceiver();

		bool OnEvent(const irr::SEvent& event) override;

		bool isKeyDown(irr::EKEY_CODE keyCode) const;
		const MouseState &getMousePosition() const;
		bool getKeyPressed(irr::EKEY_CODE &keyCode) const;

		bool pollEvent();
		std::queue<evt::eventType> getPlayerEvent(std::size_t playerId);

	private:
		bool _fillKey(irr::EKEY_CODE &keyCode);

		std::multimap<std::size_t, eventType> buffer;
		bool keyIsDown[irr::KEY_KEY_CODES_COUNT];
	};
}

#endif //CPP_INDIE_STUDIO_EVENTRECEIVER_HPP
