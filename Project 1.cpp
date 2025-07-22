#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <iomanip>
using namespace std;

const string ClientsFileName = "Clients.txt";

const string UsersFileName = "Users.txt";

enum enChoiceMenuScreen
{
	ShowClientList = 1,
	AddNewClient = 2,
	DeletClient = 3,
	UpdateClientInfo = 4,
	FindClient = 5,
	Transactions = 6,
	ManageUsers = 7,
	LogOut = 8
};

enum enChoiceManageUsersMenuScreen
{
	ShowUsertList = 1,
	AddNewUser = 2,
	DeletCUser = 3,
	UpdateUserInfo = 4,
	FindUser = 5,
	MainMenue = 6


};

enum enPermissionAccess
{

  PerListClients = 1,
  PerAddNewClients = 2,
  PerDeleteClients = 4,
  PerUpdateClients = 8,
  PerFindClients = 16

};

struct sClient
{
	string AccountNumber;
	string PinCode;
	string Name;
	string Phone;
	double AccountBalance;
	bool MarkForDelete = false;
	bool MarkForUpdate = false;
};

struct sUsers
{
	string UserName;
	string Password;
	int Permissions;

	bool MarkUserForUpdate = false;
	bool MarkUserForDelete = false;

};

vector<string> SplitString(string S1, string Delim)
{
	vector<string> vString;
	size_t pos = 0;
	string sWord;
	while ((pos = S1.find(Delim)) != std::string::npos)
	{
		sWord = S1.substr(0, pos);
		if (sWord != "")
		{
			vString.push_back(sWord);
		}
		S1.erase(0, pos + Delim.length());
	}
	if (S1 != "")
	{
		vString.push_back(S1);
	}
	return vString;
}

sClient ConvertLinetoRecord(string Line, string Seperator = "#//#")
{
	sClient Client;
	vector<string> vClientData;
	vClientData = SplitString(Line, Seperator);
	Client.AccountNumber = vClientData[0];
	Client.PinCode = vClientData[1];
	Client.Name = vClientData[2];
	Client.Phone = vClientData[3];
	Client.AccountBalance = stod(vClientData[4]);
	Client.MarkForDelete = false;
	return Client;
}

string ConvertRecordToLine(sClient Client, string Seperator = "#//#")
{
	string stClientRecord = "";
	stClientRecord += Client.AccountNumber + Seperator;
	stClientRecord += Client.PinCode + Seperator;
	stClientRecord += Client.Name + Seperator;
	stClientRecord += Client.Phone + Seperator;
	stClientRecord += to_string(Client.AccountBalance);
	return stClientRecord;
}

sUsers ConvertLinetoRecordForUsers(string Line, string Seperator = "#//#")
{
	sUsers Users;
	vector<string> vUserData;
	vUserData = SplitString(Line, Seperator);
	Users.UserName = vUserData[0];
	Users.Password = vUserData[1];
	Users.Permissions = stoi(vUserData[2]);
	return Users;
}

string ConvertRecordToLineForUsers(sUsers Users, string Seperator = "#//#")
{
	string stUserRecord = "";
	stUserRecord += Users.UserName + Seperator;
	stUserRecord += Users.Password + Seperator;
	stUserRecord += to_string(Users.Permissions);

	return stUserRecord;
}

vector <sClient> LoadClientsDataFromFile(string ClientsFileName)
{
	vector <sClient> vClients;
	fstream MyFile;
	MyFile.open(ClientsFileName, ios::in);
	if (MyFile.is_open())
	{
		string Line;
		sClient Client;
		while (getline(MyFile, Line))
		{
			Client = ConvertLinetoRecord(Line);
			vClients.push_back(Client);
		}
		MyFile.close();
	}
	return vClients;
}

vector <sUsers> LoadUsersDataFromFileForUser(string UsersFileName)
{
	vector <sUsers> vUsers;
	fstream MyFile;

	MyFile.open(UsersFileName, ios::in);
	if (MyFile.is_open())
	{
		string Line;
		sUsers User;
		while (getline(MyFile, Line))
		{
			User = ConvertLinetoRecordForUsers(Line);
			vUsers.push_back(User);
		}
		MyFile.close();
	}
	return vUsers;



}

