#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
#include <vector>
#include <ctime>
#include <windows.h>
#include <conio.h>

using namespace std;

struct User
{
  string username = " ";
  double wealth_point = 10000;
  int happiness_point = 60;
};

struct Item
{
  string item_name = "";
  int quantity = 0;
  double price = 0;
  int happiness = 0;
};

struct History
{
  string detail = " ";
  double credit = 0;
  double debit = 0;
  int happy = 0;
  int sad = 0;
};

struct Stock
{
  string symbol = " ";
  string comp_name = " ";
  float market_cap = 0;
  int est_change = 0;
  int volume = 0;
};

struct Event
{
  string event_name = " ";
  double price = 0;
  int happiness = 0;
};

// Game setup
void delay(int milliseconds);
void setup(struct User &player);
void header(int day, string username, double wealth_point, int happiness_point);
void insurance_purchace(int day, string username, double wealth_point, int happiness_point);
// Stock section
void create_stock_list(Stock stock_arr[], const int stock_arr_sz); // Create stock list from file
void print_stock_list(Stock stock_arr[], const int stock_arr_sz); // Print stock list
void stock_ex(User &player, Stock stock_arr[], const int stock_arr_sz, int &comp_choice, int &money_invest, vector<History> &trx); // Driver for the stock function
void invest_process(User &player, Stock stock_arr[], const int stock_arr_sz, int &comp_choice, int &money_invest, vector<History> &trx); // Process for player to invest
void profit_cal(User &player, Stock stock_arr[], int &comp_choice, int &money_invest, vector<History> &trx); // Calculate money invest 
void random_generator(Stock stock_arr[], const int stock_arr_sz, int &randNum); // Random generate value
// Store section
void create_store_list(Item item_arr[], const int arr_sz); // Create store list from file
void print_item_detail(Item item_arr[], const int arr_sz); // Print store list
void store(struct User &player, Item item_arr[], const int arr_sz, vector<History> &trx); // Driver for the store function
void displayiPhone(); // iPhone display
void displayHuawei(); // Huawei display
void displayBook(); // Book display
void displayDessert(); // Dessert display
void displayNike(); // Nike display
void displayMusic(); // Music album display
// Work section
void work(struct User &player, vector<History> &trx); // Driver for the work function
void working_bar(); // Simulation of work
// Random event
void create_event_list(Event event_arr[], const int event_arr_size); //Create event list from file
void rand_event_car_acc();
void rand_event_flood();
void rand_event_tornado();
void rand_event_earthquake();
void rand_event_fire_acc();
// Other
void daily_expense(struct User &player, vector<History> &trx); // Calculation for the daily expense
void bank_interest(struct User &player, vector<History> &trx); // Calculation for the daily interest
void hist(struct User &player, vector<History> &trx); // Print history
void ending(struct User &player); // Show the ending of the game
// ASCII art
void displayconfusedcat();
void displayElizabethDunn();
void displayMonaLisa();
void greatestend();
void displayWarrenBuffett();
void displayWarrenBuffett2();
void displayUncleSam();
void displayJustRight();
void displayDisappointed();
void displayJackieChan();
void displaystockMarket();
void displayInsurance();
bool insurance = false;

int main() 
{
  srand(time(NULL));
  int comp_choice, money_invest;
  bool day_flag, work_flag;
  char choice;
  User player1;
  History temp_trx;
  bool stock_flag = false;
  bool event_flag = true;
  int randNum = 0;
  int day = 1; // count of day
  const int round = 5; // fixed number of rounds
  const int stock_arr_sz = 7; // fixed number of company
  const int item_arr_sz = 6; // fixed number of items
  const int place_arr_size = 4; // fixed number of place
  const int event_arr_size = 5; // fixed number of random events
  int rand_event_day = 2 + (rand() % (round - 1)); // Event happens at a random day //
  int rand_event_no = rand() % (round - 1); // Type of random event that happens //
  Stock stock_arr[stock_arr_sz] = {};
  Item item_arr[item_arr_sz] = {};
  Event event_arr[event_arr_size] = {};
  // Dynamic array
  vector<History> trx;
  string place_arr[place_arr_size] = {"Work", "Stock Exchange", "Store", "End of Day"};
  
  setup(player1);
  create_stock_list(stock_arr, stock_arr_sz);
  create_store_list(item_arr, item_arr_sz);
  create_event_list(event_arr, event_arr_size);
  
  for(; day < round + 1; day++)
  {
    cin.clear();
    day_flag = true;
    work_flag = true;
    stock_flag = false;
    comp_choice = 0;
    money_invest = 0;

    if(day == rand_event_day && event_flag == true)
    {
      system("cls");
      cout << "OH NO!\n\n";

      switch (rand_event_no)
      {
        case 0:
          rand_event_car_acc();          
          break;
        case 1:
          rand_event_flood();
          break;
        case 2:
          rand_event_tornado();
          break;
        case 3:
          rand_event_earthquake();
          break;    
        default:
          rand_event_fire_acc();
          break;
      }
      system("PAUSE");

    if (insurance == TRUE)
    {
      displayInsurance();

    }
    else
    {
      cout << "\n\t\tYou lost " << event_arr[rand_event_no].price << " wealth points and " 
           << event_arr[rand_event_no].happiness << " happiness points :( \n\n";
      event_flag = false;

      // Deduction from player
      player1.wealth_point = player1.wealth_point - event_arr[rand_event_no].price;
      player1.happiness_point = player1.happiness_point - event_arr[rand_event_no].happiness;

      // History record
      temp_trx.detail = "Random event";
      temp_trx.debit = event_arr[rand_event_no].price;
      temp_trx.sad = event_arr[rand_event_no].happiness;
      // Add transc hist into the vector array
      trx.push_back(temp_trx);

      system("PAUSE");  // A short pause and prompt user to press any key before continue
      system("cls");
    }
    }

    while(day_flag)
    {
      cin.clear();
      system("cls");
      header(day, player1.username, player1.wealth_point, player1.happiness_point);
      // Run the main menu here
      cout << "Where would you like to go?\n";
      
      if(work_flag)
      {
        for(int j = 0; j < place_arr_size; j++)
          cout << j + 1 << ". " << place_arr[j] << endl;
        
        cout << "\nChoice: ";
        cin >> choice;

        switch(choice)
        {
          case '1':
            cout << "\nWould you like to spend 5 happiness points to earn wealth points? [Y/N]\n";
            cout << "Choice: ";
            cin >> choice;

            if(choice == 'Y' || choice == 'y') 
            {
              system("cls");
              work(player1, trx);
              work_flag = false;
              system("PAUSE");
            }
            else if(choice == 'N' || choice == 'n')
              break;
            else
            {
              cout << "\nInvalid input! Please try again later..\n";
              system("PAUSE");
            } 
            break;
          case '2':
            system("cls");
            stock_ex(player1, stock_arr, stock_arr_sz, comp_choice, money_invest, trx);
            if(money_invest) 
              stock_flag = true;
            break;
          case '3':
            system("cls");
            store(player1, item_arr, item_arr_sz, trx);
            break;
          case '4':
            cout << "\nWould you like to end this round? [Y/N]\n";
            cout << "Choice: ";
            cin >> choice;

            if(choice == 'Y' || choice == 'y')        
              day_flag = false;
            else if (choice == 'N' || choice == 'n')
              break;
            else
              cout << "Invalid input! Please try again later...\n";
            
            cout << "\nWould you like to buy insurance for RM 1000 and 5 hapiness point? [Y/N]\n";
            cout << "Choice: ";
            cin >> choice;

            if(choice == 'Y' || choice == 'y'){        
              insurance = true;
              player1.wealth_point = player1.wealth_point - 1000;
              player1.happiness_point = player1.happiness_point - 5;
            }
            else if (choice == 'N' || choice == 'n')
              break;
            else
              cout << "Invalid input! Please try again later...\n";
            break;
          default:
            cout << "Invalid input! Please try again later..." << endl;
        }
      }
      // Show menu with no work option
      else 
      {
        for(int j = 1; j < place_arr_size; j++)
          cout << j << ". " << place_arr[j] << endl;
        
        cout << "\nChoice: ";
        cin >> choice;

        switch(choice)
        {
          case '1':
            system("cls");
            stock_ex(player1, stock_arr, stock_arr_sz, comp_choice, money_invest, trx);
            if(money_invest) 
              stock_flag = true;
            break;
          case '2':
            system("cls");
            store(player1, item_arr, item_arr_sz, trx);
            break;
          case '3':
            cout << "\nWould you like to end this round? [Y/N]\n";
            cout << "Choice: ";
            cin >> choice;

            if(choice == 'Y' || choice == 'y')        
              day_flag = false;
            else if (choice == 'N' || choice == 'n')
              break;
            else
              cout << "Invalid input! Please try again later...\n";
            
            cout << "\nWould you like to buy insurance for RM 1000 and 5 hapiness point? [Y/N]\n";
            cout << "Choice: ";
            cin >> choice;

            if(choice == 'Y' || choice == 'y'){        
              insurance = true;
              player1.wealth_point = player1.wealth_point - 1000;
              player1.happiness_point = player1.happiness_point - 5;
            }
            else if (choice == 'N' || choice == 'n')
              break;
            else
              cout << "Invalid input! Please try again later...\n";
            break;
          default:
            cout << "Invalid input! Please try again later..." << endl;
            system("PAUSE");
        }
      }           
    }
    cout << endl;
    // Before end of the day
    // Daily expenses are deducted from wealth points
    daily_expense(player1, trx);
    cout << endl;
    // Bank interest
    bank_interest(player1, trx);
    // Stock calculation
    random_generator(stock_arr, stock_arr_sz, randNum);
    if(stock_flag)
    {
      cout << "\nStock's return" << endl;
      profit_cal(player1, stock_arr, comp_choice, money_invest, trx);
    }

    system("PAUSE");
    system("cls");
  }

  ending(player1);
  hist(player1, trx);
    
  if(player1.happiness_point < 80 || player1.wealth_point < 15000)
  {
  	cout << "\t ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ \n\n";
  	cout << "\t Tip: \n\n";
    cout << "\t ~ Track and plan how much you spend daily\n";
    cout << "\t ~ Set long-term saving goals \n";
  	cout << "\t ~ Start an emergency fund \n";
    cout << "\t ~ Always check available balance and avoid overdrawing \n\n";
    cout << "\t ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ \n\n"; 
	}
	
  cout << "\n\n\tPlay Again?" << endl << endl;
  cout << "\tChoose [R] to Restart or any other key to exit.\t";
    	
  char choice_restart;
  cin >> choice_restart;

	if(choice_restart == 'R' || choice_restart == 'r')
	{
    cin.clear();
    system("cls");
    main();
  }
  else
    cout << "\n\tThank you for playing!\n\n\n";
  
  return 0;
}

// Do time delay
void delay(int milliseconds)
{
  // Storing start time 
  clock_t start_time = clock();

  // looping till required time is not achieved 
  while (clock() < start_time + milliseconds);
}

