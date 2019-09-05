//Author Fredatovich P. 98141269
//Assignment 2

/*##############################
PROGRAM DESCRIPTION
Simple ATM simulation - reads two txt files (account listing "acct.txt" / transaction listing "tranz.txt")
Displays on screen the accounts in acct.txt, then asks to (c)ontinue.
Applies a (W)ithdrawl or (D)eposit amount from the tranz.txt to the acct.txt files.
Ignores invalmID accounts and transaction mTypes.
Displays accounts after processing.
###############################*/


#include <iostream>
#include <fstream>
#include <iomanip>

using namespace std;
const int MAX_ACCOUNTS = 100; //Maximum number ATM accounts
const int MAX_TRANS = 100;   //Maximum number of transactions to process

//=============================================================
//Classes

/**
 class Transaction represents the transactions to be processed.
 */
class Transaction{
public:
    /*
    * Class Transactions holds the data for the transactions to be applied to the accounts in ATM class.
     * As no dynamic memory is used, only a member initialiser list is provided with the default constructor.
     */
    Transaction(int id=0, char type ='0', double transAmount = 0.00);
    friend istream & operator >> (istream& ftrans, Transaction & trans);
    friend ostream& operator << (ostream& display, const Transaction & trans);
    int readTrans(Transaction trans[]);
    int getmID(){return mID;}
    char getmType(){return mType;}
    double getamount(){return mTransAmount;}
private:
    /*integer for transaction ID relating to account number*/
    int mID;
    /*char for transaction mType - only (W)ithdraw and (D)eposit accepted*/
    char mType;
    /*double for transaction amount to be processed*/
    double mTransAmount;
};

Transaction::Transaction(int id, char type, double transAmount):mID(id),mType(type),mTransAmount(transAmount){}

/**
 * Input operator overload to load values from file into array
 * @param   [in] ftrans istream variable copied by reference
 * @param   [in] trans Transaction array passed by reference to set values
 * @return  [out] ftrans istream variable to update the next item in the for loop
 */
istream & operator >> (istream& ftrans, Transaction & trans){
    ftrans>> trans.mID;
    ftrans>> trans.mType;
    ftrans>> trans.mTransAmount;
    return ftrans;
}

/**
 * Output operator overload.  NOT USED - ONLY PROVIDED FOR ASSIGNMENT REQUIREMENTS
 * @param [in] fact istream variable copied by reference
 * @param [in] atm array item to be display passed by reference
 * @return [out] fact istream variable for multiple display
 */
ostream& operator << (ostream& display, const Transaction& trans){
    display << trans.mID;
    display << trans.mType;
    display << trans.mTransAmount;
    return display;
}

/**
 * Public member method of class Transaction to read an input file and load into trans array with input overloading
 * @param trans[in] passed from main
 * @return numtrans - num of transactions read into aray
 */
int Transaction :: readTrans(Transaction trans[]){
    int numtrans=0;
    ifstream ftrns("tranz.txt");
    if(!ftrns){
        cerr << "ERROR opening input file";
        return -1;
    }
    string extract;
    getline(ftrns, extract);
    while(ftrns >> trans[numtrans]){
        if((trans[numtrans].mType == 'D')||(trans[numtrans].mType == 'W')){
            numtrans++;
        }
    }
    ftrns.close();
    return numtrans;
}
//=========================================

/*
 * Class ATM represents the accounts and there balances held in the ATM machine.
 * As no dynamic memory is used, only a member initialiser list is provided with the default constructor.
 */
class ATM{
public:
    ATM(int account=0, int balance=0, int transactionNum=0);

    friend istream & operator >> (istream& fact, ATM & atm);
    friend ostream& operator << (ostream& display, const ATM& acc);
    int readAccount(ATM atm[]);
    void applyTransaction(Transaction trans[], int num);
    int getaccount(){ return mAccount;}
    void setBalance(int amount){
        if(amount>=0){mBalance = amount;}
    }
    void setAccount(int number){mAccount=number;}
private:
    /*An int type mAccount that records the account number in the ATM*/
    int mAccount;
    /*A double type mBalance to record the balance of the account in the ATM*/
    double mBalance;
    /*A double type mTransactionNum to keep a record of the number of transactions per account*/
    int mTransactionNum;
};

ATM::ATM(int account, int balance, int transactionNum):mAccount(account), mBalance(balance), mTransactionNum(transactionNum){}


