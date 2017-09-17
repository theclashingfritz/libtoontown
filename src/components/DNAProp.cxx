#include "DNAProp.h"

#include <modelNode.h>

TypeHandle DNAProp::_type_handle;

DNAProp::DNAProp(const std::string& name): DNANode(name), m_code(""), m_color(LVecBase4f(1)) {
    
}

DNAProp::~DNAProp() {
    
}

void DNAProp::make_from_dgi(DatagramIterator& dgi, DNAStorage* store) {
    DNANode::make_from_dgi(dgi, store);
    m_code = dgi.get_string();
    m_color = DGI_EXTRACT_COLOR;
}

void DNAProp::traverse(NodePath& np, DNAStorage* store) {
    NodePath _np;
    if (m_code == "DCS") {
        PT(ModelNode) node = new ModelNode(m_name);
        node->set_preserve_transform(ModelNode::PT_net);
        _np = np.attach_new_node(node);
    } else {
        NodePath result = store->find_node(m_code);
        if (result.is_empty())
            return;
        
        _np = result.copy_to(np);
    }
    
    _np.set_name(m_name);
    _np.set_pos_hpr_scale(m_pos, m_hpr, m_scale);
    _np.set_color_scale(m_color);
    
    traverse_children(_np, store);
}

void DNAProp::raise_code_not_found() {
    DNAGroup::raise_code_not_found(m_code.c_str());
}

void DNAProp::write(std::ostream& out, DNAStorage *store, unsigned int nbyte) {
    indent(out, nbyte);
    out << "prop \"" << m_name << "\" [\n";
    indent(out, nbyte + 1);
    out << "code [ \"" << m_code << "\" ]\n";
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
    indent(out, nbyte + 1);
    out << "scale [ " << m_scale[0] << " " << m_scale[1] << " " << m_scale[2] << " ]\n";
    if (m_color != LVecBase4f(1)) {
        indent(out, nbyte + 1);
        out << "color [ " << m_color[0] << " " << m_color[1] << " " << m_color[2] << " " << m_color[3] << " ]\n";
    }
    for (dna_group_vec_t::iterator it = m_children.begin(); it != m_children.end(); ++it) {
        (*it)->write(out, store, nbyte + 1);
    }
    indent(out, nbyte);
    out << "]\n";
}