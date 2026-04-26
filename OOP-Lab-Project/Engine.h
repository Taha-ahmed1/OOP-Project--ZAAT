// Engine class represents composition inside Vehicle class
// Demonstrates operator overloading and friend function
// Stores engine specifications like horsepower, cylinders etc.

#ifndef ENGINE_H
#define ENGINE_H

#include <iostream>
using namespace std;

class Engine {
	private:
	    const string layout;
	    int cylinders;
	    int horsepower;
	    float displacement;
	    bool twinTurbo;
	
	public:
	    Engine(): layout("V-Type"), cylinders(8), horsepower(400), displacement(4.0), twinTurbo(true) {}
	
	    Engine(int c,int hp,float d,bool t): layout("V-Type"),cylinders(c),horsepower(hp), displacement(d), twinTurbo(t) {}
	
	    void display() const {
	        cout<<"Engine: V"<<cylinders<<" | "<<horsepower<<"HP | "<<displacement<<"L\n"<<endl;
	    }
	
	    int getHP() const {return horsepower; }
		
		// Operator overloading used to compare horsepower
	    bool operator>(const Engine& e) {
	        return horsepower>e.horsepower;
	    }
		
		// Friend function used to compare private engine horsepower
		// Used because direct access to private data is required
	   friend void compareEngine(const Engine&, const Engine&);
};

 inline void compareEngine(const Engine& e1,const Engine& e2) {
		    if(e1.horsepower> e2.horsepower){
		        cout<<"Engine 1 stronger\n";
			}
		    else{
		        cout<<"Engine 2 stronger\n";
			}
		}
	
#endif