vector <sClient> SaveCleintsDataToFile(string FileName, vector<sClient> vClients)
{
	fstream MyFile;
	MyFile.open(FileName, ios::out);
	string DataLine;
	if (MyFile.is_open())
	{
		for (sClient C : vClients)
		{
			DataLine = ConvertRecordToLine(C);
			MyFile << DataLine << endl;
		}
		MyFile.close();
	}
	return vClients;
}

vector <sUsers> SaveUsersDataToFileForUser(string FileName, vector<sUsers> vUsers)
{
	fstream MyFile;
	MyFile.open(FileName, ios::out);
	string DataLine;

	if (MyFile.is_open())
	{
		for (sUsers U : vUsers)
		{
			DataLine = ConvertRecordToLineForUsers(U);
			MyFile << DataLine << endl;
		}
		MyFile.close();
	}
	return vUsers;
}

vector <sClient> SaveCleintsDataToFileForDelete(string FileName, vector<sClient> vClients)
{

	fstream MyFile;
	MyFile.open(FileName, ios::out);
	string DataLine;
	if (MyFile.is_open())
	{
		for (sClient C : vClients)
		{
			if (C.MarkForDelete == false)
			{
				DataLine = ConvertRecordToLine(C);
				MyFile << DataLine << endl;
			}
		}
		MyFile.close();
	}
	return vClients;
}

vector <sUsers> SaveCleintsDataToFileForDeleteForUser(string FileName, vector<sUsers> vUsers)
{

	fstream MyFile;
	MyFile.open(FileName, ios::out);
	string DataLine;
	if (MyFile.is_open())
	{
		for (sUsers &U : vUsers)
		{
			if (U.MarkUserForDelete == false)
			{
				DataLine = ConvertRecordToLineForUsers(U);
				MyFile << DataLine << endl;
			}
		}
		MyFile.close();
	}
	return vUsers;
}

bool FindClientByAccountNumber(string AccountNumber, vector<sClient> vClients, sClient& Client)
{
	for (sClient C : vClients)
	{
		if (C.AccountNumber == AccountNumber)
		{
			Client = C;
			return true;
		}
	}
	return false;
}

bool FindClientByUserName(string UserName, vector<sUsers> vUsers, sUsers& Users)
{
	for (sUsers U : vUsers)
	{
		if (U.UserName == UserName)
		{
			Users = U;
			return true;
		}
	}
	return false;
}

sClient AddNewClients(string AccountNumber, vector<sClient>& vClients, sClient& Client)
{
	cout << "\nEnter Account Number :";
	getline(cin >> ws, AccountNumber);
	while (FindClientByAccountNumber(AccountNumber, vClients, Client) != false)
	{
		cout << "Client with [" << AccountNumber << "] already exists, Enter another Account Number?";
		getline(cin, AccountNumber);
	}
	Client.AccountNumber = AccountNumber;
	cout << "Enter Pin Code : ";
	getline(cin, Client.PinCode);
	cout << "Enter Name : ";
	getline(cin, Client.Name);
	cout << "Enter Phone : ";
	getline(cin, Client.Phone);
	cout << "Enter Account Balance : ";
	cin >> Client.AccountBalance;
	vClients.push_back(Client);
	return Client;
}

char readMore()
{
	char c;
	cout << "\n\nClient Added Successfully, Do you want to add more clients? 'y' or 'n': ";
	cin >> c;
	cin.ignore(1, '\n');
	return tolower(c);
}

char readUsersMore()
{
	char c;
	cout << "\n\nUser Added Successfully, Do you want to add more users? 'y' or 'n': ";
	cin >> c;
	cin.ignore(1, '\n');
	return tolower(c);
}

bool MarkClientForDeleteByAccountNumber(string AccountNumber, vector <sClient>& vClients)
{
	for (sClient& C : vClients)
	{
		if (C.AccountNumber == AccountNumber)
		{
			C.MarkForDelete = true;
			return true;
		}
	}
	return false;
}

bool MarkUserForDeleteByUserName(string UserName, vector <sUsers>& vUsers)
{
	for (sUsers& U : vUsers)
	{
		if (U.UserName == UserName)
		{
			U.MarkUserForDelete = true;
			return true;
		}
	}
	return false;
}

