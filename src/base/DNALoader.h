#ifndef _H_DNA_LOADER_
#define _H_DNA_LOADER_

#include "dnabase.h"
#include "DNAGroup.h"
#include "DNAStorage.h"
#include "DNAData.h"

#include <nodePath.h>
#include <coordinateSystem.h>

class EXPCL_DNA DNALoader
{
    PUBLISHED:
        DNALoader();
        ~DNALoader();
        
        NodePath load_DNA_file(DNAStorage* store, const Filename& file, CoordinateSystem coords, bool store_group = false, bool is_pdna = false);
        DNAGroup *load_DNA_file_AI(DNAStorage* store, const Filename& file);
        
    public:
        PointerTo<PandaNode> build_graph(NodePath &path, DNAStorage *store, int store_group = 0);
        
    private:
       void handle_storage_data(DatagramIterator& dgi); 
       void handle_comp_data(DatagramIterator& dgi);
       void load_DNA_file_base(DNAStorage* store, const Filename& file);
       
       DNAStorage *m_cur_store;
       DNAGroup *m_cur_comp;
       DNAData *m_data;
};

#endif
