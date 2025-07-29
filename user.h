#ifndef USER_H     // Prevent multiple inclusions of this header file
#define USER_H

#include "necessaryheader.h"  // Include the custom header

termios oldt;  // Used to store old terminal settings (for hiding password)

// Function to turn off terminal echo (for password input)
void disableEcho() 
{
    termios newt;
    tcgetattr(STDIN_FILENO, &oldt); // Get current terminal settings
    newt = oldt;
    newt.c_lflag &= ~(ICANON | ECHO); // Disable input buffering and echo
    tcsetattr(STDIN_FILENO, TCSANOW, &newt); // Apply new settings
}

// Function to restore terminal echo
void restoreEcho() 
{
    tcsetattr(STDIN_FILENO, TCSANOW, &oldt); // Restore original settings
}

// Class to manage CA staff users
class user 
{
    // Member variables for storing user info
    char username[100];
    char password[100];
    char correctusername[100];
    char correctpassword[100];
    char name[20];
    char mobile_number[15];

    // Private function to take password input while hiding characters
    void inputhidePassword() 
    {
        int i = 0;
        char ch;
        disableEcho(); // Hide input
        while (true) 
        {
            ch = getchar();
            if (ch == '\n') break; // Stop when Enter is pressed
            if ((ch == 127 || ch == 8) && i > 0) // Handle backspace
            {
                i--;
                cout << "\b \b";
            } 
            else if (i < 99) 
            {
                password[i] = ch;  // Save character to password
                i++;
                cout << "*";  // Show asterisk instead
            }
        }
        password[i] = '\0';  // End password string
        restoreEcho();       // Restore terminal
    }

public:

    // Constructor to set default admin login credentials
    user() 
    {   
        strcpy(correctusername, "mohitpareek");
        strcpy(correctpassword, "mohit@123");
        strcpy(name, "Mohit pareek");
        strcpy(mobile_number, "8769672576");
    }

    // Validate login for hardcoded (admin) user
    bool validate() 
    { 
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        system("clear");
        header();
        cout<<"\n🔷  🇱 🇴 🇬 🇮 🇳     🇼 🇮 🇳 🇩 🇴 🇼\n\n";
        cout << "\nEnter Username: ";
        cin.getline(username, 100);

        cout << "Enter Password: ";
        inputhidePassword();  // Take hidden password input

        bool flag = true;
        if (strcmp(username, correctusername) == 0 && strcmp(password, correctpassword) == 0) 
        {
            cout << "\n\nLogin Successful \n";
            cout<<"\n\nRedirecting to main menu in 3 seconds...\n";
            sleep(3);
            return flag;
        } 
        else 
        {
            cout << "\n\nInvalid Username or Password \n";
            flag = false;
            return flag;
        }
    }

    // Validate login from file (for general users)
    bool file_user_validate()
    {
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); 
        system("clear");
        header();
        cout<<"\n🔷  🇱 🇴 🇬 🇮 🇳     🇼 🇮 🇳 🇩 🇴 🇼\n\n";
        char input_username[100];
        char input_password[100];

        cout << "\nEnter Username: ";
        cin.getline(input_username, 100);

        cout << "Enter Password: ";
        int i = 0;
        char ch;
        disableEcho();
        while (true) 
        {
            ch = getchar();
            if (ch == '\n') break;
            if ((ch == 127 || ch == 8) && i > 0) 
            {
                i--;
                cout << "\b \b";
            } 
            else if (i < 99) 
            {
                input_password[i] = ch;
                i++;
                cout << "*";
            }
        }
        input_password[i] = '\0';
        restoreEcho();

        bool user_found = false;
        fstream f;
        f.open("user.dat", ios::in | ios::binary);

        // Check if entered username and password match any user in file
        while (f.read((char*)this, sizeof(*this)))
        {
            if (strcmp(this->username, input_username) == 0 && strcmp(this->password, input_password) == 0)
            {
                user_found = true;
            }
        }
        f.close();