bool MarkClientForUpdateByAccountNumber(string AccountNumber, vector <sClient>& vClients)
{
	for (sClient& C : vClients)
	{
		if (C.AccountNumber == AccountNumber)
		{
			C.MarkForUpdate = true;
			return true;
		}
	}
	return false;
}

bool MarkUserForUpdateByUserName(string UserName, vector <sUsers>vUsers)
{
	for (sUsers& U: vUsers)
	{
		if (U.UserName == UserName)
		{
			U.MarkUserForUpdate = true;
			return true;
		}
	}
	return false;
}

void PrintClientCard(sClient Client)
{
	cout << "\nThe following are the client details:\n";
	cout << "\n------------------------------------------\n";
	cout << "Account Number: " << Client.AccountNumber;
	cout << "\nPin Code     : " << Client.PinCode;
	cout << "\nName         : " << Client.Name;
	cout << "\nPhone        : " << Client.Phone;
	cout << "\nAccount Balance: " << Client.AccountBalance << endl;
	cout << "------------------------------------------\n";
}

void PrintUsertCard(sUsers User)
{
	cout << "\nThe following are the User details:\n";
	cout << "\n------------------------------------------\n";
	cout << "User Name : " << User.UserName;
	cout << "\nPasswor : " << User.Password;
	cout << "\nPermissions  : " << User.Permissions;
	cout << "\n------------------------------------------\n";
}

string ReadClientAccountNumber()
{
	string AccountNumber = "";
	cout << "\nPlease enter AccountNumber? ";
	cin >> AccountNumber;
	return AccountNumber;
}

string ReadUserName()
{
	string UserName = "";
	cout << "\nPlease enter User Name? ";
	cin >> UserName;
	return UserName;
}

bool DeleteClientByAccountNumber(string AccountNumber, vector<sClient>& vClients)
{
	sClient Client;
	char Answer = 'n';
	if (FindClientByAccountNumber(AccountNumber, vClients, Client))
	{
		PrintClientCard(Client);
		cout << "\nAre you sure you want delete this client? y/n ?";
		cin >> Answer;
		if (Answer == 'y' || Answer == 'Y')
		{
			MarkClientForDeleteByAccountNumber(AccountNumber, vClients);
			SaveCleintsDataToFileForDelete(ClientsFileName, vClients);
			cout << "\nClient Deleted Successfully.\n\n";
			vClients = LoadClientsDataFromFile(ClientsFileName);
			return true;
		}
	}
	else
	{	
		cout << "\nClient with Account Number (" << AccountNumber << ") Not Found!\n";
		return false;
	}
	return false;
}

bool DeleteClientByUserName(string UserName, vector <sUsers>vUsers)
{
	sUsers User;
	char Answer = 'n';
	if (FindClientByUserName(UserName, vUsers, User))
	{
		PrintUsertCard(User);
		cout << "\nAre you sure you want delete this User? y/n ?";
		cin >> Answer;
		if (Answer == 'y' || Answer == 'Y')
		{
			MarkUserForDeleteByUserName(UserName, vUsers);
			SaveCleintsDataToFileForDeleteForUser(UsersFileName, vUsers);

			cout << "\nClient Deleted Successfully.\n\n";
			vUsers = LoadUsersDataFromFileForUser(UsersFileName);
			return true;
		}
	}
	else
	{
		cout << "\nClient with Account Number (" << UserName << ") Not Found!\n";
		return false;
	}
	return false;
}

void UpdateDataClient(string AcountNumber, vector<sClient>& vClients)
{
	for (sClient& C : vClients)
	{
		if (AcountNumber == C.AccountNumber)
		{
			cout << "\n\n\nEnter Pin Code : ";
			getline(cin >> ws, C.PinCode);
			cout << "Enter Name : ";
			getline(cin, C.Name);
			cout << "Enter Phone : ";
			getline(cin, C.Phone);
			cout << "Enter Account Balance : ";
			cin >> C.AccountBalance;
			break;
		}
	}
}

void UpdateDataUser(string UserName, vector<sUsers>& vClients)
{
	for (sUsers& U : vClients)
	{
		if (UserName == U.UserName)
		{
			cout << "\n\n\nEnter Password : ";
			getline(cin >> ws, U.Password);
			
			break;
		}
	}
}

