#pragma once

#include <string>

#include "core/gpu/mesh.h"
#include "utils/glm_utils.h"

namespace object2D
{

    // Create square with given bottom left corner, length and color
    Mesh* CreateSquare(const std::string &name, glm::vec3 leftBottomCorner, float length, glm::vec3 color, bool fill = false);
    Mesh* CreateRegtangle(const std::string& name, glm::vec3 leftBottomCorner, float l, float L, glm::vec3 color, bool fill = false);
    Mesh* CreateTurret(const std::string& name, glm::vec3 leftBottomCorner, float L, glm::vec3 color, bool fill = false);
    Mesh* CreateHeart(const std::string& name, glm::vec3 leftBottomCorner, float l, float L, glm::vec3 color, bool fill = false);
    Mesh* CreateHexagone(const std::string& name, glm::vec3 leftBottomCorner, float len, glm::vec3 color, bool fill = false);
    Mesh* CreateStar(const std::string& name, glm::vec3 leftBottomCorner, float len, glm::vec3 color, bool fill = false);
}
