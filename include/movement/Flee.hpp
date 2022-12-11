/**
 * @file Flee.hpp
 * @author Arthur Lang (arthur.lang.pro@gmail.Com)
 * @brief Flee declaration
 * @date 2022-12-07
 */

#pragma once

#include <glm/geometric.hpp>

#include "movement/Kinetic.hpp"
#include "movement/utils.hpp"
#include "movement/SteeringAlgorithm.hpp"

namespace smort::movement {
    class Flee : public SteeringAlgorithm {
        public:
            Flee(const Kinetic &state, Kinetic &target);
            ~Flee() = default;

            Steering getSteering() override;

            float maxSpeed = 1.0f;
    };
} // namespace smort::movement