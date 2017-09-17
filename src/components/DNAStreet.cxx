#include "DNAStreet.h"

TypeHandle DNAStreet::_type_handle;

DNAStreet::DNAStreet(const std::string& name): DNANode(name), m_code(""),
                                               m_street_texture(""),
                                               m_sidewalk_texture(""),
                                               m_curb_texture(""),
                                               m_street_color(LVecBase4f(1)),
                                               m_sidewalk_color(LVecBase4f(1)),
                                               m_curb_color(LVecBase4f(1))
{
}

DNAStreet::~DNAStreet()
{
}

void DNAStreet::make_from_dgi(DatagramIterator& dgi, DNAStorage* store)
{
    DNANode::make_from_dgi(dgi, store);
    m_code = dgi.get_string();
    m_street_texture = dgi.get_string();
    m_sidewalk_texture = dgi.get_string();
    m_curb_texture = dgi.get_string();
    m_street_color = DGI_EXTRACT_COLOR;
    m_sidewalk_color = DGI_EXTRACT_COLOR;
    m_curb_color = DGI_EXTRACT_COLOR;
}

void DNAStreet::traverse(NodePath& np, DNAStorage* store)
{
    NodePath result = store->find_node(m_code);
    if (result.is_empty())
    {
        raise_code_not_found();
        return;
    }
    
    NodePath _np = result.copy_to(np);
    _np.set_name(m_name);
    
    PT(Texture) street_texture = get_texture(m_street_texture, store);
    PT(Texture) sidewalk_texture = get_texture(m_sidewalk_texture, store);
    PT(Texture) curb_texture = get_texture(m_curb_texture, store);
    
    NodePath street_node = _np.find("**/*_street");
    NodePath sidewalk_node = _np.find("**/*_sidewalk");
    NodePath curb_node = _np.find("**/*_curb");
    
    if (!street_node.is_empty() && street_texture)
    {
        street_node.set_texture(street_texture, 1);
        street_node.set_color_scale(m_street_color);
    }
    
    if (!sidewalk_node.is_empty() && sidewalk_texture)
    {
        sidewalk_node.set_texture(sidewalk_texture, 1);
        sidewalk_node.set_color_scale(m_sidewalk_color);
    }
    
    if (!curb_node.is_empty() && curb_node)
    {
        curb_node.set_texture(curb_texture, 1);
        curb_node.set_color_scale(m_curb_color);
    }
    
    _np.set_pos_hpr_scale(m_pos, m_hpr, m_scale);
}
        
PT(Texture) DNAStreet::get_texture(const std::string& texture, DNAStorage* store)
{
    if (!texture.size())
        return NULL;
   
    PT(Texture) tex = store->find_texture(texture);
    if (!tex)
    {
        raise_code_not_found(texture.c_str());
        return NULL;
    }

    return tex;
}

void DNAStreet::write(std::ostream& out, DNAStorage *store, unsigned int nbyte) {
    indent(out, nbyte);
    out << "street \"" << m_name << "\" [\n";
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
    if (m_street_color != LVecBase4f(1) || m_sidewalk_color != LVecBase4f(1) || m_curb_color != LVecBase4f(1)) {
        indent(out, nbyte + 1);
        out << "color [ " << m_street_color[0] << " " << m_street_color[1] << " " << m_street_color[2] << " " << m_street_color[3] << " ]\n";
        indent(out, nbyte + 1);
        out << "color [ " << m_sidewalk_color[0] << " " << m_sidewalk_color[1] << " " << m_sidewalk_color[2] << " " << m_sidewalk_color[3] << " ]\n";
        indent(out, nbyte + 1);
        out << "color [ " << m_curb_color[0] << " " << m_curb_color[1] << " " << m_curb_color[2] << " " << m_curb_color[3] << " ]\n";
    }
    indent(out, nbyte + 1);
    out << "texture [ \"" << m_street_texture << "\" ]\n";
    indent(out, nbyte + 1);
    out << "texture [ \"" << m_sidewalk_texture << "\" ]\n";
    indent(out, nbyte + 1);
    out << "texture [ \"" << m_curb_texture << "\" ]\n";
    for (dna_group_vec_t::iterator it = m_children.begin(); it != m_children.end(); ++it) {
        (*it)->write(out, store, nbyte + 1);
    }
    indent(out, nbyte);
    out << "]\n";
}