bool UpdateClientByAccountNumber(string AccountNumber, vector<sClient>& vClients)
{
	sClient Client;
	char Answer = 'n';
	if (FindClientByAccountNumber(AccountNumber, vClients, Client))
	{
		PrintClientCard(Client);
		cout << "\nAre you sure you want Update this client? y/n ?";
		cin >> Answer;
		if (Answer == 'y' || Answer == 'Y')
		{
			UpdateDataClient(AccountNumber, vClients);
			SaveCleintsDataToFile(ClientsFileName, vClients);
			cout << "\nClient Updated Successfully.\n";
			return true;
		}
	}
	else
	{
		cout << "\nClient with Account Number (" << AccountNumber << ") Not Found!\n";
		return false;
	}
	return false;
}

bool UpdateUserByUserName(string UserName, vector<sUsers>& vUsers)
{
	sUsers Client;
	char Answer = 'n';
	if (FindClientByUserName(UserName, vUsers, Client))
	{
		PrintUsertCard(Client);
		cout << "\nAre you sure you want Update this User? y/n ?";
		cin >> Answer;
		if (Answer == 'y' || Answer == 'Y')
		{
			UpdateDataUser(UserName, vUsers);
			SaveUsersDataToFileForUser(UsersFileName, vUsers);
			cout << "\nUser Updated Successfully.\n";
			return true;
		}
	}
	else
	{
		cout << "\nUser with Account Number (" << UserName << ") Not Found!\n";
		return false;
	}
	return false;
}

void PrintClientRecord(sClient Client)
{
	cout << "| " << setw(15) << left << Client.AccountNumber;
	cout << "| " << setw(10) << left << Client.PinCode;
	cout << "| " << setw(40) << left << Client.Name;
	cout << "| " << setw(12) << left << Client.Phone;
	cout << "| " << setw(12) << left << Client.AccountBalance;
}

void PrintAllClientsData(vector<sClient> vClients)
{
	cout << "\n\t\t\t\t\tClient List (" << vClients.size() << ") Client(s).";
	cout << "\n_______________________________________________________";
	cout << "_________________________________________\n" << endl;
	cout << "| " << left << setw(15) << "Accout Number";
	cout << "| " << left << setw(10) << "Pin Code";
	cout << "| " << left << setw(40) << "Client Name";
	cout << "| " << left << setw(12) << "Phone";
	cout << "| " << left << setw(12) << "Balance";
	cout << "\n_______________________________________________________";
	cout << "_________________________________________\n" << endl;
	for (sClient Client : vClients)
	{
		PrintClientRecord(Client);
		cout << endl;
	}
	cout << "\n_______________________________________________________";
	cout << "_________________________________________\n" << endl;
}

void AddClientScreen(string AccountNumber, vector<sClient>& vClients, sClient& Client)
{
	cout << "\n_______________________________________\n\n";
	cout << "\tAdding New Client Screen  \n";
	cout << "_______________________________________\n\n";
	cout << "Adding New Client :  \n";
	AddNewClients(AccountNumber, vClients, Client);
	SaveCleintsDataToFile(ClientsFileName, vClients);
	while (readMore() == 'y')
	{
		cout << "\n\n";
		AddNewClients(AccountNumber, vClients, Client);
		SaveCleintsDataToFile(ClientsFileName, vClients);
	}
}

void MainMenueScreen()
{
	cout << "===================================================\n";
	cout << "\t\tMain Menue Screen\n";
	cout << "===================================================\n";
	cout << "\t[1] Show ClientList.\n";
	cout << "\t[2] Add New Client.\n";
	cout << "\t[3] Delet Client.\n";
	cout << "\t[4] Update ClientInfo.\n";
	cout << "\t[5] Find Client.\n";
	cout << "\t[6] Transactions.\n";
	cout << "\t[7] Manage Users.\n";
	cout << "\t[8] Logout.\n";
	cout << "===================================================\n";
}

int ReturnChoiceMenueScreen()
{
	system("cls");
	MainMenueScreen();
	int choice;
	cout << "Choose what do you want to do? [1 to 8]: ";
	cin >> choice;
	system("cls");
	return choice;
}

void ReturnMenueScreenForUser()
{
	system("cls");
	MainMenueScreen();
	system("cls");
}

