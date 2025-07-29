#ifndef INCOMETAX_H
#define INCOMETAX_H

#include "necessaryheader.h"

// Class to handle income tax operations
class incometax
{
    // Private data members to store tax details
    int age;
    char it_financial_year[15];
    char it_name_of_ferm[30];
    char it_residential[15];
    double it_net_taxable_amount;
    double it_total_income_from_all_sources;
    double taxable_income;
    double it_total_deductions;
    double it_surcharge;
    double it_cess;

public:

    // PAN number is public so it can be accessed outside
    char pan_number[20];

    // Function to choose between old and new tax regime
    void tax_calculator()
    {
        system("clear");
        header();
        cout<<"\n🧾   🇫 🇮 🇱 🇱     🇮 🇳 🇨 🇴 🇲 🇪     🇹 🇦 🇽\n\n";
        int choose;
        cout<<"\n1.Old regime\n2.New regime\nChoose tax regime: ";
        cin>>choose;
        bool flag = true;
        while(flag)
        {
            if(choose == 1 || choose == 2)
            {
                // If old regime selected
                if(choose==1)
                {
                    flag = false;
                    old_regime();
                }

                // If new regime selected
                if(choose == 2)
                {
                    flag = false;
                    new_regime();
                }
            }
            else
            {
                cout<<"\nChoose correct option...";
            }
        }
    }

    // Function to calculate tax based on old regime
    void old_regime()
    {
        taxable_income = it_total_income_from_all_sources;

        // If income < 5 lakh, no tax
        if(it_total_income_from_all_sources < 500000)
        {
            it_net_taxable_amount = 0;
        }
        // If income is between 5 to 10 lakh
        else if(it_total_income_from_all_sources < 1000000)
        {
            it_total_income_from_all_sources -= it_total_deductions;
            it_net_taxable_amount = it_total_income_from_all_sources * 0.2;
            it_cess = it_net_taxable_amount * 0.04;
            it_net_taxable_amount += it_cess;
        }
        // If income is above 10 lakh
        else if(it_total_income_from_all_sources >= 1000000)
        {
            bool flag = true;
            it_total_income_from_all_sources -= it_total_deductions;
            it_net_taxable_amount = it_total_income_from_all_sources * 0.3;

            // Surcharge conditions
            if(it_total_income_from_all_sources >= 5000000 && it_total_income_from_all_sources < 10000000)
            {
                it_surcharge = it_net_taxable_amount * 0.1;
                it_net_taxable_amount += it_surcharge;
                it_cess = it_net_taxable_amount * 0.04;
                it_net_taxable_amount += it_cess;
                flag = false;
            }
            else if(it_total_income_from_all_sources >= 10000000 && it_total_income_from_all_sources < 20000000)
            {
                it_surcharge = it_net_taxable_amount * 0.15;
                it_net_taxable_amount += it_surcharge;
                it_cess = it_net_taxable_amount * 0.04;
                it_net_taxable_amount += it_cess;
                flag = false;
            }
            else if(it_total_income_from_all_sources >= 20000000 && it_total_income_from_all_sources < 50000000)
            {
                it_surcharge = it_net_taxable_amount * 0.25;
                it_net_taxable_amount += it_surcharge;
                it_cess = it_net_taxable_amount * 0.04;
                it_net_taxable_amount += it_cess;
                flag = false;
            }
            else if(it_total_income_from_all_sources >= 50000000)
            {
                it_surcharge = it_net_taxable_amount * 0.37;
                it_net_taxable_amount += it_surcharge;
                it_cess = it_net_taxable_amount * 0.04;
                it_net_taxable_amount += it_cess;
                flag = false;
            }

            // If no surcharge applied, add only cess
            if(flag)
            {
                it_cess = it_net_taxable_amount * 0.04;
                it_net_taxable_amount += it_cess;
            }
        }
    }