void setup(struct User &player) 
{
  string row1 = "888       888 d8b          .d8888b.                                  888";
  string row2 = "888   o   888 Y8P         d88P  Y88b                                 888";
  string row3 = "888  d8b  888             Y88b.                                      888";
  string row4 = "888 d888b 888 888 88888888 \"Y888b.   88888b.   .d88b.  88888b.   .d88888";
  string row5 = "888d88888b888 888    d88P     \"Y88b. 888 \"88b d8P  Y8b 888 \"88b d88\" 888";
  string row6 = "88888P Y88888 888   d88P        \"888 888  888 88888888 888  888 888  888";
  string row7 = "8888P   Y8888 888  d88P   Y88b  d88P 888 d88P Y8b.     888  888 Y88b 888";
  string row8 = "888P     Y888 888 88888888 \"Y8888P\"  88888P\"   \"Y8888  888  888  \"Y88888";
  string row9 = "                                     888                                 ";
  string row10 = "                                     888                                ";
  string row11 = "                                     888                                ";

  cout << row1 << endl;
  delay(50);
  cout << row2 << endl;
  delay(50);
  cout << row3 << endl;
  delay(50);
  cout << row4 << endl;
  delay(50);
  cout << row5 << endl;
  delay(50);
  cout << row6 << endl;
  delay(50);
  cout << row7 << endl;
  delay(50);
  cout << row8 << endl;
  delay(50);
  cout << row9 << endl;
  delay(50);
  cout << row10 << endl;
  delay(50);
  cout << row11 << endl << endl << endl;
  delay(50);

  system("PAUSE");
  system("cls");
  
  do
  {
    cout << "\n\tWhat's Your Name? ";
    getline(cin, player.username);
    system("cls");
  } while (player.username == "");

  system("cls");
  cout << "\n\tHello, " << player.username << "!! \n\n";
  cout << "\t1. You are given RM 10,000 Wealth Points and 50 Happiness Points to begin.\n";
  cout << "\t2. To win the game, you need to reach a target amount of RM 12,000 Wealth Points and 80 Happiness Points within 5 days.\n";
  cout << "\t3. Points can be spent and earned through selection of events.\n";
  cout << "\t4. 500 wealth points and 5 happiness points will be deducted each day for daily expenses.\n";
  cout << "\t5. Beware, random events that affect your points might happen anytime!\n";
  cout << "\n\n\tAre You A Wise Spender?\n\n" << endl;
  system("PAUSE");
  system("cls");
}

void header(int day, string username, double wealth_point, int happiness_point)
{
  cout << left << "Day: " << day;
  cout << setw(68) << right << "Username\t\t: " << username << endl;
  cout << setw(80) << right << "Wealth point\t: RM " << wealth_point << endl;
  cout << setw(80) << right << "Happiness point\t: " << happiness_point << "%" << endl;
  cout << "\n\n";
}

// Create the item array from a file
void create_store_list(Item item_arr[], const int arr_sz)
{
  ifstream fin("item_list.txt");

  if(fin.is_open() && !fin.eof())
  {
    for (int i = 0; i < arr_sz; i++)
    {
      fin >> item_arr[i].item_name 
          >> item_arr[i].quantity 
          >> item_arr[i].price
          >> item_arr[i].happiness;
    }
  }
  else
  {
    cerr << "Error detected. \"item_list.txt\" is not found..." << endl;
    system("PAUSE");
    exit(1);
  }

  fin.close();
}

// Print the item list
void print_item_detail(Item item_arr[], const int arr_sz)
{
  cout << left;
  cout << "---------------------------------------------------------------------------------" << endl;
  cout << setw(5) << "No." << setw(30) << "Item Name" << setw(10) << "Qty" << setw(18) << "Price (RM)" << setw(10) << "Happiness\n";
  cout << "---------------------------------------------------------------------------------" << endl;
  
  for (int i = 0; i < arr_sz; i++)
  {
    cout << setw(5) << i + 1;
    cout << setw(30) << item_arr[i].item_name;
    cout << setw(10) << item_arr[i].quantity;
    cout << setw(18) << fixed << setprecision(2) << item_arr[i].price;
    cout << setw(10) << item_arr[i].happiness << "\n";
  }
  return;
}

void stock_ex(User &player, Stock stock_arr[], const int stock_arr_sz, int &comp_choice, int &money_invest, vector<History> &trx)
{
  char choice;
  displaystockMarket();
  while(true)
  {
    print_stock_list(stock_arr, stock_arr_sz);
    cout << "\nDo you want to invest in stock exchange (Y/N): ";
    cin >> choice;

    if(choice == 'Y' || choice == 'y')
    {
      // Promt user to select a company to invests
      invest_process(player, stock_arr, stock_arr_sz, comp_choice, money_invest, trx);
      return;
    }
    else if(choice == 'N' || choice == 'n') // Back to main menu
    {
      cout << "Going back to the main menu...\n" << endl;
      system("PAUSE");
      system("cls");
      return;
    }
    else 
    {
      cout << "Invalid input! Please try again later..." << endl;
      system("PAUSE");
      system("cls");
    }
  }
}

void print_stock_list(Stock stock_arr[], const int stock_arr_sz)
{
  cout << "---------------------------------------------------------------------------------------------------------------" << endl;
  cout << left << setw(5) << "No." << setw(16) << "Stock Symbol" << setw(18) << "Companay name" 
       << setw(25) << "Market Cap(in Billion)" << setw(20) << "Estimate change" << setw(20) << "Volume(in Million)" << endl;
  cout << "---------------------------------------------------------------------------------------------------------------" << endl;

  // Loop that display all the values of the array
  for(int i = 0; i < stock_arr_sz; i++) 
  {
    cout << left << i + 1 << ".   " << setw(16) << stock_arr[i].symbol << setw(18) << stock_arr[i].comp_name << setw(25) 
         << stock_arr[i].market_cap << stock_arr[i].est_change << "%\t\t    "<< setw(20) << stock_arr[i].volume << endl;
  }
}

void random_generator(Stock stock_arr[], const int stock_arr_sz, int &randNum)
{
  for(int i = 0; i < stock_arr_sz; i++) //loop that randomize the stock market's change
  {
    randNum = rand() % 5;

    switch(randNum)
    {    
      case 0:
        stock_arr[i].market_cap = stock_arr[i].market_cap * 0.9;
        stock_arr[i].est_change = -10;
        stock_arr[i].volume = rand() % 91;
        break;
      case 1:
        stock_arr[i].market_cap = stock_arr[i].market_cap * 0.8;
        stock_arr[i].est_change = 10;
        stock_arr[i].volume = rand() % 91;
        break;
      case 2:
        stock_arr[i].market_cap = stock_arr[i].market_cap * 1.15;
        stock_arr[i].est_change = 15;
        stock_arr[i].volume = rand() % 91;
        break;
      case 3:
        stock_arr[i].market_cap = stock_arr[i].market_cap * 1.2;
        stock_arr[i].est_change = 20;
        stock_arr[i].volume = rand() % 91;
        break;
      case 4:
        stock_arr[i].market_cap = stock_arr[i].market_cap * 1.3;
        stock_arr[i].est_change = 30;
        stock_arr[i].volume = rand() % 91;
        break;
      default:
        break;
    }
  }
}

void create_stock_list(Stock stock_arr[], const int stock_arr_sz)
{
  ifstream fin("stock_list.txt");

  if(fin.is_open() && !fin.eof())
  {
    for(int i = 0; i < stock_arr_sz; i++)
    {
      fin >> stock_arr[i].symbol
          >> stock_arr[i].comp_name
          >> stock_arr[i].market_cap
          >> stock_arr[i].est_change
          >> stock_arr[i].volume;
    }
  }
  else
  {
    cerr << "Error detected. \"stock_list.txt\" is not found..." << endl;
    system("PAUSE");
    exit(1);
  }

  fin.close();
}

void invest_process(User &player, Stock stock_arr[], const int stock_arr_sz, int &comp_choice, int &money_invest, vector<History>& trx)
{
  History temp_trx;

  cout << "\nWhich company you want to invest in (1 to 7): "; 
  cin >> comp_choice;

  if (comp_choice < 1 || comp_choice > stock_arr_sz)
  {
    cout << "Invalid input! Please try again later..." << endl;
    system("PAUSE");
    system("cls");
  }
  else
  {
    cout << "\nHow much do you want to invest (in RM): ";
    cin >> money_invest;
    
    //Deduct the money invest from the player bank acc
    player.wealth_point = player.wealth_point - money_invest;

    // Record in transaction history
    temp_trx.detail = "Invest " + stock_arr[comp_choice - 1].comp_name;
    temp_trx.debit = money_invest;
    // Add transc hist into the vector array
    trx.push_back(temp_trx);
    
    cout << "Transaction is successfully done!" << endl;
    system("PAUSE");
    system("cls");
  }
}

void profit_cal(User &player, Stock stock_arr[], int &comp_choice, int &money_invest, vector<History>& trx)
{
  History temp_trx;

  if (stock_arr[comp_choice - 1].est_change < 0)
  {
    cout << "You had invested " << stock_arr[comp_choice - 1].comp_name << " with " << money_invest << endl;
    cout << "You had lost " << money_invest * 10/100 << " from the " << stock_arr[comp_choice - 1].comp_name << " company" << endl;
    
    money_invest = money_invest * 90/100;
    player.wealth_point = player.wealth_point + money_invest;
    
    // Record in transaction history
    temp_trx.detail = "Return " + stock_arr[comp_choice - 1].comp_name;
    temp_trx.credit = money_invest;
    temp_trx.sad = 2;
    // Add transc hist into the vector array
    trx.push_back(temp_trx);
  }
  else
  {
    cout << "You had invested " << stock_arr[comp_choice - 1].comp_name << " with " << money_invest << endl;
    cout << "You had earned " << money_invest * stock_arr[comp_choice - 1].est_change / 100 
         << " from the " << stock_arr[comp_choice - 1].comp_name << " company" << endl;

    money_invest += money_invest * stock_arr[comp_choice - 1].est_change / 100;
    player.wealth_point = player.wealth_point + money_invest;
    
    // Record in transaction history
    temp_trx.detail = "Return " + stock_arr[comp_choice - 1].comp_name;
    temp_trx.credit = money_invest;
    temp_trx.happy = 2;
    // Add transc hist into the vector array
    trx.push_back(temp_trx);
  }
}

// Store - a place for user to buy anything they want
void store(struct User &player, Item item_arr[], const int arr_sz, vector<History>& trx)
{
  int choice;
  char inner_choice;
  bool choice_flag = true;
  bool flag = true;
  History temp_trx;
  
  // Show the item cost and happiness for each item
  print_item_detail(item_arr, arr_sz);
  cout << "\nPlease enter the index of item to purchase it.\n";
  cout << "You may return to the main menu by entering '0'\n\n";
  cout << "Choice: ";
  cin >> choice;
  
  //Confirmation for purchase of item
  switch(choice)
  {
    case 1:
    case 2:
    case 3:
    case 4:
    case 5:
    case 6:
    {
      while(choice_flag)
      {  
        cout << "Item name: " << item_arr[choice - 1].item_name << endl;
        cout << "Item price: " << item_arr[choice - 1].price << endl;
        cout << "Happiness point: " << item_arr[choice - 1].happiness << endl;
        cout << "\nAre you sure you want to purchase this item? [Y/N]\n";
        cout << "Choice: ";
        cin >> inner_choice;

        if (item_arr[choice - 1].quantity == 0)
        {
          cout << "\nSorry. This product is out of stock...\n";
          system("PAUSE");
          choice_flag = false;
        }
        else if(inner_choice == 'Y' || inner_choice == 'y')
        {
          // Reduce the quantity of product
          item_arr[choice - 1].quantity--; 
          
          // Calculation for the points
          player.wealth_point = player.wealth_point - item_arr[choice - 1].price;
          player.happiness_point = player.happiness_point + item_arr[choice - 1].happiness;

          // Record in transaction history
          temp_trx.detail = item_arr[choice - 1].item_name;
          temp_trx.debit = item_arr[choice - 1].price;
          temp_trx.happy = item_arr[choice - 1].happiness;
          // Add transc hist into the vector array
          trx.push_back(temp_trx);

          if(choice == 1)
            displayiPhone();
          else if(choice == 2)
            displayHuawei();
          else if(choice == 3)
            displayBook();
          else if(choice == 4)
            displayDessert();
          else if(choice ==5)
            displayNike();
          else if(choice == 6)
            displayMusic();
        
          cout << "Thank you for your purchase. Have a nice day!\n";
          choice_flag = false;
          flag = false;
          system("cls");
        }
        else if(inner_choice == 'N' || inner_choice == 'n')
          choice_flag = false;
        else
        {
          cout << "Invalid input! Please try again later..\n";
          break;
        }
      }
    }
      break;
    case 0:
      return;
    default:
      cout << "Invalid input! Please try again later..\n";
      break;
  }
}

