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
	using idSprite = long;

	class Renderer {
	public:
		Renderer();
		~Renderer();

		void render();
		bool isRunning() const;
		void clearScene();
		void close();

		vec2d<int> getMousePosition() const;
		bool getKeyPressed(irr::EKEY_CODE &keyCode) const;

		irr::scene::ISceneNode *createElem(irr::core::stringw const &filename);
		irr::scene::IAnimatedMeshSceneNode *createAnimatedElem(irr::core::stringw const &filename);

		bool addTexture(irr::scene::ISceneNode *node, const irr::core::stringw &filename);
		void addAnimation(irr::scene::IAnimatedMeshSceneNode *node, const std::string &identifier,
			const vec2d<int> &range
		);

		void setAnimation(irr::scene::IAnimatedMeshSceneNode *node, const std::string &identifier);
		bool setAnimationSpeed(irr::scene::IAnimatedMeshSceneNode *node, float speed);
		bool setPosition(irr::scene::ISceneNode *node, const vec3d<float> &pos);
		bool setScale(irr::scene::ISceneNode *node, float scale);
		bool rotate(irr::scene::ISceneNode *node, const vec3d<float> &angle);

		vec3d<float> getSize(irr::scene::ISceneNode *node);

		void load2D(irr::core::stringw const &filename, const vec2d<int> &pos,
			const irr::core::rect<irr::s32> &rect
		);
		void load2D(irr::core::stringw const &filename, const vec2d<int> &pos);
		void addArchive(irr::core::stringw const &filename);

		bool isKeyPressed(irr::EKEY_CODE code);

		private:
		irr::IrrlichtDevice *device;
		irr::video::IVideoDriver *driver;
		irr::scene::ISceneManager *smgr;
		irr::gui::IGUIEnvironment *guienv;
		std::vector<gfx::image2D> images;
		MyEventReceiver eventReceiver;
		using animationMap = std::unordered_map<std::string, vec2d<int>>;
		std::unordered_map<irr::scene::ISceneNode *, animationMap> animations;
	};
};

#endif //CPP_INDIE_STUDIO_RENDERER_HPP