    // Function to calculate tax based on new regime
    void new_regime()
    {
        taxable_income = it_total_income_from_all_sources;

        if(it_total_income_from_all_sources < 700000)
        {
            it_net_taxable_amount = 0;
        }
        else if(it_total_income_from_all_sources < 900000)
        {
            it_net_taxable_amount = it_total_income_from_all_sources * 0.1;
            it_cess = it_net_taxable_amount * 0.04;
            it_net_taxable_amount += it_cess;
        }
        else if(it_total_income_from_all_sources < 1200000)
        {
            it_net_taxable_amount = it_total_income_from_all_sources * 0.15;
            it_cess = it_net_taxable_amount * 0.04;
            it_net_taxable_amount += it_cess;
        }
        else if(it_total_income_from_all_sources < 1500000)
        {
            it_net_taxable_amount = it_total_income_from_all_sources * 0.2;
            it_cess = it_net_taxable_amount * 0.04;
            it_net_taxable_amount += it_cess;
        }
        else if(it_total_income_from_all_sources >= 1500000)
        {
            it_net_taxable_amount = it_total_income_from_all_sources * 0.3;
            bool flag = true;

            // Surcharge slabs for new regime
            if(it_total_income_from_all_sources >= 5000000 && it_total_income_from_all_sources < 10000000)
            {
                it_surcharge = it_net_taxable_amount * 0.1;
                it_net_taxable_amount += it_surcharge;
                it_cess = it_net_taxable_amount * 0.04;
                it_net_taxable_amount += it_cess;
                flag = false;
            }
            else if(it_total_income_from_all_sources >= 10000000 && it_total_income_from_all_sources < 20000000)
            {
                it_surcharge = it_net_taxable_amount * 0.15;
                it_net_taxable_amount += it_surcharge;
                it_cess = it_net_taxable_amount * 0.04;
                it_net_taxable_amount += it_cess;
                flag = false;
            }
            else if(it_total_income_from_all_sources >= 20000000)
            {
                it_surcharge = it_net_taxable_amount * 0.25;
                it_net_taxable_amount += it_surcharge;
                it_cess = it_net_taxable_amount * 0.04;
                it_net_taxable_amount += it_cess;
                flag = false;
            }

            // If no surcharge then add only cess
            if(flag)
            {
                it_cess = it_net_taxable_amount * 0.04;
                it_net_taxable_amount += it_cess;
            }
        }
    }

    // Function to input all income and deduction related data
    void it_input()
    {
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); 
        system("clear");
        header();
        cout<<"\n🧾   🇫 🇮 🇱 🇱     🇮 🇳 🇨 🇴 🇲 🇪     🇹 🇦 🇽\n\n";
        cout<<"\nEnter basic details :- \n";
        cout<<"\nEnter name of client: ";
        cin.getline(it_name_of_ferm,30);
        cout<<"\nEnter pan number: ";
        cin.getline(pan_number,20);
        cout<<"\nEnter financial year: ";
        cin.getline(it_financial_year,15);
        cout<<"\nEnter residential: ";
        cin.getline(it_residential,15);
        cout<<"\nEnter age: ";
        cin>>age;

        // Input all types of incomes
        cout<<"\nFor filling details about income press 'Enter' ";
        cin.ignore();
        cin.get();
        system("clear");
        double salary_income , business_income , house_property_income , other_source_income ;
        it_total_income_from_all_sources = 0 ;
        header();
        cout<<"\n🧾   🇫 🇮 🇱 🇱     🇮 🇳 🇨 🇴 🇲 🇪     🇹 🇦 🇽\n\n";
        cout<<"\nEnter all details about Income :-\n ";
        cout<<"\nEnter income from salary: ";
        cin>>salary_income;
        cout<<"\nEnter income from business: ";
        cin>>business_income;
        cout<<"\nEnter income from house property or rent: ";
        cin>>house_property_income;
        cout<<"\nEnter income from other sources: ";
        cin>>other_source_income;
        it_total_income_from_all_sources = salary_income + business_income + house_property_income + other_source_income;

