#include "user.h"               // Includes the header file for user-related functions (like login)
#include "incometax.h"          // Includes the header file for income tax-related operations
#include "balancesheet.h"       // Includes the header file for balance sheet operations
#include "gstreturn.h"          // Includes the header file for GST return-related features
#include "clientindividual.h"   // Includes the header file for individual client management
#include "clientcompany.h"      // Includes the header file for company client management
#include "necessaryheader.h"    // Includes any other required common headers (like iostream, etc.)

// This is the main function to control the home page / dashboard of the CA assistant system
void main_page()
{
    user userobj;                       // Create a user object to handle login and user menu
    bool valid = userobj.login_Execute();  // Ask user to login, store result in valid

    if(valid)  // If login is successful
    {
        bool flag = true;  // flag controls the main menu loop
        while(flag)
        {   
            system("clear");  // Clear the console screen
            header();         // Display the common header

            // Display main menu options
            cout << "\n🏠  🇼 🇪 🇱 🇨 🇴 🇲 🇪     🇹 🇴     🇲 🇦 🇮 🇳     🇵 🇦 🇬 🇪\n\n"
            "1. Individual client management \n"
            "2. Company management\n"
            "3. CA staff users management\n"
            "4. Exit\n"
            "\nChoose option (1/2/3/4): ";

            int choose;
            cin >> choose;  // Take user input

            // Check if the input is valid (between 1 to 4)
            if(choose >= 1 && choose <= 4)    
            {
                switch(choose)
                {
                    case 1: 
                        client_individual client;  // Create object for individual client
                        client.client_menu();      // Open individual client menu
                        break;

                    case 2: 
                        client_company company;    // Create object for company client
                        company.company_menu();    // Open company menu
                        break;

                    case 3: 
                        userobj.menu();            // Open user management menu
                        break;

                    case 4: 
                        cout << "\nThanks..\nClosing program ";  // Exit message
                        flag = false;             // Exit loop
                }  
            }
            else  // If input is not 1 to 4
            {
                cout << "\nYou choose wrong option , choose correct option";
                cout << "\nPress enter to try again ";
                cin.ignore();  // Clear input buffer
                cin.get();     // Wait for enter key
            }
        }
    }
}

// Main function to start the program
int main()
{
    main_page();  // Call the main page function
    return 0;     // End of program
}
