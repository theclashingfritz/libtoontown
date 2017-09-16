#include "CPetChase.h"

#include "components/CMover.h"

NotifyCategoryDef(CPetChase, "");

TypeHandle CPetChase::_type_handle;

CPetChase::CPetChase(NodePath f_target, float f_min_dist, float f_move_angle) {
    target = f_target;
    min_dist = f_min_dist;
    move_angle = f_move_angle;
    
    look_at_node = NodePath("lookatNode");
    look_at_node.hide();
    
    vel = LVector3f(0.0);
    rot_vel = LVector3f(0.0);
}

CPetChase::~CPetChase() {
    look_at_node.remove_node();
}

void CPetChase::set_target(NodePath f_target) {
    CPetChase_cat.debug() << "set_target(NodePath f_target)" << std::endl;
    if (!f_target.is_empty()) {
        target = f_target;
    }
}

void CPetChase::set_mover(CMover *mover) {
    CPetChase_cat.debug() << "set_mover(CMover *mover)" << std::endl;
    CImpulse::set_mover(mover);
    look_at_node.reparent_to(m_nodepath);
    vel = LVector3f(0.0);
    rot_vel = LVector3f(0.0);
}

void CPetChase::set_min_dist(float f_min_dist) {
    CPetChase_cat.debug() << "set_min_dist(" << f_min_dist << ")" << std::endl;
    min_dist = f_min_dist;
}

void CPetChase::set_move_angle(float f_move_angle) {
    CPetChase_cat.debug() << "set_move_angle(" << f_move_angle << ")" << std::endl;
    move_angle = f_move_angle;
}

void CPetChase::process(float dt) {
    CPetChase_cat.debug() << "process(" << dt << ")" << std::endl;
    LVector3f target_pos = target.get_pos(m_nodepath);
    CPetChase_cat.spam() << "Target's Pos is LVector3f(" << target_pos[0] << ", " << target_pos[1] << ", " << target_pos[2] << ")" << std::endl;
    float x = target_pos[0];
    float y = target_pos[1];
    double distance = sqrt((x * x) + (y * y));
    LVector3f look_at_node_pos = look_at_node.get_pos();
    CPetChase_cat.spam() << "Look at Node's pos is LVector3f(" << look_at_node_pos[0] << ", " << look_at_node_pos[1] << ", " << look_at_node_pos[2] << ")" << std::endl;
    look_at_node.look_at(target);
    float rel_h = ((fmod((look_at_node.get_h(m_nodepath) + 180.0), 360.0)) - 180.0);
    CPetChase_cat.spam() << "rel_h in CPetChase::process() is " << rel_h << "!" << std::endl;
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
    if ((distance > min_dist) && (std::fabs(rel_h) < move_angle)) {
        v_forward = m_mover->get_fwd_speed();
    }
    
    double distance_left = distance - min_dist;
    
    if ((distance > min_dist) && (v_forward * dt > distance_left)) {
        v_forward = distance_left / dt;
    }
    
    if (v_forward != 0.0) {
        vel.set_y(v_forward);
        CPetChase_cat.spam() << "Adding Shove of LVector3f(" << vel[0] << ", " << vel[1] << ", " << vel[2] << ")!" << std::endl;
        m_mover->add_shove(LVector3f(vel));
        vel = LVector3f(0.0);
    }
    
    if (vH != 0.0) {
        rot_vel.set_x(vH);
        CPetChase_cat.spam() << "Adding Rotation Shove of LVector3f(" << rot_vel[0] << ", " << rot_vel[1] << ", " << rot_vel[2] << ")!" << std::endl;
        m_mover->add_rot_shove(LVector3f(rot_vel));
        rot_vel = LVector3f(0.0);
    }
}

NodePath CPetChase::get_target() {
    CPetChase_cat.debug() << "get_target()" << std::endl;
    if (!target.is_empty()) {
        return target;
    } else {
        return NodePath();
    }
}

float CPetChase::get_min_dist() {
    CPetChase_cat.debug() << "get_min_dist()" << std::endl;
    return min_dist;
}

float CPetChase::get_move_angle() {
    CPetChase_cat.debug() << "get_move_angle()" << std::endl;
    return move_angle;
}