        // Input deductions
        cout<<"\nFor filling details about Deductions press 'Enter' ";
        cin.ignore();
        cin.get();
        system("clear");
        header();
        cout<<"\n🧾   🇫 🇮 🇱 🇱     🇮 🇳 🇨 🇴 🇲 🇪     🇹 🇦 🇽\n\n";
        cout<<"\n Enter data about deductions:-\n";
        string choice1 , choice2 ;
        string section_80C = "yes",section_80D = "yes";
        cout<<"\nEnter 'yes' if you pay any LIC , PF: ";
        getline(cin,choice1);
        cout<<"\nEnter 'yes' if you have any medical insurance: ";
        getline(cin,choice2);

        // Apply deduction amounts if user is eligible
        it_total_deductions = 0;
        if(section_80C == choice1)
        {
            it_total_deductions += 150000;
        }
        if(section_80D == choice2)
        {
            if(age<60)
            {
                it_total_deductions += 25000;
            }
            else
            {
                it_total_deductions += 50000;
            }
        }

        // Call tax calculator after inputs
        tax_calculator();
    }



    
// Function to add a new income tax record
void add_income_tax()
{
    fstream f;
    system("clear"); // Clears the screen
    header(); // Displays the header

    cout << "\n➕  🇦 🇩 🇩     🇮 🇳 🇨 🇴 🇲 🇪     🇹 🇦 🇽\n\n";

    char ch;
    f.open("tax.dat", ios::app | ios::binary); // Open file in append mode
    it_input(); // Take user input for income tax
    f.write((char*)this, sizeof(*this)); // Write data to file
    f.close(); // Close the file
}

// Function to display one income tax record in a formatted way
void it_output(int serial)
{
    cout << "| " << left << setw(5) << serial
         << "| " << setw(30) << it_name_of_ferm
         << "| " << setw(20) << pan_number
         << "| " << setw(15) << it_residential
         << "| " << setw(15) << it_financial_year
         << "| " << setw(20) << fixed << setprecision(2) << taxable_income
         << "| " << setw(20) << fixed << setprecision(2) << it_net_taxable_amount
         << "|" << endl;

    cout << "--------------------------------------------------------------------------------------------------------------------------------------------\n";
}

// Function to show all income tax records
void show_income_tax()
{
    fstream f;
    system("clear");
    header(); // Show header

    cout << "\n📄  🇦 🇱 🇱     🇮 🇳 🇨 🇴 🇲 🇪     🇹 🇦 🇽     🇩 🇪 🇹 🇦 🇮 🇱\n\n";

    f.open("tax.dat", ios::in | ios::binary); // Open file for reading
    int serial = 1;

    // Print table headers
    cout << "--------------------------------------------------------------------------------------------------------------------------------------------\n";
    cout << "| " << left << setw(5) << "S.No"
         << "| " << setw(30) << "Client Name"
         << "| " << setw(20) << "pan number"
         << "| " << setw(15) << "Residential"
         << "| " << setw(15) << "Financial year"
         << "| " << setw(20) << "Total income"
         << "| " << setw(20) << "Total tax"
         << "|" << endl;
    cout << "--------------------------------------------------------------------------------------------------------------------------------------------\n";

    // Read and display all records
    while (f.read((char*)this, sizeof(*this)))
    {
        it_output(serial++);
    }

    f.close();
}

