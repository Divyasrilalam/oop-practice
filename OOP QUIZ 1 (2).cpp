#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
#include<process.h>

struct UserCredentials
{
    char userName[50];
    char password[100];
    char phoneNo[10];
    char country[50];
    char bloodGroup[5];
};

struct BloodDonation
{
    char userName[50];
    char bloodGroup[5];
    char hospital[100];
};

struct Hospital
{
    char HostpitalName[100];
    char area[100];
};

//declaring variable
static struct UserCredentials userList[100];
static int userCount = 0;

static struct BloodDonation donationList[100];
static int donationCount = -1;

static struct BloodDonation bloodRequestList[100];
static int bloodRequestListCount = -1;

static struct Hospital hospitalList[100];
static int hospitalListCount = -1;

int main(void)
{
    int i = 0;

    while(1)
    {
        int choice;

        struct UserCredentials userCredential;

        struct UserCredentials adminCredential = {"Admin", "Admin", "1231231231", "India"};

        //User 0 is Admin
        userList[0] = adminCredential;

        printf("\n\n--------------Menu Page---------------");
        printf("\n1. Register.\n2. Login.\n3. Exit.\nPlease enter the number your choice is in:");

        scanf("%d", &choice);

        switch(choice)
        {
            case 1:
                printf("\nPlease wait while we navigate to registration page...");
                sleep(1);
                system("cls");
                UserRegistration();
                break;
            case 2:
                printf("\nPlease wait while we navigate to Login page...");
                sleep(1);
                system("cls");
                UserLogin();
                break;
            case 3:
                printf("Thank you for using the application. Please visit us back.\n");
                return;
            default:
                printf("\nInvalid input. Please enter a valid choice.");
                sleep(1);
                break;
        }
        system("cls");
    }
}

void UserRegistration()
{
    int bloodGroupChoice;

    //Declaring a character array to store the confirm password
    char confrimPassword[50];

    //Declaring UserCredentials structure variable to read data from file and store user data into file
    struct UserCredentials userCredential;

    //Printing prompt for user
    printf("\n\n--------------Registration Page---------------\n\n");

    //Reading user name from the user
    registrationStartProcess:

    printf("Please enter your user name: ");

    scanf("%s", userCredential.userName);

    //Checking if any user is having same user name
    for(int iterator = 0; iterator <= userCount; iterator++)
    {
        if(!strcmp(userCredential.userName, userList[iterator].userName))
        {
            //If user has same user name
            printf("\nUser name has already taken\n");

            sleep(3);

            //Re entering user name
            goto registrationStartProcess;
        }
    }

    //Reading user password
    passwordReEntry:
    printf("\n\nPassword: ");

    scanf("%s", userCredential.password);

    printf("\n\nPlease confirm your password: ");

    scanf("%s", confrimPassword);

    if(strcmp(confrimPassword, userCredential.password))
    {
        //If password is not same as confirm password
        printf("\nPassword Mismatch. Please re-enter password");

        //Asking user to re-enter the password
        goto passwordReEntry;
    }

    //Reading user phone number
    phoneReEntry:
    printf("\n\nPlease enter your 10 digit phone number without country code: ");

    //reading User phone number
    scanf("%s", userCredential.phoneNo);

    if(strlen(userCredential.phoneNo) != 10)
    {
        //If phone no is not equals to 10 digit number
        printf("\nPlease enter correct phone no.");

        //Asking user to reenter the phone number
        goto phoneReEntry;
    }

    //Asking user to enter country
    printf("\n\nPlease enter your country: ");

    //Reading country from user
    scanf("%s", userCredential.country);

    //Reading User blood group
    bloodGroupReEnter:
    printf("\n\n1.A+\n2.A-\n3.B+\n4.B-\n5.O+\n6.O-\n7.AB+\n8.AB-\nPlease select the number your blood group is located in:");

    scanf("%d", &bloodGroupChoice);

    switch(bloodGroupChoice)
    {
        case 1:
            strcpy(userCredential.bloodGroup, "A+");
            break;
        case 2:
            strcpy(userCredential.bloodGroup , "A-");
            break;
        case 3:
            strcpy(userCredential.bloodGroup , "B+");
            break;
        case 4:
            strcpy(userCredential.bloodGroup , "B-");
            break;
        case 5:
            strcpy(userCredential.bloodGroup , "O+");
            break;
        case 6:
            strcpy(userCredential.bloodGroup, "O-");
            break;
        case 7:
            strcpy(userCredential.bloodGroup , "AB+");
            break;
        case 8:
            strcpy(userCredential.bloodGroup , "AB-");
            break;
        default:
            printf("Please enter correct choice.");
            goto bloodGroupReEnter;
    }

    //Storing user credentials into a file
    userList[++userCount] = userCredential;

    printf("\n\nUser registration successful");
    sleep(3);
}

