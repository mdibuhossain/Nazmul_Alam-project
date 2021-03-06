#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
int i, j;
int main_exit;
void menu(void);
float interest(float t, float amount, int rate);
void fordelay(int j);
void new_acc();
void view_list();
void search_acc();
void edit(void);
void transact(void);
void erase(void);
void see(void);
void close(void);

struct date
{
    int month, day, year;
};
typedef struct bank_route
{
    char bank_name[50];
    char route[15];
} bank_route;

typedef struct clientInfo
{

    char name[60];
    int acc_no, age;
    char address[60];
    char citizenship[15];
    char phone[20];
    char acc_type[10];
    char bank_name[50];
    float amt;
    struct date dob;
    struct date deposit;
    struct date withdraw;

} clientInfo;
// upd, check, rem, transaction

float interest(float t, float amount, int rate)
{
    float SI;
    SI = (rate * t * amount) / 100.0;
    return (SI);
}
void fordelay(int j)
{
    int i, k;
    for (i = 0; i < j; i++)
        k = i;
}

void search_acc()
{

    printf("Enter you account number: ");
    FILE *accFile;
    clientInfo tmpCheck;
    int acc_no;
    scanf("%d", &acc_no);
    accFile = fopen("record.dat", "r");
    while (fscanf(accFile, "%d %s %d/%d/%d %d %s %s %s %s %f %d/%d/%d %s\n", &tmpCheck.acc_no, tmpCheck.name, &tmpCheck.dob.month, &tmpCheck.dob.day, &tmpCheck.dob.year, &tmpCheck.age, tmpCheck.address, tmpCheck.citizenship, tmpCheck.phone, tmpCheck.acc_type, &tmpCheck.amt, &tmpCheck.deposit.month, &tmpCheck.deposit.day, &tmpCheck.deposit.year, tmpCheck.bank_name) != EOF)
    {
        if (acc_no == tmpCheck.acc_no)
        {
            printf("\n\n%-15s %-20s %-20s %-16s %s\n", "ACC. NO.", "NAME", "ADDRESS", "PHONE", "BANK");
            for (int i = 1; i <= 100; i++)
                printf("-");
            puts("");
            printf("%-15d %-20s %-20s %-16s %s\n", tmpCheck.acc_no, tmpCheck.name, tmpCheck.address, tmpCheck.phone, tmpCheck.bank_name);
        }
    }
    fclose(accFile);
}

