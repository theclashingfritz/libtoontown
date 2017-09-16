#pragma once

#include "config_libtoontown.h"
#include "base/config_libotp.h"

#include <stdint.h>
#include <pandabase.h>
#include <nodepath.h>
#include <luse.h>

#define COMPCODE_GROUP 1
#define COMPCODE_VISGROUP 2
#define COMPCODE_NODE 3
#define COMPCODE_PROP 4
#define COMPCODE_SIGN 5
#define COMPCODE_SIGN_BASELINE 6
#define COMPCODE_SIGN_GRAPHIC 8
#define COMPCODE_FLAT_BUILDING 9
#define COMPCODE_WALL 10
#define COMPCODE_WINDOWS 11
#define COMPCODE_CORNICE 12
#define COMPCODE_LANDMARK_BUILDING 13
#define COMPCODE_ANIM_PROP 14
#define COMPCODE_INTERACTIVE_PROP 15
#define COMPCODE_ANIM_BUILDING 16
#define COMPCODE_DOOR 17
#define COMPCODE_FLAT_DOOR 18
#define COMPCODE_STREET 19
#define COMPCODE_RETURN 255

typedef pvector<LVecBase4f> color_tuple_t; // (LVecBase4f, LVecBase4f)
typedef pvector<color_tuple_t> color_tuple_tuple_t; // ((LVecBase4f, LVecBase4f), (LVecBase4f, LVecBase4f))
typedef pmap<int, color_tuple_tuple_t> state_map_t; // {state: color_tuple_tuple_t}
typedef pmap<int, color_tuple_t> state_map_simple_t; // {state: color_tuple_t}
typedef pmap<int, NodePath> buttons_map_t;
typedef pmap<unsigned int, state_map_t> color_map_t; // {cc: state_map_t}
typedef pmap<unsigned int, state_map_simple_t> whisper_color_map_t; // {wt: state_map_simple_t}

typedef unsigned short zone_id_t;
typedef int block_number_t;
typedef unsigned short point_index_t;

#include <datagramIterator.h>
#include <luse.h>

inline LVecBase4f dgi_extract_color(DatagramIterator& dgi)
{
    double r = dgi.get_uint8() / 255.;
    double g = dgi.get_uint8() / 255.;
    double b = dgi.get_uint8() / 255.;
    double a = dgi.get_uint8() / 255.;
    return LVecBase4f(r, g, b, a);
}

#define DGI_EXTRACT_COLOR dgi_extract_color(dgi)
                                  
// WRITE_DNA
// This is a helper for classes
// Reduces litter in class declaration
#define WRITE_DNA INLINE virtual void write_dna(std::ostream& out, bool recursive=true, int indent=0)

// WRITE_PDNA
// This is a helper for classes
// Reduces litter in class declaration
#define WRITE_PDNA INLINE virtual void write_pdna(Datagram& dg, bool recursive=true)

// Helper functions
inline void pack_color(Datagram& dg, const LVecBase3f& color)
{
    dg.add_uint8(floor(color.get_x() * 255));
    dg.add_uint8(floor(color.get_y() * 255));
    dg.add_uint8(floor(color.get_z() * 255));
}

inline void pack_color(Datagram& dg, const LVecBase4f& color)
{
    dg.add_uint8(floor(color.get_x() * 255));
    dg.add_uint8(floor(color.get_y() * 255));
    dg.add_uint8(floor(color.get_z() * 255));
    dg.add_uint8(floor(color.get_w() * 255));
}

#define PACK_COLOR pack_color(dg, m_color)

#define COMP_CODE(X) INLINE virtual unsigned char get_comp_code() {return X;}
#define COMP_NAME(X) INLINE virtual const char* get_comp_name() {return #X;}
#define INDENTED_OUT out << std::string(indent, ' ')

#define EMPTY_NODEPATH NodePath()
#define PT_EMPTY_NODEPATH &NodePath()

#define CLICKSTATE_NORMAL    0
#define CLICKSTATE_CLICK     1
#define CLICKSTATE_HOVER     2
#define CLICKSTATE_DISABLED  3

#define ROL(x, y) __asm{rol x, y}
#define ROR(x, y) __asm{ror x, y}

#define CONCATE_(X, Y) X##Y
#define CONCATE(X, Y) CONCATE_(X, Y)

