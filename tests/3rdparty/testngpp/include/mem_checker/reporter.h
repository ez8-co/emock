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

#ifndef __REPORTER_H__
#define __REPORTER_H__


namespace mem_checker
{

typedef void (*reporter_t)(const char *, unsigned int, const char *);

struct Reporter
{
	virtual void report(const char *file, unsigned int line, const char *message) = 0;

	virtual ~Reporter(){}
};

template <typename Predict>
class ConcreteReporter : public Reporter
{
public:    
	ConcreteReporter(Predict pred)      
		: predict(pred)    
	{}        

	void report(const char *file, unsigned int line, const char *message) 
	{      
		predict(file, line, message);    
	}    

private:    
	Predict predict;
};


template <typename Predict>
Reporter* createReporter(Predict pred)
{
    return new ConcreteReporter<Predict>(pred);
}

inline Reporter* createReporter(reporter_t pred)
{
    return new ConcreteReporter<reporter_t>(pred);
}

}

mem_checker::Reporter *get_info_reporter();
mem_checker::Reporter *get_failure_reporter();
void set_reporter(mem_checker::Reporter *infoReporter, mem_checker::Reporter *failureReporter);
void clr_reporter();

#endif


