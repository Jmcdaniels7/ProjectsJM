#include <iostream>
#include <string>
#include <sqlite3.h>
#include <cctype>
#include <algorithm>
#include <regex>
#include <iomanip>
#include <climits>
#include <vector>
#include <map>
#include "clock.h"

/* Program name: Database Design Final Project
*  Author: Jacob McDaniels
*  Date last updated: 3/8/2025
* Purpose: Execute on design of database using C++ and coding concepts from assignments
*/

enum shopI
{
	SCROLL,
	POTION,
	SPEED,
	HAZELNUT,
	DRAGONSHEART
};

std::map<shopI, std::string> shopItems = {
	{SCROLL, "Fire Scroll"}, 
	{POTION, "Healing Potion"}, 
	{SPEED, "Broom Upgrade: Speed"}, 
	{HAZELNUT, "Hazelnut Broom of Mediocre Speed"}, 
	{DRAGONSHEART, "DragonHeart Broom of Grand Speed"}
};


int menu();

//reports
void printCP(sqlite3_stmt *res, int rowsPerPage, int startNum);
void printCusP(sqlite3 *db, int &cus);
void printCV(sqlite3_stmt *res, int rowsPerPage, int startNum);
void printCusV(sqlite3 *db, int &cus);
void cusPurchases(sqlite3 *db, int &menuChoice);
void cusVisits(sqlite3 *db, int& menuChoice);
void reports(sqlite3 *mydb, int &menuChoice);

//updates
void changeFname(sqlite3 *db, int &cus);
void changeLname(sqlite3 *db, int &cus);
void clockOut(std::string &newOut, std::string cIN);
bool clockedIN(sqlite3 *db, std::string &cIN, int &cus);
int changes(int &cus);
void updateVisit(sqlite3 *db, std::string &cIN, int &cus);
void updates(sqlite3 *db, int &menuChoice);

//delete
void deleteCus(sqlite3 *db, int &cus);
void deleting(sqlite3 *db, int &menuChoice);

//purchase
int startPurchase(sqlite3 *db);
void insertItemSale(sqlite3 *mydb, int &pID, std::vector<int> &items);
void insertPurchase(sqlite3 *mydb, int &cus, double &pAmount);
void makePurchase(sqlite3 *, int &menuChoice);
void viewItems(sqlite3 *mydb, std::vector<int> &price, std::vector<int> &items);
void printItems(sqlite3_stmt *res, int rowsPerPage, int startNum);

//customer new or existing clocking in
void visit(sqlite3 *, int &menuChoice);
void customerInfo(std::string &fname, std::string &lname, int &age, std::string &gender, std::string &house);
void newCustomer(sqlite3 *);
std::string clockIN(std::string &clocked, std::string &newIn);
void newVisit(sqlite3 *db, int &cusID);
void printCustomerPage(sqlite3_stmt *res, int rowsPerPage, int startNum);

// tools
void viewCustomer(sqlite3 *db, int &cus, int &menuChoice);
int rollback(sqlite3 *db);
bool checkForError(int rc, sqlite3 *db, sqlite3_stmt *r, std::string msg);
int commit(sqlite3 *db);
void resetStream();


int main()
{
	int menuChoice;

	//opening the DB
	sqlite3 *mydb;
	int rc = sqlite3_open_v2("hogwarts.db", &mydb, SQLITE_OPEN_READWRITE, NULL);

	if (rc != SQLITE_OK)
	{
		std::cout << "Error in connection: " << sqlite3_errmsg(mydb) << std::endl;

	}

	//starting main menu
	while (menuChoice != 6)
	{
		menuChoice = menu();

		//starting main menu choice
		switch(menuChoice)
		{
			case 1: visit(mydb, menuChoice); break;
			case 2: makePurchase(mydb, menuChoice); break;
			case 3: updates(mydb, menuChoice); break;
			case 4: deleting(mydb, menuChoice); break;
			case 5: reports(mydb, menuChoice); break;
			case 6: return 0; 
		}

	}
	
}

void printCP(sqlite3_stmt *res, int rowsPerPage, int startNum)
{
	int stop, i = 1;
	do
	{
		stop = sqlite3_step(res);
		if (stop != SQLITE_ROW)
			break;
		if(i == 1)
		{
			if (sqlite3_column_type(res, 0) != SQLITE_NULL)
				std::cout << "First Name: " << sqlite3_column_text(res, 0) << "\n";
			if (sqlite3_column_type(res, 1) != SQLITE_NULL)
				std::cout << "Last Name: " << sqlite3_column_text(res, 1) << "\n";
			if (sqlite3_column_type(res, 2) != SQLITE_NULL)
				std::cout << "Age: " << sqlite3_column_text(res, 2) << "\n";
			if (sqlite3_column_type(res, 3) != SQLITE_NULL)
				std::cout << "Gender: " << sqlite3_column_text(res, 3) << "\n";
			if (sqlite3_column_type(res, 4) != SQLITE_NULL)
				std::cout << "House at Hogwarts: " << sqlite3_column_text(res, 4) << "\n\n\n";

		}
		std::cout << i + startNum << ".      ";
		if (sqlite3_column_type(res, 5) != SQLITE_NULL)
			std::cout << "Purchase ID: " << sqlite3_column_text(res, 5) << "\n";
		if (sqlite3_column_type(res, 6) != SQLITE_NULL)
			std::cout << "        Purchase Amount: " << sqlite3_column_text(res, 6) << " galleons\n";
		if (sqlite3_column_type(res, 7) != SQLITE_NULL)
			std::cout << "        Date: " << sqlite3_column_text(res, 7) << "\n";
		std::cout << std::endl;
		i++;

	} while (i <= rowsPerPage);

}

