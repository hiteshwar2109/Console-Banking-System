#include <iostream>
#include <fstream>
#include <cctype>
#include <iomanip>
using namespace std;

// Class to handle account-related operations
class account
{
    int acno;          // Account number
    char name[50];     // Account holder's name
    int deposit;       // Account balance
    char type;         // Type of account (C/S)
public:
    void create_account();  // Function to create a new account
    void show_account() const; // Function to display account details
    void modify();        // Function to modify account details
    void dep(int);        // Function to deposit amount
    void draw(int);       // Function to withdraw amount
    void report() const;  // Function to report account details for listing
    int retacno() const;  // Function to return account number
    int retdeposit() const; // Function to return account balance
    char rettype() const; // Function to return account type
};

// Function to create a new account
void account::create_account()
{
    system("CLS"); // Clear the screen (use "CLS" on Windows)
    cout << "\n\t\tEnter the Account No. :";
    cin >> acno;
    cout << "\n\n\t\tPlease enter the name of the Account Holder here:";
    cin.ignore(); // Clear the newline character from the buffer
    cin.getline(name, 50); // Get the account holder's name
    cout << "\n\t\tEnter Type of the Account(C/S):";
    cin >> type;
    type = toupper(type); // Convert type to uppercase
    cout << "\n\t\tEnter the Initial Amount:";
    cin >> deposit; // Set initial deposit amount
    cout << "\n\n\t\tAccount Created..";
}

// Function to display account details
void account::show_account() const
{
    cout << "\n\t\tAccount No.:" << acno;
    cout << "\n\t\tAccount Holder Name: " << name;
    cout << "\n\t\tType of Account: " << type;
    cout << "\n\t\tBalance Amount: " << deposit;
}

// Function to modify account details
void account::modify()
{
    cout << "\n\t\t\tAccount No.:" << acno;
    cout << "\n\t\t\tModify Account Holder Name :";
    cin.ignore();
    cin.getline(name, 50); // Modify account holder's name
    cout << "\n\t\t\tModify Type of Account:";
    cin >> type;
    type = toupper(type); // Convert type to uppercase
    cout << "\n\t\t\tModify Balance amount :";
    cin >> deposit; // Modify account balance
}

// Function to deposit amount into the account
void account::dep(int x)
{
    deposit += x; // Add the deposit amount to the current balance
}

// Function to withdraw amount from the account
void account::draw(int x)
{
    deposit -= x; // Subtract the withdrawal amount from the current balance
}

// Function to report account details for listing purposes
void account::report() const
{
    cout << acno << setw(10) << " " << name << setw(10) << " " << type << setw(6) << deposit << endl;
}

// Function to return account number
int account::retacno() const
{
    return acno;
}

// Function to return account balance
int account::retdeposit() const
{
    return deposit;
}

// Function to return account type
char account::rettype() const
{
    return type;
}

// Function prototypes
void write_account();
void display_sp(int);
void modify_account(int);
void delete_account(int);
void display_all();
void deposit_withdraw(int, int);

int main()
{
   char ch; // Menu choice
   int num; // Account number
   do
   {
    system("CLS"); // Clear the screen (use "clear" on Unix/Linux)
    cout << "\n\n\t\t\t====================\n";
    cout << "\t\t\t\tBANK MANAGEMENT SYSTEM";
    cout << "\n\t\t\t======================\n";

    cout << "\t\t\t\t   ::MAIN MENU::\n ";
    cout << "\n\t\t\t\t1. NEW ACCOUNT";
    cout << "\n\t\t\t\t2. DEPOSIT AMOUNT";
    cout << "\n\t\t\t\t3. WITHDRAW AMOUNT";
    cout << "\n\t\t\t\t4. BALANCE ENQUIRY";
    cout << "\n\t\t\t\t5. ALL ACCOUNT HOLDERS LIST";
    cout << "\n\t\t\t\t6. CLOSE AN ACCOUNT";
    cout << "\n\t\t\t\t7. MODIFY AN ACCOUNT";
    cout << "\n\t\t\t\t8. EXIT";
    cout << "\n\n\t\t\t\tSelect Your Option (1-8):";
    cin >> ch;

    switch(ch)
    {
      case '1':
           write_account(); // Create a new account
           break;
      case '2':
           system("CLS");
           cout << "\n\n\t\tEnter the account no. :";
           cin >> num;
           deposit_withdraw(num, 1); // Deposit amount
           break;
      case '3':
            system("CLS");
            cout << "\n\n\t\tEnter the account no. :";
            cin >> num;
            deposit_withdraw(num, 2); // Withdraw amount
            break;
      case '4':
            system("CLS");
            cout << "\n\n\t\tEnter the account no. :";
            cin >> num;
            display_sp(num); // Display account details
            break;
      case '5':
            display_all(); // Display all account holders
            break;
      case '6':
            system("CLS");
            cout << "\n\n\t\tEnter the account no. :";
            cin >> num;
            delete_account(num); // Close an account
            break;
      case '7':
            system("CLS");
            cout << "\n\n\t\tEnter the account no. :";
            cin >> num;
            modify_account(num); // Modify account details
            break;
      case '8':
            system("CLS");
            cout << "\n\n\t\t\tGood Bye";
            break;
      default:
            cout << "\a"; // Invalid option
    }
    cin.ignore();
    cin.get();
   } while(ch != '8'); // Loop until user chooses to exit
   return 0;
}

// Function to create and write a new account to the file
void write_account()
{   
    account ac; // Create an account object
    ofstream outFile; // Output file stream
    outFile.open("account.dat", ios::binary | ios::app); // Open file in binary append mode
    ac.create_account(); // Get new account details from the user
    outFile.write(reinterpret_cast<char*>(&ac), sizeof(account)); // Write account to file
    outFile.close(); // Close the file
}

