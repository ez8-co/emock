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
#include <mem_checker/check_status.h>
#include <stdlib.h>
#include <time.h>


static unsigned int check_status = 0; 
static unsigned int check_status_backup = 0;


unsigned int nullCheckStatus()
{
    return 0;
}

void initCheckStatus()
{
    srand( time(NULL) ); // use random number to avoid report the mem leaks of  previous testcase.
    unsigned int temp = rand();
    check_status = (temp == 0) ? 1 : temp;
}

void clearCheckStatus()
{
    check_status = nullCheckStatus();
}

unsigned int getCheckStatus()
{
    return check_status;
}

bool matchCheckStatus(unsigned int status)
{
    if (nullCheckStatus() == status)
    {
        return false;
    }
    
    return check_status == status;
}

void pauseCheckStatus()
{
    check_status_backup = check_status;
    check_status = nullCheckStatus();
}

void reopenCheckStatus()
{
    check_status = check_status_backup;
}


