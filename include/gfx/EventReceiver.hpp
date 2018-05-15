/*
** EPITECH PROJECT, 2018
** cpp_indie_studio
** File description:
** EventReceiver
*/
#ifndef CPP_INDIE_STUDIO_EVENTRECEIVER_HPP
#define CPP_INDIE_STUDIO_EVENTRECEIVER_HPP

#include "irrlicht/irrlicht.h"

namespace gfx {

	class MyEventReceiver : public irr::IEventReceiver
	{
	public:
		MyEventReceiver();
		bool OnEvent(const irr::SEvent& event) override;
		virtual bool IsKeyDown(irr::EKEY_CODE keyCode) const;

	private:
		bool KeyIsDown[irr::KEY_KEY_CODES_COUNT];
	};
}

#endif //CPP_INDIE_STUDIO_EVENTRECEIVER_HPP
