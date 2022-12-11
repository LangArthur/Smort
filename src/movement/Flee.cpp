/**
 * @file Flee.cpp
 * @author Arthur Lang (arthur.lang.pro@gmail.Com)
 * @brief Flee declaration
 * @date 2022-12-07
 */

#include "movement/Flee.hpp"

namespace smort::movement {
    Flee::Flee(const Kinetic &state, Kinetic &target) : SteeringAlgorithm(state, target) { }

    Steering Flee::getSteering() {
        Steering result;
        result.linear = glm::normalize(m_state.position - m_target.position);
        result.linear *= maxSpeed;
        result.angular = newOrientation(m_state.orientation, result.linear);
        return result;
    }
} // namespace smort::movement