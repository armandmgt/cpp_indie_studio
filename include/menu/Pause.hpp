/*
** EPITECH PROJECT, 2018
** cpp_indie_studio
** File description:
** Pause
*/

#ifndef CPP_INDIE_STUDIO_PAUSE_HPP
#define CPP_INDIE_STUDIO_PAUSE_HPP

#include "menu/AMenu.hpp"

namespace ids {
	namespace menu {
		class Pause : public AMenu {
		public:
			Pause(std::shared_ptr<gfx::Renderer> rend, std::shared_ptr<Music> music);
			~Pause();

			sceneId run() override;
		private:
			evt::MyEventReceiver &_events;
		};
	}
}

#endif //CPP_INDIE_STUDIO_PAUSE_HPP
