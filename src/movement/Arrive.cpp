/**
 * @file Arrive.cpp
 * @author Arthur Lang (arthur.lang.pro@gmail.Com)
 * @brief Arrive algorithm implementation
 * @date 2022-12-11
 */

#include "movement/Arrive.hpp"
#include <iostream>
namespace smort::movement {
    Arrive::Arrive(const Kinetic &state, Kinetic &target) : SteeringAlgorithm(state, target) { }

    Steering Arrive::getSteering() {
        Steering result;
        auto direction = m_target.position - m_state.position;
        auto dist = glm::length(direction);
        float targetSpeed = 0;
        if (dist < targetRadius) {
            return result;
        } else if (dist > slowRadius) {
            targetSpeed = maxSpeed;
        } else {
            targetSpeed = maxSpeed * dist / slowRadius;
        }
        auto targetVelocity = glm::normalize(direction) * targetSpeed;
        result.linear = targetVelocity - m_state.velocity;
        result.linear /= timeToTarget;
        if (glm::length(result.linear) > maxSpeed) {
            result.linear = glm::normalize(result.linear);
            result.linear *= maxSpeed;
        }
        // result.angular = newOrientation(m_state.orientation, result.linear);
        return result;
    }
} // namespace smort::movement