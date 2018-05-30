/*
** EPITECH PROJECT, 2018
** cpp_indie_studio
** File description:
** Renderable
*/
#ifndef CPP_INDIE_STUDIO_RENDERER_HPP
#define CPP_INDIE_STUDIO_RENDERER_HPP

#include <irrlicht/irrlicht.h>
#include <unordered_map>
#include <vector>
#include "common/vec.hpp"
#include "enum/EventEnum.hpp"
#include "gfx/Image2D.hpp"
#include "EventReceiver.hpp"

namespace gfx {

	using mabBinding = std::unordered_map<irr::EKEY_CODE, ids::eventKey>;
	using idSprite = size_t;

	class Renderer {
	public:
		Renderer() noexcept;
		~Renderer();
		void render();
		bool isRun() const;
		void clearScene();

		vec2d<int> getMousePosition();
		ids::eventKey pollEvent();
		idSprite createMesh(irr::core::stringw const &filename);
		idSprite createb3dMesh(irr::core::stringw const &filename);
		bool addTexture(idSprite id, std::string filename);
		bool setAnimationSpeed(idSprite, float speed);
		bool setPosition(idSprite id, vec3d<float> position);
		bool rotateMesh(idSprite id, vec3d<float> angle);
		vec3d<float> getSizeMesh(idSprite id);

		void addArchive(irr::core::stringw const &filename);
		void load2D(irr::core::stringw const &filename, vec2d<int> &positon,
			    irr::core::rect<irr::s32> &size);
		void load2D(irr::core::stringw const &filename, vec2d<int> &positon);

	private:

		irr::IrrlichtDevice *device;
		irr::video::IVideoDriver *driver;
		irr::scene::ISceneManager *smgr;
		irr::gui::IGUIEnvironment *guienv;

		std::vector<gfx::image2D> images;

		idSprite _id;
		std::vector<irr::scene::IAnimatedMeshSceneNode *> animatedMeshs;
		std::vector<irr::scene::IAnimatedMesh *> meshs;
		std::vector<irr::scene::ISceneNode *> node;

		MyEventReceiver Event;
	};
};


#endif //CPP_INDIE_STUDIO_RENDERER_HPP
