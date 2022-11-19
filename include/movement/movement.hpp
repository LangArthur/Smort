/**
 * @file movement.hpp
 * @author Arthur Lang
 * @brief declaration of movement algorithms
 * @date 2022-06-20
 */

#include <glm/geometric.hpp>

#include "movement/Kinetic.hpp"
#include "movement/utils.hpp"

namespace movement {
    SteeringOutput seek(const Kinetic &currentState, const glm::vec3 &target, float maxSpeed = 1.0f);
    SteeringOutput flee(const Kinetic &currentState, const glm::vec3 &target, float maxSpeed = 1.0f);
}