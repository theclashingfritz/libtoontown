#include "DNASignBaseline.h"

#include <nodePathCollection.h>
#include <textNode.h>

#define _USE_MATH_DEFINES
#include <math.h>

TypeHandle DNASignBaseline::_type_handle;

DNASignBaseline::DNASignBaseline(const std::string& name): DNANode(name) {
    
}

DNASignBaseline::~DNASignBaseline() {
    
}

void DNASignBaseline::make_from_dgi(DatagramIterator& dgi, DNAStorage* store) {
    DNANode::make_from_dgi(dgi, store);
    m_text = dgi.get_string();
    m_code = dgi.get_string();
    m_color = DGI_EXTRACT_COLOR;
    m_flags = dgi.get_string();
    m_indent = dgi.get_float32();
    m_kern = dgi.get_float32();
    m_wiggle = dgi.get_float32();
    m_stumble = dgi.get_float32();
    m_stomp = dgi.get_float32();
    m_width = dgi.get_float32();
    m_height = dgi.get_float32();
}

void DNASignBaseline::traverse(NodePath& np, DNAStorage* store) {
    NodePath root("signroot");
    float x = 0;
    for (unsigned int i = 0; i < m_text.size(); ++i)
    {
        PT(TextNode) tn = new TextNode("text");
        tn->set_text(std::string(1, m_text.at(i)));
        tn->set_text_color(m_color);
        
        PT(TextFont) font = store->find_font(m_code);
        if (font == NULL)
        {
            raise_code_not_found(m_code.c_str());
            return;
        }
        
        tn->set_font(font);
        
        if (i == 0 && m_flags.find('b') != std::string::npos)
            tn->set_text_scale(1.5);
        
        NodePath np = root.attach_new_node(tn);
        np.set_scale(m_scale);
        np.set_depth_write(0);
        if (i & 1)
        {
            np.set_pos(x + m_stumble, 0, m_stomp);
            np.set_r(-m_wiggle);
        }
        
        else
        {
            np.set_pos(x - m_stumble, 0, m_stomp);
            np.set_r(m_wiggle); 
        }
        
        x += tn->get_width() * np.get_sx() + m_kern;
    }
    
    for (int i = 0; i < root.get_num_children(); ++i)
    {
        NodePath c = root.get_child(i);
        c.set_x(c.get_x() - x / 2.);
    }

    if (m_width != 0 && m_height != 0)
    {
        for (int i = 0; i < root.get_num_children(); ++i)
        {
            NodePath node = root.get_child(i);

            double A = (node.get_x() / (m_height / 2.));
            double B = (m_indent * M_PI / 180.);

            double theta = A + B;
            double d, x, y, radius;
            d = node.get_y();
            x = sin(theta) * (m_width / 2.);
            y = (cos(theta) - 1) * (m_height / 2.);
            radius = hypot(x, y);

            if (radius != 0)
            {
                double j = (radius + d) / radius;
                x *= j;
                y *= j;
            }
            node.set_pos(x, 0, y);
            node.set_r(node, theta * 180. / M_PI);
        }
    }

    NodePathCollection collection = root.find_all_matches("**/+TextNode");
    for (int i = 0; i < collection.get_num_paths(); ++i)
    {
        NodePath np = collection.get_path(i);
        NodePath np2 = np.get_parent().attach_new_node(DCAST(TextNode, np.node())->generate());
        np2.set_transform(np.get_transform());
        np.remove_node();
    }

    NodePath _np = np.attach_new_node(root.node());
    _np.set_pos_hpr(m_pos, m_hpr);
    _np.set_depth_offset(50);

    traverse_children(_np, store);
    _np.flatten_strong();
}

void DNASignBaseline::write(std::ostream& out, DNAStorage *store, unsigned int nbyte) {
    out << "baseline [\n";
    
    if (m_code.size()) {
        out << "code [ \"" << m_code << "\" ]\n";
    }
    
    if (m_color != LVecBase4f(1, 1, 1, 1)) {
        out << "color [ " << m_color.get_x() << " "
                     << m_color.get_y() << " " << m_color.get_z()
                     << " " << m_color.get_w() << " ]\n";
    }
    
    if (m_pos != LVecBase3f(0) || m_hpr != LVecBase3f(0) || m_scale != LVecBase3f(1)) {
        out << "pos [ " << m_pos[0] << " " << m_pos[1] << " " << m_pos[2] << "]\n";
        out << "hpr [ " << m_hpr[0] << " " << m_hpr[1] << " " << m_hpr[2] << "]\n";
        out << "scale [ " << m_scale[0] << " " << m_scale[1] << " " << m_scale[2] << "]\n";
    }

    if (m_flags.size()) {
        out << "flags [ \"" << m_flags << "\" ]";
    }
    
    WRITE_IF_NOT_NULL(indent);
    WRITE_IF_NOT_NULL(kern);
    WRITE_IF_NOT_NULL(wiggle);
    WRITE_IF_NOT_NULL(stumble);
    WRITE_IF_NOT_NULL(stomp);
    WRITE_IF_NOT_NULL(width);
    WRITE_IF_NOT_NULL(height);
    
    for (size_t i = 0; i < m_text.size(); ++i) {
        out << "text [\n " << "letters [ \"" << m_text.at(i) << "\" ]\n " << "]\n" << std::endl;
    }
    
    for (dna_group_vec_t::iterator it = m_children.begin(); it != m_children.end(); ++it) {
        (*it)->write(out, store, nbyte);
    }
    
    out << "]\n";
}