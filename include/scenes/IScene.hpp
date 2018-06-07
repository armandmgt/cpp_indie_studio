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
			enum sceneId {
				GAME, QUIT, MENU, SETTINGS, SCORE, PAUSE, BACK
			};
			virtual ~IScene() = default;

			virtual sceneId run() = 0;
		};
}
#endif //SCENE_HPP