void printCusP(sqlite3 *db, int &cus)
{
	std::string cuspQuery = "select f_name, l_name, age, gender, house_at_hogwarts, purchase_ID, purchase_amount, date from customer join purchase on customer.customer_ID = purchase.customer_ID where customer.customer_ID = @cus";

	sqlite3_stmt *res;

	int rc = sqlite3_prepare_v2(db, cuspQuery.c_str(), -1, &res, NULL);

	if (rc != SQLITE_OK)
	{
		sqlite3_finalize(res);
		std::cout << "There was an error with the customer purchase query: " << sqlite3_errmsg(db) << std::endl;
		std::cout << cuspQuery << std::endl;
		return;
	}

	rc = sqlite3_bind_int(res, sqlite3_bind_parameter_index(res, "@cus"), cus);
	if (checkForError(rc, db, res, "unable to update with customer ID."))
    {
        std::cout << cuspQuery << std::endl;
        sqlite3_finalize(res);
		rollback(db);
    }

	int columnCount = sqlite3_column_count(res);
	int i = 0, rowsPerPage, totalRows;
	
	std::cout << std::left;
	int result;

	do
	{
		result = sqlite3_step(res);
		i++;

	} while (result == SQLITE_ROW);
	totalRows = i - 1;
	sqlite3_reset(res);
	
	rowsPerPage = 100;

	i = 0;

	printCP(res, rowsPerPage, i);

}

void cusPurchases(sqlite3 *db, int &menuChoice)
{
	int cus;

	//choose a customer first
	viewCustomer(db, cus, menuChoice);
	std::cout << std::endl;

	//prepared statement of customer and their purchases
	printCusP(db, cus);
}

void printCV(sqlite3_stmt *res, int rowsPerPage, int startNum)
{

	int stop, i = 1;
	do
	{
		stop = sqlite3_step(res);
		if (stop != SQLITE_ROW)
			break;
		if(i == 1)
		{
			if (sqlite3_column_type(res, 0) != SQLITE_NULL)
				std::cout << "First Name: " << sqlite3_column_text(res, 0) << "\n";
			if (sqlite3_column_type(res, 1) != SQLITE_NULL)
				std::cout << "Last Name: " << sqlite3_column_text(res, 1) << "\n";
			if (sqlite3_column_type(res, 2) != SQLITE_NULL)
				std::cout << "Age: " << sqlite3_column_text(res, 2) << "\n";
			if (sqlite3_column_type(res, 3) != SQLITE_NULL)
				std::cout << "Gender: " << sqlite3_column_text(res, 3) << "\n";
			if (sqlite3_column_type(res, 4) != SQLITE_NULL)
				std::cout << "House at Hogwarts: " << sqlite3_column_text(res, 4) << "\n\n\n";

		}
		std::cout << i + startNum << ".      ";
		if (sqlite3_column_type(res, 5) != SQLITE_NULL)
			std::cout << "Visit ID: " << sqlite3_column_text(res, 5) << "\n";
		if (sqlite3_column_type(res, 8) != SQLITE_NULL)
			std::cout << "        Date: " << sqlite3_column_text(res, 8) << "\n";
		if (sqlite3_column_type(res, 6) != SQLITE_NULL)
			std::cout << "        Clocked In: " << sqlite3_column_text(res, 6) << "\n";
		if (sqlite3_column_type(res, 7) != SQLITE_NULL)
			std::cout << "        Clocked Out: " << sqlite3_column_text(res, 7) << "\n";
		std::cout << std::endl;
		i++;

	} while (i <= rowsPerPage);
	

}

void printCusV(sqlite3 *db, int &cus)
{

	std::string cusvQuery = "select f_name, l_name, age, gender, house_at_hogwarts, visit_ID, clock_in, clock_out, date from customer join visits on customer.customer_ID = visits.customer_ID where customer.customer_ID = @cus";

	sqlite3_stmt *res;

	int rc = sqlite3_prepare_v2(db, cusvQuery.c_str(), -1, &res, NULL);

	if (rc != SQLITE_OK)
	{
		sqlite3_finalize(res);
		std::cout << "There was an error with the customer visits query: " << sqlite3_errmsg(db) << std::endl;
		std::cout << cusvQuery << std::endl;
		return;
	}

	rc = sqlite3_bind_int(res, sqlite3_bind_parameter_index(res, "@cus"), cus);
	if (checkForError(rc, db, res, "unable to verify customer ID."))
    {
        std::cout << cusvQuery << std::endl;
        sqlite3_finalize(res);
		rollback(db);
    }

	int columnCount = sqlite3_column_count(res);
	int i = 0, rowsPerPage, totalRows;
	
	std::cout << std::left;
	int result;

	do
	{
		result = sqlite3_step(res);
		i++;

	} while (result == SQLITE_ROW);
	totalRows = i - 1;
	sqlite3_reset(res);
	
	rowsPerPage = 100;

	i = 0;

	printCV(res, rowsPerPage, i);

}

void cusVisits(sqlite3 *db, int& menuChoice)
{
	int cus;

	//choose a customer
	viewCustomer(db, cus, menuChoice);
	std::cout << std::endl;

	//prepared statment of customer and their visits
	printCusV(db, cus);
}

