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
#include "gfx/Image2D.hpp"
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
		void newScene();
		irr::scene::ISceneManager *getScene();
		vec2d<int> getMousePosition();
		ids::eventKey pollEvent();
		void load2D(irr::core::stringw const &filename, vec2d<int> &positon,
			    irr::core::rect<irr::s32> &size);
		void load2D(irr::core::stringw const &filename, vec2d<int> &positon);
		void addArchive(irr::core::stringw const &filename);
		void clearScene();
		void drawText(vec2d<int> const &p, std::string const &filename, bool fillBackground = true);

	private:

		irr::IrrlichtDevice *device;
		irr::video::IVideoDriver *driver;
		irr::scene::ISceneManager *smgr;
		irr::gui::IGUIEnvironment* guienv;
		std::vector<gfx::image2D> images;
		MyEventReceiver Event;
	};
};


#endif //CPP_INDIE_STUDIO_RENDERER_HPP
