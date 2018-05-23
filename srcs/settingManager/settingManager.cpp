/*
** EPITECH PROJECT, 2018
** cpp_indie_studio
** File description:
** SettingManager
*/

#include <iostream>
#include "settingManager/settingManager.hpp"

opt::settingManager::settingManager(std::string &name) : filename(name),
							       NullDevice(0)
{
	NullDevice = irr::createDevice(irr::video::EDT_NULL);
}

opt::settingManager::~settingManager()
{
	if (NullDevice) {
		NullDevice->closeDevice();
		NullDevice->drop();
	}
}

bool opt::settingManager::load()
{
	if (!NullDevice)
		return false;

	irr::core::stringw currentSection;
	irr::io::IXMLReader* xml = NullDevice->getFileSystem()->createXMLReader(filename.c_str());
	if (!xml)
		return false;
	while (xml->read())
	{
		switch (xml->getNodeType())
		{
			case irr::io::EXN_ELEMENT:
			{
				irr::core::stringw key = xml->getAttributeValueSafe(L"name");
				if (!key.empty())
				{
					settings[key] = xml->getAttributeValueSafe(L"value");
				}
			}
			break;
			case irr::io::EXN_ELEMENT_END:
				currentSection=L"";
				break;
		}
	}
	xml->drop();
	return true;
}

irr::core::stringw opt::settingManager::getValue(irr::core::stringw const &key) const
{
	irr::core::map<irr::core::stringw,
		irr::core::stringw>::Node *value = settings.find(key);
	if (value) {
		return value->getValue();
	}
	return L"";
}

