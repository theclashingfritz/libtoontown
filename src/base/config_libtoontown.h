#pragma once

#include <pandabase.h>
#include <notifyCategoryProxy.h>

#pragma warning (disable : 4273)
#pragma warning (disable : 4275)

#ifdef BUILDING_TOONTOWN
    #define EXPCL_TOONTOWN EXPORT_CLASS 
    #define EXPTP_TOONTOWN EXPORT_TEMPL 
#else 
   #define EXPCL_TOONTOWN IMPORT_CLASS 
   #define EXPTP_TOONTOWN IMPORT_TEMPL 
#endif 

#ifdef BUILDING_DNA 
    #define EXPCL_DNA EXPORT_CLASS 
    #define EXPTP_DNA EXPORT_TEMPL 
#else 
   #define EXPCL_DNA IMPORT_CLASS 
   #define EXPTP_DNA IMPORT_TEMPL 
#endif 

#ifdef BUILDING_LIBOTP
    #define EXPCL_LIBOTP EXPORT_CLASS 
    #define EXPTP_LIBOTP EXPORT_TEMPL 
#else 
    #define EXPCL_LIBOTP IMPORT_CLASS 
    #define EXPTP_LIBOTP IMPORT_TEMPL 
#endif 

NotifyCategoryDecl(dna, EXPCL_DNA, EXPTP_DNA);
NotifyCategoryDecl(libtoontown, EXPCL_TOONTOWN, EXPTP_TOONTOWN);
extern EXPCL_TOONTOWN void init_libtoontown();

