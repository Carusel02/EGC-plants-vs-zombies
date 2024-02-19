#include "object2D.h"

#include <vector>

#include "core/engine.h"
#include "utils/gl_utils.h"


Mesh* object2D::CreateSquare(
    const std::string &name,
    glm::vec3 leftBottomCorner,
    float length,
    glm::vec3 color,
    bool fill)
{
    glm::vec3 corner = leftBottomCorner;

    std::vector<VertexFormat> vertices =
    {   // 0
        VertexFormat(corner + glm::vec3(-length * 0.5, -length * 0.5, 0), color),
        // 1
        VertexFormat(corner + glm::vec3(-length * 0.5, length * 0.5, 0), color),
        // 2
        VertexFormat(corner + glm::vec3(length * 0.5, length * 0.5, 0), color),
        // 3
        VertexFormat(corner + glm::vec3(length * 0.5, -length * 0.5, 0), color)
    };

    Mesh* square = new Mesh(name);
    std::vector<unsigned int> indices = { 0, 1, 2, 3 };

    if (!fill) {
        square->SetDrawMode(GL_LINE_LOOP);
    } else {
        // Draw 2 triangles. Add the remaining 2 indices
        indices.push_back(0);
        indices.push_back(2);
    }

    square->InitFromData(vertices, indices);
    return square;
}

Mesh* object2D::CreateRegtangle(
    const std::string& name,
    glm::vec3 leftBottomCorner,
    float l, float L,
    glm::vec3 color,
    bool fill)
{
    glm::vec3 corner = leftBottomCorner;

    std::vector<VertexFormat> vertices =
    {
        VertexFormat(corner, color),
        VertexFormat(corner + glm::vec3(l, 0, 0), color),
        VertexFormat(corner + glm::vec3(l, L, 0), color),
        VertexFormat(corner + glm::vec3(0, L, 0), color)
    };

    Mesh* rectangle = new Mesh(name);
    std::vector<unsigned int> indices = { 0, 1, 2, 3 };

    if (!fill) {
        rectangle->SetDrawMode(GL_LINE_LOOP);
    }
    else {
        // Draw 2 triangles. Add the remaining 2 indices
        indices.push_back(0);
        indices.push_back(2);
    }

    rectangle->InitFromData(vertices, indices);
    return rectangle;
}

Mesh* object2D::CreateTurret(
    const std::string& name,
    glm::vec3 leftBottomCorner,
    float L,
    glm::vec3 color,
    bool fill)
{
    glm::vec3 corner = leftBottomCorner;

    std::vector<VertexFormat> vertices =
    {   
        // 0
        VertexFormat(corner + glm::vec3(0, -L * 0.6, 0), color),
        // 1
        VertexFormat(corner + glm::vec3(-L * 0.35, 0, 0), color),
        // 2
        VertexFormat(corner + glm::vec3(0, L * 0.6, 0), color),
        // 3
        VertexFormat(corner + glm::vec3(L * 0.35, 0, 0), color),
        // 4
        VertexFormat(corner + glm::vec3(0, -L * 0.20, 0), color),
        // 5
        VertexFormat(corner + glm::vec3(L * 0.8, -L * 0.20, 0), color),
        // 6
        VertexFormat(corner + glm::vec3(L * 0.8, L * 0.20, 0), color),
        // 7
        VertexFormat(corner + glm::vec3(0 , L * 0.20, 0), color),
    };

    Mesh* turret = new Mesh(name);
    std::vector<unsigned int> indices = { 0, 1, 2, 0, 2, 3, 4, 5, 6, 4, 6, 7 };

    if (!fill) {
        turret->SetDrawMode(GL_LINE_LOOP);
    }
    else {
        turret->SetDrawMode(GL_TRIANGLES);
    }

    
    turret->InitFromData(vertices, indices);
    return turret;
}

Mesh* object2D::CreateHeart(
    const std::string& name,
    glm::vec3 leftBottomCorner,
    float l, float L,
    glm::vec3 color,
    bool fill)
{
    glm::vec3 corner = leftBottomCorner;

    std::vector<VertexFormat> vertices =
    {
        VertexFormat(corner, color),
        VertexFormat(corner + glm::vec3(-l/2.0, L/2, 0), color),
        VertexFormat(corner + glm::vec3(-l/2, L/2 + L/4, 0), color),
        VertexFormat(corner + glm::vec3(-l/4.0 - l/12.0, L, 0), color),
        VertexFormat(corner + glm::vec3(-l / 4.0 + l/12.0, L, 0), color),

        VertexFormat(corner + glm::vec3(0, L/2 + L/3, 0), color),
        VertexFormat(corner + glm::vec3(l/4.0 - l/12.0, L, 0), color),
        VertexFormat(corner + glm::vec3(l / 4.0 + l/12, L, 0), color),
        VertexFormat(corner + glm::vec3(l/2.0,L/2 + L/4, 0), color),
        VertexFormat(corner + glm::vec3(l/ 2.0, L/2, 0), color)
    };

    Mesh* heart = new Mesh(name);
    std::vector<unsigned int> indices = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };

    if (!fill) {
        heart->SetDrawMode(GL_LINE_LOOP);
    }
    else {
        heart->SetDrawMode(GL_TRIANGLE_FAN);
    }


    heart->InitFromData(vertices, indices);
    return heart;
}

