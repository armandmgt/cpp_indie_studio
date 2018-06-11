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

	using playerId = std::size_t;

	struct Event
	{
		eventType type;
		eventAction action;
		eventKey key;
	};

	struct PlayerEvent {
		playerId id;
		Event event;
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
		bool getKeyPressed(irr::EKEY_CODE &keyCode);

		bool hasEvent();
		std::queue<evt::Event> getPlayerEvent(std::size_t id);

		void setKeymap(std::array<irr::EKEY_CODE, 5> &keymapToSet);

		private:
		bool _fillKey();

		std::multimap<playerId, Event> buffer;
		std::vector<irr::EKEY_CODE> keyboardPressed;
		bool keyIsDown[irr::KEY_KEY_CODES_COUNT];
		std::map<evt::eventAction, irr::EKEY_CODE> keymap;
	};
}

#endif //CPP_INDIE_STUDIO_EVENTRECEIVER_HPP