void reports(sqlite3 *mydb, int &menuChoice)
{
	int report;

	std::cout << "What reports would you like to run?" << std::endl;
	std::cout << "1. Customer Purchases" << std::endl;
	std::cout << "2. Customer Visits" << std::endl;
	std::cout << "3. Exit" << std::endl;

	std::cin >> report;

	while(!std::cin || report < 1 || report > 3)
	{
		std::cout << "Please choose a valid option 1-3" << std::endl << std::endl;

		std::cout << "What reports would you like to run?" << std::endl;
		std::cout << "1. Customer Purchases" << std::endl;
		std::cout << "2. Customer Visits" << std::endl;
		std::cout << "3. Exit" << std::endl;

		std::cin >> report;

		resetStream();

	}

	switch(report)
	{
		case 1: cusPurchases(mydb, menuChoice); break;
		case 2: cusVisits(mydb, menuChoice); break;
		case 3: std::cout << "No reports Ran...." << std::endl; break;
	}
}
void deleteCus(sqlite3 *db, int &cus)
{
	std::string delQuery = "delete from customer where customer_id = @cus";

	sqlite3_stmt *ress;
	int returnC = sqlite3_prepare_v2(db, delQuery.c_str(), -1, &ress, NULL);

	if (checkForError(returnC, db, ress, "unable to update visit."))
    {
        std::cout << delQuery << std::endl;
        sqlite3_finalize(ress);
		rollback(db);
    }

	returnC = sqlite3_bind_int(ress, sqlite3_bind_parameter_index(ress, "@cus"), cus);
	if (checkForError(returnC, db, ress, "unable to update with customer ID."))
    {
        std::cout << delQuery << std::endl;
        sqlite3_finalize(ress);
		rollback(db);
    }

	sqlite3_step(ress);
	sqlite3_finalize(ress);
}
void deleting(sqlite3 *db, int &menuChoice)
{
	int cus;
	std::string confirm;

	//delete customers
	viewCustomer(db, cus, menuChoice);

	std::cout << "Please confirm you would like to delete Customer: " << cus << " (Yes or No)" << std::endl;
	std::cin >> confirm;

	std::transform(confirm.begin(), confirm.end(), confirm.begin(), ::tolower);

	while(!std::cin || (confirm != "yes" && confirm != "no"))
	{
		std::cout << "Invalid Response" << std::endl << std::endl;
		std::cout << "Please confirm you would like to delete Customer: " << cus << " (Yes or No)" << std::endl;
		std::cin >> confirm;

		std::transform(confirm.begin(), confirm.end(), confirm.begin(), ::tolower);
		resetStream();
	}

	if (confirm == "yes")
	{
		deleteCus(db, cus);

	}
	else
	{
		std::cout << std::endl;
		std::cout << "Customer not deleted" << std::endl << std::endl;
	}
	
}

void clockOut(std::string &newOut, std::string cIN)
{
	std::string clocked;
	
	std::cout << "When did the customer leave the shop?" << std::endl;
	std::getline(std::cin >> std::ws, clocked);

	std::regex timeStr{
		R"(([01]?[0-9]|2[0-3]):([0-5][0-9]|0[0-9])\0?([aA][mM]|[pP][mM])?)"
	};

	std::smatch parts;

	std::smatch parts2;

	if(std::regex_match(clocked, parts, timeStr))
	{
		int hour = std::stoi(parts[1]);
		int minutes = std::stoi(parts[2]);
		
		std::string tod = parts[3];

		std::string todUpper = tod;
		std::transform(todUpper.begin(), todUpper.end(), todUpper.begin(), ::tolower);

		bool valid = true;

		// next 4 lines for not allowing clocked out to be before clocked in
		std::regex_match(cIN, parts2, timeStr);

		int hour2 = std::stoi(parts2[1]);
		int minutes2 = std::stoi(parts2[2]);
		std::string tod2 = parts2[3];

		try
		{
			clockType clock1(hour, minutes, 0, tod, TWELVE);
			clockType clock2(hour2, minutes2, 0, tod2, TWELVE);
		
			if(clock2 > clock1)
			{
				valid = false;

			}
		}
		catch(const std::exception& e)
		{
			std::cerr << e.what() << '\n';
			valid = false;
		}

		if (valid)
		{
			newOut = std::to_string(hour) + ":" + std::to_string(minutes) + tod;
		}

		while(!valid)
		{
			std::cout << "When did the customer leave the shop?" << std::endl;
			std::cin >> std::ws;
			std::getline(std::cin, clocked);

			std::regex timeStr{
				R"(([01]?[0-9]|2[0-3]):([0-5][0-9]|0[0-9])\0?([aA][mM]|[pP][mM])?)"
			};

			std::smatch parts;

			if(std::regex_match(clocked, parts, timeStr))
			{
				// I tried hour validation here too
				// parts of regex
				int hour = std::stoi(parts[1]);
				int minutes = std::stoi(parts[2]);
				
				std::string tod = parts[3];

				std::string todUpper = tod;
				std::transform(todUpper.begin(), todUpper.end(), todUpper.begin(), ::tolower);

				valid = true;

				try
				{
					clockType clock1(hour, minutes, 0, tod, TWELVE);
					clockType clock2(hour2, minutes2, 0, tod2, TWELVE);
				
					if(clock2 > clock1)
					{
						valid = false;

					}
				}
				catch(const std::exception& e)
				{
					std::cerr << e.what() << '\n';
					valid = false;
				}

				if (valid)
				{
					newOut = std::to_string(hour) + ":" + std::to_string(minutes) + tod;
				}

			}
		}

		
		
	}   
}
void updateVisit(sqlite3 *db, std::string &cIN, int &cus)
{
	std::string out;

	clockOut(out, cIN);

	//not sure how to proceed on this query
	std::string outQuery = "update visits set clock_out = @out where customer_id = @cus AND clock_out is NULL";

	sqlite3_stmt *ress;
	int returnC = sqlite3_prepare_v2(db, outQuery.c_str(), -1, &ress, NULL);

	if (checkForError(returnC, db, ress, "unable to update visit."))
    {
        std::cout << outQuery << std::endl;
        sqlite3_finalize(ress);
		rollback(db);
    }

	returnC = sqlite3_bind_int(ress, sqlite3_bind_parameter_index(ress, "@cus"), cus);
	if (checkForError(returnC, db, ress, "unable to update with customer ID."))
    {
        std::cout << outQuery << std::endl;
        sqlite3_finalize(ress);
		rollback(db);
    }

	returnC = sqlite3_bind_text(ress, sqlite3_bind_parameter_index(ress, "@out"), out.c_str(), -1, SQLITE_STATIC);
	if (checkForError(returnC, db, ress, "unable to update clock out."))
    {
        std::cout << outQuery << std::endl;
        sqlite3_finalize(ress);
		rollback(db);
    }

	std::cout << sqlite3_expanded_sql(ress) << std::endl;
	sqlite3_step(ress);
	sqlite3_finalize(ress);

}
bool clockedIN(sqlite3 *db, std::string &cIN, int &cus)
{
	std::string cusQuery = "select clock_in from visits where customer_id = @cus AND clock_out is NULL";

	sqlite3_stmt *ress;
	int returnC = sqlite3_prepare_v2(db, cusQuery.c_str(), -1, &ress, NULL);

	if (checkForError(returnC, db, ress, "unable to select clockIN."))
    {
        std::cout << cusQuery << std::endl;
        sqlite3_finalize(ress);
		rollback(db);
    }

	returnC = sqlite3_bind_int(ress, sqlite3_bind_parameter_index(ress, "@cus"), cus);
	if (checkForError(returnC, db, ress, "unable to insert customer ID."))
    {
        std::cout << cusQuery << std::endl;
        sqlite3_finalize(ress);
		rollback(db);
    }

	sqlite3_step(ress);
	bool clocked = (sqlite3_column_type(ress, 0) != SQLITE_NULL);

	cIN = reinterpret_cast<const char *>(sqlite3_column_text(ress, 0));
	
	sqlite3_finalize(ress);

	return clocked;

}

