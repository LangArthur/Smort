/**
 * @file utils.cpp
 * @author Arthur Lang (arthur.lang.pro@gmail.Com)
 * @brief utilities for movements
 * @date 2022-06-26
 */

#include <math.h>
#include <glm/vec3.hpp>

namespace movement
{
    inline float newOrientation(float current, const glm::vec3 &velocity) {
        if (velocity.length)
            return atan2(-velocity.x, velocity.y);
        else
            return current;
    }
    
} // namespace Movement
