#include "DNASign.h"

#include <modelNode.h>

TypeHandle DNASign::_type_handle;

DNASign::DNASign(const std::string& name): DNAProp(name) {
    
}

DNASign::~DNASign() {
    
}

void DNASign::make_from_dgi(DatagramIterator& dgi, DNAStorage* store) {
    DNAProp::make_from_dgi(dgi, store);
}

void DNASign::traverse(NodePath& np, DNAStorage* store) {
    NodePath decal_node, _np, origin;
    decal_node = np.find("**/sign_decal");
    if (decal_node.is_empty())
        decal_node = np.find("**/*_front");
        
    if (decal_node.is_empty() || !(decal_node.get_node(0)->is_geom_node()))
        decal_node = np.find("**/+GeomNode");
        
    if (m_code.size())
    {
        _np = store->find_node(m_code).copy_to(decal_node);
        _np.set_name("sign");
    }
    
    else
        _np = decal_node.attach_new_node(new ModelNode("sign"));
        
    _np.set_depth_offset(50);
    
    origin = np.find("**/*sign_origin");
    _np.set_pos_hpr_scale(origin, m_pos, m_hpr, m_scale);
    _np.set_color(m_color);
    _np.wrt_reparent_to(origin, 0);
    traverse_children(_np, store);
    _np.flatten_strong();
}

void DNASign::write(std::ostream& out, DNAStorage *store, unsigned int nbyte) {
    indent(out, nbyte);
    out << "sign [\n";
    indent(out, nbyte + 1);
    out << "code [ \"" << m_code << "\" ]\n";
    indent(out, nbyte + 1);
    out << "color [ " << m_color[0] << " " << m_color[1] << " " << m_color[2] << " " << m_color[3] << " ]\n";
    if (m_pos != LVecBase3f(0) || m_hpr != LVecBase3f(0) || m_scale != LVecBase3f(1)) {
        indent(out, nbyte + 1);
        out << "pos [ " << m_pos[0] << " " << m_pos[1] << " " << m_pos[2] << " ]\n";
        indent(out, nbyte + 1);
        out << "hpr [ " << m_hpr[0] << " " << m_hpr[1] << " " << m_hpr[2] << "]\n";
        indent(out, nbyte + 1);
        out << "scale [ " << m_scale[0] << " " << m_scale[1] << " " << m_scale[2] << "]\n";
    }
    for (dna_group_vec_t::iterator it = m_children.begin(); it != m_children.end(); ++it) {
        (*it)->write(out, store, nbyte + 1);
    }
    indent(out, nbyte);
    out << "]\n";
}