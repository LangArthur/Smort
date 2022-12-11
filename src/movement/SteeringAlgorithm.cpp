/**
 * @file SteeringAlgorithm.cpp
 * @author Arthur Lang (arthur.lang.pro@gmail.Com)
 * @brief steering algorithm declaration
 * @date 2022-12-08
 */

#include "movement/SteeringAlgorithm.hpp"

namespace smort::movement {
    SteeringAlgorithm::SteeringAlgorithm(const Kinetic &state, Kinetic &target) : m_state(state), m_target(target) { }
} // namespace smort::movement