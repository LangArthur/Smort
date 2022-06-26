/**
 * @file movements.cpp
 * @author Arthur Lang
 * @brief file containing movement algorithms.
 * @date 2022-06-20
 */

#include <glm/geometric.hpp>

#include "movement/Kinetic.hpp"
#include "movement/utils.hpp"

namespace movement {
    SteeringOutput seek(const Kinetic &currentState, const glm::vec3 &target, int maxSpeed = 1) {
        SteeringOutput result;
        result.linear = target - currentState.position;
        glm::normalize(result.linear);
        result.linear *= maxSpeed;
        result.angular = newOrientation(currentState.orientation, result.linear);
    }

    SteeringOutput flee(const Kinetic &currentState, const glm::vec3 &target, int maxSpeed = 1) {
        SteeringOutput result;
        result.linear = target - currentState.position;
        glm::normalize(result.linear);
        result.linear *= maxSpeed;
        result.angular = newOrientation(currentState.orientation, result.linear);
    }
}