// Function to display specific account details
void display_sp(int n)
{
    account ac; // Create an account object
    bool flag = false; // Flag to check if account is found
    ifstream inFile; // Input file stream
    inFile.open("account.dat", ios::binary); // Open file in binary mode
    if (!inFile)
    {
        cout << "File could not be opened !! Press any Key...";
        return;
    }
    cout << "\n\t\t\tBALANCE DETAILS\n";
    while (inFile.read(reinterpret_cast<char*>(&ac), sizeof(account))) // Read each account from file
    {
        if (ac.retacno() == n) // Check if account number matches
        {
            ac.show_account(); // Display account details
            flag = true; // Account found
        }
    }
    inFile.close(); // Close the file
    if (flag == false)
        cout << "\n\n\t\t\tAccount number does not exist";
}

// Function to modify account details
void modify_account(int n)
{
    bool found = false; // Flag to check if account is found
    account ac; // Create an account object
    fstream File; // File stream for both input and output
    File.open("account.dat", ios::binary | ios::in | ios::out); // Open file in binary input/output mode
    if (!File)
    {
        cout << "File could not be opened !! Press any Key...";
        return;
    }

    while (!File.eof() && found == false)
    {
        File.read(reinterpret_cast<char*>(&ac), sizeof(account)); // Read account from file
        if (ac.retacno() == n) // Check if account number matches
        {
            ac.show_account(); // Display current account details
            cout << "\n\n\t\tEnter The New Details of account" << endl;
            ac.modify(); // Modify account details
            int pos = (-1) * static_cast<int>(sizeof(account)); // Calculate position to update
            File.seekp(pos, ios::cur); // Move to the position for updating
            File.write(reinterpret_cast<char*>(&ac), sizeof(account)); // Write updated account to file
            cout << "\n\n\t\t\t Record Updated";
            found = true; // Account updated
        }
    }
    File.close(); // Close the file
    if (found == false)
        cout << "\n\n\t\t\t Record Not Found ";
}

// Function to delete an account
void delete_account(int n)
{
    account ac; // Create an account object
    ifstream inFile; // Input file stream
    ofstream outFile; // Output file stream
    inFile.open("account.dat", ios::binary); // Open file in binary mode
    if (!inFile)
    {
        cout << "File could not be opened !! Press any Key...";
        return;
    }
    outFile.open("Temp.dat", ios::binary); // Open temporary file in binary mode
    inFile.seekg(0, ios::beg); // Move to the beginning of the file
    while (inFile.read(reinterpret_cast<char*>(&ac), sizeof(account))) // Read each account from file
    {
        if (ac.retacno() != n) // If account number does not match
        {
            outFile.write(reinterpret_cast<char*>(&ac), sizeof(account)); // Write to temporary file
        }
    }
    inFile.close(); // Close the original file
    outFile.close(); // Close the temporary file
    remove("account.dat"); // Delete the original file
    rename("Temp.dat", "account.dat"); // Rename temporary file to original file name
    cout << "\n\n\t\t\tRecord Deleted ..";
}

// Function to display all account holders
void display_all()
{
    account ac; // Create an account object
    ifstream inFile; // Input file stream
    inFile.open("account.dat", ios::binary); // Open file in binary mode
    if (!inFile)
    {
        cout << "File could not be opened !! Press any Key...";
        return;
    }
    cout << "\n\n\t\t\tACCOUNT HOLDER LIST\n\n";
    cout << "====================================================\n";
    cout << "A/c no.      NAME           Type  Balance\n";
    cout << "====================================================\n";
    while (inFile.read(reinterpret_cast<char*>(&ac), sizeof(account))) // Read each account from file
    {
        ac.report(); // Display account details
    }
    inFile.close(); // Close the file
}

// Function to handle deposit and withdrawal operations
void deposit_withdraw(int n, int option)
{
    int amt; // Amount for deposit/withdrawal
    bool found = false; // Flag to check if account is found
    account ac; // Create an account object
    fstream File; // File stream for both input and output
    File.open("account.dat", ios::binary | ios::in | ios::out); // Open file in binary input/output mode
    if (!File)
    {
        cout << "File could not be opened !! Press any Key...";
        return;
    }
    while (!File.eof() && found == false)
    {
        File.read(reinterpret_cast<char*>(&ac), sizeof(account)); // Read account from file
        if (ac.retacno() == n) // Check if account number matches
        {
            ac.show_account(); // Display current account details
            if (option == 1) // Deposit
            {
                cout << "\n\n\t\t\tTO DEPOSIT AMOUNT ";
                cout << "\n\n\t\tEnter The amount to be deposited: ";
                cin >> amt;
                ac.dep(amt); // Call deposit function
            }
            if (option == 2) // Withdraw
            {
                cout << "\n\n\t\t\tTO WITHDRAW AMOUNT ";
                cout << "\n\n\t\tEnter The amount to be withdrawn: ";
                cin >> amt;
                int bal = ac.retdeposit() - amt; // Check if balance is sufficient
                if (bal < 0)
                    cout << "Insufficient balance";
                else
                    ac.draw(amt); // Call withdraw function
            }
            int pos = (-1) * static_cast<int>(sizeof(ac)); // Calculate position to update
            File.seekp(pos, ios::cur); // Move to the position for updating
            File.write(reinterpret_cast<char*>(&ac), sizeof(account)); // Write updated account to file
            cout << "\n\n\t\t\t Record Updated";
            found = true; // Account updated
        }
    }
    File.close(); // Close the file
    if (found == false)
        cout << "\n\n\t\t\t Record Not Found ";
}
