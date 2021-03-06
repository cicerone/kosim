/*===============================================================================================
    Copyright (c) 2009 Kotys LLC. Distributed under the Boost Software License, Version 1.0. 
    (See accompanying file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
    Author: Cicerone Mihalache                                     
    Support: kosim@kotys.biz 
===============================================================================================*/

#ifndef KOSIM_HS_HIERARCHY_SCANNER_H
#define KOSIM_HS_HIERARCHY_SCANNER_H


#include <string>
#include <iostream>


namespace ko_sc
{
    
enum OBJECT_TYPE
{
    OT_MODULE     = 0,
    OT_PORT          ,
    OT_THREAD        , 
    OT_ALL
};

void scan_hierarchy (const sc_object* obj, OBJECT_TYPE)   ;              
void print_hierarchy();
void print_ports    (const char* p_full_name_);
void print_modules  (const char* p_full_name_);
void print_threads  (const char* p_full_name_);

int parse_args(int argc , char *argv[]);      

} // namespace


#endif // KOSIM_HS_HIERARCHY_SCANNER_H

