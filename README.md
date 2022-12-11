# Bear Robotics Korea :: Implement a simple ATM controller

--------

Write code for a simple ATM. It doesn't need any UI (either graphical or console), but a controller should be implemented and tested.

# Requirements
At least the following flow should be implemented:

Insert Card => PIN number => Select Account => See Balance/Deposit/Withdraw



For simplification, there are only 1 dollar bills in this world, no cents. Thus account balance can be represented in integer.



Your code doesn't need to integrate with a real bank system, but keep in mind that we may want to integrate it with a real bank system in the future. It doesn't have to integrate with a real cash bin in the ATM, but keep in mind that we'd want to integrate with that in the future. And even if we integrate it with them, we'd like to test our code. Implementing bank integration and ATM hardware like cash bin and card reader is not a scope of this task, but testing the controller part (not including bank system, cash bin etc) is within the scope.



A bank API wouldn't give the ATM the PIN number, but it can tell you if the PIN number is correct or not.



Based on your work, another engineer should be able to implement the user interface. You don't need to implement any REST API, RPC, network communication etc, but just functions/classes/methods, etc.



You can simplify some complex real world problems if you think it's not worth illustrating in the project.

# Initialization
Created one card and two accounts for test

Pin : 1234

Account list
0. Account number 987, money 2000
1. Account number 654, money 1000

# Tutorial

1) start

------------------------------------------------
--------------Welcome to SKD Bank---------------
------------------------------------------------
After insert card, press y

2) input : y

Card reading...

Card validated!!
Please enter your pin number

3) input : 1234

You have (2) account
Account 0, bank account number : 987
Account 1, bank account number : 654
Select Account (0~1)

4) input : 0

Select Task(0~3)
0. Account Balance
1. Deposit
2. Withdraw
3. Exit

5) input : 0

Your Balance : 2000


Select Task(0~3)
0. Account Balance
1. Deposit
2. Withdraw
3. Exit

6) input : 1

After you put the money in,
Please write down the deposit amount(-1 for Exit) :

7) input : 1000

Success Deposite

Select Task(0~3)
0. Account Balance
1. Deposit
2. Withdraw
3. Exit

8) input : 2

Please write down the withdrawal amount(-1 for Exit) :

9) input : 100

Success Withdrawal

Select Task(0~3)
0. Account Balance
1. Deposit
2. Withdraw
3. Exit

10) input : 0

Your Balance : 2900


Select Task(0~3)
0. Account Balance
1. Deposit
2. Withdraw
3. Exit


11) input : 3

Thank you.
Please remove your card

------------------------------------------------
--------------Welcome to SKD Bank---------------
------------------------------------------------
After insert card, press y