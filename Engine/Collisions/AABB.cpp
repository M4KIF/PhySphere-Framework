#include "AABB.h"

namespace Collisions {

    AABB::AABB()
    {
        //The default contructor
    }


    AABB::AABB(glm::vec3 Minimum, glm::vec3 Maximum)
    {
        //Setting the bounding box
        m_MinMax[0] = Minimum; //Lower bottom left
        m_MinMax[1] = Maximum; //Upper top right

        //Calculating the center
        center();
        dimensions();
    }


    AABB::AABB(const AABB& Copy)
    {
        //Setting the bounding box
        m_MinMax = Copy.m_MinMax;

        //Calculating the center
        center();
        dimensions();
    }


    AABB::~AABB()
    {
        // Default destructor, does nothing
    }


    glm::vec3 AABB::center(void)
    {

        //Calculating the center of the box top side 
        if (m_CenterUpdated == false)
        {
            m_Center.x = m_MinMax[0].x + ((m_MinMax[1].x - m_MinMax[0].x) / 2);
            m_Center.y = m_MinMax[0].y + ((m_MinMax[1].y - m_MinMax[0].y) / 2);
            m_Center.z = m_MinMax[1].z + ((m_MinMax[0].z - m_MinMax[1].z) / 2);

            //Modyfying the flag accordingly
            m_CenterUpdated = true;
        }

        return m_Center;
    }


    std::array<glm::vec3, 2> AABB::bounding_region()
    {
        //////////////////
        //	  0 ----- MAX
        //	 /'       /'
        //	2 ------ 3 '
        //	' '      ' '
        //	' 4      ' 5
        //	'/       '/
        //	MIN ---- 7
        //////////////////

        return m_MinMax;
    }


    glm::vec3 AABB::dimensions()
    {
        
        if (!m_DimensionsUpdated)
        {
            m_Dimensions.x = std::fabs(m_MinMax[1].x - m_MinMax[0].x);
            m_Dimensions.y = std::fabs(m_MinMax[1].y - m_MinMax[0].y);
            m_Dimensions.z = std::fabs(m_MinMax[0].z - m_MinMax[1].z);

            //Modyfying the flag accordingly
            m_DimensionsUpdated = true;
        }

        return m_Dimensions;
    }


    //All of the points have to be inside the parent bb to return true
    bool AABB::contains(AABB& compared)
    {
        //Checking if the the other aabb can be possibly contained 
        if (!intersect2(compared)) return false;

        //Getting the data that is needed for calculations
        std::array<glm::vec3, 2> aabb_minmax = compared.bounding_region();

        std::array<glm::vec3, 2> parent_2d_plane;
        std::array<glm::vec3, 2> compared_2d_plane;

        //Calculating the lower plane
        parent_2d_plane[0] = m_MinMax[0];
        parent_2d_plane[1] = glm::vec3(m_MinMax[1].x, m_MinMax[0].y, m_MinMax[1].z);

        compared_2d_plane[0] = aabb_minmax[0];
        compared_2d_plane[1] = glm::vec3(aabb_minmax[1].x, aabb_minmax[0].y, aabb_minmax[1].z);

        //Checking if it can be contained inside the bottom square of the cube
        if (!((compared_2d_plane[0].x >= parent_2d_plane[0].x) &&
            (compared_2d_plane[0].z <= parent_2d_plane[0].z) &&
            (compared_2d_plane[1].x <= parent_2d_plane[1].x) &&
            (compared_2d_plane[1].z >= parent_2d_plane[1].z) &&
            (compared_2d_plane[1].y >= parent_2d_plane[1].y))) return false;

        //Calculating the lower plane
        parent_2d_plane[0] = m_MinMax[0];
        parent_2d_plane[1] = glm::vec3(m_MinMax[1].x, m_MinMax[1].y, m_MinMax[1].z);

        compared_2d_plane[0] = aabb_minmax[0];
        compared_2d_plane[1] = glm::vec3(aabb_minmax[1].x, aabb_minmax[1].y, aabb_minmax[1].z);

        //Checking if it can be contained inside the bottom square of the cube
        if (!((compared_2d_plane[0].x >= parent_2d_plane[0].x) &&
            (compared_2d_plane[0].z <= parent_2d_plane[0].z) &&
            (compared_2d_plane[1].x <= parent_2d_plane[1].x) &&
            (compared_2d_plane[1].z >= parent_2d_plane[1].z) &&
            (compared_2d_plane[1].y <= parent_2d_plane[1].y))) return false;

        return true;
    }


    bool AABB::contains(glm::vec3 compared)
    {
        return ((compared.x > m_MinMax[0].x && compared.x < m_MinMax[1].x) &&
            (compared.y > m_MinMax[0].y && compared.y < m_MinMax[1].y) &&
            (compared.z < m_MinMax[0].z && compared.z > m_MinMax[1].z));
    }


    //Only one point has to touch the other bounding box to return true
    bool AABB::intersect1(AABB& compared)
    {
        //Variables for storing the needed comparsion data
        std::array<glm::vec3, 2> bounding_region = compared.bounding_region();
        glm::vec3 dimensions = compared.dimensions();

        //The absolute value between centers and checking for overlap
        glm::vec3 distance;

        //The sum of both bb's dimensions
        glm::vec3 sumedDimensions = dimensions + m_Dimensions;

        for (int i = 0; i < 3; i++)
        {
            distance[i] = fabs(m_Center[i] - compared.center()[i]);

            //Checking whether given coordinate overlaps
            if (!(distance[i] <= (sumedDimensions[i] * 0.5))) return false;

        }

        return true;
    }


    bool AABB::intersect2(AABB& compared)
    {
        std::array<glm::vec3, 2> bounding_box = compared.bounding_region();

        return (bounding_box[0].x <= m_MinMax[1].x && bounding_box[1].x >= m_MinMax[0].x) &&
            (bounding_box[0].y <= m_MinMax[1].y && bounding_box[1].y >= m_MinMax[0].y) &&
            (bounding_box[0].z >= m_MinMax[1].z && bounding_box[1].z <= m_MinMax[0].z);
    }


    bool AABB::strict_intersect(AABB& compared)
    {

        std::array<glm::vec3, 2> bounding_box = compared.bounding_region();

        return (bounding_box[0].x < m_MinMax[1].x && bounding_box[1].x > m_MinMax[0].x) &&
            (bounding_box[0].y < m_MinMax[1].y && bounding_box[1].y > m_MinMax[0].y) &&
            (bounding_box[0].z > m_MinMax[1].z && bounding_box[1].z < m_MinMax[0].z);
    }


    void AABB::update_position(glm::vec3 Minimum, glm::vec3 Maximum)
    {
        //Resetting the flags
        m_CenterUpdated = false;
        m_DimensionsUpdated = false;

        //Updating the coordinates
        m_MinMax[0] = Minimum;
        m_MinMax[1] = Maximum;

    }

}