void UserLogin()
{
    int choice;

    char userName[100], password[100];

    struct UserCredentials userDetails;

    loginretry:
    printf("\n\n--------------Login Page---------------\n\n");

    printf("\n1. Login.\n2. Go Back.\n\nPlease enter your choice:");

    scanf("%d", &choice);

    switch(choice)
    {
        case 1:
            break;
        case 2:
            system("cls");
            return;
        default:
            printf("Please enter correct option");
            system("cls");
            goto loginretry;
            break;
    }

    printf("\nEnter user name: ");
    scanf("%s", userName);

    //Checking if any user is having same user name
    for(int iterator = 0; iterator <= userCount; iterator++)
    {
        printf("Comparing: %s---", userList[iterator].userName);
        printf("Compared: %d\n", strcmp(userName, userList[iterator].userName));
        sleep(3);
        if(!strcmp(userName, userList[iterator].userName))
        {
            userDetails = userList[iterator];
            //Re entering user name
            goto passwordEntry;
        }
    }

    system("cls");
    printf("User Not found please retry");
    sleep(2);
    goto loginretry;

    passwordEntry:
    printf("\nEnter password: ");
    scanf("%s", password);

    if(strcmp(userDetails.password, password))
    {
        printf("Invalid credentials. Please try again");
        sleep(2);
        goto loginretry;
    }

    printf("\nLoading");

    if(strcmp("Admin",userName))
    {
        AdminPage();
    }
    else
    {
        //UserPage();
    }

    sleep(1);

    system("cls");
}

void AdminPage()
{
    int choice;

    while(1)
    {

        printf("\n\n--------------Admin Page---------------\n\n");

        choiceretry:
        printf("\n1. To view hospital list.\n2. To add hospital list.\n3. To view blood donors list.\n4. To view donation request list.\n5.To Logout.\nPlease enter your choice: ");

        scanf("%d", &choice);

        switch(choice)
        {
            case 1: ViewHospitalList();
                break;
            case 2: AddHopital();
                break;
            case 3: ViewBloodDonorsList();
                break;
            case 4: ViewBloodRequestList();
                break;
            case 5:
                printf("Signing out. Please wait");
                return;
            default:
                printf("Please enter correct choice");
                goto choiceretry;
        }
    }
}
void ViewHospitalList()
{
    char ch;
    if(hospitalListCount == -1)
    {
        printf("No hospitals added by Admin");
    }
    else
    {
        system("cls");
        printf("\n\n--------------Hospital List---------------\n\n");
        for(int iterator; iterator>= hospitalListCount; iterator++)
        {
            printf("\n\nHospital Name: %s", hospitalList[iterator].HostpitalName);
            printf("Area Name: %s", hospitalList[iterator].area);
        }
    }
    printf("\n Press any key to go back");
    scanf("%s", ch);
}

void AddHopital()
{
    struct Hospital hospital;

    printf("Enter Hopital name: ");

    scanf("%s", hospital.HostpitalName);

    printf("Enter Hospital Area: ");

    scanf("%s", hospital.area);

    hospitalList[++hospitalListCount] = hospital;

    printf("Hospital Added");
}

void ViewBloodDonorsList()
{
    char ch;
    if(donationCount == -1)
    {
        printf("No Donors yet");
    }
    else
    {
        system("cls");
        printf("\n\n--------------Donor List List---------------\n\n");
        for(int iterator; iterator>= donationCount; iterator++)
        {
            printf("\n\Donor name Name: %s", donationList[iterator].userName);
            printf("Donor Blood group: %s", donationList[iterator].bloodGroup);
            printf("Donor hospital Name: %s", donationList[iterator].bloodGroup);
        }
    }
    printf("\n Press any key to go back");
    scanf("%s", ch);
}

void ViewBloodRequestList()
{
    char ch;
    if(bloodRequestListCount == -1)
    {
        printf("No Donors yet");
    }
    else
    {
        system("cls");
        printf("\n\n--------------Donor List List---------------\n\n");
        for(int iterator; iterator>= bloodRequestListCount; iterator++)
        {
            printf("\nDonor name Name: %s", bloodRequestList[iterator].userName);
            printf("Donor Blood group: %s", bloodRequestList[iterator].bloodGroup);
            printf("Donor hospital Name: %s", bloodRequestList[iterator].bloodGroup);
        }
    }
    printf("\n Press any key to go back");
    scanf("%s", ch);
}

