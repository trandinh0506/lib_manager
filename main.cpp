#include <iostream>
#include <string>
#include <fstream>
#include <conio.h>
#include <vector>
#include <ctime>
#include <map>

struct Book{
	int isbn;
	std::string title;
	std::string subject;
	std::string author;
	std::string publisher;
	std::string date;
	int pages;
	int copies;
};
std::vector<Book> books;
std::map<std::string, std::vector<std::string>> users;
void clear() {
	system("cls");
}
void pause() {
	std::cout << "Press any key to continue . . .";
	_getch();
}
std::vector<std::string> split(const std::string input, char delimiter) {

    std::vector<std::string> tokens;
    size_t start = 0, end;
    while ((end = input.find(delimiter, start)) != std::string::npos) { // npos: the end of string
        tokens.push_back(input.substr(start, end - start));
        start = end + 1;
    }
    tokens.push_back(input.substr(start));
    return tokens;
}
void loadBook() {
	std::ifstream inputFile("database/books.db");
	if (!inputFile.is_open()) {
		std::cout << "Can not read database\n";
		pause();
		return;
	}
	std::string line;
	Book book;
	std::vector<std::string> data;
	std::getline(inputFile, line);
	while (line != "") {
		data = split(line, '|');
		book.isbn = std::stoi(data[0]);
		book.title = data[1];
		book.subject = data[2];
		book.author = data[3];
		book.publisher = data[4];
		book.date = data[5];
		book.pages = std::stoi(data[6]);
		book.copies = std::stoi(data[7]);
		books.push_back(book);
		std::getline(inputFile, line);
	}
	inputFile.close();
}
void loadUser(){
	std::ifstream inputFile("database/users.db");
	if (!inputFile.is_open()) {
		std::cout << "Can not read database\n";
	}
	std::string line;
	std::vector<std::string> data;
	std::getline(inputFile, line);
	while (line != "") {
		data = split(line, '|');
		users[data[0]] = {data[1], data[2]};
		std::getline(inputFile, line);
	}
	inputFile.close();
}
std::vector<int> maxLength(std::vector<Book> books) {
	std::vector<int> mL = {6, 7, 9, 8, 11, 6, 7, 8};
	for (auto book : books) {
		if (std::to_string(book.isbn).size() + 2 > mL[0]) mL[0] = std::to_string(book.isbn).size() + 2;
		if (book.title.size() + 2 > mL[1]) mL[1] = book.title.size() + 2;
		if (book.subject.size() + 2 > mL[2]) mL[2] = book.subject.size() + 2;
		if (book.author.size() + 2 > mL[3]) mL[3] = book.author.size() + 2;
		if (book.publisher.size() + 2 > mL[4]) mL[4] = book.publisher.size() + 2;
		if (book.date.size() + 2 > mL[5]) mL[5] = book.date.size() + 2;
		if (std::to_string(book.pages).size() + 2 > mL[6]) mL[6] = std::to_string(book.pages).size() + 2;
		if (std::to_string(book.copies).size() + 2 > mL[7]) mL[7] = std::to_string(book.copies).size() + 2;
	}
	return mL;
}
std::string mul(std::string inp, int m){
	std::string result = "";
	for (int i = 0; i < m; i++) {
		result += inp;
	}
	return result;
}
void printBook(std::vector<Book> books) {
	std::vector<int> mL = maxLength(books);
	for (int maxLen : mL) {
		std::cout << "+" << mul("-", maxLen);
	}
	std::cout << "+\n";
	std::cout << "|" << 
		 mul(" ", (mL[0] - 4) / 2) << "Isbn" << mul(" ", ((mL[0] - 4)&1 ? (mL[0] - 4) + 1 : (mL[0] - 4)) / 2) << "|" <<
		 mul(" ", (mL[1] - 5) / 2) << "Title" << mul(" ", ((mL[1] - 5)&1 ? (mL[1] - 5) + 1 : (mL[1] - 5)) / 2) << "|" << 
		 mul(" ", (mL[2] - 7) / 2) << "Subject" << mul(" ", ((mL[2] - 7)&1 ? (mL[2] - 7) + 1 : (mL[2] - 7)) / 2) << "|" <<
		 mul(" ", (mL[3] - 6) / 2) << "Author" << mul(" ", ((mL[3] - 6)&1 ? (mL[3] - 6) + 1 : (mL[3] - 6)) / 2) << "|" << 
		 mul(" ", (mL[4] - 9) / 2) << "Publisher" << mul(" ", ((mL[4] - 9)&1 ? (mL[4] - 9) + 1 : (mL[4] - 9)) / 2) << "|" <<
		 mul(" ", (mL[5] - 4) / 2) << "Date" << mul(" ", ((mL[5] - 4)&1 ? (mL[5] - 4) + 1 : (mL[5] - 4)) / 2) << "|" << 
		 mul(" ", (mL[6] - 5) / 2) << "Pages" << mul(" ", ((mL[6] - 5)&1 ? (mL[6] - 5) + 1 : (mL[6] - 5)) / 2) << "|" << 
		 mul(" ", (mL[7] - 6) / 2) << "Copies" << mul(" ", ((mL[7] - 6)&1 ? (mL[7] - 6) + 1 : (mL[7] - 6)) / 2) << "|\n";
	for (int maxLen : mL) {
		std::cout << "+" << mul("-", maxLen);
	}
	std::cout << "+\n";
	for (auto book : books) {
		int isbn = mL[0] - std::to_string(book.isbn).size(),
			title = mL[1] - book.title.size(),
			subject = mL[2] - book.subject.size(),
			author = mL[3] - book.author.size(),
			publisher = mL[4] - book.publisher.size(),
			date = mL[5] - book.date.size(),
			pages = mL[6] - std::to_string(book.pages).size(),
			copies = mL[7] - std::to_string(book.copies).size();
		std::cout << "|" <<
			mul(" ", isbn / 2) << book.isbn << mul(" ", ((isbn&1)? isbn+1 : isbn) / 2) << "|" <<
			mul(" ", title / 2) << book.title << mul(" ", ((title&1)? title+1 : title) / 2) << "|" << 
			mul(" ", subject / 2) << book.subject << mul(" ", ((subject&1)? subject+1 : subject) / 2) << "|" <<
			mul(" ", author / 2) << book.author << mul(" ", ((author&1)? author+1 : author) / 2) << "|" << 
			mul(" ", publisher / 2) << book.publisher << mul(" ", ((publisher&1)? publisher+1 : publisher) / 2) << "|" <<
			mul(" ", date / 2) << book.date << mul(" ", ((date&1)? date+1 : date) / 2) << "|" << 
			mul(" ", pages / 2) << book.pages << mul(" ", ((pages&1)? pages+1 : pages) / 2) << "|" << 
			mul(" ", copies / 2) << book.copies << mul(" ", ((copies&1)? copies+1 : copies) / 2) << "|\n";
		for (int maxLen : mL) {
		std::cout << "+" << mul("-", maxLen);
		}
		std::cout << "+\n";
	}

}
void welcome(int &option){
	std::cout << "Welcome to the library!\n";
	std::cout << "1. Admin login\n";
	std::cout << "0. Visit user\n";
	option = _getch();
	clear();
}
bool login(std::string userName, std::string password, std::string type) {
	if (users.find(userName) != users.end())
		return users[userName][0] == password && users[userName][1] == type;
	else return false;
}
void getUserInfor(std::string &userName, std::string &password){
	std::cout << "Enter username: ";
	std::cin >> userName;
	std::cout << "Enter password: ";
	password = "";
	while (true) {
		int c = _getch();
		if (c == 13) {
			std::cout << "\n";
			break;
		}
		else if (c == 8) {
			if (password.length()) password.pop_back();
			std::cout << "\r\033[K" << "Enter password: " << mul("*", password.length());
		} else {
			std::cout << "*";
			password.push_back(c);
		}
	}
}
void handleViewOnly() {
	clear();
	printBook(books);
}
void printTask() {
	std::cout << "Admin role.\nFunctionalities can be executed:\n";
	std::cout << "1. Print all book in library.\n";
	std::cout << "2. Add book.\n";
	std::cout << "3. Update book.\n";
	std::cout << "4. Delete book.\n";
	std::cout << "5. Find book.\n";
	std::cout << "6. Save.\n";
	std::cout << "7. Create new user.\n";
	std::cout << "8. Set password for user.\n";
	std::cout << "9. Delete user.\n";
	std::cout << "0. Quit.\n";
}
bool checkIsbn(int isbn) {
	for (auto book:books) {
			if (book.isbn == isbn) {
				return 0;
			}
		}
	return 1;
}
bool isValidDate(std::string date) {
    int day, month, year;
    std::vector<std::string> dates = split(date,'/');
    if (dates.size() < 3) return 0;
    day = std::stoi(dates[0]);
    month = std::stoi(dates[1]);
    year = std::stoi(dates[2]);
    std::time_t currentTime = std::time(nullptr);
    struct tm* timeInfo = std::localtime(&currentTime);

    
    timeInfo->tm_year = year - 1500; 
    timeInfo->tm_mon = month - 1;
    timeInfo->tm_mday = day;

    std::time_t convertedTime = std::mktime(timeInfo);

    // Check if the conversion was successful and the date is valid
    return convertedTime != -1 && timeInfo->tm_year == year - 1500 && timeInfo->tm_mon == month - 1 && timeInfo->tm_mday == day;
}
void addBook() {
	int isbn, pages, copies;
	std::string title, subject, author, publisher, date;
	Book book;
	clear();
	std::cout << "2. Add book.\n";
	std::cout << "Enter isbn: ";
	std::cin >> isbn;
	while(!checkIsbn(isbn)) {
		std::cout << "Isbn is Already exist!\n";
		std::cout << "Enter isbn: ";
		std::cin >> isbn;
	}
	std::cin.ignore();
	std::cout << "Enter title: ";
	std::getline(std::cin, title);
	std::cout << "Enter subject: ";
	std::getline(std::cin, subject);
	std::cout << "Enter author: ";
	std::getline(std::cin, author);
	std::cout << "Enter publisher: ";
	std::getline(std::cin, publisher);
	std::cout << "Enter date (dd/mm/yyyy): ";
	std::getline(std::cin, date);
	while(!isValidDate(date)) {
		std::cout << "Invalid date!\n";
		std::cout << "Enter date (dd/mm/yyyy): ";
		std::cin >> date;
	}
	std::cout << "Enter pages: ";
	std::cin >> pages;
	while (pages < 1) {
		std::cout << "Pages must be a nature number!\n";
		std::cout << "Enter pages: ";
		std::cin >> pages;
	}
	std::cout << "Enter copies: ";
	std::cin >> copies;
	while (copies < 1) {
		std::cout << "Copies must be a nature number!\n";
		std::cout << "Enter copies: ";
		std::cin >> copies;
	}
	book.isbn = isbn;
	book.title = title;
	book.subject = subject;
	book.author = author;
	book.publisher = publisher;
	book.date = date;
	book.pages = pages;
	book.copies = copies;
	books.push_back(book);
	std::cout << "Done!\n";
	pause();
	clear();
}
void updateBook() {
	long isbn;
	int option, pages, copies, index;
	std::string title, subject, author, publisher, date;
	std::vector<Book> selectedBook;
	clear();
	std::cout << "3. Update book.\n";
	printBook(books);
	std::cout << "Choose the book you want to update (enter isbn): ";
	std::cin >> isbn;
	while (checkIsbn(isbn)) {
		std::cout << "Incorrect isbn!\n";
		std::cout << "Choose the book you want to update (enter isbn): ";
		std::cin >> isbn;
	}
	for (int i = 0; i < books.size(); i++) {
		if (books[i].isbn == isbn) {
			selectedBook.push_back(books[i]);
			index = i;
			break;
		} 
	}
	clear();
	std::cout << "Which fields do you want to update?\n";
	std::cout << "1. Isbn.\n";
	std::cout << "2. Title.\n";
	std::cout << "3. Subject.\n";
	std::cout << "4. Author.\n";
	std::cout << "5. Publisher.\n";
	std::cout << "6. Date.\n";
	std::cout << "7. Pages.\n";
	std::cout << "8. Copies.\n";
	std::cout << "0. All.\n";
	option = _getch();
	clear();
	printBook(selectedBook);
	std::cin.ignore();
	if (option == 48) {
		std::cout << "Enter new isbn: ";
		std::cin >> isbn;
		while(!checkIsbn(isbn)) {
			std::cout << "Isbn is Already exist!\n";
			std::cout << "Enter new isbn: ";
			std::cin >> isbn;
		}
		books[index].isbn = isbn;
		std::cin.ignore();
		std::cin.ignore();
		std::cout << "Enter new title: ";
		std::getline(std::cin, title);
		books[index].title = title;
		std::cout << "Enter new subject: ";
		std::getline(std::cin, subject);
		books[index].subject = subject;
		std::cout << "Enter new author: ";
		std::getline(std::cin, author);
		books[index].author = author;
		std::cout << "Enter new publisher: ";
		std::getline(std::cin, publisher);
		books[index].publisher = publisher;
		std::cout << "Enter new date (dd/mm/yyyy): ";
		std::getline(std::cin, date);
		while(!isValidDate(date)) {
			std::cout << "Invalid date!\n";
			std::cout << "Enter new date (dd/mm/yyyy): ";
			std::cin >> date;
		}
		books[index].date = date;
		std::cout << "Enter new pages: ";
		std::cin >> pages;
		while (pages < 1) {
			std::cout << "Pages must be a nature number!\n";
			std::cout << "Enter new pages: ";
			std::cin >> pages;
		}
		books[index].pages = pages;
		std::cout << "Enter new copies: ";
		std::cin >> copies;
		while (copies < 1) {
			std::cout << "Copies must be a nature number!\n";
			std::cout << "Enter new copies: ";
			std::cin >> copies;
		}
		books[index].copies = copies;
	}
	else if (option == 49) {
		std::cout << "Enter new isbn: ";
		std::cin >> isbn;
		while(!checkIsbn(isbn)) {
			std::cout << "Isbn is Already exist!\n";
			std::cout << "Enter new isbn: ";
			std::cin >> isbn;
		}
		books[index].isbn = isbn;
	}
	else if (option == 50) {
		std::cout << "Enter new title: ";
		std::getline(std::cin, title);
		books[index].title = title;
	}
	else if (option == 51) {
		std::cout << "Enter new subject: ";
		std::getline(std::cin, subject);
		books[index].subject = subject;
	}
	else if (option == 52) {
		std::cout << "Enter new author: ";
		std::getline(std::cin, author);
		books[index].author = author;
	}
	else if (option == 53) {
		std::cout << "Enter new publisher: ";
		std::getline(std::cin, publisher);
		books[index].publisher = publisher;
	}
	else if (option == 54) {
		std::cout << "Enter new date (dd/mm/yyyy): ";
		std::getline(std::cin, date);
		while(!isValidDate(date)) {
			std::cout << "Invalid date!\n";
			std::cout << "Enter new date (dd/mm/yyyy): ";
			std::cin >> date;
		}
		books[index].date = date;
	}
	else if (option == 55) {
		std::cout << "Enter new pages: ";
		std::cin >> pages;
		while (pages < 1) {
			std::cout << "Pages must be a nature number!\n";
			std::cout << "Enter new pages: ";
			std::cin >> pages;
		}
		books[index].pages = pages;
	}
	else if (option == 56) {
		std::cout << "Enter new copies: ";
		std::cin >> copies;
		while (copies < 1) {
			std::cout << "Copies must be a nature number!\n";
			std::cout << "Enter new copies: ";
			std::cin >> copies;
		}
		books[index].copies = copies;
	}
	std::cout << "Done!\n";
	pause();
	clear();
}
void deleteBook() {
	long isbn;
	clear();
	std::cout << "4. Delete book.\n";
	printBook(books);
	std::cout << "Choose the book you want to delete (enter isbn): ";
	std::cin >> isbn;
	while (checkIsbn(isbn)) {
		std::cout << "Incorrect isbn!\n";
		std::cout << "Choose the book you want to update (enter isbn): ";
		std::cin >> isbn;
	}
	for (int i = 0; i < books.size(); i++) {
		if (books[i].isbn == isbn) {
			books.erase(books.begin() + i);
			break;
		} 
	}
	std::cout << "Done!\n";
	pause();
	clear();
}
void findBook() {
	std::vector<Book> selectedBooks;
	int option;
	std::string object;
	clear();
	std::cout << "5. Find book.\n";
	std::cout << "Choose the field you want to find.\n";
	std::cout << "1. Title.\n";
	std::cout << "2. Subject.\n";
	std::cout << "3. Author.\n";
	std::cout << "4. Publisher.\n";
	std::cout << "5. Publishing year.\n";
	std::cout << "0. Isbn.\n";
	option = _getch();
	clear();
	std::cout << "Press enter to continue\n";
	std::cin.ignore();
	clear();
	if (option == 48) {
		long isbn;
		std::cout << "Enter isbn: ";
		std::cin >> isbn;
		std::cin.ignore();
		for (int i = 0; i < books.size(); i++) 
			if (books[i].isbn == isbn) {
				selectedBooks.push_back(books[i]);
				break;	
			}
	}
	else if (option == 49) {
		std::cout << "Enter title: ";
		std::getline(std::cin, object);
		for (int i = 0; i < books.size(); i++) 
			if (books[i].title.find(object) != std::string::npos)
				selectedBooks.push_back(books[i]);
	}
	else if (option == 50) {
		std::cout << "Enter subject: ";
		std::getline(std::cin, object);
		for (int i = 0; i < books.size(); i++) 
			if (books[i].subject.find(object) != std::string::npos)
				selectedBooks.push_back(books[i]);
	}
	else if (option == 51) {
		std::cout << "Enter author: ";
		std::getline(std::cin, object);
		for (int i = 0; i < books.size(); i++) 
			if (books[i].author.find(object) != std::string::npos)
				selectedBooks.push_back(books[i]);
	}
	else if (option == 52) {
		std::cout << "Enter publisher: ";
		std::getline(std::cin, object);
		for (int i = 0; i < books.size(); i++) 
			if (books[i].publisher.find(object) != std::string::npos)
				selectedBooks.push_back(books[i]);
	}
	else if (option == 53) {
		std::cout << "Enter publishing year: ";
		std::getline(std::cin, object);
		for (int i = 0; i < books.size(); i++) 
			if (books[i].date.find(object) != std::string::npos)
				selectedBooks.push_back(books[i]);
	}
	if (selectedBooks.size()) {
		std::cout << "Result:\n";
		printBook(selectedBooks);
	}
	else std::cout << "Nothing found!\n";
	std::cout << "Done!\n";
	pause();
	clear();
}
void save() {
	clear();
	std::cout << "6. Save.\n";
	std::ofstream outputFile("database/books.db");
	if (!outputFile.is_open()) {
        std::cout << "Can not connecting to the database.\n";
		return;
    }
	for (Book book:books) {
		outputFile << book.isbn      << "|" <<
					  book.title     << "|" <<
					  book.subject   << "|" <<
					  book.author    << "|" <<
					  book.publisher << "|" <<
					  book.date      << "|" <<
					  book.pages     << "|" <<
					  book.copies    << "\n";
	}
	outputFile.close();
	std::cout << "Done!\n";
	pause();
	clear();
}
void createUser() {
	clear();
	std::string userName, password = "", passwordConfirm = "", role = "";
	bool secondTime = false;
	std::cout << "7. Create new user.\n";
	std::cout << "Note: please do not use `|` character\n";
	std::cout << "Enter username: ";
	std::cin >> userName;
	while (users.find(userName) != users.end()) {
		clear();
		std::cout << "Username is already exist!\n";
		std::cout << "Enter username: ";
		std::cin >> userName;
	}
	do {
		password = "";
		passwordConfirm = "";
		clear();
		if (secondTime)
			std::cout << "Password and password confirm not match\n";
		std::cout << "Enter password: ";
		while (true) {
			int c = _getch();
			if (c == 13) {
				std::cout << "\n";
				break;
			}
			else if (c == 8) {
				if (password.length()) password.pop_back();
				std::cout << "\r\033[K" << "Enter password: " << mul("*", password.length());
			} else {
				std::cout << "*";
				password.push_back(c);
			}
			
		}
		std::cout << "Enter password confirm: ";
		while (true) {
			int c = _getch();
			if (c == 13) {
				std::cout << "\n";
				break;
			}
			else if (c == 8) {
				if (passwordConfirm.length()) passwordConfirm.pop_back();
				std::cout << "\r\033[K" << "Enter password confirm: " << mul("*", passwordConfirm.length());
			} else {
				std::cout << "*";
				passwordConfirm.push_back(c);
			}
		}
		secondTime = true;
	} while (password != passwordConfirm);
	secondTime = false;
	do {
		clear();
		role = "";
		if (secondTime)
			std::cout << "Please select correct role!\n";
		std::cout << "Role:\n";
		std::cout << "1. User\n";
		std::cout << "0. Admin\n";
		role.push_back(_getch());
		secondTime = true;
	}
	while (!(role == "1" || role == "0"));
	
	
	users[userName] = {password, role};
	
	std::ofstream outputFile("database/users.db");
	if (!outputFile.is_open()) {
        std::cout << "Can not connecting to the database.\n";
		return;
    }
	for (const auto& user : users) {
		outputFile << user.first << "|" << user.second[0] << "|" << user.second[1] << "\n";
	}
	outputFile.close();
	std::cout << "Done!\n";
	pause();
	clear();
}
void setPass() {
	int index = 0, secondTime = 0;
	std::string userName = "", password = "", passwordConfirm = "";
	clear();
	std::cout << "8. Set password for user.\n";
	std::cout << "OTI | User name\n";
	for (auto &user : users) {
		if (user.second[1] == "1")
			if (index < 10)
				std::cout << index << "   | " << user.first << "\n";
			else if (index < 100)
				std::cout << index << "  | " << user.first << "\n";
			else if (index < 1000)
				std::cout << index << " | " << user.first << "\n";
			else
				std::cout << index << "| " << user.first << "\n";
		index++;
	}
	do {
		if (secondTime)
			std::cout << "User name not found!\nPlease enter correct user name.\n";
		std::cout << "Enter user name: ";
		std::cin >> userName;
		secondTime = 1;
		std::cout << "Username: " << userName;
	}
	while (users.find(userName) == users.end());
	secondTime = 0;
	do {
		password = "";
		passwordConfirm = "";
		clear();
		if (secondTime)
			std::cout << "Password and password confirm not match\n";
		std::cout << "Enter password: ";
		while (true) {
			int c = _getch();
			if (c == 13) {
				std::cout << "\n";
				break;
			}
			else if (c == 8) {
				if (password.length()) password.pop_back();
				std::cout << "\r\033[K" << "Enter password: " << mul("*", password.length());
			} else {
				std::cout << "*";
				password.push_back(c);
			}
			
		}
		std::cout << "Enter password confirm: ";
		while (true) {
			int c = _getch();
			if (c == 13) {
				std::cout << "\n";
				break;
			}
			else if (c == 8) {
				if (passwordConfirm.length()) passwordConfirm.pop_back();
				std::cout << "\r\033[K" << "Enter password confirm: " << mul("*", passwordConfirm.length());
			} else {
				std::cout << "*";
				passwordConfirm.push_back(c);
			}
		}
		secondTime = 1;
	} while (password != passwordConfirm);
	users[userName] = {password, "1"};
	std::ofstream outputFile("database/users.db");
	if (!outputFile.is_open()) {
        std::cout << "Can not connecting to the database.\n";
		return;
    }
	for (const auto& user : users) {
		outputFile << user.first << "|" << user.second[0] << "|" << user.second[1] << "\n";
	}
	outputFile.close();
	std::cout << "Done!\n";
	pause();
	clear();
}
void deleteUser(std::string userName) {
	int option, index = 0, secondTime = 0;
	std::string username = "", password = "", passwordConfirm = "";
	std::cout << "9. Delete user.\n";
	do{
		std::cout << "1. Delete a view-only user.\n";
		std::cout << "0. Delete my user.\n";
		option = _getch();
	}
	while (!(option == 48 || option == 49));
	
	if (option == 48) {
		std::cout << "Are you sure?\n";
		std::cout << "1. Yes.\n";
		std::cout << "Any key else. No.\n";
		if (_getch() == 49) {
			users.erase(users.find(userName));
		}
	}
	else {
		clear();
		std::cout << "OTI | User name\n";
		for (auto &user : users) {
			if (user.second[1] == "1")
				if (index < 10)
					std::cout << index << "   | " << user.first << "\n";
				else if (index < 100)
					std::cout << index << "  | " << user.first << "\n";
				else if (index < 1000)
					std::cout << index << " | " << user.first << "\n";
				else
					std::cout << index << "| " << user.first << "\n";
			index++;
		}
		do {
			if (secondTime)
				std::cout << "User name not found!\nPlease enter correct user name.\n";
			std::cout << "Enter user name: ";
			std::cin >> username;
			secondTime = 1;
		}
		while (users.find(username) == users.end());
		users.erase(users.find(username));
	}
	std::ofstream outputFile("database/users.db");
	if (!outputFile.is_open()) {
        std::cout << "Can not connecting to the database.\n";
		return;
    }
	for (const auto& user : users) {
		outputFile << user.first << "|" << user.second[0] << "|" << user.second[1] << "\n";
	}
	outputFile.close();
	std::cout << "Done!\n";
	pause();
	clear();
}
void handleAdmin(std::string userName) {
	clear();
	int task = 0;

	while(true) {
		if (task == 48) {
		std::cout << "Quit?\n1. Yes\nAny key else. No";
		if (_getch() == 49) return;
		clear();
		}
		else if (task == 49) {
			std::cout << "1. Print all book in library.\n";
			printBook(books);
			pause();
			clear();
		} else if (task == 50)
			addBook();
		else if (task == 51)
			updateBook();
		else if (task == 52) 
			deleteBook();
		else if (task == 53)
			findBook();
		else if (task == 54)
			save();
		else if (task == 55)
			createUser();
		else if (task == 56)
			setPass();
		else if (task == 57)
			deleteUser(userName);
		printTask();
		task = _getch();
		clear();
	}
}
void handleLogin(int option) {
	std::string userName, password = "";
	if (option == 49) {
		getUserInfor(userName, password);
		while (!login(userName, password, "0"))
		{
			std::cout << "Incorrect username or password\n";
			pause();
			clear();
			getUserInfor(userName, password);
		}
		handleAdmin(userName);
	}
	else {
		std::cout << "1. User login\n";
		std::cout << "0. View only\n";
		if(_getch() == 49){
			clear();
			getUserInfor(userName, password);
			while (!login(userName, password, "1"))
			{
				std::cout << "Incorrect username or password\n";
				pause();
				clear();
				getUserInfor(userName, password);
			}
			handleViewOnly();
				
		}
		else {
			handleViewOnly();
		}
	}
}
int main() {
	int option;
	loadBook();
	loadUser();
	welcome(option);
	handleLogin(option);
	return 0;	
}

