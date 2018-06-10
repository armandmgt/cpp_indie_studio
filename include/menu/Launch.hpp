/*
** EPITECH PROJECT, 2018
** cpp_indie_studio
** File description:
** Launch
*/

#ifndef LAUNCH_HPP
#define LAUNCH_HPP

#include "menu/AMenu.hpp"

namespace ids {
	namespace menu {
		class Launch : public AMenu {
		public:
			struct Items {
				std::string name;
				int timer;
				irr::core::stringw path;
				vec2d<int> pos;
			};

			Launch(std::shared_ptr<gfx::Renderer> rend, std::shared_ptr<Music> music);
			~Launch() override;
			sceneId run() override;
		private:
			void decorateScene();
			evt::MyEventReceiver &_events;
			std::vector<Items> _items;
		};
	}
}

#endif //LAUNCH_HPP
