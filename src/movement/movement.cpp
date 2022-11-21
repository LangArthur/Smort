/**
 * @file movements.cpp
 * @author Arthur Lang
 * @brief file containing movement algorithms.
 * @date 2022-06-20
 */

#include "movement/movement.hpp"

namespace smort::movement {
    Steering seek(const Kinetic &currentState, const glm::vec3 &target, float maxSpeed) {
        Steering result;
        result.linear = target - currentState.position;
        glm::normalize(result.linear);
        result.linear *= maxSpeed;
        result.angular = newOrientation(currentState.orientation, result.linear);
        return result;
    }

    Steering flee(const Kinetic &currentState, const glm::vec3 &target, float maxSpeed) {
        Steering result;
        result.linear = currentState.position - target;
        glm::normalize(result.linear);
        result.linear *= maxSpeed;
        result.angular = newOrientation(currentState.orientation, result.linear);
        return result;
    }
} // namespace smort::movement