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
        glm::vec3 linear; // linear change
        float angular; // angular change        
    };

    /**
     * @brief structure representing a state of an object.
     */
    struct Kinetic {
        glm::vec3 position;
        float orientation;
        glm::vec3 velocity; // change applied to position.
        float rotation; // changes applied to rotation.

        /**
         * @brief update the Kinetic with a steering.
         * @param steering changes to be applied on the kinetic.
         * @param deltaTime deltaTime between each update (= each rendered frame).
         */
        void update(const Steering &steering, const float deltaTime = 1) {
            position += velocity * deltaTime;
            orientation += rotation * deltaTime;

            velocity += steering.linear * deltaTime;
            rotation += steering.angular * deltaTime;
        }
    };
} // namespace smort::movement