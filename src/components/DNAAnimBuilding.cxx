#include "DNAAnimBuilding.h"

TypeHandle DNAAnimBuilding::_type_handle;

DNAAnimBuilding::DNAAnimBuilding(const std::string& name): DNALandmarkBuilding(name), m_anim_name("") {

}

DNAAnimBuilding::~DNAAnimBuilding() {
    
}

void DNAAnimBuilding::make_from_dgi(DatagramIterator& dgi, DNAStorage* store) {
    DNALandmarkBuilding::make_from_dgi(dgi, store);
    m_anim_name = dgi.get_string();
}

void DNAAnimBuilding::traverse(NodePath& np, DNAStorage* store) {
    NodePath result = store->find_node(m_code);
    if (result.is_empty()) {
        raise_code_not_found();
        return;
    }
    
    NodePath _np = result.copy_to(np);
    _np.set_name(m_name);
    _np.set_pos_hpr_scale(m_pos, m_hpr, m_scale);
    _np.set_tag("DNAAnim", m_anim_name);
    setup_suit_building_origin(np, _np);
    traverse_children(_np, store);
    _np.flatten_strong();
}


void DNAAnimBuilding::write(std::ostream& out, DNAStorage *store, unsigned int nbyte) {
    indent(out, nbyte);
    out << "anim_building \"" << m_name << "\" [\n";
    indent(out, nbyte + 1);
    out << "code [ \"" << m_code << "\" ]\n";
    if (get_building_type() != "") {
        indent(out, nbyte + 1);
        out << "building_type [ \"" << get_building_type() << "\" ]\n";
    }
    if (m_article != "") {
        indent(out, nbyte + 1);
        out << "article [ \"" << m_article << "\" ]\n";
    }
    indent(out, nbyte + 1);
    out << "title [ \"" << m_title << "\" ]\n";
    indent(out, nbyte + 1);
    out << "anim [ \"" << m_anim_name << "\" ]\n";
    indent(out, nbyte + 1);
    out << "pos [ " << m_pos[0] << " " << m_pos[1] << " " << m_pos[2] << " ]\n";
    LVecBase3f new_hpr;
    if (!temp_hpr_fix) {
        new_hpr = old_to_new_hpr(m_hpr);
    } else {
        new_hpr = LVecBase3f(m_hpr);
    }
    indent(out, nbyte + 1);
    out << "hpr [ " << new_hpr[0] << " " << new_hpr[1] << " " << new_hpr[2] << " ]\n";
    if (m_wall_color != LVecBase4f(1)) {
        indent(out, nbyte + 1);
        out << "color [ " << m_wall_color[0] << " " << m_wall_color[1] << " " << m_wall_color[2] << " " << m_wall_color[3] << " ]\n";
    }
    for (dna_group_vec_t::iterator it = m_children.begin(); it != m_children.end(); ++it) {
        (*it)->write(out, store, nbyte + 1);
    }
    indent(out, nbyte);
    out << "]\n";
}