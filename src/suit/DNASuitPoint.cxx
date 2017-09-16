#include "DNASuitPoint.h"
#include "DNAStorage.h"

TypeHandle DNASuitPoint::_type_handle;

DNASuitPoint::DNASuitPoint(point_index_t index, PointType point_type, LPoint3f const pos,
                           block_number_t landmark_building_index): m_index(index), m_point_type(point_type), m_pos(pos),
                                                                    m_landmark_building_index(landmark_building_index)
{
}

DNASuitPoint::~DNASuitPoint()
{
}

void DNASuitPoint::set_point_type(const std::string& point_type)
{
    if (point_type == "STREET_POINT")
        set_point_type(DNASuitPoint::STREET_POINT);
        
    else if (point_type == "FRONT_DOOR_POINT")
        set_point_type(DNASuitPoint::FRONT_DOOR_POINT);
        
    else if (point_type == "SIDE_DOOR_POINT")
        set_point_type(DNASuitPoint::SIDE_DOOR_POINT);
        
    else if (point_type == "COGHQ_IN_POINT")
        set_point_type(DNASuitPoint::COGHQ_IN_POINT);
        
    else if (point_type == "COGHQ_OUT_POINT")
        set_point_type(DNASuitPoint::COGHQ_OUT_POINT);
        
    else
        dna_cat.error() << "invalid point type: " << point_type << std::endl;
}


void DNASuitPoint::write(std::ostream& out, DNAStorage *store, unsigned int nbyte) {    
    std::string point_type;
    
    out << "store_suit_point [ " << m_index << ", ";
    
    switch (m_point_type) {
        case DNASuitPoint::STREET_POINT:
            out << "STREET_POINT, ";
            break;
            
        case DNASuitPoint::FRONT_DOOR_POINT:
            out << "FRONT_DOOR_POINT, ";
            break;
            
        case DNASuitPoint::SIDE_DOOR_POINT:
            out << "SIDE_DOOR_POINT, ";
            break;
            
        case DNASuitPoint::COGHQ_IN_POINT:
            out << "COGHQ_IN_POINT, ";
            break;
            
        case DNASuitPoint::COGHQ_OUT_POINT:
            out << "COGHQ_OUT_POINT, ";
            break;
            
        default:
            out << "**invalid**, ";
            break;
    }

    out << m_pos.get_x() << " " << m_pos.get_y() << " " << m_pos.get_z();

    if (m_landmark_building_index != -1) {
        out << ", " << m_landmark_building_index;
    }

    out << " ]\n";
}