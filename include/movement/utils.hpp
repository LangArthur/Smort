/**
 * @file utils.hpp
 * @author Arthur Lang (arthur.lang.pro@gmail.Com)
 * @brief declaration of utilities for movements
 * @version 0.1
 * @date 2022-06-26
 */

#pragma once

namespace movement
{
    inline float newOrientation(float current, const glm::vec3 &velocity) {
        if (velocity.length)
            return atan2(-velocity.x, velocity.y);
        else
            return current;
    }
} // namespace movement