void new_acc()
{
    clientInfo add, check, tmpCheck;
    int choice;
    FILE *ptr;

    ptr = fopen("record.dat", "a+");
    system("cls");

    printf("\t\t\t\xB2\xB2\xB2\ ADD RECORD  \xB2\xB2\xB2\xB2");

    FILE *routeFile;
    routeFile = fopen("routing.txt", "r");
    bank_route route;
    printf("\n\n\t%-50s %-50s\n", "Bank name", "Routing number");
    for (int i = 1; i <= 80; i++)
        printf("-");
    puts("");
    while (fscanf(routeFile, "%s %s\n", route.bank_name, route.route) != EOF)
    {
        printf("\t%s ", route.bank_name);
        for (int i = strlen(route.bank_name); i <= 48; i++)
            printf(".");
        printf(" %s\n", route.route);
    }
    fclose(routeFile);

    printf("\n\n\nEnter routing number: ");

    char rNumber[15];
routeInp:
    scanf("%s", rNumber);
    routeFile = fopen("routing.txt", "r");
    int flag = 1;
    while (fscanf(routeFile, "%s %s\n", route.bank_name, route.route) != EOF)
    {
        if (!strcmp(rNumber, route.route))
        {
            strcpy(add.bank_name, "");
            strcpy(add.bank_name, route.bank_name);
            printf("\n~~ %s ~~\n", add.bank_name);
            flag = 0;
            break;
        }
    }
    if (flag)
    {
        printf("\n\nDidn't match, try again");
        Sleep(900);
        goto routeInp;
    }
    fclose(routeFile);

    printf("\n\nEnter today's date(mm/dd/yyyy):");
    scanf("%d/%d/%d", &add.deposit.month, &add.deposit.day, &add.deposit.year);
account_no:
    printf("\nEnter the account number:");
    scanf("%d", &check.acc_no);
    while (fscanf(ptr, "%d %s %d/%d/%d %d %s %s %s %s %f %d/%d/%d %s\n", &tmpCheck.acc_no, tmpCheck.name, &tmpCheck.dob.month, &tmpCheck.dob.day, &tmpCheck.dob.year, &tmpCheck.age, tmpCheck.address, tmpCheck.citizenship, tmpCheck.phone, tmpCheck.acc_type, &tmpCheck.amt, &tmpCheck.deposit.month, &tmpCheck.deposit.day, &tmpCheck.deposit.year, tmpCheck.bank_name) != EOF)
    {
        if (check.acc_no == tmpCheck.acc_no)
        {
            printf("Account no. already in use!");
            fordelay(1000000000);
            goto account_no;
        }
    }
    add.acc_no = check.acc_no;
    printf("\nEnter the name:");
    scanf("%s", add.name);
    printf("\nEnter the date of birth(mm/dd/yyyy):");
    scanf("%d/%d/%d", &add.dob.month, &add.dob.day, &add.dob.year);
    printf("\nEnter the age:");
    scanf("%d", &add.age);
    printf("\nEnter the address:");
    scanf("%s", add.address);
    printf("\nEnter the citizenship number:");
    scanf("%s", add.citizenship);
    printf("\nEnter the phone number: ");
    scanf("%s", add.phone);
    printf("\nEnter the amount to deposit:$");
    scanf("%f", &add.amt);
    printf("\n~~ %s ~~\n", add.bank_name);
    printf("\nType of account:\n\t#Saving\n\t#Current\n\t#Fixed1(for 1 year)\n\t#Fixed2(for 2 years)\n\t#Fixed3(for 3 years)\n\n\tEnter your choice:");
    scanf("%s", add.acc_type);

    fprintf(ptr, "%d %s %d/%d/%d %d %s %s %s %s %f %d/%d/%d %s\n", add.acc_no, add.name, add.dob.month, add.dob.day, add.dob.year, add.age, add.address, add.citizenship, add.phone, add.acc_type, add.amt, add.deposit.month, add.deposit.day, add.deposit.year, add.bank_name);

    fclose(ptr);
    printf("\nAccount created successfully!");
add_invalid:
    printf("\n\n\n\t\tEnter 1 to go to the main menu and 0 to exit:");
    scanf("%d", &main_exit);
    system("cls");
    if (main_exit == 1)
        menu();
    else if (main_exit == 0)
        close();
    else
    {
        printf("\nInvalid!\a");
        goto add_invalid;
    }
}
void view_list()
{
    clientInfo add;
    FILE *view;
    view = fopen("record.dat", "r");
    int test = 0;
    system("cls");
    printf("\n\n%-15s %-20s %-20s %-16s %s\n", "ACC. NO.", "NAME", "ADDRESS", "PHONE", "BANK");
    for (int i = 1; i <= 100; i++)
        printf("-");
    puts("");

    while (fscanf(view, "%d %s %d/%d/%d %d %s %s %s %s %f %d/%d/%d %s", &add.acc_no, add.name, &add.dob.month, &add.dob.day, &add.dob.year, &add.age, add.address, add.citizenship, add.phone, add.acc_type, &add.amt, &add.deposit.month, &add.deposit.day, &add.deposit.year, add.bank_name) != EOF)
    {
        printf("%-15d %-20s %-20s %-16s %s\n", add.acc_no, add.name, add.address, add.phone, add.bank_name);
        test++;
    }

    fclose(view);
    if (test == 0)
    {
        system("cls");
        printf("\nNO RECORDS!!\n");
    }

view_list_invalid:
    printf("\n\nEnter 1 to go to the main menu and 0 to exit:");
    scanf("%d", &main_exit);
    system("cls");
    if (main_exit == 1)
        menu();
    else if (main_exit == 0)
        close();
    else
    {
        printf("\nInvalid!\a");
        goto view_list_invalid;
    }
}
void edit(void)
{
    clientInfo upd, add;
    int choice, test = 0;
    FILE *old, *newrec;
    old = fopen("record.dat", "r");
    newrec = fopen("new.dat", "w");

    printf("\nEnter the account no. of the customer whose info you want to change:");
    scanf("%d", &upd.acc_no);
    while (fscanf(old, "%d %s %d/%d/%d %d %s %s %s %s %f %d/%d/%d %s", &add.acc_no, add.name, &add.dob.month, &add.dob.day, &add.dob.year, &add.age, add.address, add.citizenship, add.phone, add.acc_type, &add.amt, &add.deposit.month, &add.deposit.day, &add.deposit.year, add.bank_name) != EOF)
    {
        if (add.acc_no == upd.acc_no)
        {
            test = 1;
            printf("\nWhich information do you want to change?\n1.Address\n2.Phone\n\nEnter your choice(1 for address and 2 for phone):");
            scanf("%d", &choice);
            system("cls");
            if (choice == 1)
            {
                printf("Enter the new address:");
                scanf("%s", upd.address);
                fprintf(newrec, "%d %s %d/%d/%d %d %s %s %s %s %f %d/%d/%d %s\n", add.acc_no, add.name, add.dob.month, add.dob.day, add.dob.year, add.age, upd.address, add.citizenship, add.phone, add.acc_type, add.amt, add.deposit.month, add.deposit.day, add.deposit.year, add.bank_name);
                system("cls");
                printf("Changes saved!");
            }
            else if (choice == 2)
            {
                printf("Enter the new phone number:");
                scanf("%s", upd.phone);
                fprintf(newrec, "%d %s %d/%d/%d %d %s %s %s %s %f %d/%d/%d %s\n", add.acc_no, add.name, add.dob.month, add.dob.day, add.dob.year, add.age, add.address, add.citizenship, upd.phone, add.acc_type, add.amt, add.deposit.month, add.deposit.day, add.deposit.year, add.bank_name);
                system("cls");
                printf("Changes saved!");
            }
        }
        else
            fprintf(newrec, "%d %s %d/%d/%d %d %s %s %s %s %f %d/%d/%d %s\n", add.acc_no, add.name, add.dob.month, add.dob.day, add.dob.year, add.age, add.address, add.citizenship, add.phone, add.acc_type, add.amt, add.deposit.month, add.deposit.day, add.deposit.year, add.bank_name);
    }
    fclose(old);
    fclose(newrec);
    remove("record.dat");
    rename("new.dat", "record.dat");

    if (test != 1)
    {
        system("cls");
        printf("\nRecord not found!!\a\a\a");
    edit_invalid:
        printf("\nEnter 0 to try again,1 to return to main menu and 2 to exit:");
        scanf("%d", &main_exit);
        system("cls");
        if (main_exit == 1)

            menu();
        else if (main_exit == 2)
            close();
        else if (main_exit == 0)
            edit();
        else
        {
            printf("\nInvalid!\a");
            goto edit_invalid;
        }
    }
    else
    {
        printf("\n\n\nEnter 1 to go to the main menu and 0 to exit:");
        scanf("%d", &main_exit);
        system("cls");
        if (main_exit == 1)
            menu();
        else
            close();
    }
}

