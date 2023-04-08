#include <iostream>
#include <string>
using namespace std;

class Date {
private:
    int dd;
    int mm;
    int yy;

public:
    Date(int d, int m, int y);
    Date(string ch);
    void IncrementerDate();
    friend ostream& operator<<(ostream& flux , const Date& D){
        flux<< D.dd << "/" << D.mm << "/" << D.yy <<endl;
        return flux;
    }
};

Date::Date(int d, int m, int y){
    if (y>0) yy=y;
    dd=-1;
    mm=-1;
    if (d>0) {
        if (d<=31 && (m==1 || m==3 || m==5 || m==7 || m==8 || m==10 || m==12)){
            dd=d;
            mm=m;
        }
        if (d<=30 && ( m==4 || m==6 || m==9 || m==11)){
            dd=d;
            mm=m;
        }
        if (d<=29 && m==2){ 
            if ((y%4)==0 && d==29)
            {
                dd=d;
                mm=m;
            }
            else if ((y%4)!=0 && d<=28) {
                dd=d;
                mm=m;
            }
        }
    }
}

Date::Date(string ch){
    string ch1,ch2,ch3;
    ch1=ch.substr(0, ch.find('/'));
    dd = atoi(ch1.c_str());
    ch2=ch.erase(0, ch.find('/') + 1);
    ch2=ch.substr(0, ch.find('/'));
    mm= atoi(ch2.c_str());
    ch3=ch.erase(0, ch.find('/') + 1);
    yy = atoi(ch3.c_str());
    if (dd <= 0 || mm <= 0 || mm > 12) {
        dd = -1;
        mm = -1;
    }
    else if (mm == 2) {
        if (yy % 4 == 0 ) {
            if (dd > 29) {
                dd = -1;
                mm = -1;
            }
        } 
        else {
            if (dd > 28) {
                dd = -1;
                mm = -1;
            }
        }
    }
    else if ((mm == 4 || mm == 6 || mm == 9 || mm == 11) && dd > 30) {
        dd = -1;
        mm = -1;
    } 
    else if (dd > 31) {
        dd = -1;
        mm = -1;
    }
}

void Date::IncrementerDate(){
	if( mm==4 || mm==6 || mm==9 || mm==11 ){
		if (dd==30) {
			dd=1 ;
			mm++;
		}
		else dd++; 
	}
	if (mm==12){
		if (dd==31){
			dd=1;
			mm=1;
			yy++;
		}
		else dd++;
	}
	if (mm==1||mm==3||mm==5||mm==7||mm==8||mm==10){
		if (dd==31){
			dd=1;
			mm++;
		}
		else dd++;
	}
	if (mm==2 ){
		if (dd==29 && yy%4==0){
			dd=1;
			mm++;
		}
		if (dd==28 && yy%4!=0){
			dd=1;
			mm++;
		}
		else dd++;
	}	
}

int main(){
Date d1("31/4/2015");
Date d2("29/2/2012");
Date d3("29/2/2013");
Date d4(40,1,2016);
Date d5(11,10,2012);
cout << d1 << endl ;
cout << d2 << endl ;
cout << d3 << endl ;
cout << d4 << endl ;
cout << d5 << endl ; 
return 0;}