        if (user_found)
        {       
            cout << "\n\nLogin Successful \n";
            cout<<"\n\nRedirecting to main menu in 3 seconds...\n";
            sleep(3);
            return user_found;
        }
        else 
        {
            cout << "\n\nInvalid Username or Password \n";
            return user_found;
        }
    }

    // Input user details
    void user_input() 
    {
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); 
        cout << "\nEnter name: ";
        cin.getline(name, 20);
        cout << "Enter username: ";
        cin.getline(username, 100);
        cout << "Enter password: ";
        cin.getline(password, 100);
        cout << "Enter mobile number: ";
        cin.getline(mobile_number, 15);
    }

    // Output user details (for displaying in table)
    void user_output(int serial)
    {
        cout << "| " << left << setw(5) << serial
            << "| " << setw(20) << name
            << "| " << setw(20) << username
            << "| " << setw(15) << "********"  // Don't show real password
            << "| " << setw(15) << mobile_number
            << "|" << endl;

        cout << "--------------------------------------------------------------------------------------\n";
    }

    // Add new user(s)
    void add_user()
    {
        fstream f;
        system("clear");
        header();
        cout << "\n👥  🇦 🇩 🇩     🇺 🇸 🇪 🇷 🇸\n\n"; 
        char ch;
        f.open("user.dat", ios::app | ios::binary);

        do
        {
            user_input();  // Get user input
            f.write((char*)this, sizeof(*this));  // Save to file
            cout << "\nDo you want to enter another user press(y): ";
            cin >> ch;
        } while (ch == 'y' || ch == 'Y');

        f.close();
    }

    // Show all users
    void show_user()
    {
        fstream f;
        system("clear");
        header();
        cout << "\n📋  🇦 🇱 🇱     🇺 🇸 🇪 🇷     🇩 🇪 🇹 🇦 🇮 🇱 🇸\n\n"; 
        f.open("user.dat", ios::in | ios::binary);
        int serial = 1;

        cout << "--------------------------------------------------------------------------------------\n";
        cout << "| " << left << setw(5) << "S.No"
            << "| " << setw(20) << "Name"
            << "| " << setw(20) << "Username"
            << "| " << setw(15) << "Password"
            << "| " << setw(15) << "Mobile Number"
            << "|" << endl;
        cout << "--------------------------------------------------------------------------------------\n";

        while (f.read((char*)this, sizeof(*this)))
        {
            user_output(serial++);
        }
        f.close();
    }

    // Update an existing user's details
    void update()
    {  
        fstream up; 
        system("clear");
        header();
        cout << "\n🔄  🇺 🇵 🇩 🇦 🇹 🇪     🇺 🇸 🇪 🇷\n\n"; 
        char input_username[100];

        cin.ignore(numeric_limits<streamsize>::max(), '\n'); 
        cout << "\nEnter username whose data you want to update: ";
        cin.getline(input_username, 100);

        up.open("user.dat", ios::in | ios::out | ios::binary);
        bool found = false; 

        while (up.read((char*)this, sizeof(*this)))
        {  
            if (strcmp(this->username, input_username) == 0)
            {
                up.seekp(sizeof(*this) * -1, ios::cur); // Go back to previous record
                cout << "\nPlease enter new values :- " << endl;
                user_input();
                up.write((char*)this, sizeof(*this));
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

    // Delete a user from file
    void user_delete()
    {  
        fstream n, up; 
        system("clear");
        header();
        cout << "\n🗑️  🇩 🇪 🇱 🇪 🇹 🇪     🇺 🇸 🇪 🇷\n\n"; 
        char input_username[100];

        cin.ignore(numeric_limits<streamsize>::max(), '\n'); 
        cout << "\nEnter username whose data you want to delete: ";
        cin.getline(input_username, 100);

        up.open("user.dat", ios::in | ios::binary);
        bool flag = true;
        n.open("updated.dat", ios::app | ios::binary);

        // Copy all users except the one to be deleted
        while (up.read((char*)this, sizeof(*this)))
        {  
            if (strcmp(this->username, input_username) == 0)
            {
                flag = false;
            }
            else
            {
                n.write((char*)this, sizeof(*this)); 
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

        remove("user.dat");  // Delete original
        rename("updated.dat", "user.dat");  // Rename updated file
        n.close();
        up.close();
    }

    // Display user menu
    void menu()
    {   
        bool flag = true;
        while (flag)
        {   
            system("clear");
            int choice;
            header();
            cout << "\n📂  🇼 🇪 🇱 🇨 🇴 🇲 🇪     🇹 🇴     🇲 🇪 🇳 🇺     🇧 🇦 🇷\n\n"
                "1. Show all Users\n"
                "2. Add user\n"
                "3. Delete user\n"
                "4. update user\n"
                "5. Back\n"
                "Enter your choice: ";
            cin >> choice;

            if (choice >= 1 && choice <= 5)    
            { 
                switch (choice)
                {
                    case 1: show_user(); wait(); break;
                    case 2: add_user(); wait(); break;
                    case 3: user_delete(); cout << "\nPress enter to go menu bar..." << endl; cin.get(); break;
                    case 4: update(); cout << "\nPress enter to go menu bar..." << endl; cin.get(); break; 
                    case 5: flag = false; break;         
                }
            }
            else
            {
                cout << "\nInvalid choice..";
                wait();
            }
        }
    }

    // Wait function for pause
    void wait()
    { 
        cout << "\nPress enter to go menu bar..." << endl;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cin.get();
    }

    // Choose login type and validate accordingly
    bool login_Execute()
    {
        int type = logintype();  
        bool check;
        if (type == 1)
        {
            check = validate();  // Admin login
        }
        else if (type == 2)
        {
            check = file_user_validate();  // General login
        }
        return check;
    }

    // Choose login method: admin or general user
    int logintype()
    {
        while (true)
        { 
            system("clear");
            header();
            cout << "\n🔐  🇱 🇴 🇬 🇮 🇳     🇹 🇾 🇵 🇪\n\n"; 
            cout << "1. Login as a Administrator\n"
                 << "2. General login" << endl;
            int choose;
            cout << "\nChoose option: ";
            cin >> choose;

            switch (choose)
            {
                case 1: return 1;
                case 2: return 2;
                default:
                    {
                        cout << "\n\nwrong option , choose correct option (1 or 2)... ";
                        cout << "\n\nPress enter for back...";
                        cin.ignore();
                        cin.get(); 
                    }      
            }
        }
    }
};

#endif // End of user.h