void transact(void)
{
    clientInfo transaction, add;
    int choice, test = 0;
    FILE *old, *newrec;
    old = fopen("record.dat", "r");
    newrec = fopen("new.dat", "w");

    printf("Enter the account no. of the customer:");
    scanf("%d", &transaction.acc_no);
    while (fscanf(old, "%d %s %d/%d/%d %d %s %s %s %s %f %d/%d/%d %s", &add.acc_no, add.name, &add.dob.month, &add.dob.day, &add.dob.year, &add.age, add.address, add.citizenship, add.phone, add.acc_type, &add.amt, &add.deposit.month, &add.deposit.day, &add.deposit.year, add.bank_name) != EOF)
    {

        if (add.acc_no == transaction.acc_no)
        {
            test = 1;
            if (strcmpi(add.acc_type, "fixed1") == 0 || strcmpi(add.acc_type, "fixed2") == 0 || strcmpi(add.acc_type, "fixed3") == 0)
            {
                printf("\a\a\a\n\nYOU CANNOT DEPOSIT OR WITHDRAW CASH IN FIXED ACCOUNTS!!!!!");
                fordelay(1000000000);
                system("cls");
                menu();
            }
            printf("\n\nDo you want to\n1.Deposit\n2.Withdraw?\n\nEnter your choice(1 for deposit and 2 for withdraw):");
            scanf("%d", &choice);
            if (choice == 1)
            {
                printf("Enter the amount you want to deposit:$ ");
                scanf("%f", &transaction.amt);
                add.amt += transaction.amt;
                fprintf(newrec, "%d %s %d/%d/%d %d %s %s %s %s %f %d/%d/%d %s\n", add.acc_no, add.name, add.dob.month, add.dob.day, add.dob.year, add.age, add.address, add.citizenship, add.phone, add.acc_type, add.amt, add.deposit.month, add.deposit.day, add.deposit.year, add.bank_name);
                printf("\n\nDeposited successfully!");
            }
            else
            {
                printf("Enter the amount you want to withdraw:$ ");
                scanf("%f", &transaction.amt);
                add.amt -= transaction.amt;
                fprintf(newrec, "%d %s %d/%d/%d %d %s %s %s %s %f %d/%d/%d %s\n", add.acc_no, add.name, add.dob.month, add.dob.day, add.dob.year, add.age, add.address, add.citizenship, add.phone, add.acc_type, add.amt, add.deposit.month, add.deposit.day, add.deposit.year, add.bank_name);
                printf("\n\nWithdrawn successfully!");
            }
        }
        else
        {
            fprintf(newrec, "%d %s %d/%d/%d %d %s %s %s %s %f %d/%d/%d %s\n", add.acc_no, add.name, add.dob.month, add.dob.day, add.dob.year, add.age, add.address, add.citizenship, add.phone, add.acc_type, add.amt, add.deposit.month, add.deposit.day, add.deposit.year, add.bank_name);
        }
    }
    fclose(old);
    fclose(newrec);
    remove("record.dat");
    rename("new.dat", "record.dat");
    if (test != 1)
    {
        printf("\n\nRecord not found!!");
    transact_invalid:
        printf("\n\n\nEnter 0 to try again,1 to return to main menu and 2 to exit:");
        scanf("%d", &main_exit);
        system("cls");
        if (main_exit == 0)
            transact();
        else if (main_exit == 1)
            menu();
        else if (main_exit == 2)
            close();
        else
        {
            printf("\nInvalid!");
            goto transact_invalid;
        }
    }
    else
    {
        printf("\nEnter 1 to go to the main menu and 0 to exit:");
        scanf("%d", &main_exit);
        system("cls");
        if (main_exit == 1)
            menu();
        else
            close();
    }
}
void erase(void)
{
    clientInfo rem, add;
    FILE *old, *newrec;
    int test = 0;
    old = fopen("record.dat", "r");
    newrec = fopen("new.dat", "w");
    printf("Enter the account no. of the customer you want to delete:");
    scanf("%d", &rem.acc_no);
    while (fscanf(old, "%d %s %d/%d/%d %d %s %s %s %s %f %d/%d/%d %s", &add.acc_no, add.name, &add.dob.month, &add.dob.day, &add.dob.year, &add.age, add.address, add.citizenship, add.phone, add.acc_type, &add.amt, &add.deposit.month, &add.deposit.day, &add.deposit.year, add.bank_name) != EOF)
    {
        if (add.acc_no != rem.acc_no)
            fprintf(newrec, "%d %s %d/%d/%d %d %s %s %s %s %f %d/%d/%d %s\n", add.acc_no, add.name, add.dob.month, add.dob.day, add.dob.year, add.age, add.address, add.citizenship, add.phone, add.acc_type, add.amt, add.deposit.month, add.deposit.day, add.deposit.year, add.bank_name);

        else
        {
            test++;
            printf("\nRecord deleted successfully!\n");
        }
    }
    fclose(old);
    fclose(newrec);
    remove("record.dat");
    rename("new.dat", "record.dat");
    if (test == 0)
    {
        printf("\nRecord not found!!\a\a\a");
    erase_invalid:
        printf("\nEnter 0 to try again,1 to return to main menu and 2 to exit:");
        scanf("%d", &main_exit);

        if (main_exit == 1)
            menu();
        else if (main_exit == 2)
            close();
        else if (main_exit == 0)
            erase();
        else
        {
            printf("\nInvalid!\a");
            goto erase_invalid;
        }
    }
    else
    {
        printf("\nEnter 1 to go to the main menu and 0 to exit:");
        scanf("%d", &main_exit);
        system("cls");
        if (main_exit == 1)
            menu();
        else
            close();
    }
}

