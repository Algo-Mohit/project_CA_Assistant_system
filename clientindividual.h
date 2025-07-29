#ifndef CLIENTINDIVIDUAL_H
#define CLIENTINDIVIDUAL_H

#include "necessaryheader.h"
#include "incometax.h"

// Class for handling individual clients
class client_individual 
{
    // Data members to store client details
    char client_name[20];
    char client_pan[20];
    char client_address[30];
    char client_phone_number[15];
    char client_audit_status[20];
    char audit_status[20];
    incometax it; // Object to handle income tax for the client

public:

    // This function updates audit status to "Filled" if the PAN matches
    void update_Audit_Status(const char* pan_number) 
    {
        char compare_pan[20];
        strcpy(compare_pan,pan_number);
        fstream file;
        file.open("client.dat", ios::in | ios::out | ios::binary);
        if (!file) 
        {
            cout << "client.dat not open\n";
            return;
        }

        // Read through each client and update if PAN matches
        while (file.read((char*)this, sizeof(*this))) 
        {   
            if(strcmp(client_pan,compare_pan) == 0) 
            {
                file.seekp(sizeof(*this) * -1 , ios::cur);
                strcpy(audit_status,"Filled");
                file.write((char*)this, sizeof(*this));
                break;
            }
        }
        file.close();
    }

    // Function to take input for a client
    void client_input() 
    {
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); 
        cout << "\nEnter client name: ";
        cin.getline(client_name,20);
        cout << "Enter client pan number: ";
        cin.getline(client_pan, 20);
        cout << "Enter client phone number: ";
        cin.getline(client_phone_number, 15);
        cout<<"Enter client address: ";
        cin.getline(client_address,30);
        strcpy(audit_status,"NOT_FILLED"); // Default audit status
    }

    // Function to display a client in formatted table style
    void client_output(int serial)
    {
        cout << "| " << left << setw(5) << serial
            << "| " << setw(20) << client_name
            << "| " << setw(20) << client_pan
            << "| " << setw(15) << client_phone_number
            << "| " << setw(30) << client_address
            << "| " << setw(20) << audit_status
            << "|" << endl;

        cout << "---------------------------------------------------------------------------------------------------------------------------\n";
    }

    // Function to add a new client and save to file
    void add_client()
    {
        fstream f;
        system("clear");
        header();
        cout << "\n➕  🇦 🇩 🇩     🇨 🇱 🇮 🇪 🇳 🇹\n\n";
        char ch;
        f.open("client.dat",ios::app|ios::binary);
        do
        {
            client_input();
            f.write((char*)this,sizeof(*this));
            cout<<"\nDo you want to enter another client press(y)\nOtherwise press(n): ";
            cin>>ch;
        } while(ch == 'y' || ch == 'Y');
        f.close();
    }

    // Function to show all clients
    void show_client()
    {
        fstream f;
        system("clear");
        header();
        cout << "\n📋  🇦 🇱 🇱     🇨 🇱 🇮 🇪 🇳 🇹     🇩 🇪 🇹 🇦 🇮 🇱 🇸\n\n";
        f.open("client.dat", ios::in | ios::binary);
        int serial = 1;

        // Table header
        cout << "---------------------------------------------------------------------------------------------------------------------------\n";
        cout << "| " << left << setw(5) << "S.No"
            << "| " << setw(20) << "Name"
            << "| " << setw(20) << "Pan number"
            << "| " << setw(15) << "Phone number"
            << "| " << setw(30) << "Address"
            << "| " << setw(20) << "Audit status"
            << "|" << endl;
        cout << "---------------------------------------------------------------------------------------------------------------------------\n";

        // Display each client
        while (f.read((char*)this, sizeof(*this)))
        {
            client_output(serial++);
        }
        f.close();
    }

    // Function to update a specific client's data by PAN number
    void client_update()
    {  
        fstream up; 
        system("clear");
        header();
        cout << "\n🔄  🇺 🇵 🇩 🇦 🇹 🇪     🇨 🇱 🇮 🇪 🇳 🇹\n\n";
        char input_pan_number[20];
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); 
        cout << "\nEnter Pan number of client whose data you want to update: ";
        cin.getline(input_pan_number, 100);
        up.open("client.dat", ios::in | ios::out | ios::binary);
        bool found = false; 

        while (up.read((char*)this, sizeof(*this)))
        {  
            if (strcmp(this->client_pan, input_pan_number) == 0)
            {
                up.seekp(sizeof(*this)*-1,ios::cur);
                cout << "\nPlease enter new values :- "<<endl;
                client_input();
                up.write((char*)this, sizeof(*this));
                found = true;
                break;
            }
        } 
        up.close();

        if (found)
            cout << "\nData updated successfully\n";
        else
            cout << "\nClient not found!\n";
    }

    // Function to delete a client based on PAN number
    void client_delete()
    {  
        fstream n, up; 
        system("clear");
        header();
        cout << "\n🗑️  🇩 🇪 🇱 🇪 🇹 🇪     🇨 🇱 🇮 🇪 🇳 🇹\n\n";
        char input_pan_number[20];
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); 
        cout<<"\nEnter client pan number whose data you want to delete: ";
        cin.getline(input_pan_number,20);

        up.open("client.dat",ios::in | ios::binary);
        n.open("client_updated.dat",ios::app | ios::binary);

        bool flag = true;

        // Copy all clients except the one to be deleted
        while(up.read((char*)this,sizeof(*this)))
        {  
            if(strcmp(this->client_pan,input_pan_number)==0)
            {
                flag = false;
            }
            else
            {
                n.write((char*)this,sizeof(*this)); 
            }     
        } 

        // Replace old file
        if(!flag)
        {
            cout<<"\nData delete successfully";
        }
        else
        {
            cout<<"\n Data not Found ";
        }

        remove("client.dat");
        rename("client_updated.dat","client.dat");

        n.close();
        up.close();
    }

    // Menu function to interact with individual client features
    void client_menu()
    {   
        bool flag = true;
        while(flag)
        {   
            system("clear");
            int choice;
            header();
            cout << "\n👋  🇼 🇪 🇱 🇨 🇴 🇲 🇪     🇹 🇴     🇨 🇱 🇮 🇪 🇳 🇹     🇲 🇪 🇳 🇺     🇧 🇦 🇷\n\n"
            "1. Show all client\n"
            "2. Add client\n"
            "3. Delete client\n"
            "4. update client\n"
            "5. Fill Income Tax\n"
            "6. Income tax operations\n"
            "7. Back\n"
            "Enter your choice: ";
            cin >> choice;

            if(choice >= 1 && choice <= 7)    
            { 
                switch(choice)
                {
                    case 1:   
                        show_client();
                        wait();
                        break;

                    case 2:   
                        add_client();
                        wait();
                        break;
                    
                    case 3:   
                        client_delete();
                        cout << "\nPress enter to go menu bar..." << endl;
                        cin.get();
                        break;
                    
                    case 4:   
                        client_update();
                        cout << "\nPress enter to go menu bar..." << endl;
                        cin.get();
                        break; 

                    case 5:   
                        it.add_income_tax();
                        update_Audit_Status(it.pan_number);
                        wait();
                        break;            

                    case 6:   
                        it.income_tax_menu();
                        cout << "\nPress enter to go menu bar..." << endl;
                        cin.get();
                        break;            

                    case 7:   
                        flag = false;
                        break;         
                }
            }
            else
            {
                cout << "\nInvalid choice..";
                wait();
            }
        }
    }

    // Simple pause function to wait for user input
    void wait()
    { 
        cout << "\nPress enter to go menu bar..." << endl;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cin.get();
    }

};

#endif
