/*===============================================================================================
    Copyright (c) 2009 Kotys LLC. Distributed under the Boost Software License, Version 1.0. 
    (See accompanying file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
    Author: Cicerone Mihalache                                     
    Support: kosim@kotys.biz 
===============================================================================================*/

#ifndef KOSIM_PO_PROGRAM_OPTIONS_BASE_H
#define KOSIM_PO_PROGRAM_OPTIONS_BASE_H

#include <string>
#include <iostream>
#include <fstream>
#include <stdint.h>

#include <boost/utility.hpp>
#include <boost/program_options.hpp>

namespace po = boost::program_options;


class ProgramOptionsBase : boost::noncopyable
{
public:
    void Help();

    ProgramOptionsBase();
    ~ProgramOptionsBase();
    virtual void InitConfiguration() {};
    void   RegisterConfiguration(int ac_, char* p_av_[]);

protected:

    po::options_description* mp_generic_options    ;
    po::options_description* mp_config_options     ;
    po::options_description* mp_hidden_options     ;
    po::options_description* mp_cmdline_options    ;
    po::options_description* mp_config_file_options;
    po::options_description* mp_visible_options    ;
    po::variables_map*       mp_variable_map       ;
    po::positional_options_description* mp_positional_options;
    std::string m_config_file;    // configuration pattern file

private:

};

#endif // KOSIM_PO_PROGRAM_OPTIONS_BASE_H
