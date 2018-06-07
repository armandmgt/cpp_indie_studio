/*
** EPITECH PROJECT, 2018
** cpp_indie_studio
** File description:
** EventReceiver
*/
#ifndef CPP_INDIE_STUDIO_EVENTRECEIVER_HPP
#define CPP_INDIE_STUDIO_EVENTRECEIVER_HPP

#include <irrlicht/irrlicht.h>
#include <map>

namespace gfx {

	class MyEventReceiver : public irr::IEventReceiver
	{
	public:
		struct SMouseState
		{
			irr::core::position2di position;
			bool LeftButtonDown;
			SMouseState() : LeftButtonDown(false) { }
		} mouseState;

		MyEventReceiver();
		bool OnEvent(const irr::SEvent& event) override;

		virtual bool isKeyDown(irr::EKEY_CODE keyCode) const;

		const SMouseState &getMouseState() const;


	private:
		bool keyIsDown[irr::KEY_KEY_CODES_COUNT];
	};
}

#endif //CPP_INDIE_STUDIO_EVENTRECEIVER_HPP