void work(struct User &player, vector<History> &trx)
{
  History temp_trx;
  
  working_bar();
  cout << "\n\nGreat work!\n";
  cout << "You had been paid with 2000 wealth point\n";

  player.wealth_point = player.wealth_point + 2000;
  player.happiness_point = player.happiness_point - 5;

  // Record in transaction history
  temp_trx.detail = "Work";
  temp_trx.credit = 2000;
  temp_trx.debit = 0;
  temp_trx.happy = 0;
  temp_trx.sad = 5;
  // Add transc hist into the vector array
  trx.push_back(temp_trx);
}

void working_bar()
{
	// Initialize char for printing
	// loading bar
	char a = 177, b = 219;

	printf("\n\n");
	printf("\t\tWorking...\n\n");
  printf("\t\t");

	// Print initial loading bar
	for (int i = 0; i < 26; i++)
		printf("%c", a);

	// Set the cursor again starting
	// point of loading bar
	printf("\r");
  printf("\t\t");

	// Print loading bar progress
	for (int i = 0; i < 26; i++) 
  {
		printf("%c", b);

		// Sleep for 1 second
		Sleep(150);
	}
}

void daily_expense(struct User &player, vector<History> &trx)
{
  History temp1_trx;
  
  cout << "Daily expense\n";
  cout << "Wealth point: -RM 500\n";
  cout << "Happiness: -5\n";

  player.wealth_point = player.wealth_point - 500;
  player.happiness_point = player.happiness_point - 5;

  // Record
  temp1_trx.detail = "Daily Expenses";
  temp1_trx.debit = 500;
  temp1_trx.sad = 5;
  trx.push_back(temp1_trx);
}

void bank_interest(struct User &player, vector<History> &trx)
{
  History temp1_trx;

  cout << fixed << setprecision(2);
  cout << "Bank interest\n";
  cout << "Wealth point: +RM " << player.wealth_point * 0.015 << endl;
  cout << "Happiness: +1\n";

  // Record
  temp1_trx.detail = "Bank Interest";
  temp1_trx.credit = player.wealth_point * 0.015;
  temp1_trx.happy = 1;
  trx.push_back(temp1_trx);

  player.wealth_point = player.wealth_point * 1.015;
  player.happiness_point = player.happiness_point + 1;
}

void hist(struct User &player, vector<History> &trx)
{
  double total_credit = 10000;
  double total_debit = 0;
  int total_happy = 50;
  int total_sad = 0;

  cout << "\n\n\t\tTransaction History\n\n";
	cout << "\t\t---------------------------------------------------------------------------------------------------------------\n";
	cout << "\t\t No. |  Details                          |  Debit (RM)   |  Credit (RM)   |  Happiness (-)  |  Happiness (+)   \n";
	cout << "\t\t---------------------------------------------------------------------------------------------------------------\n";
  cout << "\n\t\t " << setw(7) << left << " " << setw(36) << left << " " << setw(16) << left << " " << setw(17) << left 
       << "10000.00" << "20" << "\n\n";

  int x = trx.size();

  for(int i = 0; i < x; i++)
  {
    total_credit += trx[i].credit;
    total_debit += trx[i].debit;
    total_happy += trx[i].happy;
    total_sad += trx[i].sad;

     cout << "\t\t " << setw(7) << left << i + 1 << setw(36) << left << trx[i].detail << setw(16) << left << trx[i].debit << setw(17) << left 
	  << trx[i].credit  << "-" << setw(17) << left << trx[i].sad << "+" << setw(19) << left << trx[i].happy << "\n";
  }

  cout << "\n\t\t---------------------------------------------------------------------------------------------------------------\n";
  cout << "\t\t                                            "<< setw(16) << left << total_debit << setw(17) << left << total_credit << setw(18) 
       << left << total_sad << total_happy;     
  cout << "\n\t\t---------------------------------------------------------------------------------------------------------------\n";
  cout << "\t\t                                            "<< setw(16) << left << "Money left : " << setw(17) << left << player.wealth_point 
       << setw(18) << left << "Happiness :" << player.happiness_point;

  cout << "\n\n\n\n\t\t";
  system("PAUSE");
  system("cls");
}

void ending(struct User &player)
{
  cout << "\n\tYou've reached the end of this game!\n\n";

  if (player.happiness_point >= 80 && player.wealth_point >= 12000)
  {
    greatestend();
    cout << "\n\n\t\tCongratulations! You are a wise spender!";
  }

  if (player.wealth_point >= 12000)
    displayWarrenBuffett2();
  else if (player.wealth_point >= 12000 && player.wealth_point < 15000)
    displayWarrenBuffett();
  else if (player.wealth_point >= 10000 && player.wealth_point < 12000 )
    displayUncleSam();
  else if (player.wealth_point >= 5000 && player.wealth_point < 10000)
    displayJustRight();
  else if (player.wealth_point >= -2000 && player.wealth_point < 5000)
    displayDisappointed();
  else if (player.wealth_point < -2000)
    displayJackieChan();

  if (player.happiness_point >= 80)
    displayMonaLisa();
  else if (player.happiness_point >= 50 && player.happiness_point < 80)
    displayElizabethDunn();
  else if (player.happiness_point < 50 )
    displayconfusedcat();
  
  system("cls");
  cout << "\t\n\t _______________________________________________________ " << endl; 
  cout << "\t|  ____________________________________________________  |" << endl;
  cout << "\t|  |                                                   | |" << endl;
  cout << "\t|  |                                                   | |" << endl;
  cout << "\t|  |                                                   | |" << endl;
  cout << "\t|  |             $$$ MONEY LEFT: " << left << setw(22) << player.wealth_point <<  "| |" << endl; 
  cout << "\t|  |             >v< HAPPINESS : " << left << setw(22) << player.happiness_point <<  "| |" << endl;
  cout << "\t|  |                                                   | |" << endl;
  cout << "\t|  |___________________________________________________| |" << endl;
  cout << "\t|________________________________________________________|" << endl;
       
  cout << "\n\tPress any key to continue and find out why ...";
  	
  getch();
  system("cls");
}

void displayiPhone()
{
    cout << "\n ~~This is your new iPhone 15 Pro Max~~                  " << endl;
    cout << "\n                         ,*vwwwwwwwwwwwwwwwwwwwwww~**,   " << endl;
    cout << "                        /'  __________                \\   " << endl;
    cout << "                        [  /@@@@      \\                ]  " << endl;
    cout << "                        [ | @@@@  @@@@ |               ]   " << endl;
    cout << "                        [ |       @@@@ |               ]   " << endl;
    cout << "                        [ | @@@@       |               ]   " << endl;
    cout << "                        [ | @@@@       |               ]   " << endl;
    cout << "                        [  \\__________/                ]  " << endl;
    cout << "                        [                              ]   " << endl;
    cout << "                        [                              ]   " << endl;
    cout << "                        [                              ]   " << endl;
    cout << "                        [                              ]   " << endl;
    cout << "                        [              .:'             ]   " << endl;
    cout << "                        [           __ :'__            ]   " << endl;
    cout << "                        [        .'`  `-'  ``.         ]   " << endl;
    cout << "                        [       :          .-'         ]   " << endl;
    cout << "                        [       :         :            ]   " << endl;
    cout << "                        [        :         `-;         ]   " << endl;
    cout << "                        [         `.__.-.__.'          ]   " << endl;
    cout << "                        [                              ]   " << endl;
    cout << "                        [                              ]   " << endl;
    cout << "                        [                              ]   " << endl;
    cout << "                        [                              ]   " << endl;
    cout << "                        [                              ]   " << endl;
    cout << "                        [                              ]   " << endl;  
    cout << "                        [                              ]   " << endl;
    cout << "                        [                              ]   " << endl;
    cout << "                        [                              ]   " << endl;
    cout << "                        'L                           ,/    " << endl;
    cout << "                          \"*vwwwwwwwwwwwwwwwwwwwwww~^     " << endl;

    cout << "\n\t\t\t\t\t " ;
    system("pause"); // A short pause and promt user to press any key before continue

    return;

}  

void displayHuawei()
{
    cout << "\n ~~This is your new Huawei Phone~~                  " << endl;
    cout << "\n                         ,*vwwwwwwwwwwwwwwwwwwwwww~**,   " << endl;
    cout << "                        /'  ____                       \\  " << endl;
    cout << "                        [  /@@@@\\                      ]  " << endl;
    cout << "                        [ | @@@@ |                     ]   " << endl;
    cout << "                        [ |      |                     ]   " << endl;
    cout << "                        [ | @@@@ |                     ]   " << endl;
    cout << "                        [ | @@@@ |                     ]   " << endl;
    cout << "                        [  \\____/                      ]  " << endl;
    cout << "                        [                              ]   " << endl;
    cout << "                        [                              ]   " << endl;
    cout << "                        [                              ]   " << endl;
    cout << "                        [            g     g           ]   " << endl;
    cout << "                        [           ggg   ggg          ]   " << endl;
    cout << "                        [       ;  $$$$L L$$$$ ;       ]   " << endl;
    cout << "                        [       @@, $$$@ @$$$ ,@@      ]   " << endl;
    cout << "                        [    ;  @@@g @@$ $@@ g@@@  ;   ]   " << endl;
    cout << "                        [    ]@  %$@@ $$ $$ @@$%  @[   ]   " << endl;
    cout << "                        [     %@@@ (*&/  \\&*) @@@%     ]  " << endl;
    cout << "                        [      \\g]]@@F    ]@@[[g/      ]  " << endl;
    cout << "                        [        '*5\"        \"*        ] " << endl;
    cout << "                        [                              ]   " << endl;
    cout << "                        [                              ]   " << endl;
    cout << "                        [                              ]   " << endl;
    cout << "                        [                              ]   " << endl;
    cout << "                        [                              ]   " << endl;  
    cout << "                        [                              ]   " << endl;
    cout << "                        [                              ]   " << endl;
    cout << "                        [                              ]   " << endl;
    cout << "                        'L                           ,/    " << endl;
    cout << "                          \"*vwwwwwwwwwwwwwwwwwwwwww~^     " << endl;

    cout << "\n\t\t\t\t\t " ;
    system("pause"); // A short pause and promt user to press any key before continue

    return;

}  

