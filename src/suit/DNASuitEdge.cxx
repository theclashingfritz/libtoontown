#include "DNASuitEdge.h"

#include "DNAStorage.h"

TypeHandle DNASuitEdge::_type_handle;

DNASuitEdge::DNASuitEdge(DNASuitPoint* start_point, DNASuitPoint* end_point,
                         zone_id_t zone_id): m_start_point(start_point), m_end_point(end_point),
                                             m_zone_id(zone_id) {

}

DNASuitEdge::~DNASuitEdge() {

}

void DNASuitEdge::write(std::ostream& out, DNAStorage *store, unsigned int nbyte) {
    indent(out, nbyte);
    out << "suit_edge [ " << get_start_point()->get_index() << " " << get_end_point()->get_index() << " ]\n";
}