void changeFname(sqlite3 *db, int &cus)
{
	std::string newFname;

	std::cout << "What would you like to change the Customers First Name to?" << std::endl;
	std::cin >> newFname;

	while(!std::cin)
	{
		std::cout << "Invalid Response" << std::endl;

		std::cout << "What would you like to change the Customers First Name to?" << std::endl;
		std::cin >> newFname;
	}

	std::string fnameQuery = "update customer set f_name = @newFname where customer_id = @cus";

	sqlite3_stmt *ress;
	int returnC = sqlite3_prepare_v2(db, fnameQuery.c_str(), -1, &ress, NULL);

	if (checkForError(returnC, db, ress, "unable to update customer."))
    {
        std::cout << fnameQuery << std::endl;
        sqlite3_finalize(ress);
		rollback(db);
    }

	returnC = sqlite3_bind_int(ress, sqlite3_bind_parameter_index(ress, "@cus"), cus);
	if (checkForError(returnC, db, ress, "unable to update with customer ID."))
    {
        std::cout << fnameQuery << std::endl;
        sqlite3_finalize(ress);
		rollback(db);
    }

	returnC = sqlite3_bind_text(ress, sqlite3_bind_parameter_index(ress, "@newFname"), newFname.c_str(), -1, SQLITE_STATIC);
	if (checkForError(returnC, db, ress, "unable to update First Name."))
    {
        std::cout << fnameQuery << std::endl;
        sqlite3_finalize(ress);
		rollback(db);
    }

	sqlite3_step(ress);
	sqlite3_finalize(ress);

}

void changeLname(sqlite3 *db, int &cus)
{
	std::string newLname;

	std::cout << "What would you like to change the Customers Last Name to?" << std::endl;
	std::cin >> newLname;

	while(!std::cin)
	{
		std::cout << "Invalid Response" << std::endl;

		std::cout << "What would you like to change the Customers Last Name to?" << std::endl;
		std::cin >> newLname;
	}

	std::string lnameQuery = "update customer set lname = @newLname where customer_id = @cus";

	sqlite3_stmt *ress;
	int returnC = sqlite3_prepare_v2(db, lnameQuery.c_str(), -1, &ress, NULL);

	if (checkForError(returnC, db, ress, "unable to update customer."))
    {
        std::cout << lnameQuery << std::endl;
        sqlite3_finalize(ress);
		rollback(db);
    }

	returnC = sqlite3_bind_int(ress, sqlite3_bind_parameter_index(ress, "@cus"), cus);
	if (checkForError(returnC, db, ress, "unable to update with customer ID."))
    {
        std::cout << lnameQuery << std::endl;
        sqlite3_finalize(ress);
		rollback(db);
    }

	returnC = sqlite3_bind_text(ress, sqlite3_bind_parameter_index(ress, "@newLname"), newLname.c_str(), -1, SQLITE_STATIC);
	if (checkForError(returnC, db, ress, "unable to update Last Name."))
    {
        std::cout << lnameQuery << std::endl;
        sqlite3_finalize(ress);
		rollback(db);
    }

	sqlite3_step(ress);
	sqlite3_finalize(ress);

}
int changes(int &cus)
{
	int ch;
	std::cout << "What information would you like to update on Customer " << cus << "?" << std::endl;
	std::cout << "1. First Name" << std::endl;
	std::cout << "2. Last Name" << std::endl;
	std::cout << "3. None" << std::endl;
	

	std::cin >> ch;

	while(!std::cin || ch < 1 || ch > 3)
	{
		std::cout << "Please choose a valid option 1-4" << std::endl;

		std::cout << "What information would you like to update on Customer " << cus << "?" << std::endl;
		std::cout << "1. First Name" << std::endl;
		std::cout << "2. Last Name" << std::endl;
		std::cout << "3. None" << std::endl;

		std::cin >> ch;
	}

	return ch;
}
void updates(sqlite3 *db, int &menuChoice)
{
	int choice;

	//this is the customer id return from viewCustomer
	int cus;

	//update visits with clock-out of customer
		// before clocking out it will print the customer info for validation and you can update if you want
	std::cout << "What would you like to do?" << std::endl;

	std::cout << "1. Clock-out customer" << std::endl;
	std::cout << "2. Update Customer Info" << std::endl;
	std::cout << "3. Exit" << std::endl;

	std::cin >> choice;

	while(!std::cin || choice < 1 || choice > 2)
	{
		std::cout << "Please choose a valid option!" << std::endl;

		std::cout << "1. Clock-out customer" << std::endl;
		std::cout << "2. Exit" << std::endl;

		std::cin >> choice;

		resetStream();
	}

	if(choice == 1)
	{
		// variable to use so that we arent picking times to clock
		// out that are before they clocked in
		std::string cIN;
		
		viewCustomer(db, cus, menuChoice);

		// if clock in is present continue to clock out
		if(clockedIN(db, cIN, cus))
		{
		
			updateVisit(db, cIN, cus);

		}
		
	}
	else if (choice == 2)
	{
		viewCustomer(db, cus, menuChoice);

		//chooses what info we want to change
		int ch = changes(cus);

		switch(ch)
		{
			case 1: changeFname(db, cus); break;
			case 2: changeLname(db, cus); break;
			case 3: std::cout << "No Customer Information Changed..." << std::endl; break;
		}
	}
}