void DeleteClientScreen(string AcountNumber, vector<sClient>& vClients)
{
	cout << "\n------------------------------------------\n";
	cout << "\tDelete Client Screen \n";
	cout << "------------------------------------------\n";
	MarkClientForDeleteByAccountNumber(AcountNumber, vClients);
	DeleteClientByAccountNumber(ReadClientAccountNumber(), vClients);
}

void UpdateClientInfoScreen(string AcountNumber, vector<sClient>& vClients)
{
	cout << "\n------------------------------------------\n";
	cout << "\tUpdate Client Screen \n";
	cout << "------------------------------------------\n";
	MarkClientForUpdateByAccountNumber(AcountNumber, vClients);
	UpdateClientByAccountNumber(ReadClientAccountNumber(), vClients);
}

void FindClientsScreen(vector<sClient>& vClients, sClient& Client)
{
	cout << "\n------------------------------------------\n";
	cout << "\tFind Client Screen \n";
	cout << "------------------------------------------\n";
	string AcountNumber = ReadClientAccountNumber();
	if ((FindClientByAccountNumber(AcountNumber, vClients, Client)) != false)
	{
		PrintClientCard(Client);
		cout << "\n\n";
	}
	else
		cout << "\nClient with Account Number[" << AcountNumber << "] is not found!\n\n";
}

short ReadTransactionsMenueOption()
{
	cout << "Choose what do you want to do? [1 to 4]? ";
	short Choice = 0;
	cin >> Choice;
	return Choice;
}

void PrintClientRecordBalanceLine(sClient Client)
{
	cout << "| " << left << setw(15) << Client.AccountNumber;
	cout << "| " << left << setw(40) << Client.Name;
	cout << "| " << left << setw(12) << Client.AccountBalance;
}

void ShowTotalBalances()
{
	vector <sClient> vClients = LoadClientsDataFromFile(ClientsFileName);
	cout << "\n\t\t\t\t\tBalances List (" << vClients.size() << ") Client(s).";
	cout << "\n_______________________________________________________";
	cout << "_________________________________________\n" << endl;
	cout << "| " << left << setw(15) << "Account Number";
	cout << "| " << left << setw(40) << "Client Name";
	cout << "| " << left << setw(12) << "Balance";
	cout << "\n_______________________________________________________";
	cout << "_________________________________________\n" << endl;
	double TotalBalances = 0;
	if (vClients.size() == 0)
	{
		cout << "\t\t\t\tNo Clients Available In the System!";
	}
	else
	{
		for (sClient Client : vClients)
		{
			PrintClientRecordBalanceLine(Client);
			TotalBalances += Client.AccountBalance;
			cout << endl;
		}
	}
	cout << "\n_______________________________________________________";
	cout << "_________________________________________\n" << endl;
	cout << "\t\t\t\t\t   Total Balances = " << TotalBalances;
}

bool DepositBalanceToClientByAccountNumber(string AccountNumber, double Amount, vector <sClient>& vClients)
{
	char Answer = 'n';
	cout << "\n\nAre you sure you want to perform this transaction? (y/n): ";
	cin >> Answer;
	if (Answer == 'y' || Answer == 'Y')
	{
		for (sClient& C : vClients)
		{
			if (C.AccountNumber == AccountNumber)
			{
				C.AccountBalance += Amount;
				SaveCleintsDataToFile(ClientsFileName, vClients);
				cout << "\n\nDone Successfully. New balance is: " << C.AccountBalance << endl;
				return true;
			}
		}
		cout << "\nAccount not found!\n";
		return false;
	}
	cout << "\nTransaction canceled.\n";
	return false;
}

void ShowWithDrawScreen()
{
	cout << "\n-----------------------------------\n";
	cout << "\tWithdraw Screen";
	cout << "\n-----------------------------------\n";
	sClient Client;
	vector <sClient> vClients = LoadClientsDataFromFile(ClientsFileName);
	string AccountNumber = ReadClientAccountNumber();
	while (!FindClientByAccountNumber(AccountNumber, vClients, Client))
	{
		cout << "\nClient with [" << AccountNumber << "] does not exist.\n";
		AccountNumber = ReadClientAccountNumber();
	}
	PrintClientCard(Client);
	double Amount = 0;
	cout << "\nPlease enter withdraw amount? ";
	cin >> Amount;
	while (Amount > Client.AccountBalance)
	{
		cout << "\nAmount Exceeds the balance, you can withdraw up to : " << Client.AccountBalance << endl;
		cout << "Please enter another amount? ";
		cin >> Amount;
	}
	DepositBalanceToClientByAccountNumber(AccountNumber, -Amount, vClients);
}

