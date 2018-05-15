/*
** EPITECH PROJECT, 2018
** Event
** File description:
** none
*/

#ifndef EVENT_HPP_
	#define EVENT_HPP_

	#include <irrlicht.h>

	namespace is {

		class Event : public IEventReceiver
		{
			Event();
			~Event();
		};
	}

#endif