Mesh* object2D::CreateHexagone(
    const std::string& name,
    glm::vec3 leftBottomCorner,
    float len,
    glm::vec3 color,
    bool fill)
{
    glm::vec3 corner = leftBottomCorner;
    glm::vec3 sec_color = glm::vec3(0.92f, 0.82f, 0.50f);

    std::vector<VertexFormat> vertices =
    {
        // 0
        VertexFormat(corner + glm::vec3(-len * 0.3, -len * 0.4, 2), color),
        // 1
        VertexFormat(corner + glm::vec3(-len * 0.5, 0, 2), color),
        // 2
        VertexFormat(corner + glm::vec3(-len * 0.3 , len * 0.4, 2), color),
        // 3
        VertexFormat(corner + glm::vec3(len * 0.3, len * 0.4, 2), color),
        // 4
        VertexFormat(corner + glm::vec3(len * 0.5, 0, 2), color),
        // 5
        VertexFormat(corner + glm::vec3(len * 0.3, -len * 0.4, 2), color),
        // 6
        VertexFormat(corner + glm::vec3(-len * 0.3 * 0.7, -len * 0.4 * 0.7, 3), sec_color),
        // 7
        VertexFormat(corner + glm::vec3(-len * 0.5 * 0.7, 0, 3), sec_color),
        // 8
        VertexFormat(corner + glm::vec3(-len * 0.3 * 0.7, len * 0.4 * 0.7, 3), sec_color),
        // 9
        VertexFormat(corner + glm::vec3(len * 0.3 * 0.7, len * 0.4 * 0.7, 3), sec_color),
        // 10
        VertexFormat(corner + glm::vec3(len * 0.5 * 0.7, 0, 3), sec_color),
        // 11
        VertexFormat(corner + glm::vec3(len * 0.3 * 0.7, -len * 0.4 * 0.7, 3), sec_color)
        

    };

    Mesh* hexagone = new Mesh(name);
    std::vector<unsigned int> indices = { 0, 1, 2,
                                          0, 2, 3,
                                          0, 3, 5,
                                          3, 4, 5,
                                          6, 7, 8,
                                          6, 8, 9,
                                          6, 9, 11,
                                          11, 9, 10
                                        };

    if (!fill) {
        hexagone->SetDrawMode(GL_LINE_LOOP);
    }

    hexagone->InitFromData(vertices, indices);
    return hexagone;
}

Mesh* object2D::CreateStar(
    const std::string& name,
    glm::vec3 leftBottomCorner,
    float len,
    glm::vec3 color,
    bool fill)
{
    glm::vec3 corner = leftBottomCorner;

    std::vector<VertexFormat> vertices =
    {   
        // 0
        VertexFormat(corner + glm::vec3(0, -len * 0.15, 0), color),
        // 1 
        VertexFormat(corner + glm::vec3(-len/3.2 , -len * 0.4, 0), color),
        // 2
        VertexFormat(corner + glm::vec3(-len/5, len/10, 0), color),
        // 3
        VertexFormat(corner + glm::vec3(-len/2, len/5, 0), color),
        // 4
        VertexFormat(corner + glm::vec3(-len/10, len/5, 0), color),
        // 5
        VertexFormat(corner + glm::vec3(0 , len/2, 0), color),
        // 6
        VertexFormat(corner + glm::vec3(len/10, len/5, 0), color),
        // 7
        VertexFormat(corner + glm::vec3(len/2, len/5, 0), color),
        // 8
        VertexFormat(corner + glm::vec3(len/5, len/10, 0), color),
        // 9
        VertexFormat(corner + glm::vec3(len/3.2, -len * 0.4, 0), color)
    };

    Mesh* star = new Mesh(name);
    std::vector<unsigned int> indices = { 0, 3, 7, 4, 5, 6, 0, 1, 2, 0, 8, 9};

    if (!fill) {
        star->SetDrawMode(GL_LINE_LOOP);
    }
    else {
        star->SetDrawMode(GL_TRIANGLE_FAN);
    }


    star->InitFromData(vertices, indices);
    return star;
}