void TransactionsMenueScreen(vector<sClient>& vClients)
{
	while (true)
	{
		system("cls");
		cout << "\n-----------------------------------\n";
		cout << "\tTransactions Menu\n";
		cout << "-----------------------------------\n";
		cout << "[1] Deposit\n";
		cout << "[2] Withdraw\n";
		cout << "[3] Show Total Balances\n";
		cout << "[4] Main Menu\n";
		cout << "-----------------------------------\n";
		short Choice = ReadTransactionsMenueOption();
		switch (Choice)
		{
		case 1:
		{
			string AccountNumber = ReadClientAccountNumber();
			sClient Client;
			if (FindClientByAccountNumber(AccountNumber, vClients, Client))
			{
				PrintClientCard(Client);
				double Amount;
				cout << "\nPlease enter deposit amount: ";
				cin >> Amount;
				DepositBalanceToClientByAccountNumber(AccountNumber, Amount, vClients);
			}
			else
			{
				cout << "\nAccount not found!\n";
			}
			system("pause");
			break;
		}
		case 2:
		{
			ShowWithDrawScreen();
			system("pause");
			break;
		}
		case 3:
		{
			ShowTotalBalances();
			system("pause");
			break;
		}
		case 4:
		default:
			return;
		}
	}
}

void LoginScreen()
{

	cout << "\n========================================\n";
	cout << "\tLogin Screen";
	cout << "\n========================================\n";

}

bool CheckValdtionForUser(vector<sUsers> vUsers, sUsers& User)
{

	string inputUsername, inputPassword;
	cout << "Enter User Name : ";
	getline(cin >> ws, inputUsername);

	cout << "Enter Password : ";
	getline(cin >> ws, inputPassword);

	for (sUsers user : vUsers)
	{
		if (user.UserName == inputUsername && user.Password == inputPassword)
		{
			User = user;
			return true;
		}
	}

	return false;
}

void LoginScreenHandle(vector<sUsers> vUsers, sUsers& User)
{
	bool check;
	LoginScreen();
	do
	{
		check = CheckValdtionForUser(vUsers, User);

		if (!check)
		{
			system("cls");
			LoginScreen();
			cout << "Invalid UserName/Password!\n";
		}
		else
		{
			ReturnMenueScreenForUser();
		}

	} while (!check);
}

void  ManageUsersMenueScreen()
{
	cout << "===================================================\n";
	cout << "\t\tManage User Menue Screen\n";
	cout << "===================================================\n";
	cout << "\t[1] List Users.\n";
	cout << "\t[2] Add New User.\n";
	cout << "\t[3] Delet User.\n";
	cout << "\t[4] Update User.\n";
	cout << "\t[5] Find Client.\n";
	cout << "\t[6] Main Menue.\n";
	cout << "===================================================\n";
}

short ReturnChoiceManageUsersMenueScreen()
{
	ManageUsersMenueScreen();
	int choice;
	cout << "Choose what do you want to do? [1 to 6]: ";
	cin >> choice;
	return choice;
}

void PrintUserRecordForUser(sUsers User)
{
	cout << "| " << setw(15) << left << User.UserName;
	cout << "| " << setw(10) << left << User.Password;
	cout << "| " << setw(40) << left << User.Permissions;

}

void PrintAllUsersData(vector<sUsers>& vUsers)
{
	
	vUsers = LoadUsersDataFromFileForUser(UsersFileName);

	cout << "\n\t\t\t\t\tUser List (" << vUsers.size() << ") User(s).";
	cout << "\n_______________________________________________________";
	cout << "_________________________________________\n" << endl;
	cout << "| " << left << setw(15) << "User Name";
	cout << "| " << left << setw(10) << "Password";
	cout << "| " << left << setw(40) << "Permissions";
	cout << "\n_______________________________________________________";
	cout << "_________________________________________\n" << endl;

	if (vUsers.size() == 0)
	{
		cout << "\t\t\t\tNo Users Available In the System!";
	}
	else
	{
		for (sUsers User : vUsers)
		{
			PrintUserRecordForUser(User);
			cout << endl;
		}
	}
	cout << "\n_______________________________________________________";
	cout << "_________________________________________\n" << endl;
}

