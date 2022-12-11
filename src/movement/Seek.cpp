/**
 * @file Seek.cpp
 * @author Arthur Lang (arthur.lang.pro@gmail.Com)
 * @brief Seek declaration
 * @date 2022-12-07
 */

#include "movement/Seek.hpp"

namespace smort::movement {
    Seek::Seek(const Kinetic &state, Kinetic &target) : SteeringAlgorithm(state, target) { }

    Steering Seek::getSteering() {
        Steering result;
        result.linear = m_target.position - m_state.position;
        glm::normalize(result.linear);
        result.linear *= maxSpeed;
        result.angular = newOrientation(m_state.orientation, result.linear);
        return result;
    }
} // namespace smort::movement