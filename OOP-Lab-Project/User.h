// User system demonstrates INHERITANCE hierarchy
// User -> Buyer, Seller, Admin
// Also demonstrates interface abstraction using Notifiable

#ifndef USER_H
#define USER_H

#include "Listing.h"
#include <iostream>
#include <string>
using namespace std;

class IUser{
	public:
	    virtual void dashboard() = 0;
};

class User :public IUser {
	protected:
	    string name,email;
	    int phone,id;
	
	public:
	    User(string n="",string e="",int p=0,int i=0) {
	        name=n; email=e; phone=p; id=i;
	    }
		
    	string getName() const { return name; }
    	string getEmail() const { return email; }
    	int getPhone() const { return phone; }
    	int getId() const { return id; }
	    virtual void dashboard() = 0;
};

class Notifiable {
	public:
	    virtual void notify(string msg)=0;
};

class Buyer : public User, public Notifiable {
	private:
	    Listing* favorites[5];
	    int favCount;
	
	public:
	    Buyer(string n="",string e="",int p=0,int i=0):User(n,e,p,i), favCount(0) {
	        for(int i=0;i<5;i++){
	            favorites[i] = NULL;
			}
	    }
		
		// Stores pointers to Listing objects
		// Demonstrates DMA
	    void saveFav(Listing* l) {
	    	if(favCount < 5) {
	       		favorites[favCount++] = l;
	        	notify("Added to favorites!");
	   	 	}
	    }
	
	    void viewFav() const {
	        cout<<"\n--- Favorite Listings ---\n";
	        for(int i=0;i<favCount;i++) {
	            if(favorites[i])
	                favorites[i]->display();
	        }
	    }
	
		void notify(string msg) {
		    cout<<"Buyer Notification: "<<msg<<endl;
		}
		
		void dashboard() {
    		cout<< "\n========== BUYER DASHBOARD ==========\n";
    		cout<<"Name  : "<<name<<endl;
    		cout<<"Email : "<<email<<endl;
   			cout<<"Phone : "<<phone<<endl;
    		cout<<"ID    : "<<id<<endl;
    		cout<<"=====================================\n";
		}	
};

class Seller : public User, public Notifiable {
	public:
	    Seller(string n="",string e="",int p=0,int i=0):User(n,e,p,i) {}
	
	    void notify(string msg){
	        cout<<"Seller Notification: "<<msg<<endl;
	    }
	
		void dashboard(){
		    cout<<"\n========== SELLER DASHBOARD ==========\n";
		    cout<<"Name  : "<<name<<endl;
		    cout<<"Email : "<<email<<endl;
		    cout<<"Phone : "<<phone<<endl;
		    cout<<"ID    : "<<id<<endl;
		    cout<<"=====================================\n";
		}
};

// Admin has special privileges to approve/remove listings
class Admin : public User {
	public:
	    Admin(string n="",string e="",int p=0,int i=0):User(n,e,p,i) {}
	
	    void dashboard(){
		    cout<<"\n========== ADMIN PANEL ==========\n";
		    cout<<"Name  : "<<name<<endl;
		    cout<<"Email : "<<email<<endl;
		    cout<<"Phone : "<<phone<<endl;
		    cout<<"ID    : "<<id<<endl;
		    cout<<"=================================\n";
		}
		
		void approveSilent(Listing& l) {
   			 l.approve(); 
		}
	    void approveListing(class Listing& l, Notifiable* user);
		void removeListing(class Listing& l, Notifiable* user);
};


#endif
