#include <ios>
#include <string>
#include <fstream>
#include <filesystem>
#include <utility>
#include <iostream>
#include <ctime>

#define println(x) std::cout << x;;

std::string getln(){
  std::string x; std::cin >> x;
  return x;
}

struct date {
  int day;
  int month;
  int year;

  std::string construct(){
    std::time_t t = std::time(0);   // get time now
    std::tm* now = std::localtime(&t);

    day = now->tm_mday, month = now->tm_mon, year = now->tm_year + 1900;
    return std::string(std::to_string(day) + "/" + std::to_string(month) + "/" + std::to_string(year));
  }
};

struct ledger_entry {
  date date;
  std::string account_from;
  std::string account_to;
  int amount;
};

std::pair<std::ofstream, std::ofstream> init (ledger_entry entry){
  std::string account_to_ledger = std::string(entry.account_to + ".ledger"),
    account_from_ledger = std::string(entry.account_from + ".ledger");

  if (!std::filesystem::exists(account_to_ledger)){
    std::ofstream f(account_to_ledger);
    f << account_to_ledger << std::endl;
  }

  if (!std::filesystem::exists(account_from_ledger)){
    std::ofstream f(account_from_ledger);
    f << account_from_ledger << std::endl;
  }

  std::ofstream from_ledger(account_from_ledger, std::ios_base::app),
    to_ledger(account_to_ledger, std::ios_base::app);

  return std::make_pair(std::move(from_ledger), std::move(to_ledger));
}

void write_transaction (ledger_entry entry) {
  std::pair files = init(entry);
  files.first << std::string("to," + entry.account_to + "," + entry.date.construct() + "," + std::to_string(entry.amount)) << std::endl;
  files.second << std::string("from," + entry.account_from + "," + entry.date.construct() + "," + std::to_string(entry.amount)) << std::endl; 
}

ledger_entry construct_entry(){
  println("Sender's Name: ");
  std::string sender_name = getln();

  println("Reciever's Name: ");
  std::string receiver_name = getln();

  println("Amount: ")
  int amnt = std::stoi(getln());

  date current;
  current.construct();

  return ledger_entry {
    current,
    sender_name,
    receiver_name,
    amnt,
  };
}

int main(){
  ledger_entry x = construct_entry();
  write_transaction(x);
  return 0;
}
