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
#include <deque>
#include "common/vec.hpp"
#include "enum/EventEnum.hpp"
#include "gfx/Image2D.hpp"
#include "event/EventReceiver.hpp"

namespace gfx {

	using idSprite = long;

	class Renderer {
	public:
		Renderer();
		~Renderer();

		void render();
		bool isRunning() const;
		void clearScene();
		void close();

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
		void remove2D(irr::core::stringw const &filename);
		void addArchive(irr::core::stringw const &filename);
		void setCameraFPS();
		evt::MyEventReceiver &getEventReceiver();

	public:
		evt::MyEventReceiver eventReceiver;
	private:
		irr::IrrlichtDevice *device;
		irr::video::IVideoDriver *driver;
		irr::scene::ISceneManager *smgr;
		irr::gui::IGUIEnvironment *guienv;
		std::deque<gfx::Image2D> images;
		using animationMap = std::unordered_map<std::string, vec2d<int>>;
		std::unordered_map<irr::scene::ISceneNode *, animationMap> animations;
	};
};

#endif //CPP_INDIE_STUDIO_RENDERER_HPP
