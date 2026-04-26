// Listing class connects Vehicle with Marketplace
// Demonstrates association + friend access by Admin
// Handles approval, removal and sold status

#ifndef LISTING_H
#define LISTING_H

#include "Vehicle.h"
#include <iostream>
#include <string>
using namespace std;

class Listing {
	private:
	    int listingID;
	    Vehicle* vehicle;
	    bool approved;
	    bool sold;
	
	public:
	    Listing(int id,Vehicle* v) {
	        listingID=id;
	        vehicle=v;
	        approved=false;
	        sold=false;   
	    }
	
	    void approve(){approved=true; }
	    void remove(){approved=false; }
		bool isApproved() const{return approved;}
		bool isSold() const {return sold; }
		void markSold() {sold=true; }

		Vehicle* getVehicle() const{return vehicle;}
		void display() {
		    if(approved && vehicle){
		        cout<<"Listing ID: "<<listingID<<endl;
		        vehicle->display();
		    }
		}
	
	    friend class Admin;
};

#endif
