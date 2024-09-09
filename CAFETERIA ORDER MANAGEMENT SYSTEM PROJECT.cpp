//                     CAFETERIA ORDER MANAGEMENT SYSTEM

#include <iostream>
#include<fstream>
using namespace std;

class Menu {
private:
	
    string item;
    int price, itemNo;
    
public:
	
    Menu(){
	 itemNo=0;
     item=(""); // Default constructor
	 price=0;
	 }
	  
    Menu(int IN, string I, int p ){
     itemNo=IN;
	 item=I;
	 price=p; 
	}
	
    string getItem() {
        return item;
    }
    
    int getItemNo() {
        return itemNo;
    }
    
    int getPrice() {
        return price;
    }
    
};
class Order {
public:
    int itemNo;
    int quantity;

    Order(){
    	itemNo=0;
		quantity=0;
	}
	
    Order(int itemN, int Quantity) {
       itemNo=itemN;
	    quantity=Quantity; 	
	}
	
	int operator *(Menu m){
		return quantity*m.getPrice();
	}
	
};

// Overloaded << operator to print the order details

    ostream& operator<<(ostream& O,Order obj){   // Returning the class name  would not allow chaining of output operations in this way eg:(O<< obj1 << obj2 << obj3;)
		O<<obj.itemNo<<" "<<" X "<< obj.quantity<<"."; 
    return O;
    }
    
class Cafe {
private:
    Menu menu_Items[20];          // Array to hold menu items
    int count;              // Counter to keep track of the number of items
    Order currentOrder[100];           // Fixed-size array for orders
    int ordercount;             // Counter to keep track of the number of orders

public:
    Cafe(){       // Initialize count and orderCount to 0
    count=0;
    ordercount=0;
 }
  void add(int ItemNo, string Item, int Price) {
        if (count < 20) {
            menu_Items[count] = Menu(ItemNo, Item, Price);
            count++;
        } else {                                                          //defensive check
            cout << "Menu is full ! dont add more items" << endl;
        }
    }
    
	void display_menu(){
	for(int i=0; i<count;i++){
		cout<< menu_Items[i].getItemNo()<<"-"<<" "<< menu_Items[i].getItem()<<" "<< menu_Items[i].getPrice()<<endl;
	}
	}
	
	void place_order(){
	int order_num, quant;
	
	cout<<"NOTE : Enter a number between 1 and 20 to order. "<<endl;
	while (true) {
            cout << "Enter item No for order (0 to finish): "; 
			cin>>order_num;
            if (order_num==0) break;
            cout<<"Enter quantity of item: "; 
			cin>>quant;
			
			bool found=false;  //assume item isnt found
			for (int i = 0; i < count; i++){   //then check item one by one
				if(order_num==menu_Items[i].getItemNo()){  
					currentOrder[ordercount] = Order(order_num, quant); // Add the order to currentOrder array
                    ordercount++; // Increment the order counter
					found=true;  // if found(item) then stop (break)
					break;
				}
			}
			if(!found){
				cout<<"item not found"<<endl;
			}
			
    }
    
	}
	void showOrder(){
    cout << "<<<<< Current Order >>>>>" << endl;
    for (int i = 0; i < ordercount; i++) {
        cout<<currentOrder[i]<<endl;     //currentorder is object of Order class // Using overloaded << operator to print order details
    }
	}
	void cancel_order(){
	ordercount=0;  //reset count to zero
	cout<<"Order cancelled."<<endl;
	}

   
   
    // Operator overloading for removing orders
    void operator-=(int itemNo) {
        bool found = false;
        for (int i = 0; i<ordercount; i++) {
            if (currentOrder[i].itemNo == itemNo) {
                for (int j = i; j < ordercount - 1; j++) {
                    currentOrder[j] = currentOrder[j + 1];
                }
                ordercount--;
                found = true;
                cout << "Item removed from order." << endl;
                break;
            }
        }
        if (!found) {
            cout << "Item not found in order." << endl;
        }
    }
	void update_order(){
	int choice;
	int n;
	cout<<"1. Add Item."<<endl;
	cout<<"2. Remove Item."<<endl;
	cout<<"Choose Option (Enter 1 or 2) :";
	cin>>choice;
	
	if(choice==1){
		place_order();
	}else if(choice==2){
		cout<<"Enter item no to remove: ";
		cin>>n;   //n=item number
	    operator-=(n);    // Call the overloaded -= operator directly  
	}else{
		cout<<"Invalid choice."<<endl;
	}
	}
	
	string bill_itemname(int itemNo){
	for(int i=0; i<count;i++){
		if(menu_Items[i].getItemNo()== itemNo){
			return menu_Items[i].getItem();
		}
	}
	
	return " ";
	}


    int bill_price(int itemNo){
	for(int i=0; i<count;i++){
			if(menu_Items[i].getItemNo()== itemNo){
				return menu_Items[i].getPrice();
			}
	}
	return 0;
	}
	
	void bill_receipt(){
	ofstream bill("Receipt.txt");
	if (!bill){
	cout<<"Cannot create receipt file "<<endl;
	}
	
	int total=0;
	bill<<"==============================="<<endl;
	bill<<"__________Bill Receipt_________"<<endl;
	bill<<"==============================="<<endl;
	bill<<endl;
	
	for(int i=0; i<ordercount;i++){
		int item_num=currentOrder[i].itemNo;
		string item_name=bill_itemname(item_num);
		int price=bill_price(item_num);
		int Quantity=currentOrder[i].quantity;
		int t=currentOrder[i]*menu_Items[item_num-1];
		bill<<item_num<<": "<<" "<<item_name<<" "<<price<<" X "<<Quantity<<endl;
		total=total+t;
	}
	
	bill<<"_______________________________________"<<endl;
	bill<<"Total :"<<total<<endl;
	bill.close();
	
	cout<<"Bill Receipt generated (check Receipt.txt )"<<endl;
	}

};
int main() {
    Cafe C;
    C.add(1, "Chicken Burger", 150);
    C.add(2, "Zinger Burger", 250);
    C.add(3, "French Fries", 50);
    C.add(4, "Juice", 100);
    C.add(5, "Coffee", 80);
    C.add(6, "Tea", 60);
    C.add(7, "Samosa", 120);
    C.add(8, "Ice Cream", 90);
    C.add(9, "Sandwich", 130);
    C.add(10, "Pizza Slice", 200);
    C.add(11, "Mineral water", 80);
    C.add(12, "Biryani", 120);
    C.add(13, "Milkshake", 150);
    C.add(14, "Chicken Patties", 160);
    C.add(15, "Chicken Roll ", 40);
    C.add(16, "Chicken Paratha", 100);
    C.add(17, "Brownie", 200);
    C.add(18, "Cheese Sandwich", 140);
    C.add(19, "Macroni", 220);
    C.add(20, "Bun Kabab", 100);


    cout <<"<<<<< Cafeteria Menu >>>>>"<<endl<<endl;
    C.display_menu();

    C.place_order();
    C.showOrder();
    

    
    char choice;
    while (true) {
        cout<<"Do you want to modify (press m), cancel (press c), or finalize (press f) the order? "; 
		cin>>choice;
		if (choice == 'm') {
		C.update_order();
		C.showOrder();
		} else if (choice == 'c') {
		C.cancel_order();
		break;
		}else if (choice == 'f') {
		cout<<"Order finalized. Thank you!"<<endl;
		C.bill_receipt();
		break;
		} else {
		cout << "Invalid choice. Try again." << endl;
        }
        
	}

    return 0;
	}


