/**
 * @file movements.cpp
 * @author Arthur Lang
 * @brief file containing movement algorithms.
 * @date 2022-06-20
 */

#include "movement/movement.hpp"

namespace movement {
    SteeringOutput seek(const Kinetic &currentState, const glm::vec3 &target, float maxSpeed) {
        SteeringOutput result;
        result.linear = target - currentState.position;
        glm::normalize(result.linear);
        result.linear *= maxSpeed;
        result.angular = newOrientation(currentState.orientation, result.linear);
        return result;
    }

    SteeringOutput flee(const Kinetic &currentState, const glm::vec3 &target, float maxSpeed) {
        SteeringOutput result;
        result.linear = currentState.position - target;
        glm::normalize(result.linear);
        result.linear *= maxSpeed;
        result.angular = newOrientation(currentState.orientation, result.linear);
        return result;
    }
}