void see(void)
{
    clientInfo check, add;
    FILE *ptr;
    int test = 0, rate;
    int choice;
    float time;
    float intrst;
    ptr = fopen("record.dat", "r");
    printf("Do you want to check by\n1.Account no\n2.Name\nEnter your choice:");
    scanf("%d", &choice);
    if (choice == 1)
    {
        printf("Enter the account number:");
        scanf("%d", &check.acc_no);

        while (fscanf(ptr, "%d %s %d/%d/%d %d %s %s %s %s %f %d/%d/%d %s", &add.acc_no, add.name, &add.dob.month, &add.dob.day, &add.dob.year, &add.age, add.address, add.citizenship, add.phone, add.acc_type, &add.amt, &add.deposit.month, &add.deposit.day, &add.deposit.year, add.bank_name) != EOF)
        {
            if (add.acc_no == check.acc_no)
            {
                system("cls");
                test = 1;

                printf("\nAccount NO.:%d\nName:%s \nDOB:%d/%d/%d \nAge:%d \nAddress:%s \nCitizenship No:%s \nPhone number:%s \nType Of Account:%s \nAmount deposited:$ %.2f \nDate Of Deposit:%d/%d/%d\nBank: %s\n\n", add.acc_no, add.name, add.dob.month, add.dob.day, add.dob.year, add.age, add.address, add.citizenship, add.phone,
                       add.acc_type, add.amt, add.deposit.month, add.deposit.day, add.deposit.year, add.bank_name);
                if (strcmpi(add.acc_type, "fixed1") == 0)
                {
                    time = 1.0;
                    rate = 9;
                    intrst = interest(time, add.amt, rate);
                    printf("\n\nYou will get $%.2f as interest on %d/%d/%d", intrst, add.deposit.month, add.deposit.day, add.deposit.year + 1);
                }
                else if (strcmpi(add.acc_type, "fixed2") == 0)
                {
                    time = 2.0;
                    rate = 11;
                    intrst = interest(time, add.amt, rate);
                    printf("\n\nYou will get $.%.2f as interest on %d/%d/%d", intrst, add.deposit.month, add.deposit.day, add.deposit.year + 2);
                }
                else if (strcmpi(add.acc_type, "fixed3") == 0)
                {
                    time = 3.0;
                    rate = 13;
                    intrst = interest(time, add.amt, rate);
                    printf("\n\nYou will get $.%.2f as interest on %d/%d/%d", intrst, add.deposit.month, add.deposit.day, add.deposit.year + 3);
                }
                else if (strcmpi(add.acc_type, "saving") == 0)
                {
                    time = (1.0 / 12.0);
                    rate = 8;
                    intrst = interest(time, add.amt, rate);
                    printf("\n\nYou will get $.%.2f as interest on %d of every month", intrst, add.deposit.day);
                }
                else if (strcmpi(add.acc_type, "current") == 0)
                {

                    printf("\n\nYou will get no interest\a\a");
                }
            }
        }
    }
    else if (choice == 2)
    {
        clientInfo check, add;
        printf("Enter the name:");
        scanf("%s", check.name);
        while (fscanf(ptr, "%d %s %d/%d/%d %d %s %s %s %s %f %d/%d/%d %s", &add.acc_no, add.name, &add.dob.month, &add.dob.day, &add.dob.year, &add.age, add.address, add.citizenship, add.phone, add.acc_type, &add.amt, &add.deposit.month, &add.deposit.day, &add.deposit.year, add.bank_name) != EOF)
        {
            if (strcmpi(add.name, check.name) == 0)
            {
                system("cls");
                test = 1;
                printf("\nAccount NO.:%d\nName:%s \nDOB:%d/%d/%d \nAge:%d \nAddress:%s \nCitizenship No:%s \nPhone number:%s \nType Of Account:%s \nAmount deposited:$ %.2f \nDate Of Deposit:%d/%d/%d\nBank: %s\n\n", add.acc_no, add.name, add.dob.month, add.dob.day, add.dob.year, add.age, add.address, add.citizenship, add.phone,
                       add.acc_type, add.amt, add.deposit.month, add.deposit.day, add.deposit.year, add.bank_name);
                if (strcmpi(add.acc_type, "fixed1") == 0)
                {
                    time = 1.0;
                    rate = 9;
                    intrst = interest(time, add.amt, rate);
                    printf("\n\nYou will get $.%.2f as interest on %d/%d/%d", intrst, add.deposit.month, add.deposit.day, add.deposit.year + 1);
                }
                else if (strcmpi(add.acc_type, "fixed2") == 0)
                {
                    time = 2.0;
                    rate = 11;
                    intrst = interest(time, add.amt, rate);
                    printf("\n\nYou will get $.%.2f as interest on %d/%d/%d", intrst, add.deposit.month, add.deposit.day, add.deposit.year + 2);
                }
                else if (strcmpi(add.acc_type, "fixed3") == 0)
                {
                    time = 3.0;
                    rate = 13;
                    intrst = interest(time, add.amt, rate);
                    printf("\n\nYou will get $.%.2f as interest on %d/%d/%d", intrst, add.deposit.month, add.deposit.day, add.deposit.year + 3);
                }
                else if (strcmpi(add.acc_type, "saving") == 0)
                {
                    time = (1.0 / 12.0);
                    rate = 8;
                    intrst = interest(time, add.amt, rate);
                    printf("\n\nYou will get $.%.2f as interest on %d of every month", intrst, add.deposit.day);
                }
                else if (strcmpi(add.acc_type, "current") == 0)
                {

                    printf("\n\nYou will get no interest\a\a");
                }
            }
        }
    }

    fclose(ptr);
    if (test != 1)
    {
        system("cls");
        printf("\nRecord not found!!\a\a\a");
    see_invalid:
        printf("\nEnter 0 to try again,1 to return to main menu and 2 to exit:");
        scanf("%d", &main_exit);
        system("cls");
        if (main_exit == 1)
            menu();
        else if (main_exit == 2)
            close();
        else if (main_exit == 0)
            see();
        else
        {
            system("cls");
            printf("\nInvalid!\a");
            goto see_invalid;
        }
    }
    else
    {
        printf("\nEnter 1 to go to the main menu and 0 to exit:");
        scanf("%d", &main_exit);
    }
    if (main_exit == 1)
    {
        system("cls");
        menu();
    }

    else
    {

        system("cls");
        close();
    }
}

