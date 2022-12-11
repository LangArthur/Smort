/**
 * @file Seek.hpp
 * @author Arthur Lang (arthur.lang.pro@gmail.Com)
 * @brief Seek declaration
 * @date 2022-12-07
 */

#pragma once

#include <glm/geometric.hpp>

#include "movement/Kinetic.hpp"
#include "movement/utils.hpp"
#include "movement/SteeringAlgorithm.hpp"

namespace smort::movement {
    class Seek : public SteeringAlgorithm {
        public:
            Seek(const Kinetic &state, Kinetic &target);
            ~Seek() = default;

            Steering getSteering() override;

            float maxSpeed = 1.0f;
    };
} // namespace smort::movement