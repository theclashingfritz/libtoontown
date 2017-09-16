#include "CPetLeash.h"

#include "components/CMover.h"

NotifyCategoryDef(CPetLeash, "");

TypeHandle CPetLeash::_type_handle;

CPetLeash::CPetLeash(NodePath f_origin, float f_length) {
    origin = f_origin;
    length = f_length;
}

CPetLeash::~CPetLeash() {

}

void CPetLeash::process(float dt) {
    CPetLeash_cat.debug() << "process(" << dt << ")" << std::endl;
    LVector3f target_pos = m_nodepath.get_pos();
    float target_dist = LVector3f(target_pos - origin.get_pos()).length();
    if (target_dist > length) {
        float excess = target_dist - length;
        LVector3f shove = LVector3f(target_pos);
        shove.normalize();
        shove *= -excess;
        m_mover->add_shove(shove);
    }
}
