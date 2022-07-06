#include "AABB.h"

AABB::AABB()
{
    //The default contructor
}

AABB::AABB(glm::vec3 UpperTopLeft, glm::vec3 LowerBottomRight)
{
    m_MinMax[0] = LowerBottomRight;
    m_MinMax[1] = UpperTopLeft;
}

AABB::AABB(AABB& Copy)
{
    // Setting the box coordinates

    m_MinMax = Copy.BoundingRegion();

    // Calculating the center and that is it

    auto var = Copy.Center();

}

AABB::~AABB()
{
    // Default destructor, does nothing
}

glm::vec3 AABB::Center(void)
{

    //Calculating the center of the box top side 

    if (m_CenterUpdated == false)
    {
        m_Center.x = m_MinMax[1].x + (m_MinMax[0].x - m_MinMax[1].x) / 2;
        m_Center.y = m_MinMax[0].y + (m_MinMax[1].y - m_MinMax[0].y) / 2;
        m_Center.z = m_MinMax[0].z + (m_MinMax[1].z - m_MinMax[0].z) / 2;
    }

    // Modyfying the flag accordingly

    m_CenterUpdated = true;

    return m_Center;
}

std::array<glm::vec3, 2> AABB::BoundingRegion()
{

    //	  0 ----- MAX
    //	 /'       /'
    //	2 ------ 3 '
    //	' '      ' '
    //	' 4      ' 5
    //	'/       '/
    //	MIN ---- 7

    return m_MinMax;
}

glm::vec3 AABB::Dimensions()
{
    glm::vec3 dimensions = glm::vec3();

    dimensions.x = std::fabs(m_MinMax[0].x - m_MinMax[1].x);
    dimensions.y = std::fabs(m_MinMax[1].y - m_MinMax[0].y);
    dimensions.z = std::fabs(m_MinMax[0].z - m_MinMax[1].z);

    return dimensions;
}

bool AABB::Collides(AABB& compared)
{

    // TODO: Write the collision code later, after the implementation of all of the
    // important graphics oriented things

    return false;
}

bool AABB::Contains(AABB& compared)
{

    // TODO: Write the contains code later, after the implementation of all of the
    // important graphics oriented things

    return false;
}

void AABB::Update(glm::vec3 Minimum, glm::vec3 Maximum)
{
    m_CenterUpdated = false;

    // Updating the coordinates

    m_MinMax[0] = Minimum;
    m_MinMax[1] = Maximum;

    // Updating the center

    auto var = Center();

    m_CenterUpdated = true;

}
