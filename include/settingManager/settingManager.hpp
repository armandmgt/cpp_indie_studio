/*
** EPITECH PROJECT, 2018
** cpp_indie_studio
** File description:
** SettingManager
*/
#ifndef CPP_INDIE_STUDIO_SETTINGMANAGER_HPP
#define CPP_INDIE_STUDIO_SETTINGMANAGER_HPP

#include <irrlicht/irrlicht.h>
#include <string>

namespace opt {

	class settingManager {
	public:
		explicit settingManager(std::string &name);
		~settingManager();
		bool load();
		irr::core::stringw getValue(irr::core::stringw const &name) const;

	private:
		std::string &filename;
		irr::IrrlichtDevice* NullDevice;
		irr::core::map<irr::core::stringw, irr::core::stringw> settings;
	};
}


#endif //CPP_INDIE_STUDIO_SETTINGMANAGER_HPP