int startPurchase(sqlite3 *db)
{
    int rc = sqlite3_exec(db, "begin transaction", NULL, NULL, NULL);
    if (rc != SQLITE_OK)
    {
        std::cout << "There was an error in start purchase: "
                  << sqlite3_errmsg(db) << std::endl;
        return rc;
    }
    return SQLITE_OK;
}

void insertPurchase(sqlite3 *mydb, int &cus, double &pAmount)
{
	//we need cusID, pAmount, and date
	char formatDate[80];
    time_t currentDate = time(NULL);
    strftime(formatDate, 80, "%F", localtime(&currentDate));
    std::string invDate(formatDate);

	int amount = pAmount;

	std::string payQuery = "insert into purchase (customer_id, purchase_amount, date) values(@cus, @amount, @date)";

	sqlite3_stmt *ress;
	int returnC = sqlite3_prepare_v2(mydb, payQuery.c_str(), -1, &ress, NULL);

	if (checkForError(returnC, mydb, ress, "unable to insert purchase."))
    {
        std::cout << payQuery << std::endl;
        sqlite3_finalize(ress);
		rollback(mydb);
    }

	//insert customer ID
	returnC = sqlite3_bind_int(ress, sqlite3_bind_parameter_index(ress, "@cus"), cus);
	if (checkForError(returnC, mydb, ress, "unable to insert customer ID."))
    {
        std::cout << payQuery << std::endl;
        sqlite3_finalize(ress);
		rollback(mydb);
    }

	//insert purchase amount
	returnC = sqlite3_bind_int(ress, sqlite3_bind_parameter_index(ress, "@amount"), amount);
	if (checkForError(returnC, mydb, ress, "unable to insert purchase amount."))
    {
        std::cout << payQuery << std::endl;
        sqlite3_finalize(ress);
		rollback(mydb);
    }

	//insert date
	returnC = sqlite3_bind_text(ress, sqlite3_bind_parameter_index(ress, "@date"), invDate.c_str(), -1, SQLITE_STATIC);
	if (checkForError(returnC, mydb, ress, "unable to insert purchase date."))
    {
        std::cout << payQuery << std::endl;
        sqlite3_finalize(ress);
		rollback(mydb);
    }

	sqlite3_step(ress);
	sqlite3_finalize(ress);
}

void insertItemSale(sqlite3 *mydb, int &pID, std::vector<int> &items)
{
	//attributes for item_sales
	//purchase_id, item_id

	int item;

	for (int i = 0; i < items.size(); i++)
	{
		item = items[i];

		std::string saleQuery = "insert into item_sales (purchase_id, item_id) values(@pID, @item)";

		sqlite3_stmt *ress;
		int returnC = sqlite3_prepare_v2(mydb, saleQuery.c_str(), -1, &ress, NULL);

		if (checkForError(returnC, mydb, ress, "unable to insert item sale."))
		{
			std::cout << saleQuery << std::endl;
			sqlite3_finalize(ress);
			rollback(mydb);
		}

		//insert purchase ID
		returnC = sqlite3_bind_int(ress, sqlite3_bind_parameter_index(ress, "@pID"), pID);
		if (checkForError(returnC, mydb, ress, "unable to insert purchase ID."))
		{
			std::cout << saleQuery << std::endl;
			sqlite3_finalize(ress);
			rollback(mydb);
		}

		//insert itemID
		returnC = sqlite3_bind_int(ress, sqlite3_bind_parameter_index(ress, "@item"), item);
		if (checkForError(returnC, mydb, ress, "unable to insert item ID."))
		{
			std::cout << saleQuery << std::endl;
			sqlite3_finalize(ress);
			rollback(mydb);
		}

		sqlite3_step(ress);
		sqlite3_finalize(ress);
	}
	

}
void makePurchase(sqlite3 *mydb, int &menuChoice)
{
	int cus;
	double pAmount;
	std::vector<int> price;
	std::vector<int> items;

	int rc = startPurchase(mydb);

	//view customer and print customer
	viewCustomer(mydb, cus, menuChoice);

	//view item and print item
	viewItems(mydb, price, items);

	//turning string to double and adding
	for (int i = 0; i < price.size(); i++)
	{
		pAmount += price[i];
	}

	//make transact
		// insert into purchase and item sale
	insertPurchase(mydb, cus, pAmount);

	int pID = sqlite3_last_insert_rowid(mydb);

	insertItemSale(mydb, pID, items);

	std::cout << "Transaction Successful!" << std::endl << std::endl;

	std::cout << "Receipt" << std::endl << std::endl;
	std::cout << "Items in Purchase:" << std::endl;

	for(int i = 0; i < items.size(); i++)
	{
		//need map for this
		std::cout << i + 1 << ". " << shopItems[static_cast<shopI>(items[i] - 1)] << std::endl;
	}
	std::cout << std::endl;

	std::cout << "Total: " << pAmount <<  " Galleons" << std::endl << std::endl;


	commit(mydb);

}

