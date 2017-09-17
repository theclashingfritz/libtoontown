#include "DNAAnimProp.h"

#include <modelNode.h>

TypeHandle DNAAnimProp::_type_handle;

DNAAnimProp::DNAAnimProp(const std::string& name): DNAProp(name), m_anim_name("") {
    
}

DNAAnimProp::~DNAAnimProp() {
    
}

void DNAAnimProp::make_from_dgi(DatagramIterator& dgi, DNAStorage* store) {
    DNAProp::make_from_dgi(dgi, store);
    m_anim_name = dgi.get_string();
}

void DNAAnimProp::traverse(NodePath& np, DNAStorage* store) {
    NodePath _np;
    
    if (m_code == "DCS") {
        PT(ModelNode) node = new ModelNode(m_name);
        node->set_preserve_transform(ModelNode::PT_net);
        _np = np.attach_new_node(node);
    } else {
        /// XXX TO DO: Check find_node result
        _np = store->find_node(m_code).copy_to(np);
        _np.set_name(m_name);
    }
    
    _np.set_tag("DNAAnim", m_anim_name);
    _np.set_pos_hpr_scale(m_pos, m_hpr, m_scale);
    _np.set_color_scale(m_color);
    traverse_children(_np, store);
}

void DNAAnimProp::write(std::ostream& out, DNAStorage *store, unsigned int nbyte) {
    indent(out, nbyte);
    out << "anim_prop \"" << m_name << "\" [\n";
    indent(out, nbyte + 1);
    out << "code [ \"" << m_code << "\" ]\n";
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