bool FindUsertByUserName(string UserName, vector<sUsers> vUsers, sUsers& User)
{
	for (sUsers U : vUsers)
	{
		if (U.UserName == UserName)
		{
			User = U;
			return true;
		}
	}
	return false;
}

short ReadPermissionsToSet()
{
	short Permissions = 0;


	char Choice = 'n';
	cout << "\nDo you want to give full access? y/n ? ";
	cin >> Choice;

	if (Choice == 'n' || Choice == 'N')
	{
		cout << "\n\nDo you want to give access to :";
		cout << "\n\nShow Client List? y/n? ";
		cin >> Choice;
		if (Choice == 'y' || Choice == 'Y')
			Permissions |= PerListClients;

		cout << "\n\nAdd New Client? y/n? ";
		cin >> Choice;
		if (Choice == 'y' || Choice == 'Y')
			Permissions |= PerAddNewClients;

		cout << "\n\nDelete Client? y/n? ";
		cin >> Choice;
		if (Choice == 'y' || Choice == 'Y')
			Permissions |= PerDeleteClients;

		cout << "\n\nUpdate Client? y/n? ";
		cin >> Choice;
		if (Choice == 'y' || Choice == 'Y')
			Permissions |= PerUpdateClients;

		cout << "\n\nFind Client? y/n? ";
		cin >> Choice;
		if (Choice == 'y' || Choice == 'Y')
			Permissions |= PerFindClients;
	}
	else
		Permissions = -1;
	return Permissions;
}

bool HasPermission(enPermissionAccess Permission, sUsers& User)
{
	if ((User.Permissions & Permission) != Permission)
	{
		cout << "\n------------------------------------\n";
		cout << "Access Denied \nYou don't have permission to do this action.\nPlease contact your Admin.";
		cout << "\n------------------------------------\n";
		system("pause");
		system("cls");
		return false;
	}
	return true;
}

sUsers AddNewUsers(string UserName, vector<sUsers>& vUser, sUsers& User)
{
	cout << "\nEnter UserName:";
	getline(cin >> ws, UserName);
	while (FindUsertByUserName(UserName, vUser, User) != false)
	{
		cout << "User with [" << UserName << "] already exists, Enter another User Name?";
		getline(cin, UserName);
	}
	User.UserName = UserName;

	string password;

	cout << "Enter Password  : ";
	cin >> password;
	User.Password = password;

	User.Permissions = ReadPermissionsToSet();



	vUser.push_back(User);
	return User;
}

void AddUserScreen(string UserName, vector<sUsers>& vUser, sUsers& User)
{
	cout << "\n_______________________________________\n\n";
	cout << "\tAdding New User Screen  \n";
	cout << "_______________________________________\n\n";
	cout << "Adding New User :  \n";
	AddNewUsers(UserName, vUser, User);
	SaveUsersDataToFileForUser(UsersFileName, vUser);

	while (readUsersMore() == 'y')
	{
		cout << "\n\n";
		AddNewUsers(UserName, vUser, User);
		SaveUsersDataToFileForUser(UsersFileName, vUser);
		
	}
}

void UpdateUserInfoScreen(string UserName, vector<sUsers>& vUsers)
{
	cout << "\n------------------------------------------\n";
	cout << "\tUpdate User Screen \n";
	cout << "------------------------------------------\n";
	MarkUserForUpdateByUserName(UserName, vUsers);
	UpdateUserByUserName(ReadUserName(), vUsers);
}

void DeleteUserScreen(string UserName, vector<sUsers>& vUsers)
{
	cout << "\n------------------------------------------\n";
	cout << "\tDelete User Screen \n";
	cout << "------------------------------------------\n";
	MarkUserForDeleteByUserName(UserName, vUsers);
	DeleteClientByUserName(ReadUserName(), vUsers);
}

