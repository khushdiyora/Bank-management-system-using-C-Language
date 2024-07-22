# Bank-management-system-using-C-Language

This program is a simple banking management system implemented in C. It provides functionalities to manage customer records, including depositing and withdrawing money, updating records, deleting records, and viewing mini statements.

Features

- Add Customer Records: Enter details like account number, name, and initial balance.
- Display All Records: View all customer records stored in the system.
- Search Record: Look up customer information using their account number.
- Deposit/Withdraw: Modify the account balance by depositing or withdrawing money.
- Update/Delete Records: Change or remove customer records.
- Mini Statement: Display a summary of a customer's account.

Instructions

**1. Compilation**

To compile the C program, you need a C compiler such as GCC. Open your terminal or command prompt and navigate to the directory containing your main.c file.

Run the following command to compile the program:

```bash
gcc main.c -o banking_management
```

This command will create an executable file named banking_management.

**2. Execution**

After compilation, run the executable to start the program:

On Linux or macOS:

```bash
./banking_management
```

On Windows:

```bash
banking_management.exe
```

**3. Usage**

Once the program is running, you'll see a menu with the following options:

- Display All Records: Shows all customer records.
- Search Record: Allows you to search for a customer record by account number.
- Deposit Amount: Enter an account number and an amount to deposit.
- Withdraw Amount: Enter an account number and an amount to withdraw.
- Delete Record: Remove a customer record by account number.
- Update Customer Information: Modify the details of a customer record.
- Mini Statement: Display a summary of a customer’s account.

Follow the on-screen prompts to interact with the program.

**4. Data Structures**

- Customer: Structure to store account number, name, and balance.
- Stack: Stack data structure used to keep track of operations (for undo functionality).

**5. Future Improvements**

- File Handling: Add functionality to save and load customer data from a file.
- Input Validation: Improve error handling and validation of user inputs.
- Enhanced Features: Implement features such as transaction history and interest calculation.

### Example Commands

Here’s how you might use the program:

```bash

To deposit money:

Enter the account number: 12345
Enter the amount to deposit: 500

To withdraw money:

Enter the account number: 12345
Enter the amount to withdraw: 200

To update customer information:

Enter the account number to update: 12345
Enter new account number: 54321
Enter new name: John Doe
Enter new balance: 1000

```
