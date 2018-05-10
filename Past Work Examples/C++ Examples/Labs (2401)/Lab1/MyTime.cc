//Modified by Mark Brown - file provided by jdolan for 2401 class [22/01/2016] 
// The implementation file for the MyTime class
#include "MyTime.h" 
#include <cstdlib> 
#include <iostream> 
#include <iomanip>

using namespace std; 
// Constructors
MyTime::MyTime(int h, int m){
	hours = h;
	minutes = m;
}
void MyTime::Reset(int h, int m){
	hours = h;
	minutes = m;
}
void MyTime::simplify(){
       	hours += minutes/60;
	minutes = minutes%60;
}
MyTime MyTime::operator + (const MyTime& t1) const{
	MyTime tmp;
    tmp.hours = hours + t1.hours;
	tmp.minutes = minutes + t1.minutes;
	tmp.simplify();
	return tmp;
}
MyTime MyTime::operator - (const MyTime& t1) const{
	MyTime tmp;
	tmp.minutes = abs((hours*60+minutes) -
					(t1.hours*60+t1.minutes));
	tmp.simplify();
	return tmp;
}
MyTime MyTime::operator / (int num) const{
	MyTime tmp;
	tmp.minutes = hours*60 + minutes;
	tmp.minutes /= num;
	tmp.simplify();
	return tmp;
}
MyTime MyTime::operator * (int num) const{
	MyTime tmp;
	tmp.minutes = hours*60 + minutes;
	tmp.minutes *= num;
	tmp.simplify();
	return tmp;
}
bool MyTime::operator == (const MyTime& t1) const{
	return hours == t1.hours && minutes == t1.minutes;
}
bool MyTime::operator < (const MyTime& t1) const{
	return (hours*60 + minutes) < (t1.hours*60 + t1.minutes);
}
bool MyTime::operator <=(const MyTime& t1) const{
	return (hours*60 + minutes) <= (t1.hours*60 + t1.minutes);
}
void MyTime::input(istream&ins){
	char junk;
	ins>>hours;
  	ins.get(junk);
	ins>>minutes;
	simplify();
}
void MyTime::output(ostream& outs) const{
        outs<<hours<<':'<<setw(2)<<setfill('0')<<minutes;
}
std::ostream& operator <<(ostream& fout, const MyTime& t1){
   t1.output(fout);
	return fout;
}
std::istream& operator >> (istream& fin, MyTime& t1){
	t1.input(fin);
	return fin;
}
