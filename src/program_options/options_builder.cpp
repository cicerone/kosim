/*===============================================================================================
    Copyright (c) 2009 Kotys LLC. Distributed under the Boost Software License, Version 1.0. 
    (See accompanying file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
    Author: Cicerone Mihalache                                     Support: kosim@kotys.biz 
===============================================================================================*/

#include <stdlib.h>
#include "options_builder.h"
#include "program_options.h"

OptionsBuilder::OptionsBuilder()
{
}

OptionsBuilder::~OptionsBuilder()
{
}

void OptionsBuilder::SetArgument(const char* p_arg_)
{
    string arg(p_arg_);
    m_argv.push_back(arg);
}

void OptionsBuilder::BuildArgv()
{
//    printf("size is (%d)\n", m_argv.size());

    mp_argv = (char**)calloc(m_argv.size(), sizeof(char*));
    for (uint32_t i = 0; i < m_argv.size(); i++)
    {
        mp_argv[i] = const_cast<char *>(m_argv[i].c_str());
//        printf("argument(%d) is (%s)\n", i, mp_argv[i]);
    }
}

void  OptionsBuilder::InitProgramOptions()
{
    ProgramOptions* p_program_options = ProgramOptions::GetInstance(m_argv.size(), mp_argv);
//    p_program_options->Help();
}

