/**
 * @file utils.hpp
 * @author Arthur Lang (arthur.lang.pro@gmail.Com)
 * @brief declaration of utilities for movements
 * @version 0.1
 * @date 2022-06-26
 */

#pragma once

namespace smort::movement
{
    /**
     * @brief give a new orientation base on the current orientation and a direction vector
     * @param current the current orientation (in radian).
     * @param direction direction vector
     * @return float 
     */
    inline float newOrientation(float current, const glm::vec3 &direction) {
        if (direction.length)
            return atan2(-direction.x, direction.y);
        else
            return current;
    }
} // namespace smort::movement