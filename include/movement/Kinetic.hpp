/**
 * @file kinetic.hpp
 * @author Arthur Lang
 * @brief kinetic data structure.
 * @date 2022-06-20
 */

#pragma once

#include <glm/vec3.hpp>

namespace smort::movement {

    /**
     * @brief structure representing changes to be apply to a Kinetic element.
     */
    struct Steering {
        glm::vec3 linear {0, 0, 0}; // linear change
        float angular { 0.0f }; // angular change        
    };

    /**
     * @brief structure representing a state of an object.
     */
    struct Kinetic {
        glm::vec3 position;
        float orientation;
        glm::vec3 velocity; // change applied to position.
        float rotation; // changes applied to rotation.
        float maxSpeed { 1.0f };

        /**
         * @brief update the Kinetic with a steering.
         * @param steering changes to be applied on the kinetic.
         * @param deltaTime deltaTime between each update (= each rendered frame).
         */
        void update(const Steering &steering, const float deltaTime = 1) {
            velocity += steering.linear * deltaTime;
            if (glm::length(velocity) > maxSpeed) {
                glm::normalize(velocity);
                velocity *= maxSpeed;
            }
            rotation += steering.angular * deltaTime;
            position += velocity * deltaTime;
            orientation += rotation * deltaTime;
        }
    };
} // namespace smort::movement