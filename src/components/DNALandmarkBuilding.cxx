#include "DNALandmarkBuilding.h"

#include <cctype>

TypeHandle DNALandmarkBuilding::_type_handle;

DNALandmarkBuilding::DNALandmarkBuilding(const std::string& name): DNANode(name), m_code(""),
                                                                   m_building_type(""),
                                                                   m_title(""),
                                                                   m_article(""),
                                                                   m_wall_color(LVecBase4f(1))
{
}

DNALandmarkBuilding::~DNALandmarkBuilding() {
    
}

void DNALandmarkBuilding::make_from_dgi(DatagramIterator& dgi, DNAStorage* store) {
    DNANode::make_from_dgi(dgi, store);   
    m_code = dgi.get_string();
    m_building_type = dgi.get_string();
    m_title = dgi.get_string();
    m_article = dgi.get_string();
    m_wall_color = DGI_EXTRACT_COLOR;
}

void DNALandmarkBuilding::traverse(NodePath& np, DNAStorage* store) {
    NodePath result = store->find_node(m_code);
    if (result.is_empty()) {
        raise_code_not_found(m_code.c_str());
        return;
    }
    
    NodePath _np = result.copy_to(np);
    _np.set_name(m_name);
    _np.set_pos_hpr_scale(m_pos, m_hpr, m_scale);
    
    if (store->allow_suit_origin(_np))
        setup_suit_building_origin(np, _np);

    traverse_children(_np, store);

    if (get_building_type() != "gagshop") {
        _np.flatten_strong();
    }
}

void DNALandmarkBuilding::setup_suit_building_origin(NodePath& a, NodePath& b) {
    if ((m_name.substr(0, 2) == "tb") && (isdigit(m_name[2])) && (m_name.find(":") != std::string::npos))
    {
        std::stringstream ss;
        ss << 's' << m_name.substr(1, m_name.size());
        
        NodePath node = b.find("**/*suit_building_origin");
        if (node.is_empty())
        {
            dna_cat.warning() << m_name << " couldn't find suit building origin" << std::endl;
            node = a.attach_new_node(ss.str());
            node.set_pos_hpr_scale(m_pos, m_hpr, m_scale);
        }
        
        else
        {
            node.wrt_reparent_to(a);
            node.set_name(ss.str());
        }
    }
}

void DNALandmarkBuilding::write(std::ostream& out, DNAStorage *store, unsigned int nbyte) {
    indent(out, nbyte);
    out << "landmark_building \"" << m_name << "\" [\n";
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