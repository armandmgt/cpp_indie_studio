/*
** EPITECH PROJECT, 2018
** cpp_indie_studio
** File description:
** LoadGame
*/

#ifndef CPP_INDIE_STUDIO_LOADGAME_HPP
#define CPP_INDIE_STUDIO_LOADGAME_HPP
#include "menu/AMenu.hpp"

namespace ids {
	namespace menu {
		class LoadGame : public AMenu {
			struct Items {
				irr::core::stringw path;
				vec2d<int> pos;
				vec2d<int> size;
			};
		public:
			LoadGame(std::shared_ptr<gfx::Renderer> rend, std::shared_ptr<Music> music);
			~LoadGame() override;

			sceneId run() override;
		private:
			void	itemEvent();
			evt::MyEventReceiver &_events;
			std::vector<Items> _items;
			std::size_t _itemIndex;
		};
	}
};

#endif //CPP_INDIE_STUDIO_LOADGAME_HPP
