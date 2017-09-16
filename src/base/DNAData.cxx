#include "DNAData.h"

TypeHandle DNAData::_type_handle;

DNAData::DNAData(const std::string& name) : DNAGroup(m_name) {
    m_cur_store = nullptr;
    cord_system = get_default_coordinate_system();
}

DNAData::~DNAData() {
    
}

void DNAData::pre_write() {
    
}

void DNAData::set_coordinate_system(CoordinateSystem &system) {
    if (!system) {
        cord_system = get_default_coordinate_system();
        return;
    }
    cord_system = system;
}

void DNAData::set_dna_filename(Filename &file) {
    dna_filename = file;
}

void DNAData::set_dna_storage(DNAStorage &storage) {
    m_cur_store = &storage;
}

bool DNAData::resolve_dna_filename(Filename file, DSearchPath s_path) {
    VirtualFileSystem *vfs = VirtualFileSystem::get_global_ptr();
    std::string extension = "dna";
    ConfigVariableSearchPath model_path = get_model_path();
    if (vfs->resolve_filename(file, s_path, extension)) {
        auto file_found = vfs->get_file(file, 1);
        return (file_found != NULL && file_found != nullptr);
    } else if (vfs->resolve_filename(file, model_path.get_value(), extension)) {
        auto file_found = vfs->get_file(file, 1);
        return (file_found != NULL && file_found != nullptr);
    } else {
        return false;
    }
}

CoordinateSystem DNAData::get_coordinate_system() {
    return cord_system;
}

Filename DNAData::get_dna_filename() {
    return dna_filename;
}

DNAStorage *DNAData::get_dna_storage() {
    if (m_cur_store == NULL || m_cur_store == nullptr) {
        DNAStorage *new_storage = new DNAStorage;
        return new_storage;
    }
    return m_cur_store;
}

DNAData *DNAData::make_copy() {
    DNAData *copy = new DNAData(m_name);
    copy->set_coordinate_system(cord_system);
    copy->set_dna_filename(Filename(dna_filename));
    if (m_cur_store == NULL || m_cur_store == nullptr) {
        DNAStorage *new_storage = new DNAStorage;
        copy->set_dna_storage(*new_storage);
    } else {
        copy->set_dna_storage(*m_cur_store);
    }
    
    return copy;
}

void DNAData::write(std::ostream& out, DNAStorage *store, unsigned int nbyte) {
    store->write(out, nbyte);
    out << std::endl;
}