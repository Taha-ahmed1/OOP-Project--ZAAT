#include "Engine.h"
#include "User.h"
#include "Vehicle.h"
#include "Listing.h"
#include "Marketplace.h"
#include <iostream>
#include <string>
// File handling used to save marketplace state
// Data stored in CSV format for persistence
#include <fstream>
using namespace std;

void Admin::approveListing(Listing &l, Notifiable* user) {
    l.approve();
    user->notify("Your listing has been APPROVED!");
}

void Admin::removeListing(Listing &l, Notifiable* user) {
    l.remove();
    user->notify("Your listing has been REMOVED!");
}

void saveListings(Marketplace& market) {
    ofstream file("listings.csv");

    // Header 
    file<<"ID,Brand,Model,Price,Approved,Sold\n";

    for(int i=0;i<market.getCount();i++){
        Listing* l = market.getListing(i);

        if(l){
            Vehicle* v = l->getVehicle();

            if(v){
                file << i+1 << ","<< v->getBrand() <<  ","<< v->getModel()<<  ","<< v->getPrice() <<  ","<< l->isApproved() <<  ","<< l->isSold()<< "\n";
            }
        }
    }

    file.close();
    cout<<"Listings saved to Excel (CSV) successfully!\n";
}

void loadListings() {
    ifstream file("listings.csv");

    string line;
    cout<<"\n--- Saved Listings ---\n";
    getline(file, line); 
    while(getline(file, line)){
        cout<<line<<endl;
    }
    file.close();
}



