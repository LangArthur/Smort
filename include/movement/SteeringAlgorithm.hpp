/**
 * @file SteeringAlgorithm.hpp
 * @author Arthur Lang (arthur.lang.pro@gmail.Com)
 * @brief abstract class for all steering algorithms (seek, flee ...)
 * @date 2022-12-07
 */

#pragma once

#include <memory>

#include <glm/geometric.hpp>

#include "movement/Kinetic.hpp"
#include "movement/utils.hpp"

namespace smort::movement {
    class SteeringAlgorithm {
        public:
            SteeringAlgorithm(const Kinetic &state, Kinetic &target);
            ~SteeringAlgorithm() = default;

            inline void setTarget(Kinetic &target) {
                m_target = target;
            }

            virtual Steering getSteering() = 0;

        protected:
            const Kinetic &m_state;
            Kinetic &m_target;
    };
} // namespace smort::movement