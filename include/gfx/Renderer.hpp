/*
** EPITECH PROJECT, 2018
** cpp_indie_studio
** File description:
** Renderable
*/
#ifndef CPP_INDIE_STUDIO_RENDERER_HPP
#define CPP_INDIE_STUDIO_RENDERER_HPP

#include <irrlicht/irrlicht.h>
#include <vector>
#include "common/vec.hpp"
#include "enum/EventEnum.hpp"
#include "Renderable.hpp"
#include "EventReceiver.hpp"

namespace gfx {

	using mabBinding = std::unordered_map<irr::EKEY_CODE, ids::eventKey>;

	class Renderer {
	public:
		Renderer();
		~Renderer();
		void render(std::vector<Renderable> &v);
		void render();
		bool isRun();
		vec2d<int> getMousePosition();
		ids::eventKey pollEvent();

	private:
		void renderGameBoad();

		irr::IrrlichtDevice *device;
		irr::video::IVideoDriver *driver;
		irr::scene::ISceneManager *smgr;
		MyEventReceiver Event;
	};
};


#endif //CPP_INDIE_STUDIO_RENDERER_HPP
