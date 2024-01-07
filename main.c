#include <stdio.h>
#include <stdlib.h>
#include <time.h>

time_t t;

void game() {
  char player[] = "Player";
  int customers;
  int weather;
  int day_cycle;
  float balance;
  int day = 1;
  int lemon_stock = 0;
  int lemon_age = 0;
  int old_lemon_stock;
  int glass_stock = 0;
  int stock;
  float price;
  int tip;
  int tip_chance;
  int base_customers = 12;

  printf("the\nLemonade Stand\nGame\n\n");
  printf("Who are you: ");
  scanf("%s", player);
  printf("Starting Game...\n\n");
  day_cycle = 1;

  while (day_cycle) {
    weather = rand() % 7;
    // Important data of day
    printf("%s - Day %d\n", player, day);
    if (weather == 1) {
      printf("It is cloudy day, less customers will come...\n\n");
    } else if (weather == 3) {
      printf("It is sunny day, more customers will come!\n\n");
    } else {
      printf("It is mild day, regular customer will come.\n\n");
    }

    // Balance and stock
    balance = 100;

    printf("Your balance is %.2f.\n", balance);
    printf("Actually you've %d lemons, %d glasses.\n", lemon_stock, glass_stock);
    printf("There are %d old lemons, with %d days old.\n", old_lemon_stock, lemon_age);

    // Buy lemons and glasses
    printf("\nWould you like to buy more?\n(Y/N): ");
    char willBuy;
    scanf(" %c", &willBuy);

    while (willBuy == 'y') {
      int lemon_buy, glass_buy;
      float lemon_price = 0.5;
      float glass_price = 0.5;

      printf("Buy lemons, cost %.2f$/u: ", lemon_price);
      scanf(" %d", &lemon_buy);

      if (lemon_buy > 0) {
        float cost = lemon_buy * lemon_price;
        if (balance < cost) {
          printf("You don't have enough money to buy %d lemons!\n", lemon_buy);
          continue;
        }
        balance -= cost;
        printf("Successfully buyed %d lemons.\nYour balance now is %.2f.\n", lemon_buy, balance);
        lemon_stock += lemon_buy;
      } else {
        printf("Buy lemons!\n");
        continue;
      }

      printf("\nBuy glasses, cost %.2f$/u: ", glass_price);
      scanf(" %d", &glass_buy);

      if (glass_buy > 0) {
        float cost = glass_buy * glass_price;
        if (balance < cost) {
          printf("You don't have enough money to buy %d glasses!\n", glass_buy);
          continue;
        }
        balance -= cost;
        printf("Successfully buyed %d glasses.\nYour balance now is %.2f.\n", glass_buy, balance);
        glass_stock += glass_buy;
      } else {
        printf("Buy glasses!\n");
        continue;
      }
      break;
    }
    printf("\nNow you've %d lemons and %d glasses.\n", lemon_stock, glass_stock);

    // Make limonade & Limonade price
    stock = 0;
    printf("\nYou've %d lemonades.\nWould you like to make more?\n(Y/N): ", stock);
    char makeLemonade;
    scanf(" %c", &makeLemonade);

    while (makeLemonade == 'y') {
      int needLemon = 2;
      printf(
        "\nYou need %d lemons in a glass per lemonade\nHow many lemonades would you make?: ",
        needLemon
      );
      int lemonades;
      scanf("%d", &lemonades);
      if (lemonades > 0) {
        if ((lemonades * 2) > lemon_stock) {
          printf(
            "\nYou're out of lemons to make %d lemonades.\nYou've %d lemons.\n",
            lemonades, lemon_stock
          );
          continue;
        }
        if (lemonades > glass_stock) {
          printf("\nYou're out of glasses to make %d lemonades.\nYou've %d glasses.\n",
            lemonades, glass_stock
          );
          continue;
        }

        stock += lemonades;
      } else {
        printf("Make lemonades!");
        continue;
      }
      lemon_stock -= lemonades * 2;
      glass_stock -= lemonades;
      break;
    }
    printf("Nice, now you've %d lemonades.\n", stock);

    price = 0;
    while (price < 1) {
      printf("\nBefore start selling, set price to your lemonades: ");
      scanf(" %f", &price);

      if (price < 1) {
        printf("\nAre you sure you want giveaway limonades?\n");
        while (getchar() != '\n');
        continue;
      }
      break;
    }

    printf("Perfect, you're ready to sell limonades at %.2f$!\n", price);

    // Customer calculation
    int adjust_customers = 0;
    int total_customers = 0;
    int buyer_customers = 0;
    int sold_lemonades = 0;
    int earns = 0;

    if (weather == 1) {
      if (price > 2) {
        adjust_customers = base_customers - 2;
      } else {
        adjust_customers = base_customers + 5;
      }
    }

    if (weather == 3) {
      if (price > 2) {
        adjust_customers = base_customers - 3;
      } else {
        adjust_customers = base_customers + 2;
      }
    }

    if (stock > 0 && rand() % 100 < 10) {
      adjust_customers -= stock * 0.2;
    }

    if (adjust_customers < 8) {
      adjust_customers = 8;
    }

    total_customers = adjust_customers;

    if (stock >= total_customers) {
      sold_lemonades = total_customers;
      buyer_customers = total_customers;
    } else {
      sold_lemonades = stock;
      buyer_customers = stock;
    }

    stock -= sold_lemonades;
    earns = price * sold_lemonades;
    balance += earns;
    // Resume of day
    printf("Resuming your day...\n");
    printf("\nDay %d finished.\nHere is a resume of what happened:\n", day);
    printf(
      "\n%d Customers visited your lemonade stand.\nOnly %d buyed lemonades.",
      total_customers, buyer_customers
    );
    printf("\nYou won %d$!\nYou sold %d lemonades.\n", earns, sold_lemonades);
    printf("Now your balance is %.2f$!\n", balance);
    // Cleanup
    printf("\nProceed to cleanup of stand?\n(Y/N): ");
    char cleanup;
    scanf(" %c", &cleanup);

    while (cleanup == 'y') {
      printf("There are %d lemons, tomorrow they will be 1 day old.\n", lemon_stock);
      printf("There are %d glasses, wash them now and save.\n", glass_stock);
      if (lemon_age < 1) {
        printf("No need of cleanup lemons.\n");
      } else {
        printf("\nStarting cleanup of %d lemons...\n", old_lemon_stock);
        old_lemon_stock = 0;
        printf("Cleaned up old lemons!\n");
      }
      break;
    }

    // Proceed to next day
    printf("Proceed to next day?\n(Y/N): ");
    char nextDay;
    while (1) {
      scanf(" %c", &nextDay);

      if (nextDay != 'y' && nextDay != 'n') {
        printf("\nIncorrect input.\nProceed to next day?\n(Y/N): ");
        while (getchar() != '\n');
        continue;
      }
      break;
    }

    // End game
    if (nextDay == 'n') {
      day_cycle = 0;
      break;
    }

    old_lemon_stock += lemon_stock;
    lemon_age++;
    day++;
  }
}

int main() {
  srand((unsigned) time(&t));
  game();
  return 0;
}