void viewItems(sqlite3 *mydb, std::vector<int> &prices, std::vector<int> &items)
{
	//make sure this lines up with your hogwarts db
	std::string itemQuery = "SELECT item_id, item_description, item_price from items";

	sqlite3_stmt *res;

	int rc = sqlite3_prepare_v2(mydb, itemQuery.c_str(), -1, &res, NULL);

	if (rc != SQLITE_OK)
	{
		sqlite3_finalize(res);
		std::cout << "There was an error with the customer query: " << sqlite3_errmsg(mydb) << std::endl;
		std::cout << itemQuery << std::endl;
		return;
	}

	std::cout << "Please choose the items you would like to purchase: (select -1 to finalize) " << std::endl;

	int columnCount = sqlite3_column_count(res);
	int i = 0, choice = 0, rowsPerPage, totalRows;
	
	std::cout << std::left;
	int result;

	do
	{
		do
		{
			result = sqlite3_step(res);
			i++;

		} while (result == SQLITE_ROW);
		totalRows = i - 1;
		sqlite3_reset(res);
		
		rowsPerPage = 10;

		i = 0;

		// need to get this to line up better
		printItems(res, rowsPerPage, i);
		std::cin >> choice;
		
		while (!std::cin || choice < -1 || choice > 5)
		{
			if (!std::cin)
			{
				resetStream();
			}
			std::cout << "That is not a valid choice! Try again!" << std::endl;
			std::cin >> choice;
		}

		sqlite3_reset(res);
		for (int i = 0; i < choice; i++)
			sqlite3_step(res);

		double price = sqlite3_column_double(res, 2);

		// we need to turn price into double
		if(choice != -1)
		{
			items.push_back(choice);
			prices.push_back(price);

		}
		
		

	} while(choice != -1);

}
void printItems(sqlite3_stmt *res, int rowsPerPage, int startNum)
{
	int stop, i = 1;
	do
	{
		stop = sqlite3_step(res);
		if (stop != SQLITE_ROW)
			break;
		std::cout << i + startNum << ". ";
		if (sqlite3_column_type(res, 0) != SQLITE_NULL)
			std::cout << "Item ID: " << sqlite3_column_text(res, 0) << " ";
		if (sqlite3_column_type(res, 1) != SQLITE_NULL)
			std::cout << "      Name: " << sqlite3_column_text(res, 1) << " ";
		if (sqlite3_column_type(res, 2) != SQLITE_NULL)
			std::cout << "              Price: " << sqlite3_column_text(res, 2) << " ";
		std::cout << std::endl;
		i++;

	} while (i <= rowsPerPage);
}

int menu()
{
	int ch;

	std::cout << "Hogsmeade Wizarding Goods" << std::endl;

	std::cout << "Select an option below:" << std::endl;

	std::cout << "1. Entering Customer" << std::endl;
	std::cout << "2. Transact" << std::endl;
	std::cout << "3. Update visit" << std::endl;
	std::cout << "4. Delete customer" << std::endl;
	std::cout << "5. Run Reports" << std::endl;
	std::cout << "6. exit" << std::endl;

	std::cin >> ch;
	std::cout << std::endl;

	while(!std::cin || ch < 1 || ch > 6)
	{
		std::cout << "Please select a valid option!" << std::endl;

		ch = menu();
	}

	return ch;
}

void visit(sqlite3 *mydb, int &choice)
{
	std::string answer1;

	// new customer and log customer entering
	std::cout << "Is the customer new to Hogsmeade Wizarding Goods?" << std::endl;
	std::cin >> answer1;

	std::transform(answer1.begin(), answer1.end(), answer1.begin(), ::toupper);

	while (!std::cin || (answer1 != "YES" && answer1 != "NO"))
	{
		std::cout << "Please enter a valid respsonse!" << std::endl;

		std::cout << "Is the customer new to Hogsmeade Wizarding Goods?" << std::endl;
		std::getline(std::cin , answer1);

		std::transform(answer1.begin(), answer1.end(), answer1.begin(), ::toupper);
	}

	if (answer1 == "YES")
	{
		//enter in customer if new
		newCustomer(mydb);

		int cusID = sqlite3_last_insert_rowid(mydb);

		newVisit(mydb, cusID);
	}
	else
	{
		int cus;
		
		// else choose existing customer to log in
		viewCustomer(mydb, cus, choice);
		
		//then clock them in
		newVisit(mydb, cus);

		std::cout << std::endl << std::endl;
	}
		
}

void customerInfo(std::string &fname, std::string &lname, int &age, std::string &gender, std::string &house)
{

	std::cout << "What is the customers first name?" << std::endl;
	std::cin >> fname;

	std::cout << "What is "<< fname << "'s last name?" << std::endl;
	std::cin >> lname;

	std::cout << "How old is " << fname << " " << lname << "?" << std::endl;
	std::cin >> age;

	std::cout << "Is "<< fname << " " << "Male or Female?" << std::endl;
	std::cin >> gender;

	std::transform(gender.begin(), gender.end(), gender.begin(), ::tolower);

	while(!std::cin || (gender != "male" && gender != "female"))
	{
		std::cout << "Please choose a valid gender option!" << std::endl;

		std::cout << "Is "<< fname << " " << "Male or Female?" << std::endl;
		std::cin >> gender;

		std::transform(gender.begin(), gender.end(), gender.begin(), ::tolower);
	}

	std::cout << "What is " << fname << " " << lname << "'s House at Hogwarts(Gryffindor, Slytherin, HufflePuff, Ravenclaw)?" << std::endl;
	std::cin >> house;

	std::transform(house.begin(), house.end(), house.begin(), ::tolower);

	while(!std::cin || (house != "gryffindor" && house != "slytherin" && house != "hufflepuff" && house != "ravenclaw"))
	{
		std::cout << "Please choose a valid option: Gryffindor, Slytherin, HufflePuff, Ravenclaw" << std::endl;

		std::cin >> house;

		std::transform(house.begin(), house.end(), house.begin(), ::tolower);
	}
	
	
}

