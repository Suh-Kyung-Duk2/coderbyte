#include <iostream>
#include <vector>
#include <string>
#include <array>
#include <tuple>
#include <safeint.h>
using namespace msl::utilities;
using namespace std;
#define InfoNum 4
typedef enum
{   //Server Results
    eServer_Fail = -1,
    eServer_Success = 1
};
typedef enum
{   //Interface Display Command
    eDCMD_TBD = -1,
    eDCMD_AskCard,
    eDCMD_AskPIN,
    eDCMD_AskAccount,
    eDCMD_AskTask,
    eDCMD_ShowBalance,
    eDCMD_AskDeposite,
    eDCMD_AskWithDrawal,
    eDCMD_Success,
    eDCMD_Finalize,
    eDCMD_Failed
};
typedef enum
{   //ATM Task command
    eTCMD_TBD = -1,
    eTCMD_AccountBalance = 0,
    eTCMD_Deposit = 1,
    eTCMD_Withdraw = 2,
    eTCMD_Exit = 3
};
class ServerDB {
private:
    //Member variable
    vector<int>  Cardlist;
    vector<int>  Pinlist;
    vector<vector<tuple<int, int>>>  Accountlist; //Account with money

public:
    //Method
    void Initialize(void);
    int CardNumbValidity(int tmp);
    int PinNumbValidity(int AccountIdx, int choice);
    vector<int> ReturnAccountlist(int AccountIdx);
    int ReturnAccountMoney(int AccountIdx, int AccountChoice) { return get<1>(Accountlist[AccountIdx][AccountChoice]); };
    int Deposite(int AccountIdx, int AccountChoice, int AddMoney);
    int WithDraw(int AccountIdx, int AccountChoice, int WithDrawMoney);
};
void ServerDB::Initialize() {
    //initial account
    Cardlist.push_back(928002);
    Pinlist.push_back(1234);
    vector<tuple<int, int>> tmp;
    tmp.push_back(make_tuple(987, 2000));
    tmp.push_back(make_tuple(654, 1000));
    Accountlist.push_back(tmp);
}
int ServerDB::CardNumbValidity(int tmp) {
    auto CardNumbtmp = find(Cardlist.begin(), Cardlist.end(), tmp);
    if (CardNumbtmp == Cardlist.end()) {
        return eServer_Fail;
    }
    else {
        int AccountIDX = (CardNumbtmp - Cardlist.begin());
        return AccountIDX;
    }
    return eServer_Fail;
}
int ServerDB::PinNumbValidity(int AccountIdx, int choice) {
    if (Pinlist[AccountIdx] == choice) {
        return eServer_Success; //Pin is correct
    }
    else {
        return eServer_Fail;
    }
}
vector<int> ServerDB::ReturnAccountlist(int AccountIdx) {
    vector<int> ListOnly;
    for (int i = 0; i < Accountlist[AccountIdx].size(); i++) {
        ListOnly.push_back(get<0>(Accountlist[AccountIdx][i]));
    }
    return ListOnly; //Account list return;
}

int ServerDB::Deposite(int AccountIdx, int AccountChoice, int AddMoney) {
    SafeInt<int> X1(get<1>(Accountlist[AccountIdx][AccountChoice]));
    SafeInt<int> X2(AddMoney);
    SafeInt<int> X3(0);
    try
    {
        X3 = X1 + X2;
    }
    catch (SafeIntException e)
    {
        return eServer_Fail;// Money overflow
    }
    get<1>(Accountlist[AccountIdx][AccountChoice]) = X3;
    return eServer_Success;
}
int ServerDB::WithDraw(int AccountIdx, int AccountChoice, int WithDrawMoney) {

    if (get<1>(Accountlist[AccountIdx][AccountChoice]) < WithDrawMoney) { //impossible for negative withdraw
        return eServer_Fail;
    }
    else {
        get<1>(Accountlist[AccountIdx][AccountChoice]) = get<1>(Accountlist[AccountIdx][AccountChoice]) - WithDrawMoney;
        return eServer_Success;
    }
}

