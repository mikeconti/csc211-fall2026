#include <iostream>

// Implement the following public methods for the class date
// add_years, which adds a number of years to the current date
// add_months, which adds a number of months to the current date
// add_days, which adds a number of days to the current date

//If you have time, improve the methods to avoid overflowing months and days (13-34-2028 does not exist)

class Date {
    private:
        int month;
        int year;
        int day;

    public:
        
        void set(int m, int d, int y);
        void print();

        void addDay(int n);
        void addMonths(int n);
        void addYears(int n);
};



void Date::print() {
    std::cout << month << '-'  << day << '-'  << year << std::endl;
}


void Date::set(int m, int d, int y) {
    month = m;
    day = d;
    year = y;
}



void Date::addDay(int n){
    day += n;

}

void Date::addMonths(int n){
    month += n;

}


void Date::addYears(int n){
    year += n;

}


int main(){

    Date today;

    today.set(11, 12, 2026);

    today.print();

    today.addYears(1);
    today.addMonths(1);
    today.addDay(1);

    today.print();

    return 0;
}