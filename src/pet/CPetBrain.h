#pragma once

#include "util.h"

#include <pandabase.h>
#include <typedReferenceCount.h>

NotifyCategoryDecl(CPetBrain, EXPCL_TOONTOWN, EXPTP_TOONTOWN);

class EXPCL_TOONTOWN CPetBrain : public TypedReferenceCount {
    
    PUBLISHED:
        CPetBrain();
        ~CPetBrain();
        
        bool is_attending_us(NodePath path1, NodePath path2);
    
    TYPE_HANDLE(CPetBrain, TypedObject);
};