int rollback(sqlite3 *db)
{
	int rc = sqlite3_exec(db, "rollback", NULL, NULL, NULL);
    if (rc != SQLITE_OK)
    {
        std::cout << "There was an error - rolling back the transaction: "
                  << sqlite3_errmsg(db) << std::endl;
        return rc;
    }
    return SQLITE_OK;
}

bool checkForError(int rc, sqlite3 *db, sqlite3_stmt *r, std::string msg)
{
    if (rc != SQLITE_OK)
    {
        sqlite3_finalize(r);
        std::cout << msg << " " << sqlite3_errmsg(db) << std::endl;
        return true;
    }
    return false;
}

int commit(sqlite3 *db)
{
    std::string query = "commit";
    int rc = sqlite3_exec(db, query.c_str(), NULL, NULL, NULL);
    if (rc != SQLITE_OK)
    {
        std::cout << "There was an error - committing transaction: " << sqlite3_errmsg(db) << std::endl;
        rollback(db);
        return rc;
    }
    return SQLITE_OK;
}

void newCustomer(sqlite3 *db)
{
	std::string fname, lname, gender, house;
	int age;

	//gathering new customer info
	customerInfo(fname, lname, age, gender, house);

	//insert into customer table query
	std::string insertCus = "insert into customer (f_name, l_name, age, gender, house_at_hogwarts) values(@fname, @lname, @age, @gender, @house)";

	sqlite3_stmt *ress;
	int returnC = sqlite3_prepare_v2(db, insertCus.c_str(), -1, &ress, NULL);

	if (checkForError(returnC, db, ress, "unable to insert customer."))
    {
        std::cout << insertCus << std::endl;
        sqlite3_finalize(ress);
		rollback(db);
    }

	//bind for fname
	returnC = sqlite3_bind_text(ress, sqlite3_bind_parameter_index(ress, "@fname"), fname.c_str(), -1, SQLITE_STATIC);
	if (checkForError(returnC, db, ress, "unable to insert first name."))
    {
        std::cout << insertCus << std::endl;
        sqlite3_finalize(ress);
		rollback(db);
    }

	//bind for lname
	returnC = sqlite3_bind_text(ress, sqlite3_bind_parameter_index(ress, "@lname"), lname.c_str(), -1, SQLITE_STATIC);
	if (checkForError(returnC, db, ress, "unable to insert last name."))
    {
        std::cout << insertCus << std::endl;
        sqlite3_finalize(ress);
		rollback(db);
    }

	// bind for age
	returnC = sqlite3_bind_int(ress, sqlite3_bind_parameter_index(ress, "@age"), age);
	if (checkForError(returnC, db, ress, "unable to insert age."))
    {
        std::cout << insertCus << std::endl;
        sqlite3_finalize(ress);
		rollback(db);
    }

	//bind for gender
	returnC = sqlite3_bind_text(ress, sqlite3_bind_parameter_index(ress, "@gender"), gender.c_str(), -1, SQLITE_STATIC);
	if (checkForError(returnC, db, ress, "unable to insert gender."))
    {
        std::cout << insertCus << std::endl;
        sqlite3_finalize(ress);
		rollback(db);
    }

	// bind for house at hogwarts
	returnC = sqlite3_bind_text(ress, sqlite3_bind_parameter_index(ress, "@house"), house.c_str(), -1, SQLITE_STATIC);
	if (checkForError(returnC, db, ress, "unable to insert house at hogwarts."))
    {
        std::cout << insertCus << std::endl;
        sqlite3_finalize(ress);
		rollback(db);
    }

	sqlite3_step(ress);
	sqlite3_finalize(ress);
}

