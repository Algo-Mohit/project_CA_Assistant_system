#ifndef BALANCESHEET_H
#define BALANCESHEET_H

#include "necessaryheader.h"  // Common header files needed (like iostream, fstream, etc.)

// Balance sheet class definition
class balance_sheet
{
    // Basic company info
    char company_name[30];
    char balance_sheet_gst_number[20];
   
    // Liabilities and equity section
    double capital_ac;       // Capital Account
    double reservers;        // Reserves and Surplus
    double loan;             // Loan from bank
    double creditors;        // Creditors amount
    double liabilities_sum;  // Total of all liabilities

    // Assets section
    double fixed_assets;
    double cash;
    double bank_balance;
    double debtors;
    double stock;
    double assets_sum;       // Total of all assets
    double investments;

public:

    // Input all data for a new balance sheet
    void balance_sheet_input()
    {
        system("clear");  // Clears screen
        header();
        cout << "\n📊 🇧 🇦 🇱 🇦 🇳 🇨 🇪     🇸 🇭 🇪 🇪 🇹\n\n"; 
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); 

        // Get company info
        cout<<"\nEnter company name: ";
        cin.getline(company_name,30);
        cout<<"\nEnter gst number: ";
        cin.getline(balance_sheet_gst_number,20);

        // Get liabilities
        cout<<"\n\nPress enter for Liablities and equity input..";
        cin.get();
        system("clear");
        header();
        cout << "\n📊 🇧 🇦 🇱 🇦 🇳 🇨 🇪     🇸 🇭 🇪 🇪 🇹\n\n"; 
        cout<<"\nEnter liabilities and equity:-\n\n ";
        cout<<"Enter amount of capital A/c ( Owners personal money invested in business): ";
        cin>>capital_ac;
        cout<<"\nEnter amount of reservers and surplus ( company last year profit ): ";
        cin>>reservers;
        cout<<"\nEnter loan amount from bank: ";
        cin>>loan;
        cout<<"\nEnter amount of creditors: ";
        cin>>creditors;

        // Calculate total liabilities
        liabilities_sum = capital_ac + reservers + loan + creditors;

        // Get assets
        cout<<"\n\nPress enter for Assets input..";
        cin.ignore();
        cin.get();
        system("clear");
        header();
        cout << "\n📊 🇧 🇦 🇱 🇦 🇳 🇨 🇪     🇸 🇭 🇪 🇪 🇹\n\n"; 
        cout<<"Enter Assets :-\n\n";
        cout<<"Enter amount of fixed assets: ";
        cin>>fixed_assets;
        cout<<"\nEnter amount of cash: ";
        cin>>cash;
        cout<<"\nEnter amount of bank balance: ";
        cin>>bank_balance;
        cout<<"\nEnter amount of debtors: ";
        cin>>debtors;
        cout<<"\nEnter vlaue of stock present: ";
        cin>>stock;
        cout<<"\nEnter investment: ";
        cin>>investments;

