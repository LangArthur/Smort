/**
 * @file kinetic.hpp
 * @author Arthur Lang
 * @brief kinetic data structure.
 * @date 2022-06-20
 */

#pragma once

#include <glm/vec3.hpp>

namespace movement {

    /**
     * @brief structure representing changes to be apply to a Kinetic element.
     */
    struct SteeringOutput {
        glm::vec3 linear; // linear change
        float angular; // angular change        
    };

    /**
     * @brief structure representing a state of an object.
     */
    struct Kinetic {
        glm::vec3 position;
        float orientation; // current orientation
        glm::vec3 velocity;
        float rotation; // changes applied to rotation in the next update

        void update(const SteeringOutput &steering, const float time = 1) {
            position += velocity * time;
            orientation += rotation * time;

            velocity += steering.linear * time;
            rotation += steering.angular * time;
        }
    };
}