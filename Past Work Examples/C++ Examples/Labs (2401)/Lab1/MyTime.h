//Modified by Mark Brown - file provided by jdolan for 2401 class [22/01/2016]
#include <iostream>
    
class MyTime {
  public:
    MyTime(int h = 0, int m = 0); //default constructor to set all values to 0 unless provided different
         
    void Reset(int h, int m); //used to reset the data once provided
   
    MyTime operator + (const MyTime& t1) const;//overload the + operator within the class MyTime
 
    MyTime operator - (const MyTime& t1) const;//overload the - operator within the class MyTime
 
    MyTime operator * (int num) const;//overload the * operator within the class MyTime
    MyTime operator / (int num) const;//overload the / operator within the class MyTime
    bool operator == (const MyTime& t1) const;//overload the == operator within the class MyTime
    bool operator < (const MyTime& t1) const;//overload the < operator within the class MyTime
    bool operator <= (const MyTime& t1) const;//overload the <= operator within the class MyTime
    void input(std::istream& ins);//takes the input from the screen and converts the data into useful variables
    void output(std::ostream& outs) const;//prints to the screen in a uniform fashion
    int get_hours() const{return hours;}//used to get the hours
    int get_minutes() const{return minutes;}//used to get the minutes
   
  private:
      void simplify();//simplifies the minutes into hours - example 1:75 will simplify to 2:15
      int hours; // hours can be > 24
      int minutes; // 0 <= minutes <= 59
 };
std::istream& operator >>(std::istream& fin, MyTime& t1);//used to overload the >> operator of the istream 
std::ostream& operator <<(std::ostream& fout, const MyTime& t1);//used to overload the << operation of the ostream
