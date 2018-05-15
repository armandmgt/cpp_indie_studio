/*
** EPITECH PROJECT, 2018
** cpp_indie_studio
** File description:
** GameContainer
*/

#ifndef CPP_INDIE_STUDIO_GAMECONTAINER_HPP
#define CPP_INDIE_STUDIO_GAMECONTAINER_HPP

#include <irrlicht/irrlicht.h>
#ifdef _IRR_WINDOWS_
#pragma comment(lib, "Irrlicht.lib")
#pragma comment(linker, "/subsystem:windows /ENTRY:mainCRTStartup")
#endif

namespace ids {
	class GameContainer {
		public:
		virtual ~GameContainer();
		static GameContainer *create();
		GameContainer(GameContainer const &) = delete;
		GameContainer &operator=(GameContainer const &) = delete;

		void start();

		private:
		GameContainer();

		irr::video::IVideoDriver* driver;
		irr::scene::ISceneManager* smgr;
		irr::gui::IGUIEnvironment* guienv;
		irr::IrrlichtDevice *device;
	};
}

#endif //CPP_INDIE_STUDIO_GAMECONTAINER_HPP
