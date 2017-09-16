#include "CPetBrain.h"

NotifyCategoryDef(CPetBrain, "");

TypeHandle CPetBrain::_type_handle;

CPetBrain::CPetBrain() {

}

CPetBrain::~CPetBrain() {
    
}

bool CPetBrain::is_attending_us(NodePath path1, NodePath path2) {
  CPetBrain_cat.debug() << "is_attending_us(NodePath path1, NodePath path2)" << std::endl;
  LVector3f v4;
  LVector3f v6;
  LVector3f v8;
  float path1B; // [sp+64h] [bp+4h]@1
  float path1A; // [sp+64h] [bp+4h]@3
  float path1C; // [sp+64h] [bp+4h]@7
  float path1D; // [sp+64h] [bp+4h]@9
  bool result;

  v4 = path2.get_pos(path1);
  path1B = ((v4[1] * v4[1]) + (v4[0] * v4[0]) + (v4[2] * v4[2]));
  if (path1B > 100.0 ) {
      result = false;
  } else {
      result = true;
  }
  if (result == true) {
      return result;
  }
  v6 = path1.get_pos(path2);
  path1A = ((v6[1] * v6[1]) + (v6[0] * v6[0]) + (v6[2] * v6[2]));
  if ( path1A == 0.0 ) {
      v6[0] = 0.0;
      v6[1] = 0.0;
      v6[2] = 0.0;
  } else {
      path1B = path1A - 1.0;
      if ( path1B >= 9.999999949504854e-13 || path1B <= -9.999999949504854e-13 ) {
          path1D = 1.0 / sqrt(path1A);
          v6[0] = v6[0] * path1D;
          v6[1] = v6[1] * path1D;
          v6[2] = path1D * v6[2];
      }
  }
  v8 = LVector3f::forward();
  path1C = ((v8[1] * v6[1]) + (v8[0] * v6[0]) + (v8[2] * v6[2]));
  if ( path1C < 0.8 ) {
      result = true;
  } else {
      result = false;
  }
  return result;
}