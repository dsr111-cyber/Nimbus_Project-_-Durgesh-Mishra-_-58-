/* src/portfolio.c
 * Person A (feature/core)
 * Simple Portfolio skeleton: implements data structures, view() and metrics()
 * Other functions are placeholders for teammates (buy/sell/update/save/load/menu)
 */

#include <stdio.h>
#include <string.h>

#define MAX_STOCKS 100
#define SYMBOL_LEN 16

typedef struct {
    char symbol[SYMBOL_LEN];
    int qty;
    double buy_price;
    double cur_price;
} Stock;

/* Global portfolio array (simple for semester 1) */
Stock portfolio[MAX_STOCKS];
int count = 0;

/* ---------- Person A: implemented functions ---------- */

/* Print current holdings in a neat table */
void view() {
    if (count == 0) {
        printf("Portfolio is empty.\n");
        return;
    }
    printf("%-10s %-6s %-10s %-10s\n", "Symbol", "Qty", "Buy", "Cur");
    for (int i = 0; i < count; ++i) {
        printf("%-10s %-6d %-10.2f %-10.2f\n",
               portfolio[i].symbol,
               portfolio[i].qty,
               portfolio[i].buy_price,
               portfolio[i].cur_price);
    }
}

/* Compute and print basic portfolio metrics */
void metrics() {
    double total_cost = 0.0;
    double market_value = 0.0;
    for (int i = 0; i < count; ++i) {
        total_cost += portfolio[i].buy_price * portfolio[i].qty;
        market_value += portfolio[i].cur_price * portfolio[i].qty;
    }
    double unrealized = market_value - total_cost;
    double pct = (total_cost == 0.0) ? 0.0 : (unrealized / total_cost) * 100.0;

    printf("Total cost basis : %.2f\n", total_cost);
    printf("Market value      : %.2f\n", market_value);
    printf("Unrealized P/L    : %.2f\n", unrealized);
    printf("Portfolio return  : %.2f%%\n", pct);
}

/* ---------- Placeholders for teammates to implement (do not modify) ---------- */

/* Person B will implement buying logic here */
/* --------- Person B: BUY FUNCTION ----------- */
void buy() {
    char sym[SYMBOL_LEN];
    int q;
    double p;

    printf("Enter stock symbol: ");
    scanf("%15s", sym);
    printf("Enter quantity: ");
    scanf("%d", &q);
    printf("Enter buy price: ");
    scanf("%lf", &p);

    // check if exists
    for(int i = 0; i < count; i++) {
        if(strcmp(portfolio[i].symbol, sym) == 0) {
            // update average buy price
            double old_cost = portfolio[i].qty * portfolio[i].buy_price;
            double new_cost = q * p;
            portfolio[i].qty += q;
            portfolio[i].buy_price = (old_cost + new_cost) / portfolio[i].qty;
            portfolio[i].cur_price = p;
            printf("Updated %s\n", sym);
            return;
        }
    }

    // add new stock
    if(count < MAX_STOCKS) {
        strcpy(portfolio[count].symbol, sym);
        portfolio[count].qty = q;
        portfolio[count].buy_price = p;
        portfolio[count].cur_price = p;
        count++;
        printf("Added %s to portfolio\n", sym);
    } else {
        printf("Portfolio full! Cannot buy.\n");
    }
}

/* --------- Person B: SELL FUNCTION ----------- */
void sell() {
    char sym[SYMBOL_LEN];
    int q;
    double p;

    printf("Enter stock symbol: ");
    scanf("%15s", sym);

    int index = -1;
    for(int i = 0; i < count; i++) {
        if(strcmp(portfolio[i].symbol, sym) == 0) {
            index = i;
            break;
        }
    }

    if(index == -1) {
        printf("Stock not found!\n");
        return;
    }

    printf("Enter quantity to sell: ");
    scanf("%d", &q);
    printf("Enter sell price: ");
    scanf("%lf", &p);

    if(q > portfolio[index].qty) {
        printf("You don't have enough shares!\n");
        return;
    }

    portfolio[index].qty -= q;
    portfolio[index].cur_price = p;

    if(portfolio[index].qty == 0) {
        // remove stock from array
        for(int j = index; j < count - 1; j++) {
            portfolio[j] = portfolio[j + 1];
        }
        count--;
        printf("All shares sold. Stock removed.\n");
    } else {
        printf("Sold %d shares of %s\n", q, sym);
    }
}


/* Person C will implement price updates here */
void update_prices() {
    printf("[Person C] update_prices() not implemented yet.\n");
}

/* Person C will implement save/load persistence here */
void save_file() {
    printf("[Person C] save_file() not implemented yet.\n");
}

void load_file() {
    printf("[Person C] load_file() not implemented yet.\n");
}

/* Person D will implement UI improvements and docs */
void ui_help() {
    printf("[Person D] ui_help() not implemented yet.\n");
}

/* Simple menu (minimal) */
int menu() {
    printf("\n1) View  2) Buy  3) Sell  4) Update Prices\n");
    printf("5) Metrics  6) Save  7) Load  0) Exit\n");
    printf("Choice: ");
    int c;
    if (scanf(\"%d\", &c) != 1) { while (getchar() != '\\n'); return -1; }
    while (getchar() != '\\n'); /* clear leftover input */
    return c;
}

/* main loop */
int main() {
    int choice;
    /* load_file();  -- Person C will implement persistence later */
    while ((choice = menu()) != 0) {
        switch (choice) {
            case 1: view(); break;
            case 2: buy(); break;
            case 3: sell(); break;
            case 4: update_prices(); break;
            case 5: metrics(); break;
            case 6: save_file(); break;
            case 7: load_file(); break;
            default: printf(\"Invalid choice.\\n\"); break;
        }
    }
    /* save_file(); -- Person C will enable this later */
    printf(\"Goodbye!\\n\");
    return 0;
}

