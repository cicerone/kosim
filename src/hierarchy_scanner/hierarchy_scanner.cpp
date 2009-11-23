
#include <string>
#include <iostream>

#include <systemc.h>

namespace ko_sc
{


void scan_hierarchy_obj(const sc_object* obj)               
{
   std::vector<sc_object*> p_children = obj->get_child_objects();
   for ( unsigned i = 0; i < p_children.size(); i++ )
   {
       if ( p_children[i] ) 
       {
            printf("name(%s)   kind(%s)\n", p_children[i]->name(),  p_children[i]->kind());
            scan_hierarchy_obj( p_children[i] );
       }
   }         
}


void scan_hierarchy_name(const char* p_full_name_)               
{
    cout << p_full_name_ << endl;
    if (strcmp(p_full_name_, "Top1") == 0) {
        printf("They match!\n");
    }
    else {
        printf("They DO NOT match!\n");
    }
    //const sc_object* p_root_obj = sc_find_object( p_full_name_ );
    const sc_object* p_root_obj = sc_find_object("Top1");

    if (p_root_obj != NULL) {
        scan_hierarchy_obj(p_root_obj);
    }
    else {
        printf("incorrect root name(%s)\n", p_full_name_);
    }
}

} // namespace