int main() {
	int index;
	Listing* selected = NULL;
	Listing* l = NULL;

	// INITIAL ENGINE + VEHICLE SETUP
	// Hardcoded test data for marketplace initialization
	
    Engine e1(8,450,4.0,true);
    Engine e2(12,700,6.0,true);
    Engine e3(4,310,5.0,false);

    LuxuryCar c1("Mercedes","S-Class",2023,650000,e1);
    ElectricCar c2("Tesla","Model S",2024,700000,e2);
	Bike b1("Kawasaki","Ninja H2-R",2025,125000,e3);
	
    Listing l1(1,&c1);
    Listing l2(2,&c2);
    Listing l3(3,&b1);

    Marketplace market;
    market.addListing(&l1);
    market.addListing(&l2);
    market.addListing(&l3);
    
    Admin admin("Zulfiqar","admin@mail.com",123,1);
    Buyer buyer("Ali","ali@mail.com",111,2);
    Seller seller("Ahmed","ahmed@mail.com",222,3);

    int roleChoice;
	
	// ROLE BASED SYSTEM STARTS
	// Admin, Buyer, Seller selection
    do {
    	cout<<"\n---------- ZAAT LUXURY AUTOS ----------\n"<<endl;
        cout<<"\n===== Select Profile =====\n";
        cout<<"1. Admin\n2. Buyer\n3. Seller\n0. Exit\n"<<endl;
        cout<<"Enter Choice: ";
        cin>>roleChoice;
        cout<<"\n";
        cout<<"---------------------------------------------\n";

        switch(roleChoice) {
	        // ADMIN
	        case 1: {
	            int choice;
	            do {
	                cout<<"\n------ Admin Panel ------\n"<<endl;
	                admin.dashboard();
	                cout<<"1. Approve Listings\n";
	                cout<<"2. Remove Listing\n";
	                cout<<"3. View Listings\n";
	                cout<<"4. Save Listings\n";
					cout<<"5. Load Listings\n";
	                cout<<"0. Back\n"<<endl;
	                cout<<"Enter Choice: ";
	                cin>>choice;
	                cout<<"\n";
	                cout<<"---------------------------------------------\n";
	
	                switch(choice) {
						case 1:
						    for(int i=0;i<market.getCount();i++){
						        Listing* l=market.getListing(i);
						        if(l && !l->isApproved()){
						            admin.approveListing(*l,&seller);
						        }
						    }
						    cout<<"New listings approved!\n";
						    break;
							
	                    case 2:
	                        admin.removeListing(l1, &seller);
	                        cout<<"First Listing Removed!\n";
	                        break;
	
	                    case 3:
	                        market.showAll();
	                        break;
	                        
	                    case 4:
						    saveListings(market);
						    break;
						
						case 5:
						    loadListings();
						    break;
	                }
	
	            } while(choice!=0);
	            break;
        	}

	        // BUYER
	        case 2: {
	            int choice;
	            do {
			        cout<<"\n------ Buyer Menu ------\n"<<endl;
			        buyer.dashboard();
			        cout<<"1. View Listings\n";
			        cout<<"2. Save Favorite\n";
			        cout<<"3. View Favorites\n";
			        cout<<"4. Filter by Price\n";
			        cout<<"5. Purchase Car\n";
			        cout<<"0. Back\n"<<endl;
			        cout<<"Enter Choice: ";
			        cin>>choice;
			        cout<<"\n";
			        cout<<"---------------------------------------------\n";
	
	                switch(choice) {
	                    case 1:{
							cout<<"\n--- Listings ---\n";
							market.showAll();
							break;						
						}
	
						case 2: {
						    if(market.getCount()==0) {
						        cout<<"No listings available to save.\n";
						        break;
						    }
						
						    market.showAll();
						    cout<<"Enter listing number to save: ";
						    cin>>index;
							
							// Exception handling used for input validation
							// Prevents invalid listing selection and crashes
							
						    if(cin.fail()){
						        cin.clear();
						        cin.ignore(1000,'\n');
						        cout<<"Invalid input type!\n";
						        break;
						    }
						
						    try {
						        if(index<=0||index>market.getCount()){
						            throw "Invalid listing number!";
								}
						
						        selected = market.getListing(index-1);
						
						        if(selected==NULL){
						            throw "Listing does not exist!";
								}
						
						        buyer.saveFav(selected);
						
						    } catch(const char* msg) {
						        cout<<msg<<endl;
						    }
						
						    break;
						}
						case 3:{
						    buyer.viewFav();
						    break;
						}

						case 4: {
						    double price;
						    cout<<"Enter max price: ";
						    cin>>price;
						
						    if(cin.fail()){
						        cin.clear();
						        cin.ignore(1000,'\n');
						        cout<<"Invalid input!\n";
						        break;
						    }
						
						    market.filterByPrice(price);
						    break;
						}
						
						case 5: {
						    if(market.getCount()==0){
						        cout<<"No listings available.\n";
						        break;
						    }
						
						    market.showAll();
						    cout<<"Enter listing number to purchase: ";
						    cin>>index;
							
							//Exception Handling
						    if(cin.fail()){
						        cin.clear();
						        cin.ignore(1000,'\n');
						        cout<<"Invalid input!\n";
						        break;
						    }
						
						    try {
						        if(index<=0 ||index>market.getCount()){
						            throw "Invalid listing!";
								}
						
						        selected=market.getListing(index-1);
						
						        if(selected == NULL){
						            throw "Listing not found!";
								}
						
						        if(!selected->isApproved()){
						            throw "Listing not approved!";
								}
						
						        if(selected->isSold()){
						            throw "Car already sold!";
								}
						
						        //            MARK SOLD
						        selected->markSold();
						
						        //          NOTIFICATIONS
						        buyer.notify("Car purchased successfully!");
						        seller.notify("Your car has been sold!");
						        cout<<"[ADMIN NOTICE]: A car has been sold.\n";
						
						        cout<<"Purchase successful!\n";
						
						    } catch(const char* msg){
						        cout<<msg<<endl;
						    }
						
						    break;
						}
						    
	                }
	
	            } while(choice!=0);
	            break;
	        }
	
	        // SELLER
	        case 3: {
	            int choice;
	            do {
	                cout<<"\n------ Seller Menu ------\n"<<endl;
	                seller.dashboard();
	                cout<<"1. Add New Car\n";
	                cout<<"2. View Listings\n";
	                cout<<"3. Update Listing\n";
					cout<<"4. Delete Listing\n";					
	                cout<<"0. Back\n"<<endl;
	                cout<<"Enter Choice: ";
	                cin>>choice;
	                cout<<"\n";
	                cout<<"---------------------------------------------\n";
	
	                switch(choice) {
	                    case 1: {
	                        string brand, model;
	                        double price;
	
	                        cout<<"Enter Brand: ";
	                        cin>>brand;
	                        cout<<"Enter Model: ";
	                        cin>>model;
	                        cout<<"Enter Price: ";
	                        cin>>price;
	                        
							// Runtime creation of vehicle + polymorphic storage in listing
	                        Engine newEngine(8,400,4.0,true);
	                        
							Vehicle* newCar= new LuxuryCar(brand, model, 2024, price, newEngine);
							Listing* newListing= new Listing(market.getCount()+1,newCar);
							market.addListing(newListing);
	
	                        seller.notify("New listing added. Waiting for approval.\n");
	                        break;
	                    }
	
	                    case 2:{
	                        market.showAll();
							break;
						}
	                    
	                    case 3: {
						    int index;
						    double newPrice;
						
						    market.showAll();
						    cout<<"Enter listing number to update: ";
						    cin>>index;
						    
						    // Exception handling
							if(cin.fail()){
							    cin.clear();
							    cin.ignore(1000,'\n');
							    cout<<"Invalid input type!\n";
							}
							try {
							    if(index <=0 || index > market.getCount())
							        throw "Invalid index!";
							
							    l = market.getListing(index-1);
							
							    double newPrice;
							    cout<<"Enter new price: ";
							    cin>>newPrice;
							
							    if(newPrice <=0){
							        throw "Invalid price!";
								}
							
							    l->getVehicle()->setPrice(newPrice);
							
							} catch(const char* msg){
							    cout<<msg<<endl;
							}
						
						    if(l){
						        cout<<"Enter new price: ";
						        cin>>newPrice;
						
						        l->getVehicle()->setPrice(newPrice);
						        cout<<"Updated successfully!\n";
						    }
						    break;
						}
						
						case 4: {
						    int index;
						
						    market.showAll();
						    cout<<"Enter listing number to delete: ";
							cin>>index;
							
							//Exception Handling
							if(cin.fail()){
							    cin.clear();
							    cin.ignore(1000,'\n');
							    cout<<"Invalid input type!\n";
							}
							try {
							    if(index <=0 || index > market.getCount())
							        throw "Invalid index!";
							
							    l = market.getListing(index-1);
							
							    l->remove();
							    seller.notify("Listing removed!");
							
							} catch(const char* msg){
							    cout<<msg<<endl;
							}
						
						    if(l){
						        l->remove();
						        seller.notify("Listing removed.");
						    }
						    break;
						}
						
	                }
	
	            } while(choice!=0);
	            break;
	        }
	
	    }

    } while(roleChoice!=0);

    return 0;
}