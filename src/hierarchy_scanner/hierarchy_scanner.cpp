
#include <string>
#include <iostream>

#include <systemc.h>
#include "hierarchy_scanner.h"

namespace ko_sc
{


void scan_hierarchy(const sc_object* obj, const OBJECT_TYPE type_)               
{
   std::vector<sc_object*> children = obj->get_child_objects();
   for ( unsigned i = 0; i < children.size(); i++ )
   {
       if ( children[i] ) 
       {
            switch(type_) 
            {
                case OT_MODULE:
                    if (strcmp(children[i]->kind(), "sc_module") == 0) 
                        printf("name(%30s)   kind(%10s)\n", children[i]->name(),  children[i]->kind());
                    break;
                case OT_PORT  :
                    if (strcmp(children[i]->kind(), "sc_port") == 0) 
                        printf("name(%30s)   kind(%10s)\n", children[i]->name(),  children[i]->kind());
                    break;
                case OT_THREAD:
                    if (strcmp(children[i]->kind(), "sc_thread_process") == 0) 
                        printf("name(%30s)   kind(%10s)\n", children[i]->name(),  children[i]->kind());
                    break;
                case OT_ALL   :
                    printf("name(%30s)   kind(%10s)\n", children[i]->name(),  children[i]->kind());
                    break;
            }

            scan_hierarchy(children[i], type_ );
       }
   }         
}

void print_hierarchy()
{
    std::vector<sc_object*> tops = sc_get_top_level_objects();
    for ( unsigned i = 0; i < tops.size(); i++ )
    {
        if ( tops[i] )
           scan_hierarchy(tops[i], OT_ALL);
    }
}

void print_ports(const char* p_full_name_)
{
    const sc_object* p_root_obj = sc_find_object( p_full_name_ );

    if (p_root_obj != NULL) {
        scan_hierarchy(p_root_obj, OT_PORT);
    }
    else {
        fprintf(stderr, "ERROR! Incorrect root name(%s)!\n", p_full_name_);
    }
}


void print_modules  (const char* p_full_name_)
{
    const sc_object* p_root_obj = sc_find_object( p_full_name_ );

    if (p_root_obj != NULL) {
        scan_hierarchy(p_root_obj, OT_MODULE);
    }
    else {
        fprintf(stderr, "ERROR! Incorrect root name(%s)!\n", p_full_name_);
    }
}

void print_threads(const char* p_full_name_)
{
    const sc_object* p_root_obj = sc_find_object( p_full_name_ );

    if (p_root_obj != NULL) {
        scan_hierarchy(p_root_obj, OT_THREAD);
    }
    else {
        fprintf(stderr, "ERROR! Incorrect root name(%s)!\n", p_full_name_);
    }
}


int parse_args (int argc , char *argv[]) 
{
    for (int i = 0; i < argc; i++)
    {
        printf("arg(%d) is (%s)\n", i, argv[i]);
    }
    return argc;
}


} // namespace