void close(void)
{
    printf("\n\n\n\nThis C Mini Project is developed by Code With C team!");
}

void menu(void)
{
    int choice;
    system("cls");
    system("color 9");
    printf("\n\n\t\t\tCUSTOMER ACCOUNT BANKING MANAGEMENT SYSTEM");
    printf("\n\n\n\t\t\t\xB2\xB2\xB2\xB2\xB2\xB2\xB2 WELCOME TO THE MAIN MENU \xB2\xB2\xB2\xB2\xB2\xB2\xB2");
    printf("\n\n\t\t1.Create new account\n\t\t2.Update information of existing account\n\t\t3.For transactions\n\t\t4.Check the details of existing account\n\t\t5.Removing existing account\n\t\t6.View customer's list\n\t\t7.Search account\n\t\t8.Exit\n\n\n\n\n\t\t Enter your choice:");
    scanf("%d", &choice);

    system("cls");
    switch (choice)
    {
    case 1:
        new_acc();
        break;
    case 2:
        edit();
        break;
    case 3:
        transact();
        break;
    case 4:
        see();
        break;
    case 5:
        erase();
        break;
    case 6:
        view_list();
        break;
    case 7:
        search_acc();
        break;
    case 8:
        close();
        break;
    }
}
int main()
{
    char pass[10], password[20] = "a";
    int i = 0;
    printf("\n\n\t\tEnter the password to login:");
    scanf("%s", pass);
    /*do
    {
    //if (pass[i]!=13&&pass[i]!=8)
        {
            printf("*");
            pass[i]=getch();
            i++;
        }
    }while (pass[i]!=13);
    pass[10]='\0';*/
    if (strcmp(pass, password) == 0)
    {
        printf("\n\nPassword Match!\nLOADING");
        for (i = 0; i <= 6; i++)
        {
            fordelay(100000000);
            printf(".");
        }
        system("cls");
        menu();
    }
    else
    {
        printf("\n\nWrong password!!\a\a\a");
    login_try:
        printf("\nEnter 1 to try again and 0 to exit:");
        scanf("%d", &main_exit);
        if (main_exit == 1)
        {

            system("cls");
            main();
        }

        else if (main_exit == 0)
        {
            system("cls");
            close();
        }
        else
        {
            printf("\nInvalid!");
            fordelay(1000000000);
            system("cls");
            goto login_try;
        }
    }
    return 0;
}
