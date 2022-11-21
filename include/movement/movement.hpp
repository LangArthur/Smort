/**
 * @file movement.hpp
 * @author Arthur Lang
 * @brief declaration of movement algorithms
 * @date 2022-06-20
 */

#include <glm/geometric.hpp>

#include "movement/Kinetic.hpp"
#include "movement/utils.hpp"

namespace smort::movement {
    /**
     * @brief A kinematic seek behaviour.
     * @param currentState state of the AI-controlled element.
     * @param target position of the target element.
     * @param maxSpeed speed of the seeking element.
     * @return Steering Steering to applied on the seeking element.
     */
    Steering seek(const Kinetic &currentState, const glm::vec3 &target, float maxSpeed = 1.0f);
    /**
     * @brief A kinematic flee behaviour.
     * @param currentState state of the AI-controlled element.
     * @param target position of the target element.
     * @param maxSpeed speed of the fleeing element.
     * @return Steering Steering to applied on the fleeing element.
     */
    Steering flee(const Kinetic &currentState, const glm::vec3 &target, float maxSpeed = 1.0f);
} // namespace smort::movement