/**
 * Input operator overload.
 * @param [in] fact istream variable copied by reference
 * @param [in] atm array item to be display passed by reference
 * @return [out] fact istream variable to update the next item in the for loop
 */
istream & operator >>(istream& fact, ATM & atm){
    fact>> atm.mAccount;
    fact>>atm.mBalance;
    return fact;
}

/**
 * Output operator overload
 * @param   [in] display istream variable copied by reference
 * @param   [in] ATM acc array passed by reference to set values
 * @return  [out] display istream variable for multiple display
 */
ostream& operator<<(ostream& display, const ATM& acc){
    display << "ACCT#  " << setw(4) << acc.mAccount;
    display << "  Bal: " << setw(8) << acc.mBalance;
    display << "  Trans so far: " << setw(4) << acc.mTransactionNum;
    return display;
}

/**
 * Public member method of class ATM to read acct.txt file and load into atm array with input overloading.
 * Utilises data validation to eliminate negative values AFTER loading into array, hence the second if condition
 * to assess the last value in the loop.
 * @param [in] Array passed to function
 * @return [out] number of accounts correctly read.
 */
int ATM :: readAccount(ATM atm[]){
    int numAccounts=0;
    ifstream fact("acct.txt");
    if(!fact){
        cerr << "ERROR opening input file";
        return -1;
    }

    while(fact >> atm[numAccounts]){
        if((atm[numAccounts].mAccount < 0)||(atm[numAccounts].mBalance < 0.0)){
            numAccounts--;
        }
        numAccounts++;
    }
    if(atm[numAccounts].getaccount()<0){
        atm[numAccounts].setAccount(0);
        atm[numAccounts].setBalance(0);
    }
    fact.close();
    return numAccounts;
}

/**
 * Public member function of class ATM set up as a member to have access to private data members of class ATM.
 * As each account value is passed, the account value is checked against each entry in the transaction array,
 * updating each account with all transactions relating to that account, thereby updating the final value of the
 * account at the close of scope of the function.
 * Data validation with only positive values for amount and balance processed.
 * @param trans [in] Array of transactions is passed
 * @param num [in] number of transactions is passed to control the end iteration of the for loop.
 */
void ATM :: applyTransaction(Transaction trans[], int num){
    double tempBalance=0;
    for(int i=0; i<num; ++i) {
        if (mAccount > 0) {}
        if (mAccount == trans[i].getmID()) {
            if (trans[i].getmType() == 'D') {
                if (trans[i].getamount() > 0) {
                    tempBalance = mBalance + trans[i].getamount();
                    mBalance=tempBalance;
                    ++mTransactionNum;
                }
            }
            if (trans[i].getmType() == 'W') {
                if (trans[i].getamount() > 0) {
                    tempBalance = mBalance - trans[i].getamount();
                    if (tempBalance >= 0){
                        mBalance = tempBalance;
                        ++mTransactionNum;
                    }
                }
            }
        }
    }
}

// Function Prototypes
void info(); //Displays author info.

//###########################################################
int main(){
    info();

    ATM acctsArray[MAX_ACCOUNTS];
    Transaction transArray[MAX_TRANS];
    ATM acctObject; //object  that interfers with other objects. flase stitc
    Transaction transObject;

    int numAcc = acctObject.readAccount(acctsArray);
    if(numAcc < 0) {return 1;}
    int numTrans = transObject.readTrans(transArray);
    if(numTrans < 0) {return 1;}

    cout << "Initial data as in file \"acct.txt\"" << endl << numAcc << " correct accounts read from the file.\n" << endl;
    int i=0;
    for(ATM const &acct : acctsArray){
        if(i==numAcc){break;}
        cout << acct << endl;
        i++;
    }

    for(ATM & acct: acctsArray){
        acct.applyTransaction(transArray, numTrans);
    }

    cout << "\nAfter processing data in file \"tranz.txt\"" << endl << endl;
    i=0;
    for(ATM const &acct : acctsArray){
        if(i==numAcc){break;}
        cout << acct << endl;
        i++;
    }
    cout<<"------Done---"<<endl;

}
//########################################################

//Function Definitions
void info(){
    //Introduction header displayed
    cout << "Assignment 1 part 1\n";
    cout << "Fredatovich P. 98141269\n";
    cout << "159.234 OOP\n" << endl;
}