// Function to update income tax data using PAN number
void income_tax_update()
{
    fstream up;
    system("clear");
    header();

    cout << "\n🔄  🇺 🇵 🇩 🇦 🇹 🇪     🇮 🇳 🇨 🇴 🇲 🇪     🇹 🇦 🇽\n\n";

    char input_pan_number[20];
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    cout << "\nEnter pan  number of client whose income tax data you want to update: ";
    cin.getline(input_pan_number, 20);

    up.open("tax.dat", ios::in | ios::out | ios::binary);
    bool found = false;

    // Find the record to update
    while (up.read((char*)this, sizeof(*this)))
    {
        if (strcmp(this->pan_number, input_pan_number) == 0)
        {
            up.seekp(sizeof(*this) * -1, ios::cur); // Go back one record
            cout << "\nPlease enter new values :- " << endl;
            it_input(); // Take new data
            up.write((char*)this, sizeof(*this)); // Write updated data
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

// Function to delete income tax record using PAN number
void income_tax_delete()
{
    fstream n, up;
    system("clear");
    header();

    cout << "\n🗑️  🇩 🇪 🇱 🇪 🇹 🇪     🇮 🇳 🇨 🇴 🇲 🇪     🇹 🇦 🇽\n\n";

    char input_pan_number[20];
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    cout << "\nEnter client pan number whose Income tax data you want to delete: ";
    cin.getline(input_pan_number, 20);

    up.open("tax.dat", ios::in | ios::binary); // Original file
    n.open("tax_updated.dat", ios::app | ios::binary); // Temp file

    bool flag = true;

    while (up.read((char*)this, sizeof(*this)))
    {
        if (strcmp(this->pan_number, input_pan_number) == 0)
        {
            flag = false; // Found, so skip writing this record
        }
        else
        {
            n.write((char*)this, sizeof(*this)); // Copy other records
        }
    }

    if (!flag)
    {
        cout << "\nData delete successfully";
    }
    else
    {
        cout << "\n Data not Found ";
    }

    remove("tax.dat"); // Delete original file
    rename("tax_updated.dat", "tax.dat"); // Rename temp file
    n.close();
    up.close();
}

// Function to search income tax data by PAN number
void search_income_tax_by_pan()
{
    fstream n;
    system("clear");
    header();

    cout << "\n🔍  🇸 🇪 🇦 🇷 🇨 🇭     🇮 🇳 🇨 🇴 🇲 🇪     🇹 🇦 🇽\n\n";

    char input_pan_number[20];
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    cout << "\nEnter client pan number whose Income tax data you want : ";
    cin.getline(input_pan_number, 20);

    n.open("tax.dat", ios::in | ios::binary);
    bool flag = true;
    int serial = 1;

    // Print table headers
    cout << "--------------------------------------------------------------------------------------------------------------------------------------------\n";
    cout << "| " << left << setw(5) << "S.No"
         << "| " << setw(30) << "Client Name"
         << "| " << setw(20) << "pan number"
         << "| " << setw(15) << "Residential"
         << "| " << setw(15) << "Financial year"
         << "| " << setw(20) << "Total income"
         << "| " << setw(20) << "Total tax"
         << "|" << endl;
    cout << "--------------------------------------------------------------------------------------------------------------------------------------------\n";

    // Search and display matching record
    while (n.read((char*)this, sizeof(*this)))
    {
        if (strcmp(this->pan_number, input_pan_number) == 0)
        {
            it_output(serial++);
            flag = false;
        }
    }

    if (flag)
    {
        cout << "\n Data not Found ";
    }

    n.close();
}

// Menu to manage income tax section
void income_tax_menu()
{
    bool flag = true;

    while (flag)
    {
        system("clear");
        int choice;
        header();

        cout << "\n👋  🇼 🇪 🇱 🇨 🇴 🇲 🇪     🇹 🇴     🇮 🇳 🇨 🇴 🇲 🇪     🇹 🇦 🇽     🇲 🇪 🇳 🇺\n\n"
             "1. Show all Tax\n"
             "2. Delete Tax\n"
             "3. update Tax\n"
             "4. Search client tax by pan number\n"
             "5. Back"
             "\nEnter your choice: ";
        cin >> choice;

        if (choice >= 1 && choice <= 5)
        {
            switch (choice)
            {
                case 1:
                    show_income_tax();
                    wait();
                    break;

                case 2:
                    income_tax_delete();
                    cout << "\nPress enter to go menu bar..." << endl;
                    cin.get();
                    break;

                case 3:
                    income_tax_update();
                    cout << "\nPress enter to go menu bar..." << endl;
                    cin.get();
                    break;

                case 4:
                    search_income_tax_by_pan();
                    cout << "\nPress enter to go menu bar..." << endl;
                    cin.get();
                    break;

                case 5:
                    flag = false; // Exit menu
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

// Wait function to pause and wait for user input
void wait()
{
    cout << "\nPress enter to go menu bar..." << endl;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cin.get();
}


};

#endif