/*
** EPITECH PROJECT, 2018
** cpp_indie_studio
** File description:
** IScene
*/

#ifndef ISCENE_HPP
#define ISCENE_HPP

namespace ids {
		class IScene {
		public:
			enum SceneId {
				GAME, QUIT, MENU, SETTINGS, SCORE, PAUSE
			};
			virtual ~IScene() = default;
			virtual SceneId getSceneId() = 0;
		};
}

#endif //SCENE_HPP
