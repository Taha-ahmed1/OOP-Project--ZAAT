// Marketplace manages all listings
// Demonstrates aggregation and runtime search/filtering

#ifndef MARKETPLACE_H
#define MARKETPLACE_H
#include <iostream>
#include "Listing.h"
#include <string>
using namespace std;

class Searchable {
	public:
	    virtual void searchByBrand(string)=0;
};

class Marketplace :public Searchable {
	private:
	    Listing* list[20];
	    int count;
	
	public:
	    Marketplace(){ count=0; }
	
	    void addListing(Listing* l){
	        list[count++] = l;
	    }
	    
		int getCount(){return count;}
		
		Listing* getListing(int index) const{
		    if(index>=0 && index<count){
		        return list[index];
			}
		    return nullptr;
		}
		

		void showAll(){
		    bool found=false;
		    for(int i=0;i<count;i++){
		        if(list[i]->isApproved() && !list[i]->isSold()){
		            list[i]->display();
		            found=true;
		        }
		    }
		    if(!found){
		        cout<<"No approved listings available.\n";
		    }
		}
		
		// Implements filtering using runtime object data
		// Uses encapsulation through getter functions
		void searchByBrand(string brand){
		    bool found=false;
		
		    for(int i=0;i<count;i++){
		        if(list[i]->isApproved()){
		            Vehicle* v=list[i]->getVehicle();
		            if(v && v->getBrand()==brand){
		                list[i]->display();
		                found=true;
		            }
		        }
		    }
		
		    if(!found){
		        cout<<"No matching listings found.\n";
		    }
		}
		
		// Implements filtering using runtime object data
		// Uses encapsulation through getter functions
		void filterByPrice(double maxPrice){
		    bool found=false;
		
		    for(int i=0;i<count;i++){
		        if(list[i]->isApproved() && !list[i]->isSold()){
		            Vehicle* v = list[i]->getVehicle();
		
		            if(v && v->getPrice() <= maxPrice){
		                list[i]->display();
		                found=true;
		            }
		        }
		    }
		
		    if(!found)
		        cout<<"No cars under this price.\n";
		}
};

#endif