void displayBook()
{
    cout << "\n~~This is your new Book~~            " << endl;
    cout << "        _________   _________          " << endl;
    cout << "   ____/      452\\ /     453 \\____   " << endl;
    cout << " /| ------------- |  ------------ |\\  " << endl;
    cout << "||| To be or not  | ------------- |||  " << endl;
    cout << "||| to be?        | ------------- |||  " << endl;
    cout << "||| That is the   | ------------- |||  " << endl;
    cout << "||| Question      | ------------- |||  " << endl;
    cout << "||| ~Shakespeare  | ------------- |||  " << endl;
    cout << "|||  ------------ | ----------    |||  " << endl;
    cout << "||| ------------- |  ------------ |||  " << endl;
    cout << "||| ------------- | ------------- |||  " << endl;
    cout << "||| ------------- | ------ -----  |||  " << endl;
    cout << "||| ------------  | ------------- |||  " << endl;
    cout << "|||_____________  |  _____________|||  " << endl;
    cout << "L/_____/--------\\_//W-------\\_____\\J" << endl;

    cout << "\n\t\t\t\t\t " ;
    system("pause"); // A short pause and promt user to press any key before continue

    return;
}

void displayDessert()
{
    cout << "\n~~This is your Dessert~~            " << endl;
    cout << "                                           ,@*^\"**Nmg     @*\"%      " << endl;
    cout << "                                           *&g     g '&g @-  @-       " << endl;
    cout << "                                             ]P    \"&g  %@  ]P    ,g " << endl;
    cout << "                                    *Nwg     gC      *%  ]K,@   gC`*$ " << endl;
    cout << "                                       7*Ngg@gg        M  ]@` ,@\\  gP" << endl;
    cout << "                                      ggN@7b  *]g         ]PNgP   @L  " << endl;
    cout << "                                    gP\" $-  *   &pP*****Nw@C@\"  )P  " << endl;
    cout << "                                   $P   ]b     gP         ?&g  g]C    " << endl;
    cout << "                                   @      \"?M@C`            ]b@-j[   " << endl;
    cout << "                                  ,$gggggggg$Qggggggggggggggg$gg@g;   " << endl;
    cout << "                                )P-    @              ]r          !]g " << endl;
    cout << "                                ]C     @     ;ggg     ]r            @ " << endl;
    cout << "                                 @     @    #C  -$    ]r           #C " << endl;
    cout << "                                 ]g    ]g  ;@    $-   ]r          ]F  " << endl;
    cout << "                                  ]g    `""=     $-   ]r         ,K   " << endl;
    cout << "                                   ]g            $-   $F        )K    " << endl;
    cout << "                                    ]b           $`   ]C       gF     " << endl;
    cout << "                                     ^&g         ?&gggP      ,@*      " << endl;
    cout << "                                       ]Ng                 ,@C        " << endl;
    cout << "                                         ]%w,           ,gP*          " << endl;
    cout << "                                            \"*MNgggggmPP*            " << endl;
    cout << "                                               gC   7@                " << endl;
    cout << "                                        yggggm**     '*Nwggg,         " << endl;
    cout << "                                       #F                   7@        " << endl;
    cout << "                                       7NmwwwwwwwwwwwwwwwwwmNL        " << endl;

    cout << "\n\t\t\t\t\t " ;
    system("pause"); // A short pause and promt user to press any key before continue

    return;
}

void displayNike()
{
    cout << "\n~~This is your new Nike shoe~~" << endl;
    cout << "                                                         ,,," << endl;
    cout << "                                                      g@N""*BN," << endl;
    cout << "                                                     @K       %@g" << endl;
    cout << "                                                    ]@          *@g" << endl;
    cout << "                                                    @P           ,@@," << endl;
    cout << "                                                   $@     g@$@   @P\"%N" << endl;
    cout << "                                                  g@-   g@P@@   ]@   \"@g" << endl;
    cout << "                                               ,@@\"   ,@P,@P    ]@     %@," << endl;
    cout << "                                     ,,,ggg@@NP\"    ,@@ g@\"      ]@,    \"@g" << endl;
    cout << "                               ,g@NPP*"" y@P    ,,gg@` g@W,        BN    ]@@" << endl;
    cout << "                            ,g@P       ,@@gg@@M*\"]@P  @P-`\"BN       \"@g  @K$@" << endl;
    cout << "                           @@\"N@p     @@N*\"    ,@P  ,@C     ]@        \"$@P -@" << endl;
    cout << "                         ,g@\"*NP-   g@\"      ,@@-  g@       -@P      ,@@\"  ]@" << endl;
    cout << "                        $@\"*@p   ,g@@       g@\"   @@         @P   ,g@P    g@`" << endl;
    cout << "                      gg@\"*NP    @@@g     g@C   ,@P         ]@  g@P`    g@P" << endl;
    cout << "                     ]@g\"$@     ]@P\"Bg,,g@P    g@`         g@W@P`    ,g@\"" << endl;
    cout << "                   gp@@\"MM`    ]@@L  `\"*`     @@         ,@@P\"    ,g@\"`" << endl;
    cout << "                   @g,j@p     /@ ]@         ,@P       ,g@P\"    ,g@*`" << endl;
    cout << "                ,g@@,\"P**N@Ng/@`  %@      ,@@      ,g@P\"    ,g@*-" << endl;
    cout << "                ]@w,$@      \"R@g,  \"N@gg@@*-     g@P\"    ,g@*-" << endl;
    cout << "               ,@P`""          '*@w           g@P\"    ,g@*-" << endl;
    cout << "              g@"                 "@g      g@P*    ,g@P-" << endl;
    cout << "             @@                     ]@, g@P*    ,g@P-" << endl;
    cout << "           g@\"                       g@P*    ,g@P-" << endl;
    cout << "         ,@@@Ngg,                 g@P*    ,g@*-" << endl;
    cout << "       ,@P     `\"*BN,          g@P`    ,g@*-" << endl;
    cout << "      g@\"           %@,     g@P\"    ,g@P-" << endl;
    cout << "    ,@P              ]@  g@N\"    ,g@P-" << endl;
    cout << "    @P               @@@N\"    ,g@P-" << endl;
    cout << "   @@              g@N\"    ,g@P-" << endl;
    cout << "   @P          ,g@P\"    ,g@*-" << endl;
    cout << "   %@      ,g@@*\"    ,g@*-" << endl;
    cout << "    %@@@@NP\"`    ,g@@P-" << endl;
    cout << "     *@w,  ,,gg@NP'" << endl;
    cout << "        \"\"*\"\"\"-" << endl;

    cout << "\n\t\t\t\t\t " ;
    system("pause"); // A short pause and promt user to press any key before continue

    return;
}

void displayMusic()
{
    cout << "\n~~This is your new Ed Sheran music album~~" << endl;
    cout << "\n  ______    _    _____ _  " << endl;
    cout << " |  ____|  | |  / ____| |                         " << endl;
    cout << " | |__   __| | | (___ | |__   ___  ___ _ __ __ _ _ __ " << endl;
    cout << " |  __| / _` |  \\___ \\| '_ \\ / _ \\/ _ \\ '__/ _` | '_ \\ " << endl;
    cout << " | |___| (_| |  ____) | | | |  __/  __/ | | (_| | | | |" << endl;
    cout << " |______\\__,_| |_____/|_| |_|\\___|\\___|_|  \\__,_|_| |_|" << endl;
    cout << "\n                     :+""  ~<<::""+:" << endl;
    cout << "                +Xi<<<<!<  `<<!?!<<<HMti%L" << endl;
    cout << "            :?HMMMM:<<<!<~ <<<!X<<<!MM88MMh?x" << endl;
    cout << "          !HMRMMRMMM:<<<!< <<<!!<<<MR88MRMMRMH?." << endl;
    cout << "        ?NMMMMMMMMMMM<<<?<  <<!!<<XM88RMMMMMMMMM?" << endl;
    cout << "      !88888MMMMMMRMMk<<!!  <<H!<<M88MRMMRMMMRMMRM!" << endl;
    cout << "     <M8888888MMMMMMMM:<<!  <<H<<488RMMMMMMMMMMMMMM>:" << endl;
    cout << "   xHMRMMR888888RMMMMMM<<!< <!!<<988RMMMRMMRMMMMM?!<<%" << endl;
    cout << "  :XMMMMMMMM88888MMMMMMH<<~ ~~~<X8RMMMMMMMMMMM!!<~    k" << endl;
    cout << "  <<<!MMRMMRMMR8888MMP.n~       #R.#MMRMMRM?<~~   .nMMh." << endl;
    cout << " !MMH:<<<!*MMMMMMM8Pu! n\"       \"+ \"h!MM!!~   :@MMMMMMM/" << endl;
    cout << ".HMRMMRMMMH:<<\"*RM M @             * \"   .nMMMMMMMRMMRMMk" << endl;
    cout << "MMMMMMMMMMMMMMMMx < \"      .u.        4'MMMMMMMMMMMMMMMM9" << endl;
    cout << "!RMMRMMMRMMRMMMMMX M     @P   #8     4 MMRMMMRMMRMMMMMMR<" << endl;
    cout << "!MMMMMMMMMMMMMMMMM !    '8     8!    ' MtMMMMMMMMMMMMMMM!" << endl;
    cout << "kMMRMMRMMRMMMRMMR4 H     #8.  @8     H MMMMRMMMMMMRMMRMM!" << endl;
    cout << "MMMMMMMMMMMMMMMMM>M         \"`      .~i <!?MMMMMMMMMMMMM9" << endl;
    cout << "'9MMRMMMRMMRMMP!   : %             H @ 8NRMHx<<<!!MMMMMR!" << endl;
    cout << " >MMMMMMMMM\"   <<HMk!i *u       .* x*xR88888MMMMHi<<<<~<" << endl;
    cout << "  !RMM#~   :<:MMRMMMMH.*n:      :*.HRMMMRM8888888MRMMM!" << endl;
    cout << "  !     <<:tMMMMMMMMMM8RM<::: :<<XMMMMMMMMMR88888888MM!" << endl;
    cout << "   ~ <<<XHMRMMMMMMRMM8RM<<<<< `!<<MRMMRMMRMMMRR888888#" << endl;
    cout << "     :HMMMMMMMMMMMM988MM<<X!<~'~<<<MMMMMMMMMMMMMR88#!" << endl;
    cout << "      ~MMRMMMRMMRMM88MM<<<?<<  <<<<!RMMMRMMRMMMMMM!" << endl;
    cout << "        xMMMMMMMM988MM%<<<?<<: <!<<<?MMMMMMMMMMMX" << endl;
    cout << "          !?MMMM@88MMR<<<<!<<<  <:<<<MRMMRMMMP!" << endl;
    cout << "            \"X*988RMM!<<<?!<<~  <!<<<<MMMMM?\"" << endl;
    cout << "                !X*MM<<<<H!<<`  <?<<<<<)!" << endl;
    cout << "                     \"+:uX!<<< .::+\"\"" << endl;

    cout << "\n\t\t\t\t\t " ;
    system("pause"); // A short pause and promt user to press any key before continue

    return;
}

void create_event_list(Event event_arr[], const int event_arr_size)
{
  ifstream fin("event_list.txt");

  if(fin.is_open() && !fin.eof())
  {
    for (int i = 0; i < event_arr_size; i++)
    {
      fin >> event_arr[i].event_name 
          >> event_arr[i].price
          >> event_arr[i].happiness;
    }
  }
  else
  {
    cerr << "Error detected. \"event_list.txt\" is not found..." << endl;
    system("PAUSE");
    exit(1);
  }
  fin.close();
}