std::string clockIN(std::string &clocked, std::string &newIn)
{
	// there is something causing the program to not use input 
	//validation here and valid answers stop the output
	std::cout << "When did the customer enter the shop?" << std::endl;
	std::cin >> std::ws;
	std::getline(std::cin, clocked);

	std::regex timeStr{
		R"(([01]?[0-9]|2[0-3]):([0-5][0-9]|0[0-9])\0?([aA][mM]|[pP][mM])?)"
	};

	std::smatch parts;

	if(std::regex_match(clocked, parts, timeStr))
	{
		int hour = std::stoi(parts[1]);
		int minutes = std::stoi(parts[2]);
		
		std::string tod = parts[3];

		std::string todUpper = tod;
		std::transform(todUpper.begin(), todUpper.end(), todUpper.begin(), ::tolower);

		bool valid = true;

		if ((hour <= 0 || hour > 12) || (minutes < 0 || minutes > 59) || (tod != "am" && tod != "pm"))
		{
			valid = false;
		}

		while(!valid)
		{
			std::cout << "When did the customer enter the shop?" << std::endl;
			std::cin >> std::ws;
			std::getline(std::cin, clocked);

			std::regex timeStr{
				R"(([01]?[0-9]|2[0-3]):([0-5][0-9]|0[0-9])\0?([aA][mM]|[pP][mM])?)"
			};

			std::smatch parts;

			if(std::regex_match(clocked, parts, timeStr))
			{
				// I tried hour validation here too
				// parts of regex
				int hour = std::stoi(parts[1]);
				int minutes = std::stoi(parts[2]);
				
				std::string tod = parts[3];

				std::string todUpper = tod;
				std::transform(todUpper.begin(), todUpper.end(), todUpper.begin(), ::tolower);

				bool valid = true;

				if ((hour <= 0 || hour > 12) || (minutes < 0 || minutes > 59) || (tod != "am" && tod != "pm"))
				{
					valid = false;
				}
			}
			resetStream();	
		}

		if (valid)
		{
			newIn = std::to_string(hour) + ":" + std::to_string(minutes) + tod;
		}
		
	}               
	else
	{

		while(!(std::regex_match(clocked, parts, timeStr)))
		{
			std::cout << "Not a match, Please enter a valid time!" << std::endl;

			std::cout << "When did the customer enter the shop?" << std::endl;
			std::cin >> std::ws;
			std::getline(std::cin, clocked);

			std::regex timeStr{
				R"(([01]?[0-9]|2[0-3]):([0-5][0-9]|0[0-9])\0?([aA][mM]|[pP][mM])?)"
			};

			std::smatch parts;

			if(std::regex_match(clocked, parts, timeStr))
			{
				// I tried hour validation here too
				// parts of regex
				int hour = std::stoi(parts[1]);
				int minutes = std::stoi(parts[2]);
				
				std::string tod = parts[3];

				std::string todUpper = tod;
				std::transform(todUpper.begin(), todUpper.end(), todUpper.begin(), ::tolower);

				bool valid = true;

				if ((hour <= 0 || hour > 12) || (minutes < 0 || minutes > 59) || (tod != "am" && tod != "pm"))
				{
					valid = false;
				}
			}
		}
	}
	return newIn;
}
void newVisit(sqlite3 *db, int &cusID)
{
	std::string clocked, in, newIn;

	in = clockIN(clocked, newIn);

	std::string visitQuery = "insert into visits (customer_ID, clock_in, date) values(@cusID, @in, @date)";

	//needed for current date
	char formatDate[80];
    time_t currentDate = time(NULL);
    strftime(formatDate, 80, "%F", localtime(&currentDate));
    std::string invDate(formatDate);

	sqlite3_stmt *res;
	int returnC = sqlite3_prepare_v2(db, visitQuery.c_str(), -1, &res, NULL);

	if (checkForError(returnC, db, res, "unable to insert visit."))
    {
        std::cout << visitQuery << std::endl;
        sqlite3_finalize(res);
		rollback(db);
    }

	//bind for customer ID
	returnC = sqlite3_bind_int(res, sqlite3_bind_parameter_index(res, "@cusID"), cusID);
	if (checkForError(returnC, db, res, "unable to insert customer ID."))
    {
        std::cout << visitQuery << std::endl;
        sqlite3_finalize(res);
		rollback(db);
    }

	//bind for clock in
	returnC = sqlite3_bind_text(res, sqlite3_bind_parameter_index(res, "@in"), in.c_str(), -1, SQLITE_STATIC);
	if (checkForError(returnC, db, res, "unable to insert time clocked in."))
    {
        std::cout << visitQuery << std::endl;
        sqlite3_finalize(res);
		rollback(db);
    }

	//bind for date of visit
	returnC = sqlite3_bind_text(res, sqlite3_bind_parameter_index(res, "@date"), invDate.c_str(), -1, SQLITE_STATIC);
	if (checkForError(returnC, db, res, "unable to insert date of visit."))
    {
        std::cout << visitQuery << std::endl;
        sqlite3_finalize(res);
		rollback(db);
    }

	sqlite3_step(res);
	sqlite3_finalize(res);
}

void printCustomerPage(sqlite3_stmt *res, int rowsPerPage, int startNum)
{
	int stop, i = 1;
	do
	{
		stop = sqlite3_step(res);
		if (stop != SQLITE_ROW)
			break;
		std::cout << i + startNum << ". ";
		if (sqlite3_column_type(res, 0) != SQLITE_NULL)
			std::cout << "Customer ID: " << sqlite3_column_text(res, 0) << " ";
		if (sqlite3_column_type(res, 1) != SQLITE_NULL)
			std::cout << "         Name: " << sqlite3_column_text(res, 1) << " ";
		if (sqlite3_column_type(res, 2) != SQLITE_NULL)
			std::cout << sqlite3_column_text(res, 2) << " ";
		std::cout << std::endl;
		i++;

	} while (i <= rowsPerPage);
}

void viewCustomer(sqlite3 *db, int &cus, int &menuChoice)
{
	//make sure this lines up with your hogwarts db
	std::string cusQuery = "SELECT customer_id, f_name, l_name from customer";

	sqlite3_stmt *res;

	int rc = sqlite3_prepare_v2(db, cusQuery.c_str(), -1, &res, NULL);

	if (rc != SQLITE_OK)
	{
		sqlite3_finalize(res);
		std::cout << "There was an error with the customer query: " << sqlite3_errmsg(db) << std::endl;
		std::cout << cusQuery << std::endl;
		return;
	}

	if(menuChoice == 1)
	{
		std::cout << "Please choose the customer you would like to clock in: " << std::endl;
	}
	else if (menuChoice == 2)
	{
		std::cout << "Please choose the customer making the purchase: " << std::endl;
	}
	else if(menuChoice == 3)
	{
		std::cout << "Please choose the customer you are updating: " << std::endl;
	}
	else if(menuChoice == 4)
	{
		std::cout << "Please choose the customer you are deleting: " << std::endl;
	}
	else if(menuChoice == 5)
	{
		std::cout << "Please choose the customer to the run the report on: " << std::endl;
	}
	

	int columnCount = sqlite3_column_count(res);
	int i = 0, choice = 0, rowsPerPage, totalRows;
	
	std::cout << std::left;
	int result;
	do
	{
		result = sqlite3_step(res);
		i++;

	} while (result == SQLITE_ROW);
	totalRows = i - 1;
	sqlite3_reset(res);
	
	rowsPerPage = 100;

	i = 0;

	printCustomerPage(res, rowsPerPage, i);
	std::cin >> choice;
	
	while (!std::cin || choice < 0 || choice > totalRows)
	{
		if (!std::cin)
		{
			resetStream();
		}
		std::cout << "That is not a valid choice! Try again!" << std::endl;
		std::cin >> choice;
	}
		
	
	sqlite3_reset(res);
	for (int i = 0; i < choice; i++)
		sqlite3_step(res);

	cus = sqlite3_column_int(res, 0);
}

void resetStream()
{
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::cout << "Please enter a valid 12 hour or 24 hour time." << std::endl;
}