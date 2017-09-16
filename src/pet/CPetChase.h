#pragma once

#include "util.h"

#include <stdlib.h> 
#include <math.h>

#include <pandabase.h>
#include <nodePath.h>

#include "CImpulse.h"

NotifyCategoryDecl(CPetChase, EXPCL_TOONTOWN, EXPTP_TOONTOWN);

class CMover;
class CPetChase;

class EXPCL_TOONTOWN CPetChase : public virtual CImpulse {
    
    PUBLISHED:
        CPetChase(NodePath f_target = NodePath(), float f_min_dist = 5.0, float f_move_angle = 20.0);
        ~CPetChase();
        
        void set_target(NodePath f_target);
        void set_mover(CMover *mover);
        void set_min_dist(float f_min_dist);
        void set_move_angle(float f_move_angle);
        virtual void process(float dt);
        
        NodePath get_target();
        
        float get_min_dist();
        float get_move_angle();
        
    private:
        NodePath target;
        NodePath look_at_node;
        float min_dist;
        float move_angle;
        LVector3f vel;
        LVector3f rot_vel;
    
    TYPE_HANDLE(CPetChase, TypedObject);
};