void rand_event_car_acc()
{
  cout << "\n\t\t\t~~You are involved in a car accident~~" << endl;
  cout << "\n                                      ]@|      ,@@@@@@   " << endl;
  cout << "                                     ]@|     g@P         " << endl;
  cout << "                                     ]@g ,g@@@@gggggg    " << endl;
  cout << "                                       ,@@@@@@P\"    @K  " << endl;
  cout << "                                      J@@@\"%@g     #@   " << endl;
  cout << "                                           ]@            " << endl;
  cout << "   ------------------@@@@@@@@@@@@BBBB@@@,   j@           " << endl;
  cout << "                  ,@@@@P`      ]@@       *@Ng            " << endl;
  cout << "  --------------$@@@@@Q        ]@@        ,]@@@@@@@@@Ng, " << endl;
  cout << "             ]@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@g| " << endl;
  cout << "    --------j@@@@Qgp@g*@@@@@@@@@@@@@@@@@@@@@Cg@@N@%@@@@K " << endl;
  cout << "       ----MM*%@@U@@@@@@]@@@@@@@@@@@@@@@@@@@@$@@@@@P$@@P " << endl;
  cout << "                  %@@@@C                      %@@@C      " << endl;
}

void rand_event_flood()
{
  cout << "\n\t\t\t~~You are involved in a Flood~~" << endl;
  cout << "\n                                           ,gg@P\"Bg                                     " << endl;
  cout << "                                      ,gg@P\"`-     *@,   ,,                             " << endl;
  cout << "                                ,gg@P*`              %@  @C\"*RBNwg,                     " << endl;
  cout << "                          ,gg@R*\"            ,,g,     \"%W@P**NBggg@K                   " << endl;
  cout << "                    ,,g@NP\"            ,,g@N*\"-`%@      \"@,     -@\"                  " << endl;
  cout << "              ,,g@N*\"`           ,,g@NP\"        \"Bg      %@    @P                    " << endl;
  cout << "              $@            ,g@NP\"                  %W     \"@,                        " << endl;
  cout << "               @p     ,g@@P\"`             ,ggg       %@      \"B@`                      " << endl;
  cout << "               '@gg@@P\"                 @P-  `%@       %W      *@,                      " << endl;
  cout << "                -  $@                  $[      ]@       \"@g      %N                     " << endl;
  cout << "                  ,@                   ]@,    ,@C         ]@,     \"Bg                   " << endl;
  cout << "                  @P                     *N@@N*-            %N      ]@,                  " << endl;
  cout << "                 ]@                                          \"Bg      %@                " << endl;
  cout << "                 @`              ,@Bgg,,                       *@,      @g               " << endl;
  cout << "                @P               @P   -\"*RNNgg,                 ]@b  ,gN\"              " << endl;
  cout << "               ]@               ]@            `@`               @-\"B@\"                 " << endl;
  cout << "               @P               @-            $K               @P                        " << endl;
  cout << "              ]@               @P            ]@               ]@                         " << endl;
  cout << "              @               ]@             @P               @C                         " << endl;
  cout << "           , @P          ,,   B-       ,,   ]@        ,      $K     ,                    " << endl;
  cout << "         ,@P%@         ,gP%N         ,g@%@,         g@*@,   ]@    g@*@,                  " << endl;
  cout << "    ggg@M\"   `*BNpggg@N\"-   *NNpggg@N*    *NNggggg@*    \"NBg@@gg@P\"   \"MBggg        " << endl;
  cout << "\n";
  cout << "          g@@,          g@@,          ,@Bg          ,@Bg          ,@BW                   " << endl;
  cout << "     ,,g@N\"  *Bgg,,,,ggN\"  \"Bgg,,,,gg@*  *%Ng,,,,,g@*  \"NNg,,,,,g@P  NNg,,,          " << endl;
  cout << "    \"\"`-         \"\"\"'          '\"\"\"         -`\"\"\"        -\"\"\"-          `\"" << endl;
}

void rand_event_tornado()
{
  cout << "\n\t\t\t~~You are involved in a Tornado~~" << endl;
  cout << "\n               . '@(@@@@@@@)@. (@@) `  .   '      " << endl;
  cout << "     .  @@'((@@@@@@@@@@@)@@@@@)@@@@@@@)@            " << endl;
  cout << "     @@(@@@@@@@@@@))@@@@@@@@@@@@@@@@)@@` .          " << endl;
  cout << "  @.((@@@@@@@)(@@@@@@@@@@@@@@))@\\@@@@@@@@@)@@@  .  " << endl;
  cout << " (@@@@@@@@@@@@@@@@@@)@@@@@@@@@@@\\@@)@@@@@@@@)      " << endl;
  cout << "(@@@@@@@@)@@@@@@@@@@@@@(@@@@@@@@//@@@@@@@@@) `      " << endl;
  cout << " .@(@@@@)##&&&&&(@@@@@@@@)::_=(@\\@@@@)@@ .   .'    " << endl;
  cout << "   @@`(@@)###&&&&&!!;;;;;;::-_=@@\\@)@`@.           " << endl;
  cout << "   `   @@(@###&&&&!!;;;;;::-=_=@.@\\@@     '        " << endl;
  cout << "      `  @.#####&&&!!;;;::=-_= .@  \\               " << endl;
  cout << "            ####&&&!!;;::=_-        `               " << endl;
  cout << "             ###&&!!;;:-_=                          " << endl;
  cout << "              ##&&!;::_=                            " << endl;
  cout << "             ##&&!;:=                               " << endl;
  cout << "            ##&&!:-                                 " << endl;
  cout << "           #&!;:-                                   " << endl;
  cout << "          #&!;=                                     " << endl;
  cout << "          #&!-                                      " << endl;
  cout << "           #&=              /\\`````\\              " << endl;
  cout << "   *        #&-            /  \\`````\\             " << endl;
  cout << "            \\\\#/'          |[]| []  |             " << endl;
}

void rand_event_earthquake()
{
  cout << "\n\t\t\t~~You are involved in an Earthquake~~" << endl;
  cout << "\n              ,                                                  g" << endl;
  cout << "               \"N                                            g gP  " << endl;
  cout << "                 *g    g                                   ,@)@,m   " << endl;
  cout << "                   g   %,                     ,N\"B       g\"gC@`   " << endl;
  cout << "                %,  \"B   \"N                ,gP\"    ]g     .PyP   " << endl;
  cout << "                 \"N   ]N   \"N           ,N\"`        ]     `      " << endl;
  cout << "                   \"N   ]g   \"      ,gP\"            $            " << endl;
  cout << "                     ]g   %      ,N\"`               $  $g          " << endl;
  cout << "                           \" ,gP\"                   @  @ N        " << endl;
  cout << "                          ,N\"-                    ,gN  @  p        " << endl;
  cout << "                         $,,                 ,gP*` ,,gNP   ]g       " << endl;
  cout << "                            -$`        ,gmP\",,gmP\"`          B    " << endl;
  cout << "                             @        ,PyR*\"-                 ]p   " << endl;
  cout << "                            $-       )P]P                      \"N  " << endl;
  cout << "                            @       ,PgP                   ]PNmggP  " << endl;
  cout << "                           $-      ,Pg\"   NMNmgg           @       " << endl;
  cout << "                           @      ,P@`   @      @         ]P        " << endl;
  cout << "                     @-""*PNmgg, ,K@     P     ]P         @         " << endl;
  cout << "                    @           - ""*RNw@,,    @         ]P         " << endl;
  cout << "                   @    @*PNmgg,           `""*PNmgg,   ,@          " << endl;
  cout << "                  @    @                             ,@P gNp        " << endl;
  cout << "                 K    @            @\"``\"*MNwg,,    gP-,@\"  \"N   " << endl;
  cout << "               ,P    `           ,P   @*PNmwgg,,,"" gP-      ]g     " << endl;
  cout << "               BwwwwwwwwwwwwwwwwN`   &wwwwwwwwwwwwwwwwwwwwwwwwwB    " << endl;
}

void rand_event_fire_acc()
{
  cout << "\n\t\t\t~~Your house is on fire~~" << endl;
  cout << "\n                                                              gg                " << endl;
  cout << "                                                            ,@\"@                 " << endl;
  cout << "                                                         ,g@\"  $F                " << endl;
  cout << "                                                   ,ggmN*\"     @                 " << endl;
  cout << "                                             ,,  ,@\"          #F                 " << endl;
  cout << "        %@mg       @*****]@                 /P g,@     ,     gF                   " << endl;
  cout << "         %r *b,    @     ]@        ,g@%mg  ]K  \"N    g@$L   @@g@K                " << endl;
  cout << "         ][   g ,,@     ]@      g@\"     *N@     ,g@P` ]@      @F                 " << endl;
  cout << "         @F    ]@@M@     ]@   ,@P          \"g ,@\"     ][     ,@                 " << endl;
  cout << "        gP      \"` @     ]@,gN`     g@*B,     *$g      @`     @                  " << endl;
  cout << "        @   '@Nm,  @     ]@\"     ,@P`   \"g     `%m,  @C    g@`                  " << endl;
  cout << "        ]@   %  `%W@  ,gP`     g@\"         \"Bg     \"%@@,gg@P\"                 " << endl;
  cout << "      ]@m@@  @    '@g@\"     ,@*   ,g@M*MBg   `%m,     *b,                        " << endl;
  cout << "       ]g    $   ,gP     ,gP\"    ]@      \"@     \"%w     \"g                    " << endl;
  cout << "        `%m,,]@g@\"     g@\"       @C       #F       *b,    @@@,                  " << endl;
  cout << "            ,@P     ,gP`          %w    ,gP          \"@g  @`%@@m,                " << endl;
  cout << "         ,gN`     g@\"               \"***\"               *B@   $,*g             " << endl;
  cout << "       ,@\"     ,@$[                                      ]K    %L '%b            " << endl;
  cout << "       @    ,gN` ][     RRRRRRRRRRRRRRRRRRRRRRRRRRRRF   /@      $   ]@            " << endl;
  cout << "        *N%N\"    ][                                    gP       ]@%N*            " << endl;
  cout << "                 ][                                  g@`         @                " << endl;
  cout << "                 ][   #@NNNNN@NNNNN@              ,gP            @   gy           " << endl;
  cout << "                 ][   #F    ]@     $F            /@              @ g@`g           " << endl;
  cout << "                 ][   #F    j@     $F    @\"\"\"\"\"\"\"@       ,,      *\"    $C " << endl;
  cout << "                 ][   #P\"\"\"\"j@\"\"\"\"\"$F    $`      @       @\"g           @" << endl;
  cout << "                 ][   #F    ]@     $F    $` @m   $      ]@   $,         ]L        " << endl;
  cout << "                 ][   $g,,,,g@,,,,,@F    $`]$ \"MB@@    ,@     g        ]@        " << endl;
  cout << "                 ][                      $`$@         gP       $r       ]@        " << endl;
  cout << "                 ][                      $` %r       #F        ]@       @C        " << endl;
  cout << "                 ][                      $`  $,     ]@          $      gP         " << endl;
  cout << "                 ][                      $`   *b,   ]F          ]L  ,g@`          " << endl;
  cout << "                 'MMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMM%m@Wgggggggggggm@P\"            " << endl;
}
void displayconfusedcat()
{
    cout << "\n\t      ~~Something bad happened to you even the cat is confused~~" << endl;
    cout << "        T\"~" << endl;
    cout << "         \\|bg^~                                                            -=" << endl;
    cout << "          \"|W|&g `~,                                                  .-jw4`\\" << endl;
    cout << "           \"w|@|\"w,  \"~,                                        ,-^`,-^|||>,`:" << endl;
    cout << "            'y||y,`\"*~  .-               `` '`\"\"\"\"\"*^M~~w.,.-^` ,-^||||A||2" << endl;
    cout << "              K|||l. .-                                  >  -<\" |||||A| |r" << endl;
    cout << "               K'' /                                       , ||||||F|||,`" << endl;
    cout << "                % '                                         \",||wA&T|'/" << endl;
    cout << "                |                                            )`|||||yC" << endl;
    cout << "               /      'y              .                       T|||r)`" << endl;
    cout << "               `   yg,                                            g`" << endl;
    cout << "              \"     %@@@             ,ggg$@@B  ^*   \"\"``\"*^L      [" << endl;
    cout << "             /        - ]         -\"*RB@NP`                       [" << endl;
    cout << "            j          )       -                                  [" << endl;
    cout << "            ]      ,e^ ,ggw~~,                                    [" << endl;
    cout << "            ] L   '    \"*||P*`       -,  ~                        ]" << endl;
    cout << "               `         \"\"    ,       \"            ^r.           ]" << endl;
    cout << "             W    \\      ,,             )               'r         L" << endl;
    cout << "             F      \"vm4@$$$&g,  - -    '                          [" << endl;
    cout << "                       ~B$$@&&&&@gg   ,-^   ` `                    L" << endl;
    cout << "                      C       -- --                               ]" << endl;
    cout << "             -        \\                 ,,,,                 , w  ^" << endl;
    cout << "             \\         '*~.,  ,,..~^""`                 ` `  `    V" << endl;
    cout << "             ]                                                     C" << endl;
    cout << "              L     ,                              ,gC           ,\"" << endl;
    cout << "               *v    *v.                        w@\"-         ,.r" << endl;
    cout << "                  `*wp,                               .-^\"`" << endl;
    cout << "                        `""**Mmmww,,,.~~=~~=F-=^""`" << endl;
    cout << "\n\t\t\t\t  \"MEOW?.\"" << endl;
    cout << "\n\t\t\t ~Confused Cat, The Meme" << endl;

    system("pause"); // A short pause and promt user to press any key before continue
    system("cls");
    return;
}

