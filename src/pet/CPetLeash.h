#pragma once

#include "util.h"

#include <stdlib.h> 
#include <math.h>

#include <pandabase.h>
#include <nodePath.h>

#include "CImpulse.h"

NotifyCategoryDecl(CPetLeash, EXPCL_TOONTOWN, EXPTP_TOONTOWN);

class CPetLeash;

class EXPCL_TOONTOWN CPetLeash : public virtual CImpulse {
    
    PUBLISHED:
        CPetLeash(NodePath f_origin, float f_length);
        ~CPetLeash();
        
        virtual void process(float dt);
        
    private:
        NodePath origin;
        float length;
    
    TYPE_HANDLE(CPetLeash, TypedObject);
};