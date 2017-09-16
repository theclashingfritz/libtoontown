#include "CPetFlee.h"

#include "components/CMover.h"

NotifyCategoryDef(CPetFlee, "");

TypeHandle CPetFlee::_type_handle;

CPetFlee::CPetFlee(NodePath f_chaser, float f_max_dist, float f_move_angle) {
    chaser = f_chaser;
    max_dist = f_max_dist;
    move_angle = f_move_angle;
    
    look_at_node = NodePath("lookatNode");
    look_at_node.hide();
    
    vel = LVector3f(0.0);
    rot_vel = LVector3f(0.0);
}

CPetFlee::~CPetFlee() {
    look_at_node.remove_node();
}

void CPetFlee::set_chaser(NodePath f_chaser) {
    CPetFlee_cat.debug() << "set_chaser(NodePath f_chaser)" << std::endl;
    if (!f_chaser.is_empty()) {
        chaser = f_chaser;
    }
}

void CPetFlee::set_mover(CMover *mover) {
    CPetFlee_cat.debug() << "set_mover(CMover *mover)" << std::endl;
    CImpulse::set_mover(mover);
    look_at_node.reparent_to(m_nodepath);
    vel = LVector3f(0.0);
    rot_vel = LVector3f(0.0);
}

void CPetFlee::set_max_dist(float f_max_dist) {
    CPetFlee_cat.debug() << "set_max_dist(" << f_max_dist << ")" << std::endl;
    max_dist = f_max_dist;
}

void CPetFlee::set_move_angle(float f_move_angle) {
    CPetFlee_cat.debug() << "set_move_angle(" << f_move_angle << ")" << std::endl;
    move_angle = f_move_angle;
}

void CPetFlee::process(float dt) {
    CPetFlee_cat.debug() << "process(" << dt << ")" << std::endl;
    LVector3f chaser_pos = chaser.get_pos(m_nodepath);
    chaser_pos.set_z(0);
    double distance = LVector3f(chaser_pos).length();
    look_at_node.look_at(chaser);
    float rel_h = ((fmod((look_at_node.get_h(m_nodepath) + 180.0), 360.0)) + 180.0);
    double epsilon = 0.0050000000000000001;
    float rot_speed = m_mover->get_rot_speed();
    float vH;
    if (rel_h < -epsilon) {
        vH = -rot_speed;
    } else if (rel_h > epsilon) {
        vH = rot_speed;
    } else {
        vH = 0;
    }
    if (std::fabs(vH * dt) > std::fabs(rel_h)) {
        vH = rel_h / dt;
    }
    
    float v_forward = 0.0;
    if ((distance < max_dist) && (std::fabs(rel_h) < move_angle)) {
        v_forward = m_mover->get_fwd_speed();
    }
    
    double distance_left = max_dist - distance;
    
    if ((distance_left > 0.0) && (v_forward * dt > distance_left)) {
        v_forward = distance_left / dt;
    }
    
    vel.set_y(v_forward);
    rot_vel.set_x(vH);
    m_mover->add_shove(vel);
    m_mover->add_rot_shove(rot_vel);
}

float CPetFlee::get_max_dist() {
    CPetFlee_cat.debug() << "get_max_dist()" << std::endl;
    return max_dist;
}

float CPetFlee::get_move_angle() {
    CPetFlee_cat.debug() << "get_move_angle()" << std::endl;
    return move_angle;
}