void displayElizabethDunn()
{
    cout << "\n\t      ~~You are not very happy you could have enjoyed more~~" << endl;
    cout << "\n                               ,,gg@@@@@@@g," << endl;
    cout << "                            ,g@$          B@@@g" << endl;
    cout << "                          j@@M$%$@$         @@$$g," << endl;
    cout << "                       ,wF`,@M$$@$&N  M    M$MMM&gw" << endl;
    cout << "                     ,#,g@ `g Rj@M$ @\"'\"*%@ $@@y'YM@" << endl;
    cout << "                    ,\\@$@`@  \"{g@M*'      '\"}T*W$@g\"M," << endl;
    cout << "                   ;l$  y   y.@M'            'j%@gl@,*L" << endl;
    cout << "                   j@  y   kL#@`                ]@@@$w\"L" << endl;
    cout << "                   $$ F$   $j$F                  *$@ $L*," << endl;
    cout << "                   $$ L    L`$L           ,,w*'   ]   $,j" << endl;
    cout << "                   $@M     F $Lg,,,      \"|,gg,       $@ L" << endl;
    cout << "                   $$&L    @ ]L|g$@@gL   '*|'      ]@ @@w'" << endl;
    cout << "                   $$@K$    Lj @** \"j@L   `        ]@   @LL" << endl;
    cout << "                   @$$@]   $@L$L`   jlL               @J W" << endl;
    cout << "                  ]@Q F]   $$WlL    lll     *Yg,,   ] $$%@@" << endl;
    cout << "                 ,My  L$  @@$QW@L,,$$@g,,,    ,/*   #  @$$@" << endl;
    cout << "                /y@$ Mj$ $y'l$@@g$g$$$$gg,m*\" '    @@$j@WjF" << endl;
    cout << "               g@   F\\$$@# ']M$$W,||  g,,,,w`'   ,   @%@|l`" << endl;
    cout << "              @@$  @L#$B' ',|    g1gM$$$MM*'    g    Qkj@l" << endl;
    cout << "             ]@#  MQ@F`,'  g   NB   $gg|*'     g     @@l|$g" << endl;
    cout << "             ]$$$$$@gT|| y   @$g,|$    @MWwwrL#       @MWg$L" << endl;
    cout << "              $$@$$$g$wg$      gg,j$ @lF`    ,l$     @$@@L|jg" << endl;
    cout << "              \"& M$          $       @        '$       @L |l$@g" << endl;
    cout << "                ]              @$TF$@$@     '  ]         @@@@   g" << endl;
    cout << "              g              @  $@@W%          }j   @@@ M&       @" << endl;
    cout << "            ,@                           @@gw~' '````$ @$          g" << endl;
    cout << "                                             ,,g@     @             g" << endl;
    cout << "                                   @@             *\"`` @          @  @" << endl;
    cout << "           ]                                 \" ,,g@@$L|               @" << endl;
    cout << "           ]                       @          ll$$$$lLL|               @" << endl;
    cout << "           ]                       @@          gl$$$$l&M*               W" << endl;
    cout << "                                @  @@@@         @*\",gpN*\"\"               W" << endl;
    cout << "                                    @@ @          ',g@@@LLj               g" << endl;
    cout << "            $                    @  @@             pl$$@ll||               @" << endl;
    cout << "\n  \"If money doesn't make you happy, then you probably aren't spending it right.\"" << endl;
    cout << "\n\t\t\t\t ~ElizabethDunn" << endl;

    system("pause"); // A short pause and promt user to press any key before continue
    system("cls");
    return;
}

void greatestend()
{
    cout << "\n\t      ~~The best outcome you can get~~" << endl;
    cout << "                       * " << endl;
    cout << "                                          * " << endl;
    cout << "               * " << endl;
    cout << "                             * " << endl;
    cout << "                                                       * " << endl;
    cout << "    * " << endl;
    cout << "                                             * " << endl;
    cout << "        * " << endl;
    cout << "                      *             * " << endl;
    cout << "                                                * " << endl;
    cout << " *                                                               * " << endl;
    cout << "                          (             ) " << endl;
    cout << "                  )      (*)           (*)      ( " << endl;
    cout << "         *       (*)      |             |      (*) " << endl;
    cout << "                  |      |~|           |~|      |          * " << endl;
    cout << "                 |~|     | |           | |     |~| " << endl;
    cout << "                 | |     | |           | |     | | " << endl;
    cout << "                ,| |a@@@@| |@@@@@@@@@@@| |@@@@a| |." << endl;
    cout << "           .,a@@@| |@@@@@| |@@@@@@@@@@@| |@@@@@| |@@@@a,. " << endl;
    cout << "         ,a@@@@@@| |@@@@@@@@@@@@.@@@@@@@@@@@@@@| |@@@@@@@a, " << endl;
    cout << "        a@@@@@@@@@@@@@@@@@@@@@' . `@@@@@@@@@@@@@@@@@@@@@@@@a " << endl;
    cout << "        ;`@@@@@@@@@@@@@@@@@@'   .   `@@@@@@@@@@@@@@@@@@@@@'; " << endl;
    cout << "        ;@@@`@@@@@@@@@@@@@'     .     `@@@@@@@@@@@@@@@@'@@@; " << endl;
    cout << "        ;@@@;,.aaaaaaaaaa       .       aaaaa,,aaaaaaa,;@@@; " << endl;
    cout << "        ;;@;;;;@@@@@@@@;@      @.@      ;@@@;;;@@@@@@;;;;@@; " << endl;
    cout << "        ;;;;;;;@@@@;@@;;@    @@ . @@    ;;@;;;;@@;@@@;;;;;;; " << endl;
    cout << "        ;;;;;;;;@@;;;;;;;  @@   .   @@  ;;;;;;;;;;;@@;;;;@;; " << endl;
    cout << "        ;;;;;;;;;;;;;;;;;@@     .     @@;;;;;;;;;;;;;;;;@@a; " << endl;
    cout << "    ,&&%;;;;;;;;@;;;;;;;;       .       ;;;;;;;;;;;;;;;;@@;;&&%, " << endl;
    cout << " .&&&&&%;;;;;;;a@;;;;;;;;     ,&&%,     ;;;;;;;;;;;;;;;;;;;;%&&&&&, " << endl;
    cout << ".&&&&&&%;;;;;;;@@;;;;;;;;   ,&&&&&&%,   ;;;;;;;;;;;;;;;;;;;;&&&&&&%," << endl;
    cout << "&&&&&&&%`;;;;;;;;;;;;;;;;  %&&&&&&&&%  ;;;;;;;;;;;;;;;;;;;'%&&&&&&&& " << endl;
    cout << "&&&&&&&&&&&%`;;;;;;;;;;;;,%&&&&&&&&&&&%,;;;;;;;;;;;;;;;'%&&&&&&&&&&& " << endl;
    cout << "`&&&&&&&&&&&&&&&&%,,,,,,,%&&&&&&&&&&&&&%,,,,,,,&&&&&&&&&&&&&&&&&&&&' " << endl;
    cout << "  `&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&'" << endl;
    cout << "      `&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&' " << endl;
    cout << "             \"\"\"\"\"\"\"\"\"\"\"\"\"\"`,,,,,,,,,'\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\" " << endl;
    cout << "                            `%&&&&&%' " << endl;
    cout << "                             `%&&&%' " << endl;
    cout << "                               %&% " << endl;
    cout << "                              %&&&% " << endl;
    cout << "                           .,%&&&&&%,. " << endl;
    cout << "                      ,%&&&&&&&&&&&&&&&&&%, " << endl;
    cout << "          ---------------------------------------------" << endl;
    cout << "\n  \"Congratz!! Never stop learning and learn to manage your money well.\"" << endl;
    cout << "\n\t\t\t\t ~Creator" << endl;

    system("pause"); // A short pause and promt user to press any key before continue
    system("cls");
    return;
}

