#ifndef CLIENTCOMPANY_H
#define CLIENTCOMPANY_H

#include "necessaryheader.h"
#include "balancesheet.h"
#include "gstreturn.h"

// Class to store and manage client company details
class client_company 
{
    // Data members to store company details
    char company_name[30];
    char company_gst_number[20];
    char company_address[40];
    char company_contact_number[15];
    char company_audit_status[20];
    char company_regestration_date[20];

    public:
    
    // Function to update GST audit status to "Filled" for a given GST number
    void gst_status(const char* gst_num )
    {
        char compare_gst[20];
        strcpy(compare_gst,gst_num);
        fstream file;
        file.open("company.dat", ios::in | ios::out | ios::binary);
        if (!file) 
        {
            cout << "company.dat not open\n";
            return;
        }

        while (file.read((char*)this, sizeof(*this))) 
        {   
            if(strcmp(company_gst_number,compare_gst) == 0) 
            {
                file.seekp(sizeof(*this) * -1 , ios::cur);
                strcpy(company_audit_status,"Filled");
                file.write((char*)this, sizeof(*this));
                break;
            }
        }
        file.close();
    }

    // Function to input company details from user
    void company_input() 
    {
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); 
        cout << "\nEnter company name: ";
        cin.getline(company_name,30);
        cout << "Enter company gst number: ";
        cin.getline(company_gst_number, 20);
        cout << "Enter company contact number: ";
        cin.getline(company_contact_number, 15);
        cout<<"Company registration date: ";
        cin.getline(company_regestration_date,20);
        cout<<"Enter company address: ";
        cin.getline(company_address,40);
        strcpy(company_audit_status,"Not Filled"); // Initially status is Not Filled
    }

    // Function to display company data in a table row format
    void company_output(int serial)
    {
        cout << "| " << left << setw(5) << serial
             << "| " << setw(30) << company_name
             << "| " << setw(20) << company_gst_number
             << "| " << setw(15) << company_contact_number
             << "| " << setw(20) << company_regestration_date
             << "| " << setw(40) << company_address
             << "| " << setw(18) << company_audit_status
             << "|" << endl;

        cout << "-------------------------------------------------------------------------------------------------------------------------------------------------------------------\n";
    }

    // Function to add one or more companies to file
    void add_company()
    {
        fstream f;
        system("clear");
        header();
        cout << "\n🏢  🇦 🇩 🇩     🇨 🇴 🇲 🇵 🇦 🇳 🇾\n\n";
        char ch;
        f.open("company.dat",ios::app|ios::binary);
        do
        {
            company_input(); // get input
            f.write((char*)this,sizeof(*this)); // write to file
            cout<<"\nDo you want to enter another company press(y)\nOtherwise press(n): ";
            cin>>ch;
        } while(ch == 'y' || ch == 'Y');
        f.close();
    }

    // Function to show all companies
    void show_company()
    {
        fstream f;
        system("clear");
        header();
        cout << "\n📋  🇦 🇱 🇱     🇨 🇴 🇲 🇵 🇦 🇳 🇾     🇩 🇪 🇹 🇦 🇮 🇱 🇸\n\n";
        f.open("company.dat", ios::in | ios::binary);
        int serial = 1;

        // Table header
        cout << "-------------------------------------------------------------------------------------------------------------------------------------------------------------------\n";
        cout << "| " << left << setw(5) << "S.No"
             << "| " << setw(30) << "Company Name"
             << "| " << setw(20) << "GST number"
             << "| " << setw(15) << "Contact number"
             << "| " << setw(20) << "Company reg. date"
             << "| " << setw(40) << "Company Address"
             << "| " << setw(18) << "GST Audit Status"
             << "|" << endl;
        cout << "-------------------------------------------------------------------------------------------------------------------------------------------------------------------\n";

        // Display all companies
        while (f.read((char*)this, sizeof(*this)))
        {
            company_output(serial++);
        }
        f.close();
    }

    // Function to update company details using GST number
    void company_update()
    {  
        fstream up; 
        system("clear");
        header();
        cout << "\n🔄  🇺 🇵 🇩 🇦 🇹 🇪     🇨 🇴 🇲 🇵 🇦 🇳 🇾\n\n";
        char gst_number[30];
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); 
        cout << "\nEnter Gst  number of company whose data you want to update: ";
        cin.getline(gst_number, 30);

        up.open("company.dat", ios::in |ios::out| ios::binary);
        bool found = false; 

        while (up.read((char*)this, sizeof(*this)))
        {  
            if (strcmp(this->company_gst_number, gst_number) == 0)
            {
                up.seekp(sizeof(*this)*-1,ios::cur);
                cout << "\nPlease enter new values :- "<<endl;
                company_input(); // get new input
                up.write((char*)this, sizeof(*this)); // update record
                found = true;
                break;
            }
        } 

        up.close();
        if (found)
            cout << "\nData updated successfully\n";
        else
            cout << "\ncompany not found!\n";
    }

    // Function to delete a company using GST number
    void company_delete()
    {  
        fstream n,up; 
        system("clear");
        header();
        cout << "\n🗑️  🇩 🇪 🇱 🇪 🇹 🇪     🇨 🇴 🇲 🇵 🇦 🇳 🇾\n\n";
        char gst_number[30];
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); 
        cout<<"\nEnter company GST number whose data you want to delete: ";
        cin.getline(gst_number,30);
        up.open("company.dat",ios::in | ios::binary);
        bool flag = true;
        n.open("company_updated.dat",ios::app | ios::binary);

        // Copy all records except the one to delete
        while(up.read((char*)this,sizeof(*this)))
        {  
            if(strcmp(this->company_gst_number,gst_number)==0)
            {
                flag = false;
            }
            else
            {
                n.write((char*)this,sizeof(*this)); 
            }     
        } 

        // Show result
        if(!flag)
        {
            cout<<"\nData delete successfully";
        }
        else
        {
            cout<<"\n Data not Found ";
        }

        // Replace old file with new updated file
        remove("company.dat");
        rename("company_updated.dat","company.dat");
        n.close();
        up.close();
    }

    // Main menu for company section
    void company_menu()
    {   
        balance_sheet bs;
        gst_return gr;
        bool flag = true;
        while(flag)
        {   
            system("clear");
            int choice;
            header();
            cout << "\n🏢  🇼 🇪 🇱 🇨 🇴 🇲 🇪     🇹 🇴     🇨 🇴 🇲 🇵 🇦 🇳 🇾     🇲 🇪 🇳 🇺\n\n"
            "1. Show all company\n"
            "2. Add company\n"
            "3. Delete company\n"
            "4. Update company\n"
            "5. Fill GST Return\n"
            "6. Balance Sheet page\n"
            "7. GST Billing page\n"
            "8. Back\n"
            "Enter your choice: ";
            cin>>choice;

            if(choice>=1 && choice<=8)    
            { 
                switch(choice)
                {
                    case 1:   
                        show_company();
                        wait();
                        break;

                    case 2:   
                        add_company();
                        wait();
                        break;

                    case 3:   
                        company_delete();
                        cout<<"\nPress enter to go menu bar..."<<endl;
                        cin.get();
                        break;

                    case 4:   
                        company_update();
                        cout<<"\nPress enter to go menu bar..."<<endl;
                        cin.get();
                        break; 

                    case 5:    
                        gr.add_gst();
                        gst_status(gr.gst_number);
                        wait();
                        break;            

                    case 6:    
                        bs.balance_sheet_menu();
                        cout<<"\nPress enter to go menu bar..."<<endl;
                        cin.get();
                        break; 

                    case 7:    
                        gr.gst_menu();
                        cout<<"\nPress enter to go menu bar..."<<endl;
                        cin.get();
                        break; 

                    case 8:   
                        flag = false;
                        break;         
                }
            }
            else
            {
                cout<<"\nInvalid choice..";
                wait();
            }
        }
    }

    // Function to pause until user presses enter
    void wait()
    { 
        cout<<"\nPress enter to go menu bar..."<<endl;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cin.get();
    }

};

#endif