        // Calculate total assets
        assets_sum = fixed_assets + cash + bank_balance + debtors + stock + investments;
    }

    // Save entered balance sheet into a binary file
    void balance_sheet_write()
    {
        fstream f;
        system("clear");
        header();

        cout << "\n📊  🇦 🇩 🇩     🇧 🇦 🇱 🇦 🇳 🇨 🇪     🇸 🇭 🇪 🇪 🇹\n\n"; 

        char ch;
        f.open("balance_sheet.dat", ios::app | ios::binary);  // Open file in append + binary mode

        do
        {
            balance_sheet_input();  // Get new data
            f.write((char*)this, sizeof(*this));  // Save object to file
            cout<<"\nDo you want to enter another balance sheet press(y): ";
            cin>>ch;
        }
        while(ch == 'y' || ch == 'Y');

        f.close();  // Close file
    }

    // Display the balance sheet in formatted way
    void balance_sheet_output()
    {
        // Print formatted header
        cout << "===================================================================================" << endl;
        cout << "| Company Name : " << setw(60) << left << company_name << "     |" << endl;
        cout << "| GSTIN : " << setw(60) << left << balance_sheet_gst_number << "            |" << endl;
        cout << "|" << setw(80) << right << "BALANCE SHEET" << " |" << endl;
        cout << "|" << setw(80) << right << "As on 31st March 2025" << " |" << endl;
        cout << "===================================================================================" << endl;

        // Column headings
        cout << "|" << setw(38) << left << " LIABILITIES"
             << "  |" << setw(38) << left << " ASSETS" << "  |" << endl;
        cout << "-----------------------------------------------------------------------------------" << endl;

        // Line-by-line values
        cout << "| " << setw(20) << left << "Capital A/c" << setw(18) << right << capital_ac
             << " | " << setw(20) << left << "Fixed Assets" << setw(18) << right << fixed_assets << " |" << endl;

        cout << "| " << setw(20) << left << "Reserves & Surplus" << setw(18) << right << reservers
             << " | " << setw(20) << left << "Investments" << setw(18) << right << investments << " |" << endl;

        cout << "| " << setw(20) << left << "Loan from Bank" << setw(18) << right << loan
             << " | " << setw(20) << left << "Cash" << setw(18) << right << cash << " |" << endl;

        cout << "| " << setw(20) << left << "Creditors" << setw(18) << right << creditors
             << " | " << setw(20) << left << "Bank Balance" << setw(18) << right << bank_balance << " |" << endl;

        cout << "| " << setw(20) << left << "" << setw(18) << right << ""
             << " | " << setw(20) << left << "Debtors" << setw(18) << right << debtors << " |" << endl;

        cout << "| " << setw(20) << left << "" << setw(18) << right << ""
             << " | " << setw(20) << left << "Stock" << setw(18) << right << stock << " |" << endl;

        // Totals
        cout << "-----------------------------------------------------------------------------------" << endl;
        cout << "| " << setw(20) << left << "TOTAL" << setw(18) << right << liabilities_sum
             << " | " << setw(20) << left << "TOTAL" << setw(18) << right << assets_sum << " |" << endl;
        cout << "===================================================================================" << endl;

        // Check if balance sheet is correct
        if (liabilities_sum == assets_sum)
            cout << "\n BALANCE SHEET IS BALANCED\n";
        else
            cout << "\n BALANCE SHEET IS NOT BALANCED\n";
    }

    // Search balance sheet by GST number
    void search_balance_sheet_by_gst()
    {
        fstream n; 
        system("clear");
        header();
        cout << "\n🔍  🇸 🇪 🇦 🇷 🇨 🇭     🇧 🇦 🇱 🇦 🇳 🇨 🇪     🇸 🇭 🇪 🇪 🇹     🇧 🇾     🇬 🇸 🇹\n\n";

        char input_gst_number[20];
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); 
        cout<<"\nEnter company GST number whose balance sheet data you want : ";
        cin.getline(input_gst_number,20);

        n.open("balance_sheet.dat", ios::in | ios::binary);
        bool flag = true;

        while(n.read((char*)this, sizeof(*this)))
        {  
            if(strcmp(this->balance_sheet_gst_number, input_gst_number) == 0)
            {
                balance_sheet_output();  // Show matching record
                flag = false;
            } 
        } 

        if(flag)
            cout<<"\n Data not Found ";

        n.close();
    }

    // Balance sheet main menu
    void balance_sheet_menu()
    {   
        bool flag = true;
        while(flag)
        {   
            system("clear");
            int choice;
            header();

            // Menu options
            cout << "\n📂  🇼 🇪 🇱 🇨 🇴 🇲 🇪     🇹 🇴     🇧 🇦 🇱 🇦 🇳 🇨 🇪     🇸 🇭 🇪 🇪 🇹     🇲 🇪 🇳 🇺\n\n"
            "1. Add Balance sheet\n"
            "2. Search Balance sheet by GST number\n"
            "3. Balance Sheet update\n"
            "4. Back"
            "\nEnter your choice: ";

            cin>>choice;

            if(choice >= 1 && choice <= 4)    
            { 
                switch(choice)
                {
                    case 1:   
                        balance_sheet_write();  // Add new
                        wait();
                        break;

                    case 2:   
                        search_balance_sheet_by_gst();  // Search by GST
                        cout<<"\nPress enter to go menu bar..."<<endl;
                        cin.get();
                        break;

                    case 3:   
                        balance_sheet_update();  // Update existing
                        cout<<"\nPress enter to go menu bar..."<<endl;
                        cin.get();
                        break;        
                    
                    case 4:  
                        flag = false;  // Exit menu
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

    // Update a balance sheet entry by GST number
    void balance_sheet_update()
    {  
        fstream up; 
        system("clear");
        header();
        cout << "\n🔄  🇺 🇵 🇩 🇦 🇹 🇪     🇧 🇦 🇱 🇦 🇳 🇨 🇪     🇸 🇭 🇪 🇪 🇹\n\n"; 

        char input_gst_number[20];
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); 
        cout << "\nEnter company gst number whose data you want to update: ";
        cin.getline(input_gst_number, 20);

        up.open("balance_sheet.dat", ios::in | ios::out | ios::binary);
        bool found = false; 

        while (up.read((char*)this, sizeof(*this)))
        {  
            if (strcmp(this->balance_sheet_gst_number, input_gst_number) == 0)
            {
                up.seekp(sizeof(*this)*-1, ios::cur);  // Move pointer back to current record
                cout << "\nPlease enter new values :- "<<endl;
                balance_sheet_input();  // Take updated values
                up.write((char*)this, sizeof(*this));  // Write new values
                found = true;
                break;
            }
        } 

        up.close();

        if (found)
            cout << "\nData updated successfully\n";
        else
            cout << "\nUser not found!\n";
    }

    // Simple pause/wait function for user
    void wait()
    { 
        cout<<"\nPress enter to go menu bar..."<<endl;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cin.get();
    }
};

#endif
