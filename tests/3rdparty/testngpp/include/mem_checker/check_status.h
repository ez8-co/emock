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

#ifndef __CHECK_STATUS_H__
#define __CHECK_STATUS_H__

unsigned int nullCheckStatus();
unsigned int getCheckStatus();
void initCheckStatus();
void clearCheckStatus();
bool matchCheckStatus(unsigned int status);
void pauseCheckStatus();
void reopenCheckStatus();


#endif