void displayMonaLisa()
{
    cout << "\n\t      ~~You are not very happy but not very sad either~~" << endl;
    cout << "\n                                     ,wg;,;" << endl;
    cout << "                                  >]\"'@\"'\"\"*<*," << endl;
    cout << "                                /\\g\"`-\"\"\"\"K*w] K" << endl;
    cout << "                               ]j'[        ]  M]" << endl;
    cout << "                                ]-$w@K4wmm\" L r$L" << endl;
    cout << "                                ]-$w@K4wmm\" L r$L" << endl;
    cout << "                                # ]  [      ]  ][" << endl;
    cout << "                               [] ]  \"*,    ]j ]]" << endl;
    cout << "                               ]]  Pw""    y%] []r" << endl;
    cout << "                                ]r/  'N***\" ]] F L" << endl;
    cout << "                                rLC  g@w    ] uP 'w" << endl;
    cout << "                               ',U /*  -    ] ]    \\" << endl;
    cout << "                              ,X\"g*         [ ]lr\"*\"*W," << endl;
    cout << "                            g\"- @*w,       ,N\"`  ,=cP*\"*W" << endl;
    cout << "                           p\"  @    `\"^**N\"- ,r*`.\"      ]" << endl;
    cout << "                          ]   ]~       /\"  ,'  ,\"   yr'\\ \\%" << endl;
    cout << "                          @\"-<%r     /`   /   ;*  /\"    W ]P" << endl;
    cout << "                       ,m\"  *r*K    /    \"    \" ]'      [  K" << endl;
    cout << "                     ;P- wwg   ]   /    \"    C  ]       [  $" << endl;
    cout << "                    ,C  P    `r]r ]`   C    [   ]       ]  $" << endl;
    cout << "                    @  ]      *\"\"\"\"*w;[    ]    ]       ]  K" << endl;
    cout << "                    [  ],    ]        \"N%w [ ;,w4Ngp;   [ /" << endl;
    cout << "                    \"w4\"\"\"*\"\"\"@P\",     Ng,*g      '%[  ,C/*" << endl;
    cout << "                             C@y  \"w/w/m/*,*        -]m)r`" << endl;
    cout << "                             \"@@,w^^\"'\"\"***\"\"****^^\"\"'\"" << endl;
    cout << "                               V'" << endl;
    cout << "\n\t\t\t  \"Mona Lisa is here to greet you.\"" << endl;
    cout << "\n\t\t\t\t ~Mona Lisa" << endl;

    system("pause"); // A short pause and promt user to press any key before continue
    system("cls");
    return;
}
void displayWarrenBuffett()
{
    cout << "\n\t\t\t~~You are better than the Man himself~~" << endl;
    cout << "\n                                wgwwg" << endl;
    cout << "                          ]gmF**-    ]-*\"Mwg" << endl;
    cout << "                    ypQF\"      )         \"'^*jy/c" << endl;
    cout << "                   g@@F        /             ~#FY~" << endl;
    cout << "                 ,Q~?\"      ,  |             \" \"]4M$Q^~" << endl;
    cout << "               ,/           *                       \"^%m[^" << endl;
    cout << "              /P          ,'=                         \"***" << endl;
    cout << "             ]`          $7\"                             }]g.=g" << endl;
    cout << "             F*     F`,;]$^                    ,-          ]w," << endl;
    cout << "            ]k        *C4e                      '  ;gmMMNmg;%K>" << endl;
    cout << "           j*,   *    ]\"                  ,  (<,gM,4@m2=  ]%RPP" << endl;
    cout << "         *@-    \"             ,  ,.,g$gg,L  `gDP';wmywg, C'@C" << endl;
    cout << "         m;+     \".            ,gN*7+-T  }]@@NBgg@P\";1+y[  ]$" << endl;
    cout << "        % ,      = ],        y@* ,J;wwgggy,]P  \"@ r}4=*'  gPY," << endl;
    cout << "       ~C         J'\\      g@@L;yg@NM**\")r QF    ]%mggm@@F   ]" << endl;
    cout << "        &x    r ~C,TC   y@NN$g@@v.    ,c  gF        ^w        ]" << endl;
    cout << "       ^*$, ' C .{'\"C)@@rT\"*?**&g,  ]}gm$%N\"     ,,Cw4*Gw,  ~  i" << endl;
    cout << "         #w  '   /)*P*        ~  \"wwe^^- \\k+w*L*jm$? Lx \"hw.,}\\ r" << endl;
    cout << "         **[   FV$bg         L          rF \"T*\"*~,, ;    , L\"`  }" << endl;
    cout << "           TN{ \"C  *.C                 j@       ,ggwmmmmg (L    ]" << endl;
    cout << "              V\"\"   R@$               y&C   gg@FL ;,ggg@P yr    ]" << endl;
    cout << "               %/    ]g            ^*;i*F,@@g@mNP*\"7+    )[     ]" << endl;
    cout << "                \"V   *               ' \"J-          .  m  **v  .[" << endl;
    cout << "                  \"%/* ')^C             ]              '-    (`\\F" << endl;
    cout << "                    \\ ` ,{',             [                   @Qj@g" << endl;
    cout << "                     *=gg,ym@c           `               >~ \"$LP\"*{PNrVrr" << endl;
    cout << "                             *b;.                   ,r   JL yY P     4`" << endl;
    cout << "                               \"      r . ]Y+l',[+r    \\/cr F]P" << endl;
    cout << "                                ]yZ'     *   `+ .= `    ;y\\*; @h,`," << endl;
    cout << "                               j7rZwL     -*]  C-    -@2m-  \"]Mp~c`" << endl;
    cout << "                             ,AK\"] ;,;]5=l, '  ~   gg@g@.J  j@F\"" << endl;
    cout << "                        ,wrj)fuk/]g*$     Z;+Cg@@@NMNN@@K;-]$P" << endl;
    cout << "                     \"'     ;r).)%@@{L,  Tj@@@@]M}L[\\]@@Y`" << endl;
    cout << "                          -\"  LTP1@R -   *\"@@@@7mw*\"\"" << endl;
    cout << "\n\t\t\t\"Risk comes from not knowing what you are doing.\"" << endl;
    cout << "\n\t\t\t\t\t ~Warren Buffett" << endl;

    system("pause"); // A short pause and promt user to press any key before continue
    system("cls");
    return;
}

void displayWarrenBuffett2()
{
    cout << "\n\t\t\t~~Are you actually Warren Buffet?~~" << endl;
    cout << "\n                                  ,=~rr~=," << endl;
    cout << "                               ,r          \"v," << endl;
    cout << "                              {   ,=^\"````\"*Wg{v" << endl;
    cout << "                             /  /\"             *r^~" << endl;
    cout << "                            / ;F                 \\, " << endl;
    cout << "                           Z`:F                   ]  }" << endl;
    cout << "                          ,||#| ,~y~~,; ,r^^^y,    F, L" << endl;
    cout << "                          $}lk@`-;g@g#@g@|;Wgg,]@w,kL j" << endl;
    cout << "                          ]@#L$*,    $' } -,   ]' `*Q&g*" << endl;
    cout << "                          [l&L \"vwwr&i   'Mm~r\"     $LL" << endl;
    cout << "                           gJ      /&&**""*        ]`j" << endl;
    cout << "                            P&L  ,L    ,     \\,    4TF" << endl;
    cout << "                            ]jWl''  ~'\"'\"\"`  `   }g,%" << endl;
    cout << "                             \"\\g                 g \"" << endl;
    cout << "                               $L\"s,        ,.,AFF" << endl;
    cout << "                          ,wM$l$&&l|lFT""`      @P{*~," << endl;
    cout << "                    ,wr\"T|$@@,l]||W|        ,,r  C\"1   *w," << endl;
    cout << "             ,+r\"\"`   ,\"\"L\\F }|$p   \"M,   ,r`    P  .V  ` .\"*w," << endl;
    cout << "         ,4`    .     `' y` |||*k     ,r`\"*w     F`; j?,,  '    '\"Mw," << endl;
    cout << "            '    '   ` .#,; '<||j    &     M|N  ]-> `},wT`  `; .```''|\"w," << endl;
    cout << "              '.  ``'  `'`W\"` '|lk /`\"\"\"`\"` '\"jy[ `|T*WL,  \\ .'=    `" << endl;
    cout << "                      ',(       \"j@       }    ]`  `.*y,y'." << endl;
    cout << "                        `) >      ]   ]        ]`:. ,~>J'.<'`" << endl;
    cout << "                           \\ >`  '.t  ]    T   F   \"<,/" << endl;
    cout << "                             V  ` ',C $          ;>;y\"" << endl;
    cout << "                               v  ' \" L     L [ <},\"" << endl;
    cout << "                                'y   ]L     ]g'~;r" << endl;
    cout << "                                  \", `]     /``/" << endl;
    cout << "                                    \",~L   / y`" << endl;
    cout << "                                      \",w ,,\"" << endl;
    cout << "                                        ]gP" << endl;
    cout << "\n\t\t\"The most important investment you can make is in yourself.\"" << endl;
    cout << "\n\t\t\t\t ~Warren Buffett" << endl;

    system("pause"); // A short pause and promt user to press any key before continue
    system("cls");
    return;
}

void displayUncleSam()
{
    cout << "\n\t\t\t~~You did well in managing your money~~" << endl;
    cout << "\n                                     ;====r*r=+=u," << endl;
    cout << "                                 v*\\              \"\"w" << endl;
    cout << "                                -  t-..,,         .-rT" << endl;
    cout << "                                 r ]  r   ]  [   [ ] C" << endl;
    cout << "                                 ]    F   ]  P   L Pj-" << endl;
    cout << "                                  C L [   ]  P  ] ] [" << endl;
    cout << "                                  ] [ ]   ]  P  [ []`" << endl;
    cout << "                                  ]74 ]   ]  P  P C[" << endl;
    cout << "                                  ,  \\---\"]\"\"^\"\"n; P,," << endl;
    cout << "                                [ ]Fw 4  \\--*  )>] P- P" << endl;
    cout << "                                *y ]c]\\  [\"*\"  `  v* z" << endl;
    cout << "                               ,z~]w -**~==,==~^^-,r\"v" << endl;
    cout << "                             j-[ w-<,C*=~===w+r*\"S  ]J" << endl;
    cout << "                             ;uK[ 7P              P P[y\"^~,                             ___________    ____" << endl;
    cout << "                             xr=* P\"              L]w)-    ]                     ______/   \\__//   \\__/____\\" << endl;
    cout << "                            -g}+[*p-             ch-<      /=                   _/   \\_/  :           //____\\\\" << endl;
    cout << "                         _ -'    (  [            ] [       - [                 /|      :  :  ..      /        \\" << endl;
    cout << "                       y        ]   'p          ;r4      [ j]                 | |     ::     ::      \\        /" << endl;
    cout << "                     ?          P7c,~4a,       gJ=w        /[ t               | |     :|     ||     \\ \\______/" << endl;
    cout << "                    \\            7`]    7C  ]L    jL       C[  r             | |     ||     ||      |\\  /  |" << endl;
    cout << "                    `           /   X   ,t, .PS<,;C)      /    L               \\|     ||     ||      |   / | \\" << endl;
    cout << "                    [           *c    (* '&(@`      A     r    ]                |     ||     ||      |  / /_\\ \\" << endl;
    cout << "                   !            .'    \"   ]\"`C ]   ^     [     -              | ___ || ___ ||      | /  /    \\" << endl;
    cout << "                  /                '~..]  \"  ] [  C       t     L               \\_-_/  \\_-_/ | ____ |/__/      \\" << endl;
    cout << "                  L         ,- --\\  [L  #      \" (       \\C     '                          _\\_--_/    \\      /" << endl;
    cout << "                 /        ;` !,   -`'-,L` P   ] /        ][      \\                          /____             /" << endl;
    cout << "                ,     ,  r |    `'. ,_) L    P \" ,`     $ >P*    P                         /     \\           /" << endl;
    cout << "               . .'` -  ]  |  `;-- `    \\]   ? C r       &^\"'\"    C                      \\______\\_________/" << endl;
    cout << "              ' '    !  |     /[L        \\L  P/,\"        P       C" << endl;
    cout << "             /          [\\  '~ {          Y ],y-         C     y\"" << endl;
    cout << "             [           .`  /`            \\]7 y         ]   ,*" << endl;
    cout << "              \\            `   `            J  x         ML>^" << endl;
    cout << "               \\          .,.                ]  \"         \"," << endl;
    cout << "                \\        .'                   L           y\"" << endl;
    cout << "                 `~ ^ '`                      'C        yr" << endl;
    cout << "                                               ],,,:=+f\\" << endl;
    cout << "\n\t\t\t\t     \"I want you.\"" << endl;
    cout << "\n\t\t\t\t ~Uncle Sam, The Meme" << endl;

    system("pause"); // A short pause and promt user to press any key before continue
    system("cls");
    return;
}

