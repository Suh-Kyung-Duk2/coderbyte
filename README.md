# Bear Robotics Korea :: Implement a simple ATM controller





# Requirements

Write code for a simple ATM. It doesn't need any UI (either graphical or console), but a controller should be implemented and tested.


At least the following flow should be implemented:

Insert Card => PIN number => Select Account => See Balance/Deposit/Withdraw



For simplification, there are only 1 dollar bills in this world, no cents. Thus account balance can be represented in integer.



Your code doesn't need to integrate with a real bank system, but keep in mind that we may want to integrate it with a real bank system in the future. It doesn't have to integrate with a real cash bin in the ATM, but keep in mind that we'd want to integrate with that in the future. And even if we integrate it with them, we'd like to test our code. Implementing bank integration and ATM hardware like cash bin and card reader is not a scope of this task, but testing the controller part (not including bank system, cash bin etc) is within the scope.



A bank API wouldn't give the ATM the PIN number, but it can tell you if the PIN number is correct or not.



Based on your work, another engineer should be able to implement the user interface. You don't need to implement any REST API, RPC, network communication etc, but just functions/classes/methods, etc.

You can simplify some complex real world problems if you think it's not worth illustrating in the project.


# Instructions




##### Compilation Instructions:
To compile, please execute the following:
```bash
$ find ./ATM_Project -name "ATM_Project.sln"
```
Note that already provided compiled .exe file using Microsoft Visual Studio Professional 2019
 (v142)

##### Running the ATM
Once compiled, the program can run as follows:
```bash
$ find ./ATM_Project/x64/Debug -name "ATM_Project.exe"
```

##### Features 

- Verify whether it is valid card.
- Verify whether it is valid Pin.
- See Balance/Deposite/Withdraw is supported.
- Deposit is supported under $100,000, and if there is too much balance in the account(overflow), it prints that deposit is not possible.
- It supports withdrawal of less than $100,000, and prints impossible if the balance is insufficient.
- The ATM is powered by admin in the main() function. While the power is on, the ATM receives customers.

##### Initializations

- For the experiment, I put one card and two accounts on the bank's server.
- Pin : 1234
- Account list
0. Account number : 987, Balance : $2,000
1. Account number : 654, Balance : $1,000

##### How to use 

To use the ATM as a Client:
- Once started, the ATM machine asks you to press "y" if you put the card in to the machine.
- After card is inserted, Atm asks for card validation to ServerDB.
- If the card is a valid, Atm asks you to enter a Pin number.
- If the Pin number is valid, the ATM machine prints out a list of accounts tied to the card and asks the user to select an account.
- After selecting an account, the ATM machine asks the user to choose between See Balance, Deposite, Withdraw and Exit.


##### Example

![ATM](https://user-images.githubusercontent.com/120086749/207247541-1aca64c0-81be-4210-82a9-2a8260675ded.JPG)

