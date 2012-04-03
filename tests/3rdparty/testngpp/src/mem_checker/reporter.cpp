/***
    testngpp is a generic C/C++ test framework.
    Copyright (C) <2010>  <Chen Guodong: sinojelly@gmail.com>

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
***/
#include <mem_checker/reporter.h>

static mem_checker::Reporter *mem_checker_info_reporter = 0;
static mem_checker::Reporter *mem_checker_failure_reporter = 0;

extern bool needToReport();
extern void file_output_func(const char * file, unsigned int line, const char* message);

mem_checker::Reporter *get_info_reporter()
{
    if ((needToReport()) && (0 != mem_checker_info_reporter))
    {
        return mem_checker_info_reporter;
    }

    // file_output_reporter can not be defined out of function, or else it causes a pure function calling.
    static mem_checker::ConcreteReporter<mem_checker::reporter_t> file_output_reporter(file_output_func); // avoid use new operator, or else memory leak occur.
    return &file_output_reporter;    
}

mem_checker::Reporter *get_failure_reporter()
{
    if ((needToReport()) && (0 != mem_checker_failure_reporter))
    {
        return mem_checker_failure_reporter;
    }

    static mem_checker::ConcreteReporter<mem_checker::reporter_t> file_output_reporter(file_output_func); // avoid use new operator, or else memory leak occur.
    return &file_output_reporter;    
}

void set_reporter
    ( mem_checker::Reporter *infoReporter
    , mem_checker::Reporter *failureReporter)
{
    if (0 != mem_checker_info_reporter)
    {
        delete mem_checker_info_reporter;
    }

    if (0 != mem_checker_failure_reporter)
    {
        delete mem_checker_failure_reporter;
    }

    mem_checker_info_reporter = infoReporter;
    mem_checker_failure_reporter = failureReporter;
}

void clr_reporter()
{
    if (0 != mem_checker_info_reporter)
    {
        delete mem_checker_info_reporter;
        mem_checker_info_reporter = 0;
    }

    if (0 != mem_checker_failure_reporter)
    {
        delete mem_checker_failure_reporter;
        mem_checker_failure_reporter = 0;
    }
}

#if 0
//////////////////////////////////////////////////////////////////////////
/// test using functor as out put function
#include <stdio.h>
struct OutPutter
{
    OutPutter(FILE* _fd)
        : fd(_fd)
    {
    }

    void operator ()(const char *file, unsigned int line, const char *message)
    {
        fprintf(fd, "[0x%x]%s(%u): %s\n", fd, file, line, message);
    }

private:
    FILE *fd;
};

void test_OutPutter()
{
    set_reporter( mem_checker::createReporter(OutPutter(stdout))
                , mem_checker::createReporter(OutPutter(stderr)));
}
#endif

