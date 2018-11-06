/*/*This program was created for the purpose of displaying a menu that has 4 options: Buying a ticket, Saving the sales, Giving a report and Closing the program.
 *
 * Author: Angel Daniel Olvera Perales
 * Date: November 5
 * email:angelolvera00@gmail.com
 *
 */
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
//Struct that stores the method of paying, whether the seat is occupied or not, the cost and the name of the buyer
struct ticket_sales {
    int payment_method;
    bool occupied;
    int cost;
    char name[100];
}//Total number of seats in the theater
        ticket_sales[400][200];
//Creates/opens the file that will store all the information we give to it
void setfile(FILE *fp) {
    fp = fopen("MrG.txt", "wb");
//Values to each seats are given
    for (int a = 0; a < 400; a++) {
        for (int b = 0; b < 200; b++) {
            strcpy(ticket_sales[a][b].name, "");
            ticket_sales[a][b].payment_method = 0;
            ticket_sales[a][b].occupied = false;
//The cost of the seats is based on the location of their seat.
            if (b < 50 || b > 149) {
                if (b < 100) {
                    ticket_sales[a][b].cost = 50;
                } else if (a < 300) {
                    ticket_sales[a][b].cost = 35;
                } else {
                    ticket_sales[a][b].cost = 20;
                }
            } else {
                if (a < 5) {
                    ticket_sales[a][b].cost = 100;
                } else if (a < 10) {
                    ticket_sales[a][b].cost = 85;
                } else if (a < 50) {
                    ticket_sales[a][b].cost = 70;
                } else if (a < 100) {
                    ticket_sales[a][b].cost = 55;
                } else if (a < 250) {
                    ticket_sales[a][b].cost = 45;
                } else if (a < 350) {
                    ticket_sales[a][b].cost = 40;
                } else {
                    ticket_sales[a][b].cost = 30;
                }
            }
        }
    }
    //Information is stored in the file
    fwrite(&ticket_sales, sizeof(ticket_sales), 1, fp);
}
//Menu for the Reports
void report() {
    printf("Select an option: \n 1.- Total sold\n 2.- Total per zone\n 3.- Total income\n 4.- Total income per zone\n 5.- Occupation rate\n 6.- Occupation rate per zone.\n Enter any other number to exit\n");
}
//Menu to select the seat in which you want to buy the ticket
void seat_zones() {
    printf("Select a zone:\n 1.-VIP\n 2.-Platinum\n 3.-Gold\n 4.-Silver\n 5.-Green\n 6.-Yellow\n 7.-Red\n 8.-Sky Blue\n 9.-Navy Blue\n 10.-Deep Blue\n Press any other number to exit\n");
}
//Displays the paymen method, only 3 ways of paying.
void pmethod() {
    printf("Select a payment method:\n 1.- American Express\n 2.- Master Card\n 3.- Visa\n Press any other number to exit.\n");
}
//Menu that will display first and will lead to all the other menus
void Main_Menu() {
    printf("Welcome to the Travelling Wilburys Memorial Park! Select an option: \n 1.- Buy a ticket.\n 2.- Save data.\n 3.- Report.\n 4.- Exit. \n  ");
}
//Process to select the seat that you want, it searches for the row and number of seat, then it asks for the payment method and name of the buyer, but it will first tell the buyer if the seat is already occupied.
void Select_Seat() {
    int zone_choice;
    int row;
    int first;
    int last;
    int seat_number;
    char name[100];
    int payment_method;
    seat_zones();
    scanf("%d", &zone_choice);

    switch (zone_choice) {
        case 1:
            first = 1;
            last = 5;
            break;
        case 2:
            first = 6;
            last = 10;
            break;
        case 3:
            first = 11;
            last = 50;
            break;
        case 4:
            first = 51;
            last = 100;
            break;
        case 5:
            first = 101;
            last = 250;
            break;
        case 6:
            first = 251;
            last = 350;
            break;
        case 7:
            first = 351;
            last = 400;
            break;
        case 8:
            first = 1;
            last = 100;
            break;
        case 9:
            first = 101;
            last = 300;
            break;
        case 10:
            first = 301;
            last = 400;
            break;
        default:
            printf("Not valid!");
            return;
    }
    do {
        printf("Choose a row between %d and %d", first, last);
        scanf("%d", &row);
    } while (row < first || row > last);
    if (zone_choice > 7) {
        do {
            printf("Select a seat (Either 1 to 50 or 151 to 200): ");
            scanf("%d", &seat_number);
        } while ((seat_number < 1 || seat_number > 50) && (seat_number < 151 || seat_number > 200));
    } else {
        do {
            printf("Select a seat (From 51 to 150) :");
            scanf("%d", &seat_number);
        } while (seat_number < 51 || seat_number > 150);
    }
    pmethod();
    scanf("%d", &payment_method);

    if (payment_method < 1 || payment_method > 3) {
        printf("Going back\n");
        return;
    }
    printf("Enter your name: ");
    //fflush fixes an error that crashes the program, the error is that when you enter the name, it starts to loop all over again and doesn't stop
    fflush(stdin);
    fgets(name, sizeof(name), stdin);
    //This following line returns a "Going Back" instead of a succesfull purchase, I don't know what causes it, but the information is still stored I think.
    printf("Enter 1 to accept, or enter any other number to cancel the operation\n");
    scanf("%d", &zone_choice);
    if (!zone_choice) {
        if (ticket_sales[row - 1][seat_number - 1].occupied) {
            printf("This seat is already taken\n");
        } else {
            ticket_sales[row - 1][seat_number - 1].occupied = true;
            ticket_sales[row - 1][seat_number - 1].payment_method = payment_method;
            strcpy(ticket_sales[row - 1][seat_number - 1].name, name);
            printf("Purchase successful!\n");
        }
    } else {
        printf("Going back\n");
    }
}
//Process that will calculate the total sales and income
int Total_sale(int first, int last, int first_seat, int last_seat, int sold) {
    int count = 0;
    int total_sales = 0;
    for (int a = first - 1; a < last; a++) {
        for (int b = first_seat - 1; b < last_seat; b++) {
            if (ticket_sales[a][b].occupied) {
                count++;
                total_sales += ticket_sales[a][b].cost;
            }
        }
    }
    if (sold) {
        return count;
    }
    return total_sales;
}
//Process to perform the sum of the totals
int zone_sale(int zone, int sale) {
    int count = 0;
    int first;
    int last;

    switch (zone) {
        case 1:
            first = 1;
            last = 5;
            break;
        case 2:
            first = 6;
            last = 10;
            break;
        case 3:
            first = 11;
            last = 50;
            break;
        case 4:
            first = 51;
            last = 100;
            break;
        case 5:
            first = 101;
            last = 250;
            break;
        case 6:
            first = 251;
            last = 350;
            break;
        case 7:
            first = 351;
            last = 400;
            break;
        case 8:
            first = 1;
            last = 100;
            break;
        case 9:
            first = 101;
            last = 300;
            break;
        case 10:
            first = 301;
            last = 400;
            break;
        default:
            first=1;
            last=200;
            break;
    }
    if (zone>7){
        count+= Total_sale(first,last,1,50,sale);
        count+= Total_sale(first,last,151,200,sale);
    }else{
        count+= Total_sale(first,last,51,150,sale);
    }
    return count;
}
//Displays the menu for the reports
void Report(){
 int selection;
 int zone=0;
 int count=0;
 float size;
//Displays the options, where based on your choice, you'll see the option that you wanted
 report();
     scanf("%d",&selection);

     switch (selection){
         case 1:
             count = zone_sale(zone,1);
             printf("Tickets sold: %d",count);
             break;
         case 2:
             do{
                 seat_zones();
                 printf("Of which zone do you want information about?");
                 scanf("%d", &zone);
             }while (zone<1||zone>10);
             count=zone_sale(zone,1);
             printf("Total tickets sold in the zone: %d", count);
             break;
         case 3:
             count= zone_sale(zone,0);
             printf("Total income: $%d",count);
             break;
         case 4: do{
             seat_zones();
             printf("Of which zone do you want information about?");
             scanf("%d",&zone);
         }while (zone<1||zone>10);
         count = zone_sale(zone,0);
         printf("Total income in the zone: $%d",count);
         break;
         case 5:
             count=zone_sale(zone,1);
             printf("Occupation rate is %f%%, count*100/80000");
             break;
         case 6: do{
             seat_zones();
             printf("Of which zone do you want information about?");
             scanf("%d",&zone);
         }while (zone<1||zone>10);
         count=zone_sale(zone,1);

         switch(zone){
             case 1:
             case 2:
                 size=5;
                 break;
             case 3:
                 size=40;
                 break;
             case 4:
             case 6:
             case 7:
                 size=50;
                 break;
             case 8:
             case 10:
                 size=100;
                 break;
             case 5:
                 size=150;
                 break;
             case 9:
             default:
                 size=200;
                 break;
         }
         printf("The occupation rate in the zone is %f%%", count/size);
         break;
         default:
             printf("Going back");
             return;
     }

}
//As the name suggests, every time we modify the program and ask it to save the progress, the file will be updated with the new information.
void update_file(FILE *fp){
    fp=fopen("MrG.txt","wb");
    fwrite(&ticket_sales, sizeof(ticket_sales),1,fp);
    fclose(fp);
}
int main() {

    FILE *fp;
    int selection;
    fp=fopen("MRG.txt","rb");
    if(fp==NULL){
        setfile(fp);
    }else{
        while(fread(&ticket_sales, sizeof(ticket_sales),1,fp));
    }
    fclose(fp);

    do{
        //Prints Main Menu and every option will display one of the menus above and perform their operations depending on what you choose.
        Main_Menu();
        scanf("%d", &selection);
        //Fflush fixes the same error that happened way back in line 156.
        fflush(stdin);

        switch (selection){
            case 1:
                Select_Seat();
                break;
            case 2:
                update_file(fp);
                printf("Saved\n");
                break;
            case 3: Report();
            break;
            case 4:
                update_file(fp);
                printf("Shutting down...\n");
                break;
            default:
                printf("Invalid\n");
                break;
        }
    }while(selection!=4);
    return 0;
}