void FindUserScreen(string UserName, vector<sUsers>& vUsers, sUsers& User)
{
	cout << "\n------------------------------------------\n";
	cout << "\nFind User Screen \n";
	cout << "------------------------------------------\n";
	string stUserName = ReadUserName();

	if (FindUsertByUserName(stUserName, vUsers, User))
		PrintUsertCard(User);
	else
		cout << "\nThis User Name  [" << stUserName << "] isn't Found! \n";
}

void ReturnManageScreen()
{

	cout << "\n\nPress any key to go back to Transactions Menue...";
	system("pause>0");
	system("cls");
}

void HandelManageUsersMenueScreen(string UserName, vector<sUsers>& vUsers, sUsers& User)

{

	while (true)
	{
		int Choice = ReturnChoiceManageUsersMenueScreen();
		system("cls");

		switch (Choice)
		{
		case enChoiceManageUsersMenuScreen::ShowUsertList:
		{
			PrintAllUsersData(vUsers);
			ReturnManageScreen();
			break;
		}
		case enChoiceManageUsersMenuScreen::AddNewUser:
		{
			AddUserScreen(UserName, vUsers, User);
			ReturnManageScreen();
			break;
		}
		case enChoiceManageUsersMenuScreen::DeletCUser:
		{
			DeleteUserScreen(UserName, vUsers);
			ReturnManageScreen();
			break;
		}
		case enChoiceManageUsersMenuScreen::UpdateUserInfo:
		{
			UpdateUserInfoScreen(UserName, vUsers);
			ReturnManageScreen();
			break;
		}
		case enChoiceManageUsersMenuScreen::FindUser:
		{
			FindUserScreen(UserName, vUsers, User);
			ReturnManageScreen();
			break;
		}
		case enChoiceManageUsersMenuScreen::MainMenue:
			return;
			

		}


	}


}

void HandelMainMenueScreen(string AccountNumber, string UserName, vector<sClient>& vClients, sClient& Client, vector<sUsers>& vUsers, sUsers& User)	
{

	
	while (true)
	{
		

		system("cls");
		
		switch (ReturnChoiceMenueScreen())
		{
			
		case enChoiceMenuScreen::ShowClientList:
			if (!HasPermission(enPermissionAccess::PerListClients, User)) break;

			PrintAllClientsData(vClients);
			ReturnManageScreen();
			break;

		case enChoiceMenuScreen::AddNewClient:
			if (!HasPermission(enPermissionAccess::PerAddNewClients, User)) break;

			AddClientScreen(AccountNumber, vClients, Client);
			ReturnManageScreen();
			break;

		case enChoiceMenuScreen::DeletClient:
			if (!HasPermission(enPermissionAccess::PerDeleteClients, User)) break;

			DeleteClientScreen(AccountNumber, vClients);
			ReturnManageScreen();
			break;

		case enChoiceMenuScreen::UpdateClientInfo:
			if (!HasPermission(enPermissionAccess::PerUpdateClients, User)) break;

			UpdateClientInfoScreen(AccountNumber, vClients);
			ReturnManageScreen();
			break;

		case enChoiceMenuScreen::Transactions:
			TransactionsMenueScreen(vClients);
			ReturnManageScreen();
			break;

		case enChoiceMenuScreen::FindClient:
			if (!HasPermission(enPermissionAccess::PerFindClients, User)) break;

			FindClientsScreen(vClients, Client);
			ReturnManageScreen();
			break;

		case enChoiceMenuScreen::ManageUsers:
			HandelManageUsersMenueScreen(UserName, vUsers, User);
			break;

		case enChoiceMenuScreen::LogOut:
			LoginScreenHandle(vUsers, User);
			break;
		}
	}
}

void BankFileSystem()
{

	vector <sClient> vClients = LoadClientsDataFromFile(ClientsFileName);
	sClient Client;
	string AccountNumber;
	string UserName;

	vector <sUsers> vUsers = LoadUsersDataFromFileForUser(UsersFileName);
	sUsers User;
	LoginScreenHandle(vUsers, User);

	HandelMainMenueScreen(AccountNumber, UserName, vClients, Client, vUsers, User);
			

}

int main()
{

	BankFileSystem();
	//Thanks for Wathching :-)
	return 0;
}
