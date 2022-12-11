/**
 * @file Arrive.hpp
 * @author Arthur Lang (arthur.lang.pro@gmail.Com)
 * @brief Arrive algorithm declaration
 * @date 2022-12-11
 */

#pragma once

#include <glm/geometric.hpp>

#include "movement/Kinetic.hpp"
#include "movement/utils.hpp"
#include "movement/SteeringAlgorithm.hpp"

namespace smort::movement {
    class Arrive : public SteeringAlgorithm {
        public:
            Arrive(const Kinetic &state, Kinetic &target);
            ~Arrive() = default;

            Steering getSteering() override;

            float maxSpeed { 1.0f };
            /* Radius for arriving at the target, for margin error */
            float targetRadius { 0.01f };
            /* Radius to start slowing down */
            float slowRadius { 0.5 };
            /* The time over which to achieve target speed. */
            float timeToTarget { 0.1 };
    };
} // namespace smort::movement