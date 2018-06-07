//
// Created by Hoodie on 07/06/2018.
//

#pragma once

#include "Systems.hpp"

namespace ecs {
	class ExplosionSystem : public System {
	public:
		explicit ExplosionSystem(std::vector<Entity> *);

		void update(double) override;
	};
}
