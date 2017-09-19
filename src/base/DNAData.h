#ifndef _H_DNA_DATA_
#define _H_DNA_DATA_

#include "dnabase.h"
#include "DNAGroup.h"
#include "DNAStorage.h"

#include <pandabase.h>
#include <nodePath.h>
#include <coordinateSystem.h>
#include <dSearchPath.h>
#include <virtualFileSystem.h>
#include <configFlags.h>
#include <configVariableSearchPath.h>

class DNAData;

class EXPCL_DNA DNAData : public DNAGroup {
    
    PUBLISHED:
        DNAData(const std::string& name);
        ~DNAData();
        
        void set_coordinate_system(CoordinateSystem &system);
        void set_dna_filename(Filename &file);
        void set_dna_storage(DNAStorage &storage);
        CoordinateSystem get_coordinate_system();
        bool resolve_dna_filename(Filename file, DSearchPath s_path);
        Filename get_dna_filename();
        DNAStorage *get_dna_storage();
        DNAData *make_copy();
        
    public:
        void pre_write();
        virtual void write(std::ostream& out, DNAStorage *store, unsigned int nbyte = 0);
        bool read(istream &file_stream, ostream &notify_stream);
        
    private:
        CoordinateSystem cord_system;
        Filename dna_filename;
        DNAStorage *m_cur_store;
        
    TYPE_HANDLE(DNAData, TypedObject);
};

#endif