#define ALLOW_ACCESS(CLASS, TYPE, MEMBER) \
  template<typename Only, TYPE CLASS::*Member> \
  struct CONCATE(MEMBER, __LINE__) { friend TYPE (CLASS::*Access(Only*)) { return Member; } }; \
  template<typename> struct Only_##MEMBER; \
  template<> struct Only_##MEMBER<CLASS> { friend TYPE (CLASS::*Access(Only_##MEMBER<CLASS>*)); }; \
  template struct CONCATE(MEMBER, __LINE__)<Only_##MEMBER<CLASS>, &CLASS::MEMBER>

#define ACCESS(OBJECT, MEMBER) \
(OBJECT).*Access((Only_##MEMBER<std::remove_reference<decltype(OBJECT)>::type>*)nullptr)

// Handy typedefs.
typedef LPoint3f LVertexf;
typedef LVector3f LNormalf;
typedef LPoint2f LTexCoordf;
typedef LPoint3f LTexCoord3f;
typedef LVecBase4f LColorf;
typedef LVecBase3f LRGBColorf;
typedef LPoint3d LVertexd;
typedef LVector3d LNormald;
typedef LPoint2d LTexCoordd;
typedef LPoint3d LTexCoord3d;
typedef LVecBase4d LColord;
typedef LVecBase3d LRGBColord;

typedef LVertexf LVertex;
typedef LNormalf LNormal;
typedef LTexCoordf LTexCoord;
typedef LTexCoord3f LTexCoord3;
typedef LColorf LColor;
typedef LRGBColorf LRGBColor;

//Define the Python Typedefs. 
typedef LMatrix4f Mat4;
typedef LMatrix3f Mat3;
typedef LVecBase4f VBase4;
typedef LVector4f Vec4;
typedef LPoint4f Point4;
typedef LVecBase3f VBase3;
typedef LVector3f Vec3;
typedef LPoint3f Point3;
typedef LVecBase2f VBase2;
typedef LVector2f Vec2;
typedef LPoint2f Point2;
typedef LQuaternionf Quat;

//Define these older Panda3D types for our new Panda3D
typedef unsigned short ushort;
typedef PointerToArray<ushort> PTA_ushort;
typedef ConstPointerToArray<ushort> CPTA_ushort;
typedef LVector3f Normalf;
typedef PointerToArray<Normalf> PTA_Normalf;
typedef ConstPointerToArray<Normalf> CPTA_Normalf;
typedef LPoint3f Vertexf;
typedef PointerToArray<Vertexf> PTA_Vertexf;
typedef ConstPointerToArray<Vertexf> CPTA_Vertexf;
typedef LPoint2f TexCoordf;
typedef PointerToArray<TexCoordf> PTA_TexCoordf;
typedef ConstPointerToArray<TexCoordf> CPTA_TexCoordf;
typedef LVecBase4f Colorf;
typedef PointerToArray<Colorf> PTA_Colorf;
typedef ConstPointerToArray<Colorf> CPTA_Colorf;

// PROPERTY MACRO (TYPE, NAME)
// This is a helper for classes
// Declares protected m_NAME variable of type TYPE
// and generates PUBLISHED INLINE setter/getter
// N.B. Anything below a PROPERTY declaration will
// default to protected
#define PROPERTY(TYPE, NAME) PUBLISHED: \
                                INLINE void set_##NAME (TYPE value) { m_##NAME = value; }; \
                                INLINE TYPE get_##NAME () { return m_##NAME ; }; \
                            protected: \
                                TYPE m_##NAME ;
                                
// PROPERTY_STRING is like above, but it uses const std::string& for setter
#define PROPERTY_STRING(NAME) PUBLISHED: \
                                INLINE void set_##NAME (const std::string& value) { m_##NAME = value; }; \
                                INLINE std::string get_##NAME () { return m_##NAME ; }; \
                            protected: \
                                std::string m_##NAME ;

// TYPE_HANDLE MACRO
// This is a helper for classes
// Reduces litter in class declaration
#define TYPE_HANDLE(NAME, PARENT) public: \
                                    static TypeHandle get_class_type() { return _type_handle; }; \
                                    virtual TypeHandle force_init_type() { init_type(); return get_class_type(); }; \
                                    virtual TypeHandle get_type() const { return get_class_type(); }; \
                                    static void init_type() { PARENT :: init_type(); register_type(_type_handle, #NAME, PARENT :: get_class_type()); }; \
                                  private: static TypeHandle _type_handle;