class ATM {
private:
    vector<array<int, InfoNum>>  Cardlist;

public:
    void launch(ServerDB* server);
    void initialize(ServerDB* server);
};
class Interface {
private:
public:
    //메소드
    int display(int cmd);
    int display(int cmd, int cmd2);
    int display(int cmd, vector<int> cmd2);
};
void ATM::initialize(ServerDB* server) {
    server->Initialize();
}
void ATM::launch(ServerDB* server) {
    Interface* interface1 = new Interface;

    int FailedFlag = -1;
    int CardNumber = interface1->display(eDCMD_AskCard);


    ///***CARD Validity check***///

    int AccountIdx = server->CardNumbValidity(CardNumber);
    if (AccountIdx != eServer_Fail) { //Card is valid

        ///***PIN Validity check (3 Trial)***///

        int ValidPinFlag = 0;
        int PinTrial = 0;
        while (PinTrial < 3)
        {
            int choice = interface1->display(eDCMD_AskPIN, PinTrial);
            ValidPinFlag = server->PinNumbValidity(AccountIdx, choice);
            if (ValidPinFlag == eServer_Fail) {
                PinTrial++;
            }
            else {
                break;
            }
        }
        if (ValidPinFlag == eServer_Success) {

            ///***Ask for Account***///

            vector<int> getAccount = server->ReturnAccountlist(AccountIdx);
            if (getAccount.size() != 0) {
                int AccountChoice = interface1->display(eDCMD_AskAccount, getAccount);

                ///***Ask for Task(until Exit request)***///

                int TaskChoice = eTCMD_TBD;
                while (TaskChoice != eTCMD_Exit)
                {
                    TaskChoice = interface1->display(eDCMD_AskTask);
                    if (TaskChoice == eTCMD_AccountBalance) {
                        int getMoney = server->ReturnAccountMoney(AccountIdx, AccountChoice);
                        interface1->display(eDCMD_ShowBalance, getMoney);
                    }
                    else if (TaskChoice == eTCMD_Deposit) {
                        int Choice = interface1->display(eDCMD_AskDeposite);
                        if (Choice != -1) {
                            if (server->Deposite(AccountIdx, AccountChoice, Choice) == eServer_Success) {
                                interface1->display(eDCMD_Success, eDCMD_AskDeposite);
                            }
                            else {
                                interface1->display(eDCMD_Failed, eDCMD_AskDeposite);
                            }
                        }

                    }
                    else if (TaskChoice == eTCMD_Withdraw) {
                        int Choice = interface1->display(eDCMD_AskWithDrawal);
                        if (Choice != -1) {
                            if (server->WithDraw(AccountIdx, AccountChoice, Choice) == eServer_Success) {
                                interface1->display(eDCMD_Success, eDCMD_AskWithDrawal);
                            }
                            else {
                                interface1->display(eDCMD_Failed, eDCMD_AskWithDrawal);
                            }
                        }
                    }
                }
            }
        }
        else {
            FailedFlag = eDCMD_AskPIN;
        }
    }
    else {
        FailedFlag = eDCMD_AskCard;
    }
    if (FailedFlag != eDCMD_TBD) {
        interface1->display(eDCMD_Failed, FailedFlag);
    }
    else {
        interface1->display(eDCMD_Finalize);
    }

    delete interface1;
}
int Interface::display(int cmd) {
    cout << endl;
    if (cmd == eDCMD_AskCard) {
        char choice;
        cout << "------------------------------------------------" << endl;
        cout << "--------------Welcome to SKD Back---------------" << endl;
        cout << "------------------------------------------------" << endl;
        int InsertTrial = 0;
        while (InsertTrial < 3) {
            cout << "After insert card, press y" << endl;
            cin.clear();
            //cin.ignore(10, '\n');
            cin >> choice;
            InsertTrial++;
            if (choice == 'y' || choice == 'Y') {
                cout << "Card reading..." << endl;
                int CardNumb = 928002; //Interface reads card number
                return CardNumb;//
            }
            else if (InsertTrial < 3) {
                cout << "Card insert failed" << endl;
                cout << "Please insert again (" << InsertTrial << " / 3)" << endl << endl;
            }
        }
    }
    if (cmd == eDCMD_AskTask) {
        cout << "Select Task(0~3)" << endl;
        cout << eTCMD_AccountBalance << ". Account Balance" << endl;
        cout << eTCMD_Deposit << ". Deposit" << endl;
        cout << eTCMD_Withdraw << ". Withdraw" << endl;
        cout << eTCMD_Exit << ". Exit" << endl;//!!!뒤로가기도?
        float choice = -1;
        int tmp = -1; //To check, choice must be integer
        cin.clear();
        cin.ignore(100, '\n');
        cin >> choice;
        tmp = choice;
        while (cin.fail() == 1 || (tmp - choice) != 0 || choice > 3 || choice < 0)
        {
            cout << "Please try again" << endl;
            cin.clear();
            cin.ignore(100, '\n');
            cin >> choice;
            tmp = choice;
        }
        return choice;
    }
    if (cmd == eDCMD_AskDeposite) {
        cout << "After you put the money in," << endl;
        cout << "Please write down the deposit amount(-1 for Exit) : ";
        float choice = -1;
        int tmp = -1; //To check, choice must be integer
        cin.clear();
        cin.ignore(100, '\n');
        cin >> choice;
        tmp = choice;
        while (cin.fail() == 1 || (tmp - choice) != 0 || choice > 100001 || choice < -1)
        {
            cout << "Please try again (deposit below 100000 dollar)" << endl << endl;
            cout << "Please write down the deposit amount(-1 for Exit) : ";
            cin.clear();
            cin.ignore(100, '\n');
            cin >> choice;
            tmp = choice;
        }
        return choice;
    }
    if (cmd == eDCMD_AskWithDrawal) {
        cout << "Please write down the withdrawal amount(-1 for Exit) : ";
        float choice = -1;
        int tmp = -1; //To check, choice must be integer
        cin.clear();
        cin.ignore(100, '\n');
        cin >> choice;
        tmp = choice;
        while (cin.fail() == 1 || (tmp - choice) != 0 || choice > 100001 || choice < -1)
        {
            cout << "Please try again (WithDrawal below 100000 dollar)" << endl << endl;
            cout << "Please write down the withdrawal amount(-1 for Exit) : ";
            cin.clear();
            cin.ignore(100, '\n');
            cin >> choice;
            tmp = choice;
        }
        return choice;
    }
    if (cmd == eDCMD_Finalize) {
        cout << "Thank you." << endl;
        cout << "Please remove your card" << endl;
    }
    return -1;
}
int Interface::display(int cmd, int cmd2) {
    cout << endl;
    if (cmd == eDCMD_AskPIN) {
        if (cmd2 == 0) {
            cout << "Card validated!!" << endl;
            cout << "Please enter your pin number" << endl;
        }
        else {
            cout << "The pin number is not valid." << endl;
            cout << "Please re-enter the pin number" << endl;
            cout << "attempts remaining(" << cmd2 << " / 3)" << endl;
        }
        float choice = -1;
        int tmp = -1; //To check, choice must be integer
        cin.clear();
        cin.ignore(100, '\n');
        cin >> choice;
        tmp = choice;
        if (cin.fail() == 1 || (tmp - choice) != 0)//if not a Pin number
        {
            return -1;
        }
        return choice;
    }
    if (cmd == eDCMD_ShowBalance) {
        cout << "Your Balance : " << cmd2 << endl << endl;
        return 1;

    }
    if (cmd == eDCMD_Success) {
        if (cmd2 == eDCMD_AskDeposite) {
            cout << "Success Deposite" << endl;
        }
        if (cmd2 == eDCMD_AskWithDrawal) {
            cout << "Success Withdrawal" << endl;
        }
    }
    if (cmd == eDCMD_Failed) {
        cout << endl << endl;
        if (cmd2 == eDCMD_AskCard) {
            cout << "Card is not valid. Thank you for using our service." << endl;
            cout << "ATM is ending..." << endl << endl;
        }
        else if (cmd2 == eDCMD_AskPIN) {
            cout << "PIN number is not valid. Thank you for using our service." << endl;
            cout << "ATM is ending..." << endl << endl;
        }
        else if (cmd2 == eDCMD_AskDeposite) {
            cout << "Your Deposite has failed. (Money overflow)." << endl;
        }
        else if (cmd2 == eDCMD_AskWithDrawal) {
            cout << "Your withdrawal has failed. Your balance is low." << endl;
        }
    }
    return -1;
}
int Interface::display(int cmd, vector<int> cmd2) {
    cout << endl;
    if (cmd == eDCMD_AskAccount) {
        cout << "You have (" << cmd2.size() << ") account" << endl;

        for (int i = 0; i < cmd2.size(); i++) {
            cout << "Account " << i << ", bank account number : " << cmd2[i] << endl;
        }
        cout << "Select Account (0~" << cmd2.size() - 1 << ")" << endl;
        float choice = -1;
        int tmp = -1; //To check, choice must be integer
        cin.clear();
        cin.ignore(100, '\n');
        cin >> choice;
        tmp = choice;
        while (cin.fail() == 1 || (tmp - choice) != 0 || choice > cmd2.size() - 1 || choice < 0)//if not a Account number
        {
            cout << "Please try again" << endl;
            cin.clear();
            cin.ignore(100, '\n');
            cin >> choice;
            tmp = choice;
        }
        return choice;
    }
    return -1;
}
int main(void) {
    ATM* atm1 = new ATM;
    ServerDB server;
    atm1->initialize(&server);
    int Atm1_Power = 1; //Bank manages the power of the atm1.
    while (Atm1_Power) { //While Atm1 Power on
        atm1->launch(&server);
    }
    delete atm1;
    return 0;

}