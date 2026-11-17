#include <iostream>




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