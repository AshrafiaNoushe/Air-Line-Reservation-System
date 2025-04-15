#include<bits/stdc++.h>
#include <fstream>
using namespace std;

class Flight
{
public:
    virtual void showFlightDetails()=0;
};

class Person
{
protected:
    int age;
    string name;
public:
    Person(string s=" ",int a=0):name(s),age(a) {}
    string getName() const
    {
        return name;
    }
    int getAge()const
    {
        return age;
    }
    void getDetails()
    {
        cout<<"Name: "<<name<<endl;
        cout<<"Age "<<age<<endl;
    }
};

class Passenger:public Person
{
protected:
    string pass_pasport;
public:
    Passenger(string n=" ",int ag =0,string p=" "):Person(n,ag),pass_pasport(p) {}
    string getPassport() const
    {
        return pass_pasport;
    }
};

class FrequentFlyer:public Passenger
{
protected:
    string membership_id;
public:
    FrequentFlyer(string s=" ",int a=0,string s1=" ",string mm=" "):Passenger(s,a,s1),membership_id(mm) {}
    string getMembership() const
    {
        return membership_id;
    }
    void showFFlightDetails()
    {
        getDetails();
        cout<<"Passport: "<<pass_pasport<<"Membership ID: "<<membership_id<<endl;
    }

};

class Ticket
{
protected:
    string TicketNo;
public:
    Ticket(string t=" "):TicketNo(t) {}

};

class EconomyClass:public Ticket
{
public:
    void Show_T_class()
    {
        cout<<"Economy Class Ticket: "<<TicketNo<<endl;
    }
};

class BusinessClass:public Ticket
{
public:
    void Show_T_class()
    {
        cout<<"Business Class Ticket: "<<TicketNo<<endl;
    }
};

class DomesticFlight:public Flight
{
protected:
    string FlightNo;
public:
    DomesticFlight(string s=""):FlightNo(s) {}
    void showFlightDetails()
    {
        cout<<"Domestic Flight No: "<<FlightNo<<endl;
    }
    string getFlightNo()
    {
        return FlightNo;
    }
};

class Reservation
{
public:
    FrequentFlyer ff;
    string FlightNo;
    string TicketNo;
    Reservation(string name,int age,string pass,string member,string flight,string ticket):ff(name,age,pass,member),FlightNo(flight),TicketNo(ticket) {}

    void saveReservation()
    {
        ofstream out("passenger.txt",ios::app);
        if(out.is_open())
        {
            out<<"---------------Reservation-------------"<<endl;
            out<<"Passenger Name: "<<ff.getName()<<endl;
            out<<"Passenger Age: "<<ff.getAge()<<endl;
            out<<"Passenger Passport ID: "<<ff.getPassport()<<endl;
            out<<"Membership ID: "<<ff.getMembership()<<endl;
            out<<"Flight No: "<<FlightNo<<endl;
            out<<"Ticket No: "<<TicketNo<<endl;
            out<<"-------------------<3------------------------"<<endl;
            out.close();
            cout<<"Info has been saved to files<3"<<endl;
        }
        else
        {
            cout<<"Error in opening file!!!"<<endl;
        }
    }

    static void viewReservation()
    {
        ifstream in("passenger.txt");
        string line;
        int pass_count=0;
        cout<<"______________________________________________ All Reservations ____________________________________________"<<endl;
        while(getline(in,line))
        {
            if(line.find("---------------Reservation-------------")!=string::npos)
            {
                pass_count++;
                cout<<"Passenger "<<setw(2)<<setfill('0')<<pass_count<<endl;
            }
            cout<<line<<endl;
        }
        in.close();
    }
    static void deleteReservation( const string& nameTodlt){
        ifstream in("passenger.txt");
        ofstream temp("temp.txt");
        string line;
        bool skip = false ,dlt =false;
        while(getline(in,line)){
            if(line.find("---------------Reservation-------------")!=string::npos){
                skip = false;
            }
            if(line.find("Passenger Name: "+nameTodlt)!= string::npos){
                skip = true;
                dlt = true;
            }
            if(!skip){
                temp<<line<<endl;
            }
            if(line.find("-------------------<3------------------------")!=string::npos){
                skip = false;
            }
        }
        in.close();
        temp.close();
        remove("passenger.txt");
        rename("temp.txt","passenger.txt");
        if(dlt){
            cout<<"Reservation for: "<<nameTodlt<<" has been canceled successfully"<<endl;
        }
        else{
            cout<<"Passenger not found!"<<endl;
        }

    }
};

void displayFlight(Flight *f)
    {
        f->showFlightDetails();
    }

void menu()
    {
        int choice;
        do
        {
            cout<<"_________________________________________EHSUAN Airline Reservation System___________________________________________"<<endl;
            cout<<"1.Add Info for Reservation"<<endl;
            cout<<"2.View All Reservation"<<endl;
            cout<<"3.Cancel Booking"<<endl;
            cout<<"4.Exit"<<endl;

            cout<<"Enter choice: "<<endl;
            cin>>choice;

            if(choice==1)
            {
                string name,pass_pasport,membership_id,FlightNo,TicketNo;
                int age;

                cin.ignore();
                cout<<"Enter Name: ";
                getline(cin,name);
                cout<<"Enter Age: ";
                cin>>age;
                cin.ignore();
                cout<<"Enter Passport id:";
                getline(cin,pass_pasport);
                cout<<"Enter Frequent flyer membership ID: ";
                getline(cin,membership_id);
                cout<<"Enter Flight No: ";
                getline(cin,FlightNo);
                cout<<"Enter Ticket No: ";
                getline(cin,TicketNo);

                Reservation r(name, age, pass_pasport, membership_id, FlightNo, TicketNo);
                DomesticFlight df(FlightNo);
                displayFlight(&df);
                r.saveReservation();
            }
            else if(choice==2)
            {
                Reservation::viewReservation();
            }
            else if(choice==3)
            {
                cin.ignore();
                string nameTodlt;
                cout<<"Enter the Passenger name to delete: ";getline(cin,nameTodlt);
                Reservation::deleteReservation(nameTodlt);
            }
            else if(choice==4){
                cout<<"Good Bye & Take care!"<<endl;
            }
            else
            {
                cout<<"Invalid choice try again!"<<endl;
            }
        }
        while(choice!=4);
    }
int main()
{
    menu();
    return 0;
}
