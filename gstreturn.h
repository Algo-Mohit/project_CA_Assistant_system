#ifndef GSTRETURN_H
#define GSTRETURN_H

#include "necessaryheader.h"

// Class to handle GST Return operations
class gst_return
{
    // Data members to store GST-related information
    char gst_company_name[20];
    char month_and_year[20];
    double sale_amount;
    double input_gst;
    double purchase_amount;
    double output_gst;
    double net_gst_payable;
    char gst_type[15];

public:

    char gst_number[20]; // GST number of the company

    // Function to take GST bill input from user
    void gst_input()
    {
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        system("clear");
        cout << "\nEnter details about gst bill :- \n";
        cout << "\nEnter company name (20 words only): ";
        cin.getline(gst_company_name,20);
        cout << "\nEnter GST number: ";
        cin.getline(gst_number,20);
        cout << "\nEnter month and year of gst bill: ";
        cin.getline(month_and_year,20);
        cout << "\nEnter Total sales amount: ";
        cin >> sale_amount;
        cout << "\nEnter Total purchase amount: ";
        cin >> purchase_amount;
        gst_calculator(); // Calculate GST based on input
    }

    // Function to calculate GST values
    void gst_calculator()
    {
        input_gst = purchase_amount * 0.18;
        output_gst = sale_amount * 0.18;
        net_gst_payable = output_gst - input_gst;

        if (net_gst_payable > 0)
        {
            strcpy(gst_type, "Payable_GST"); // GST to be paid
        }
        else
        {
            strcpy(gst_type, "Refundable_GST"); // GST to be refunded
            net_gst_payable = (net_gst_payable * -2) + net_gst_payable;
        }
    }

    // Function to display GST bill in table format
    void gst_output(int serial)
    {
        cout << fixed << setprecision(0)
             << "| " << left << setw(6) << serial
             << "| " << setw(20) << gst_company_name
             << "| " << setw(20) << gst_number
             << "| " << setw(20) << month_and_year
             << "| " << setw(15) << sale_amount
             << "| " << setw(15) << purchase_amount
             << "| " << setw(15) << gst_type
             << "| " << setw(15) << net_gst_payable
             << "|" << endl;

        cout << "-----------------------------------------------------------------------------------------------------------------------------------------------\n";
    }

    // Function to show all GST bills from file
    void show_gst()
    {
        fstream f;
        system("clear");
        header();
        cout << "\n📄  🇦 🇱 🇱     🇬 🇸 🇹     🇧 🇮 🇱 🇱     🇩 🇪 🇹 🇦 🇮 🇱 🇸\n\n";
        f.open("gst.dat", ios::in | ios::binary);
        int serial = 1;

        // Print table heading
        cout << "-----------------------------------------------------------------------------------------------------------------------------------------------\n";
        cout << "| " << left << setw(6) << "Serial"
             << "| " << setw(20) << "Company name"
             << "| " << setw(20) << "GSTIN"
             << "| " << setw(20) << "Month and Year"
             << "| " << setw(15) << "Sale amount"
             << "| " << setw(15) << "Purchase amount"
             << "| " << setw(15) << "GST type"
             << "| " << setw(15) << "GST payable"
             << "|" << endl;
        cout << "-----------------------------------------------------------------------------------------------------------------------------------------------\n";

        // Read each record and display
        while (f.read((char*)this, sizeof(*this)))
        {
            gst_output(serial++);
        }
        f.close();
    }

    // Function to add new GST bill
    void add_gst()
    {
        fstream f;
        system("clear");
        header();
        cout << "\n➕  🇦 🇩 🇩     🇬 🇸 🇹     🇧 🇮 🇱 🇱\n\n";
        f.open("gst.dat", ios::app | ios::binary);
        gst_input();
        f.write((char*)this, sizeof(*this));
        f.close();
    }

    // Function to update an existing GST bill
    void gst_update()
    {
        fstream up;
        system("clear");
        header();
        cout << "\n🔁  🇺 🇵 🇩 🇦 🇹 🇪     🇬 🇸 🇹     🇧 🇮 🇱 🇱\n\n";
        char input_gst_number[20];

        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "\nEnter GST number of company whose data you want to update: ";
        cin.getline(input_gst_number, 20);

        up.open("gst.dat", ios::in | ios::out | ios::binary);
        bool found = false;

        while (up.read((char*)this, sizeof(*this)))
        {
            if (strcmp(this->gst_number, input_gst_number) == 0)
            {
                up.seekp(sizeof(*this) * -1, ios::cur);
                cout << "\nPlease enter new values :- " << endl;
                gst_input();
                up.write((char*)this, sizeof(*this));
                found = true;
                break;
            }
        }

        up.close();
        if (found)
            cout << "\nData updated successfully\n";
        else
            cout << "\nGST bill not found!\n";
    }

    // Function to search GST bill by GST number
    void search_gst_bill_by_gst_number()
    {
        fstream n;
        system("clear");
        header();
        cout << "\n🔍  🇸 🇪 🇦 🇷 🇨 🇭     🇬 🇸 🇹     🇧 🇮 🇱 🇱     🇧 🇾     🇬 🇸 🇹     🇳 🇺 🇲 🇧 🇪 🇷\n\n";
        char input_gst_number[20];
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "\nEnter company GST number whose gst bill data you want : ";
        cin.getline(input_gst_number, 20);
        n.open("gst.dat", ios::in | ios::binary);
        bool flag = true;

        while (n.read((char*)this, sizeof(*this)))
        {
            if (strcmp(this->gst_number, input_gst_number) == 0)
            {
                // Print formatted GST bill
                cout << "==============================================\n"
                     << "                   GST BILL                   \n"
                     << "==============================================\n"
                     << " Company name: " << gst_company_name << endl
                     << " GSTIN: " << gst_number << endl
                     << " Month: " << month_and_year << endl
                     << "----------------------------------------------\n"
                     << " Total sales: " << sale_amount << endl
                     << " Total purchase: " << purchase_amount << endl
                     << " Output gst: " << output_gst << endl
                     << " Input gst: " << input_gst << endl
                     << "----------------------------------------------\n"
                     << " Gst type: " << gst_type << endl
                     << " Gst payable: " << net_gst_payable << endl
                     << "==============================================\n";
                flag = false;
            }
        }

        if (flag)
        {
            cout << "\n Data not Found ";
        }
        n.close();
    }

    // Menu to interact with GST operations
    void gst_menu()
    {
        bool flag = true;
        while (flag)
        {
            system("clear");
            int choice;
            header();
            cout << "\n👋  🇼 🇪 🇱 🇨 🇴 🇲 🇪     🇹 🇴     🇬 🇸 🇹     🇧 🇮 🇱 🇱     🇲 🇪 🇳 🇺     🇧 🇦 🇷\n\n"
                 "1. Show all gst bills\n"
                 "2. Search gst bill by gst number\n"
                 "3. Update gst bills\n"
                 "4. Back\n"
                 "Enter your choice: ";
            cin >> choice;

            if (choice >= 1 && choice <= 4)
            {
                switch (choice)
                {
                case 1:
                    show_gst();
                    wait();
                    break;

                case 2:
                    search_gst_bill_by_gst_number();
                    cout << "\nPress enter to go menu bar..." << endl;
                    cin.get();
                    break;

                case 3:
                    gst_update();
                    cout << "\nPress enter to go menu bar..." << endl;
                    cin.get();
                    break;

                case 4:
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

    // Function to pause and wait for user to press enter
    void wait()
    {
        cout << "\nPress enter to go menu bar..." << endl;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cin.get();
    }

};

#endif
