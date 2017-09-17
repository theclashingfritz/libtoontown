#include "DNABattleCell.h"

#include "DNAStorage.h"

TypeHandle DNABattleCell::_type_handle;

DNABattleCell::DNABattleCell(float width, float height, LPoint3f pos): m_width(width),
                             m_height(height), m_pos(pos) {
}

DNABattleCell::~DNABattleCell() {
    
}


void DNABattleCell::write(std::ostream& out, DNAStorage *store, unsigned int nbyte) {
    indent(out, nbyte);
    out << "battle_cell [" << m_width << " " << m_height << " " << m_pos[0] << " " << m_pos[1] << " " << m_pos[2] << "]\n";
}