void displayJustRight()
{
    cout << "\n\t\t\t~~You tried manage your money it's fine~~" << endl;
    cout << "\n                                  ,werrvw;" << endl;
    cout << "                              ,w^7    +  /-\"w" << endl;
    cout << "                            [*\"-<<]wr-[ P`V  ]," << endl;
    cout << "                           ]4r**\"r    - \\, \"w, V" << endl;
    cout << "                           ] c,wC       C \"*w/P ]," << endl;
    cout << "                          ]-   P       ]?W  /r   ]" << endl;
    cout << "                         )L   [     -rpV?      w*         P*7V   P**v                        _ _" << endl;
    cout << "                        /\\   ***wwwMw @]      ]L          %;  ]pJL  ^r >;                 .-/ / )" << endl;
    cout << "                       C  77\"**w;,   -  *w;   ]L           'yg ]p]< ]^]~ *P               |/ / /" << endl;
    cout << "                    ,r+            =<<]**w,\\  [L       r**}7Vr  ]F  ] ]^=jr               /.' /" << endl;
    cout << "=r*\"\"\"\"\"**ww; P*\"7p%-                    =q,L [L      P   /   z+w}  WP - [               // .---." << endl;
    cout << "            ,*\"*C P],C**vwww;;              ` [[    [\"k  [ ]w  ?V-\"v    P               /   .--._\\" << endl;
    cout << "            C   F]-]\"          <=7***rwwwwwwwwC]gg,;P  ;;Jgw[    \"y -  C               /    `--' /" << endl;
    cout << "          #7<] / ] ]                        yC .$  $   *q,;Cc      *  F               /     .---'" << endl;
    cout << "          P  ] P ] -P                      A-/\" 'y ]        \"-       @V              /    .'" << endl;
    cout << "         ]   [ hwf\" K                    /* f    *y \"*q      P      ]  C            "<< endl;
    cout << "         [   N\"x*\"  ]  ;\"7\"P            '         \"C   ]\\,  ]       J*wJ-" << endl;
    cout << "        ]     \"      L ]   P                       J    L              -7w" << endl;
    cout << "         W           /f7   P                      )\"    ]-                '*w" << endl;
    cout << "         ]-       r  [    ]V                     /\"      $                   -]M" << endl;
    cout << "        Jw&       ]       $ ]Y,                yC        ]-" << endl;
    cout << "e****<=    P       t     P     *w            ,C           [" << endl;
    cout << "           [       ]  ;*-        +^w       >f-            7p" << endl;
    cout << "                 ;A7 )C             -7Ywwe*                ]" << endl;
    cout << "              -\"^   y-                                      ]" << endl;
    cout << "                   Z\"                                        k" << endl;
    cout << "                  A                                          \"p" << endl;
    cout << "\n\t\t\t\t \"Just Right.\"" << endl;
    cout << "\n\t\t\t\t ~Pacha, Disney" << endl;

    system("pause"); // A short pause and promt user to press any key before continue
    system("cls");
    return;
}

void displayDisappointed()
{
    cout << "\n\t\t\t~~You did bad managing your money~~" << endl;
    cout << "\n                    ,,ggg@@@@@@@@@@@@gpgwgg,;;," << endl;
    cout << "                gg@M*\"\"`                 -+**\"TT*MN@pg/" << endl;
    cout << "             g@M[                                    \"*&&@gg" << endl;
    cout << "          ,@N*                                            `]%N@," << endl;
    cout << "         g@*                                                   ]%@g" << endl;
    cout << "       )@F                                                        \"%@g" << endl;
    cout << "      g@*                                                            ]@g" << endl;
    cout << "     @K                                                                ]@g" << endl;
    cout << "    @P                                                                   *@c" << endl;
    cout << "   #K                                                                     *&g" << endl;
    cout << "  ]@                                                                        %@" << endl;
    cout << "  @C                                                                         %K" << endl;
    cout << " $@                                      @                                   ]@" << endl;
    cout << " @F            *wgggg                   j@                                    $L" << endl;
    cout << "j@              j@  -\"*j@@@pgg/,      ,gM                               /     $K" << endl;
    cout << "]@              ]@       *@@@@@PTJ@NNMT`                               j@     ]@" << endl;
    cout << "]K               *Ng        \" ygM*            *$@mggg                  @C     $K" << endl;
    cout << "$K                 *7NmwwgmNM**                ]C   ?*T%@@ggg;      ,gP\"      @L" << endl;
    cout << "$K                                              &g      %@@@@@@PT*$P*        g@" << endl;
    cout << "%@                                               ]%wg     -?*   g@C         g@" << endl;
    cout << "]@                                                  `*TPMNNNNNMT\"          &P" << endl;
    cout << " %@            ,p                                                        y@*" << endl;
    cout << "  %@          ]@-                                                       @K`" << endl;
    cout << "   %@         @L        gppgwggg/,                                    g@*" << endl;
    cout << "    ]@       \"@r       *\"     -']\"**MNNggg,                         ;@P" << endl;
    cout << "     ]@,      ]%w            *TTTP*Mmwg,-?*TMNNp      %r           @@L" << endl;
    cout << "      ?&g                             -\"*T     %      ]K         g@\"" << endl;
    cout << "        *@g                                          gP        g@C" << endl;
    cout << "          ]Ng,                                    y@P'       g@*" << endl;
    cout << "            \"%Np,                                **      ,g@M\"" << endl;
    cout << "               '*MNgg/                              ,gg@NP\"" << endl;
    cout << "                    ?*7%@@gggggg,            ,ggp@NPT*-" << endl;
    cout << "                        @P  -<*^""T*PMMMMMMPFT""" << endl;
    cout << "                       #@" << endl;
    cout << "                      ]@" << endl;
    cout << "\n\t\t\t\t \"Disappointed.\"" << endl;
    cout << "\n\t\t\t\t ~Imgflip, The Meme" << endl;

    system("pause"); // A short pause and promt user to press any key before continue
    system("cls");
    return;
}

void displayJackieChan()
{
    cout << "\n\t\t\t~~You did bad managing your money~~" << endl;
    cout << "\n                                 ,gg@Nggpwg       rbw-Yv" << endl;
    cout << "                     ,`/LwL=L  g@@@@@@@@@@@@@@g |Y**~   T," << endl;
    cout << "                    / >*  ;#$R@@@@@@@@@@@@@@@@@@@g^.  \">, \\" << endl;
    cout << "                   *A`  =*  g@@@@@@@@@@@@@@@@@@@@@@  ~   L r" << endl;
    cout << "                  \"{ ,'   g@@@@@@@@@@@@@@@@@@@@@@L77-.)   ,]" << endl;
    cout << "                 Cr /   ]@BPCJ@@**@@@@@@@@@@@@@@@@Ngg      ']" << endl;
    cout << "               7- ,`  ,4[` ;g@@7w -]7M@@@@@@@@B@@@@@@Ki      'L" << endl;
    cout << "              /      `   g@@@P   ggg// ]%{7h2L,g/4@@@@ \"       \\" << endl;
    cout << "             /         g@@@@*  ,`=}2TT~\".Ju?PJ$S;L1@@@ >L       \\" << endl;
    cout << "            r        j@@@@@P     ]*MFj :  V\"L[P7L]j@@C            x" << endl;
    cout << "          ,*         L]@@@@C        -,      ,     -@@    '         'v" << endl;
    cout << "        /`          C  $PP%r          ,C   ] `    .M-       `         ." << endl;
    cout << "    /^w`         .<    *Ci]          CLww .s>\"    ]]          v         x=-~=" << endl;
    cout << "   A ]k        ^        ]p           ,`      '    [\"           i         `;w*F" << endl;
    cout << " >\"  j        \"          %@@          ,\"wwwl,    ,\\             T\"\"``'\"\"\"`   'v" << endl;
    cout << "-     5;    ,             }[L          \"-=-'    /- 'v    ,      \"              }" << endl;
    cout << "           |           ,=\"} 'v          ~=~,   {L    ?y<'  -^~~^`L" << endl;
    cout << "           |^=^'*`*<      C    *,.           >C L    )           " << endl;
    cout << "           ]              }      `L\"\"\"*+~..<\"  47\\   -      '     l" << endl;
    cout << "           [                Y,    ]      ,,,+*-C   -\"x       \\" << endl;
    cout << "                              -^~.,           ]      j        r" << endl;
    cout << "\n\t\t\t  \"How did you end up here?.\"" << endl;
    cout << "\n\t\t\t ~Confused Jackie Chan, The Meme" << endl;

    system("pause"); // A short pause and promt user to press any key before continue
    system("cls");
    return;
}
void displaystockMarket()
{
    cout << "\n                 _ _.-'`-._ _                                 " << endl;
    cout << "                ;.'________'.;                                  " << endl;
    cout << "     _________n.[____________].n_________                       " << endl;
    cout << "    |\"\"_\"\"_\"\"_\"\"||==||==||==||\"\"_\"\"_\"\"_\"\"]      " << endl;
    cout << "    |\"\"\"\"\"\"\"\"\"\"\"||..||..||..||\"\"\"\"\"\"\"\"\"\"\"|" << endl;
    cout << "    |LI LI LI LI||LI||LI||LI||LI LI LI LI|                      " << endl;
    cout << "    |.. .. .. ..||..||..||..||.. .. .. ..|                      " << endl;
    cout << "    |LI LI LI LI||LI||LI||LI||LI LI LI LI|                      " << endl;
    cout << "    |.. .. .. ..||..||..||..||.. .. .. ..|                      " << endl;
    cout << "    |LI LI LI LI||LI||LI||LI||LI LI LI LI|                      " << endl;
    cout << "    |          @ BURSA MALAYSIA          |                      " << endl;
    cout << "    |___________ _ _.-'`-._ _ ___________|                      " << endl;
    cout << "    |  _  _  _  ;.'________'.;  _  _  _  |                      " << endl;
    cout << "    | | || || | | |        | | | || || | |                      " << endl;
    cout << "    | | || || | | |        | | | || || | |                      " << endl;
    cout << "    | | || || | | |        | | | || || | |                      " << endl;
    cout << "    | | || || | | |        | | | || || | |                      " << endl;
    cout << " ,,;;,;;;,;;;,;;;,;;;,;;;,;;;,;;,;;;,;;;,;;,,                   " << endl;
    cout << ";;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;                  " << endl;
    cout << "\n\t\t\t\t\t " ;
    system("pause"); // A short pause and promt user to press any key before continue
    system("cls");
    return;
}

void displayInsurance()
{
  system("cls");
  cout << "\n  ________________________________________________" << endl;
  cout << " /                                                \\" << endl;
  cout << "|    _________________________________________     |" << endl;
  cout << "|   |                                         |    |" << endl;
  cout << "|   |              Insurance                  |    |" << endl;
  cout << "|   |                Certificate              |    |" << endl;
  cout << "|   |                                         |    |" << endl;
  cout << "|   |   This certifies that the policyholder  |    |" << endl;
  cout << "|   |   is covered under the terms and        |    |" << endl;
  cout << "|   |   conditions outlined in this           |    |" << endl;
  cout << "|   |   document.                             |    |" << endl;
  cout << "|   |                                         |    |" << endl;
  cout << "|   |   Policy Number: XXX-XXXX-XXXX          |    |" << endl;
  cout << "|   |   Effective Date: __/__/____            |    |" << endl;
  cout << "|   |   Expiry Date: __/__/____               |    |" << endl;
  cout << "|   |                                         |    |" << endl;
  cout << "|   |   Signature: ______________________     |    |" << endl;
  cout << "|   |_________________________________________|    |" << endl;
  cout << "|                                                  |" << endl;
  cout << " \\ ________________________________________________/" << endl;
  cout << "        \\___________________________________/" << endl;
  cout << "       ___________________________________________" << endl;
  cout << "    _-'    .-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.  --- `-_" << endl;
  cout << " _-'.-.-. .---.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.  .-.-.`-_" << endl;
  cout << "`---.-.-.-----------------------------------------------------.--.-.-.---'" << endl;
  cout << "\n\n\n But you had brought insurance, we got you covered!! \n\n\n" << endl;
  system("pause"); // A short pause and promt user to press any key before continue
  system("cls");
  return;
}