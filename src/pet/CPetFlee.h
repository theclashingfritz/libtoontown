#pragma once

#include "util.h"

#include <stdlib.h> 
#include <math.h>

#include <pandabase.h>
#include <nodePath.h>

#include "CImpulse.h"

NotifyCategoryDecl(CPetFlee, EXPCL_TOONTOWN, EXPTP_TOONTOWN);

class CMover;
class CPetFlee;

class EXPCL_TOONTOWN CPetFlee : public virtual CImpulse {
    
    PUBLISHED:
        CPetFlee(NodePath f_chaser = NodePath(), float f_max_dist = 50.0, float f_move_angle = 20.0);
        ~CPetFlee();
        
        void set_chaser(NodePath f_chaser);
        void set_mover(CMover *mover);
        void set_max_dist(float f_max_dist);
        void set_move_angle(float f_move_angle);
        virtual void process(float dt);
        
        float get_max_dist();
        float get_move_angle();
        
    private:
        NodePath chaser;
        NodePath look_at_node;
        float max_dist;
        float move_angle;
        LVector3f vel;
        LVector3f rot_vel;
    
    TYPE_HANDLE(CPetFlee, TypedObject);
};