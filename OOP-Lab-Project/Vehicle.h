// Vehicle is an ABSTRACT BASE CLASS
// Demonstrates INHERITANCE + POLYMORPHISM
// Car, Bike, ElectricCar inherit from it

#ifndef VEHICLE_H
#define VEHICLE_H

#include <iostream>
#include "Engine.h"
using namespace std;

class IVehicle {
	public:
	    virtual void display() const = 0;
};

class Vehicle : public IVehicle {
	protected:
	    string brand,model;
	    int year;
	    double price;
	    Engine engine;
	
	public:
	    Vehicle(string b="",string m="",int y=0,double p=0,Engine e=Engine()):engine(e) {
	        brand=b; model=m; year=y; price=p;
	    }
		
		// Runtime Polymorphism using virtual function
		// Each derived class (Car, Bike) overrides display()
	    virtual void display() const = 0;
	    
		string getBrand() const{return brand;}
		double getPrice() const{return price;}
	    bool operator==(const Vehicle& v){ return price == v.price; }
	    bool operator>(const Vehicle& v){ return price > v.price; }
	    string getModel() const { return model; }
		void setPrice(double p){ price = p; }
	    friend ostream& operator<<(ostream&,const Vehicle&);
};

class Car : public Vehicle {
	public:
	    Car(string b,string m,int y,double p,Engine e):Vehicle(b,m,y,p,e) {}
	
	    void display() const{
	        cout<<"Car: "<<brand<<" "<<model<<" | "<<price<<endl;
	        engine.display();
	    }
};

class LuxuryCar : public Car {
	public:
	    LuxuryCar(string b,string m,int y,double p,Engine e):Car(b,m,y,p,e) {}
	
	    void display() const{
	        cout<<"Luxury Car: "<<brand<<" "<<model<<" | "<<price<<endl;
	        cout<<"VIP Interior Feature\n";
	        engine.display();
	    }
};

class ElectricCar : public Car {
	public:
	    ElectricCar(string b,string m,int y,double p,Engine e):Car(b,m,y,p,e) {}
	
	    void display() const{
	        cout<<"Electric Car: "<<brand<<" "<<model<<" | "<<price<<endl;
	        engine.display();
	    }
};

class Bike : public Vehicle {
	public:
	    Bike(string b,string m,int y,double p,Engine e)
	    : Vehicle(b,m,y,p,e) {}
	
	    void display() const{
	        cout<<"Bike: "<<brand<<" "<<model<<" | "<<price<<endl;
	        engine.display();
	    }
};


inline ostream& operator<<(ostream& out,const Vehicle& v) {
    out<<v.brand<<" "<<v.model<<" "<<v.price;
    return out;
}

#endif
