/*
Yatharth Alpeshkumar Soni <soniyat@sheridan.desire2learn.com>
 * Nicholas dias
----------------------------------------------------------------------
 */

/* 
 * File:   main.c
 * Authors: Yatharth Alpeshkumar Soni <soniyat@sheridan.desire2learn.com>
 * Nicholas Dias
 *
 * Created on August 4, 2019, 9:41 PM
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include<ctype.h>

#define REMOVEN(str) str[strcspn(str,"\n")]=0
#define FLUSH stdin=freopen(NULL,"r",stdin)
#define MAX_LEN 100

//Struct node -> cars_t
struct node{
	size_t id;
	char * carMake;
	char * carModel;
	char * color;
	int speed;
	float price; 
	struct node *next;
	struct node *previous;
};
typedef struct node cars_t;

//safeCopy --helps in copying the strings(specifies malloc())
char *safeCopy(char *);

//function that loads the file, creates linked list and fills it with correct data
void openAndLoadFile();

//used for viewing the fields
void view();

//used for clearing the screen
void clrscr();

//creating Node
cars_t* createNodeEmpty();

//Adding whole new entity in the list
cars_t *add();

//creating Linked List
cars_t *createList();

//updating entities in the nodes
void update();

//Shows the delete menu and gives the user option to select the node he wished to delete
void delete();

//Delete the selected node
void nodeDelete(size_t);

//Removes the \n and \r from the strings
char *trimwhitespace(char *);

//saves the linked list to the file and exits from the program
void saveAndExit();

//viewAll the data
void viewAll();

//search according to the id
cars_t * search(size_t, cars_t *);

//submit the node
cars_t * submit(size_t, char *, char *, char *, int, float);

//creating the node
cars_t * createNode(size_t, char *, char *, char *, int, float); // function to create the node

//printing the node
void printNode(cars_t *);

//main linked list
cars_t * head;
cars_t * returnNode;
//Last ID of the list used for adding new Nodes to the list
size_t lastID;
        
        
int main() {
	fflush(stdin);
       
        //opening and Loading the file into the Linked List..
        openAndLoadFile();
        printf(">>>>>>>>>>>CAR DEALERSHIP APPLICATION<<<<<<<<<<<<<<<<<<<<<<");
        
        while(1){
        clrscr();
        char mainSelect = 'z'; 
	printf("\nMain Menu");
	printf("\nTo view records press 'v'.");
	printf("\nTo Add Record press 'a'. ");
	printf("\nUpdate Record press 'u'. ");
	printf("\nDelete Record press 'd'. ");
	printf("\nTo Search the Records press 's'.");
        printf("\nTo View All press 'z'");
	printf("\nTo Exit press 'e'. ");
        printf("\nPlease Enter your Selection: ");
	fflush(stdin);
        scanf(" %c", &mainSelect);
	printf("\n");
        
        //view
	if(mainSelect == 'v' || mainSelect == 'V'){
	view();		
	}
        //Add
	else if(mainSelect == 'a' || mainSelect == 'A'){
	printf("Add Selected !");
	cars_t * newNode = add();
        printNode(newNode);
        printf("\nSuccessfully Added!!\n");
	}
        
        //Update
	else if(mainSelect == 'u' || mainSelect == 'U'){
            update();
        }
	else if(mainSelect == 'z' || mainSelect == 'Z'){
            viewAll();
        }
        
        //Delete
	else if(mainSelect == 'd' || mainSelect == 'D'){
	printf("Delete Selected !");		
	}
	else if(mainSelect == 'e' || mainSelect == 'E'){
	printf("Exit Selected !");		
	saveAndExit();
	}
        //Search
	else if(mainSelect == 's' || mainSelect == 'S'){
	printf("Search Selected !");
        int idSearch;
        printf("Please enter the ID you wish to search :");
        scanf("%d", &idSearch);
	cars_t * searchResult = search(idSearch, head);
        printNode(searchResult);
        }
	else{
		printf("Invalid Entry");
		main();
	}
	}
	return 0;
}
void viewAll(){
    cars_t * tempPoint;
    tempPoint = (cars_t *)malloc(sizeof(cars_t));
    tempPoint = head;
    while(tempPoint != NULL){
        printNode(tempPoint);
        tempPoint = tempPoint->next;
    }
}

cars_t * add(){
	fflush(stdin); 
        clrscr();
        printf("\n=== ADD MENU===\n");
        cars_t *addTemp = createList();
        return addTemp;
}
cars_t *createList() {
    static cars_t *newNode = NULL;

    // We get new_node. It can be NULL in case we provide empty input 
    newNode = createNodeEmpty();
   // insertNode(&head, new_node);
    newNode->next = NULL;
    printf("Searched ID is : %zu" +(lastID-1));
    cars_t * lastNode =  search(lastID - 1, head);
    lastNode->next = newNode;
    return newNode;
}

cars_t * submit(size_t idTemp, char * carMakeTemp, char * carModelTemp, char * colorTemp, int speedTemp, float priceTemp){
    fflush(stdin); 
    printf("Inside Submit");
    cars_t*  fnNode;
    fnNode = (cars_t *)malloc(sizeof(cars_t));
    
    fnNode = search(idTemp, fnNode);
    char * carMake1 = carMakeTemp;
    char * carModel1 = carModelTemp;
    char * color1 = colorTemp;
    int speed1 = speedTemp;
    float price1 = priceTemp;
    if(idTemp == '\0'){
        printf("Error");
        main();
    }
    else{        
        fnNode -> carMake = carMake1; 
        fnNode -> carModel = carModel1;
        fnNode -> color = color1;
        fnNode -> speed = speed1;
        fnNode -> price = price1;
        return fnNode;
    }
}

cars_t * search(size_t idTemp, cars_t * fnNode){
        clrscr();
        printf("Search Menu");
        fflush(stdin); 
	fnNode = head;
        
        while(fnNode != NULL){
        if(fnNode->id == idTemp)
         return fnNode;   
        fnNode = fnNode -> next;
        }
        printf("\nThe element with the ID you searched does not exist!");
        return fnNode;
}
void update(){
	FLUSH;
    int updateSelect;
    char changeString[MAX_LEN] = {0};
    int changeInt;
    float changeFloat;
    cars_t *pos = head;
    
    printf("\n=== UPDATE MENU===\n");
    printf("Enter id you want to update: ");
    scanf(" %d", &updateSelect);
    pos = search(updateSelect, head);
    if (pos == NULL) {
        printf("List is empty Returning to Main Menu \n");
    }
        if (pos->id == updateSelect) {
            printf("What do you want to update: \n"
                    "1 for Car Make, \n"
                    "2 for Car Model, \n"
                    "3 for Color, \n"
                    "4 for Speed, \n"
                    "5 for Price, \n"
                    "6 to Exit \n");
            scanf("%d", &updateSelect);
            if (updateSelect == 1) {
                printf("Enter New Car Make: (id=%zu): ", pos->id);
                scanf("%s", &changeString);
                strcpy(pos->carMake, changeString);
            } else if (updateSelect == 2) {
                printf("Enter New Car Model: (id=%zu): ", pos->id);
                scanf("%s", &changeString);
                strcpy(pos->carModel, changeString);
            } else if (updateSelect == 3) {
                 printf("Enter New Car Color: (id=%zu): ", pos->id);
                scanf("%s", &changeString);
                strcpy(pos->color, changeString);
            } else if (updateSelect == 4) {
                printf("Enter New Car Speed: (id=%zu): ", pos->id);
                scanf("%d", &changeInt);
                pos->speed = changeInt;
            } else if (updateSelect == 5) {
                printf("Enter New Car Price: (id=%zu): ", pos->id);
                scanf("%f", &changeFloat);
                pos->price = changeFloat;
            } else if (updateSelect == 6) {
                saveAndExit();
            }
        }
}
void delete(){
	fflush(stdin); 
	char deleteSelect = 'z';
        cars_t * deleteNode = head;
        clrscr();
	
        while(1){
        clrscr();
        printNode(deleteNode);    
        printf("\n=== DELETE MENU===\n");
	printf("\nFor PREVIOUS press 'p'.");
	printf("\nFor NEXT press 'n'.");
	printf("\nFor SEARCH press 's'.");
	printf("\nTo DELETE press 'd'.");
	printf("\nTo EXIT press 'e'.");
        printf("\nPlease enter your choice:");
	scanf("%c", &deleteSelect);
	
	printf("\n");
	if(deleteSelect == 'p'){
	clrscr();
	if(deleteNode->previous != NULL){
            deleteNode = deleteNode->previous;
        }
        else{
            printf("Error Previous node does not exist!");
        }}
	else if(deleteSelect == 'n'){
	clrscr();
	if(deleteNode->next != NULL){
            deleteNode = deleteNode->previous;
        }
        else{
            printf("Error Previous node does not exist!");
        }}
	else if(deleteSelect == 'e'){
	printf("Exit Selected !\n");		
	saveAndExit();
        }
	else if(deleteSelect == 's'){
        clrscr();
        size_t nodeID;
        
        printf("\nSearch Selected !\n");		
	printf("\nPlease enter the ID of the entry you want to be deleted : ");
        scanf("%uz",&nodeID);
        deleteNode = search(nodeID, head);
	}
	else if(deleteSelect == 'd'){
        char * descision;
        size_t nodeID = deleteNode->id;
        printf("Are you sure? You wish to delete this?!\n");		
	printf("Enter 'y' for YES.");
        printf("Enter 'n' for NO.");
        scanf("%c",&descision);
        if(descision == "y" || descision == "Y"){
            nodeDelete(nodeID);
            printf("Successfully Removed");
        }
        else{
            
            printf("Attempt Cancelled!");
        }
        
        //submit();
	}
	else{
		printf("Invalid Entry\n");
		delete();
	}
        } 
}

//viewing the contents and storing them into an linked list.
void view(){
        clrscr();
	char buffer[100];
        int i;
        cars_t * tempPointer = head;
        
        while(1){    
        printNode(tempPointer);
        
        char viewSelect;
        printf("\nThe value of the selector is:  %c", viewSelect);
	
        printf("\n=== VIEW MENU===\n");
	printf("\nFor PREVIOUS press p");
	printf("\nFor NEXT press n");
	printf("\nTo SEARCH press s");
	printf("\nTo EXIT press e");
        fflush(stdin);
        scanf(" %c", &viewSelect);
        
	printf("\n");
        if(viewSelect == 'p'){
        clrscr();
	if(tempPointer->previous != NULL){
            tempPointer = tempPointer->previous;
        }
        else{
            printf("Error Previous node does not exist!");
        }
	}
	else if(viewSelect == 'n'){
        clrscr();
	printf("Next Selected !");
        if(tempPointer->next != NULL){
            tempPointer = tempPointer->next;
        }
        else{
            printf("\nError Next node does not exist!"); 
        }
	}
	else if(viewSelect == 'e'){
	printf("Exit Selected !");		
	main();
        }
	else if(viewSelect == 's'){
	printf("Search Selected !");
        int idSearch;
        printf("\nPlease enter the ID you wish to search :");
        scanf("%d", &idSearch);
	cars_t * searchResult = search(idSearch, head);
        printNode(searchResult);
	}
	else{
		printf("Invalid Entry");
	}
        }
}
cars_t * createNode(size_t idTemp, char * carMakeTemp, char * carModelTemp, char * colorTemp, int speedTemp, float priceTemp){
    cars_t*  fnNode;
    fnNode = (cars_t *)malloc(sizeof(cars_t));
    if(idTemp == '\0'){
        return NULL;
    }
    else{        
        fnNode -> id = idTemp;
        fnNode -> carMake = carMakeTemp;
        fnNode -> carModel = carModelTemp;
        fnNode -> color = colorTemp;
        fnNode -> speed = speedTemp;
        fnNode -> price = priceTemp;
        fnNode -> next = NULL;
        return fnNode;
    }
}

void printNode(cars_t * printNode){
    
    char * tempCarMake = safeCopy(printNode->carMake);
    char * tempCarModel = safeCopy(printNode->carModel);
    char * tempColor = safeCopy(printNode->color);
   
    //removing any new Line characters
   tempCarMake[strcspn(tempCarMake, "\r\n")] = 0;
   tempCarModel[strcspn(tempCarModel, "\r\n")] = 0;  
   tempColor[strcspn(tempColor, "\r\n")] = 0;
   
   //removing any whitespaces
   tempCarMake = safeCopy(trimwhitespace(tempCarMake));
   tempCarModel = safeCopy(trimwhitespace(tempCarModel));
   tempColor = safeCopy(trimwhitespace(tempColor));

   
    
    
   printf("\n------------------------------------------------------------------\n");
   printf("ID \t Car Make \t Car Model \t Color \t Average \t Price\n");
   printf("%zu \t %s \t %s \t %s \t %d \t\t %.2f", printNode->id, tempCarMake, tempCarModel, tempColor, printNode->speed, printNode->price);
}

void openAndLoadFile(){
        char buffer[500];
        
        FILE *in_file; 
        char input[500];
	
	if((in_file = fopen("TestFile.txt","r")) == NULL){
		printf("Error! Could not open the file");
		exit(-1);
	}
	
        size_t idTemp;
        char * carMakeTemp;
        char * carModelTemp;
        char * colorTemp;
        float priceTemp;
        int speedTemp;
        
        int length = 1;   
        
        cars_t * curr;
        cars_t * prev;
        returnNode = head;
        cars_t * addNode;
        addNode = (cars_t *)malloc(sizeof(cars_t));
    
        cars_t * newNode;
        newNode = (cars_t *)malloc(sizeof(cars_t));
    
        
        //while loop where all the fetching and storing is done.
        while(fgets(input, sizeof(input), in_file)){
            if(length == 1){
            idTemp = atoi(input);
            length++;
            }
            else if(length == 2){  
            carMakeTemp = safeCopy(input);
            length++;
            }
            else if(length == 3){
            carModelTemp = safeCopy(input);
            length++;
            }
            else if(length == 4){
            colorTemp = safeCopy(input);
            length++;
            }
            else if(length == 5){
            speedTemp = atoi(input);
            length++;
            }
            else if(length == 6){
            priceTemp = atof(input);
            
            length ++;
            }
            else if(length == 7){
                length ++;
                if(idTemp == 1){
                 head = createNode(idTemp, carMakeTemp, carModelTemp, colorTemp, speedTemp, priceTemp);
                 curr = head;
                 prev = curr;
                }
                else if(idTemp == 2){
          
                    newNode = createNode(idTemp, carMakeTemp, carModelTemp, colorTemp, speedTemp, priceTemp);
                    head -> next = newNode;
                    newNode -> previous = head;
                    curr = newNode;
                    prev = head;
                    newNode -> next = NULL;
                }
                else{
                    lastID = idTemp;
                    addNode = createNode(idTemp, carMakeTemp, carModelTemp, colorTemp, speedTemp, priceTemp);
                    addNode -> previous = newNode;
                    newNode -> next = addNode;
                    addNode -> next = NULL;
                    addNode = addNode->next;
                }
            }
            else {
                length = 1;
            }
        }
 	fclose(in_file);
	printf("\nThe open and load function successfully getting closed\n");        
}
char *safeCopy(char *s){
    char *t;
    t = (char *) malloc(strlen(s) + 1);
    if(t != NULL){
        strcpy(t, s);
    }
    return t;
}
char *trimwhitespace(char *str)
{
  char *end;

  // Trim leading space
  while(isspace((unsigned char)*str)) str++;

  if(*str == 0)  // All spaces?
    return str;

  // Trim trailing space
  end = str + strlen(str) - 1;
  while(end > str && isspace((unsigned char)*end)) end--;

  // Write new null terminator character
  end[1] = '\0';

  return str;
}

cars_t* createNodeEmpty() {
    cars_t* node = NULL;

    char carMakeTMP[MAX_LEN] = {0};
    char carModelTMP[MAX_LEN] = {0};
    char colorTMP[MAX_LEN] = {0};
    char speedTMP[MAX_LEN] = {0};
    char priceTMP[MAX_LEN] = {0};

    printf("Enter Car Make(id=%zu): ",(lastID+1));
    scanf(" %s", &carMakeTMP);
    FLUSH;
    printf("\n");
    //We get rid of '\n' character at the end :
    REMOVEN(carMakeTMP);

    printf("Enter Car Model: ");
    fgets(carModelTMP, sizeof (carModelTMP), stdin);
    FLUSH;
    REMOVEN(carModelTMP);

    //Car Color from User
    printf("Enter Car Color: ");
    fgets(colorTMP, sizeof (colorTMP), stdin);
    FLUSH;
    REMOVEN(colorTMP);

    //Car speed from User
    printf("Enter Car Speed: ");
    fgets(speedTMP, sizeof (speedTMP), stdin);
    FLUSH;
    REMOVEN(speedTMP);

    printf("Enter Car Price: ");
    fgets(priceTMP, sizeof (priceTMP), stdin);
    FLUSH;
    REMOVEN(priceTMP);


    node = (cars_t*) calloc(sizeof (cars_t), sizeof (char));
    if (node == NULL) {
        printf("Cannot allocate memory for a cars");
    saveAndExit(); 
    }

    //Insert id into the node
    lastID++;
    node->id = (lastID);
    //Allocate Memory for carMake and Insert carMake into the node
    node->carMake = calloc(strlen(carMakeTMP) + 1, sizeof (char));
    if (node->carMake == NULL) {
        printf("Cannot allocate memory for Make!");
    saveAndExit();
    }
    node->carMake = safeCopy(carMakeTMP);

    //Allocate Memory for carModel and Insert id into the node
    node->carModel = calloc(strlen(carModelTMP) + 1, sizeof (char));
    if (node->carModel == NULL) {
        printf("Cannot allocate memory for Model!");
    saveAndExit();
    }
    node->carModel = safeCopy(carModelTMP);

    //Allocate Memory for carColor and Insert id into the node
    node->color = calloc(strlen(colorTMP) + 1, sizeof (char));
    if (node->color == NULL) {
        printf("Cannot allocate memory for name!");
    saveAndExit();
    }
    node->color= safeCopy(colorTMP);

    //Convert speed to Integer
    int speedInt = atoi(speedTMP);
    //Insert id into the node
    node->speed = speedInt;

    //Convert price to float
    float pricefloat = atof(priceTMP);
    //Insert speed into the node
    node->price = pricefloat;
    
    node->next = NULL;
    printf("\n Car Added! \n \n");
    return node;
}
void clrscr(){
    system("@cls||clear");
}


void nodeDelete(size_t nodeID){
    size_t temp = nodeID;
    cars_t * deleteNode = search(temp, head);
     deleteNode = (cars_t *)malloc(sizeof(cars_t));
    if(temp == '\0'){
        printf("List is empty returning to main!!");
    }
    else{        
        deleteNode->id = nodeID;
        deleteNode->carMake = "\n";
        deleteNode->carModel = "\n";
        deleteNode->color = "\n";
        deleteNode->speed = 0;
        deleteNode->price = 0;
    }
}
void saveAndExit(){
    char decision;
    printf("\nWould you like to save the changes you made?\n");
    printf("\nPlease enter 'y' for yes.");
    printf("\nPlease enter 'n' for no.");
    printf("\nPlease enter your selection: ");
    fflush(stdin);
    scanf(" %c", &decision);
    if(decision == 'n'){
        exit(-1);
    }
    else{
        returnNode = head;
        int length = 1;
        char buffer[500];
        char * outID;
        char * outPrice;
        char * outSpeed;
        
        snprintf(outID, sizeof outID, "%zu", returnNode->id);;
        snprintf(outPrice, sizeof outPrice, "%f", returnNode->price);
        snprintf(outSpeed, sizeof outSpeed, "%d", returnNode->speed);
        
        FILE *out_file;
        if((out_file = fopen("outputList","w")) == NULL){
        printf("\nError Writing File!");
            printf("Jumping back to Main");
            main();
        }
        else{    
            printf("Successful");
        while(returnNode != NULL){
            fprintf(out_file, outID);
            if(returnNode->carMake != NULL){
            fprintf(out_file," %s ,", returnNode->carMake);
            }
            if(returnNode->carModel != NULL){
            fprintf(out_file," %s ,",returnNode->carModel);
            }
            if(returnNode->color != NULL){
            fprintf(out_file," %s ,",returnNode->color);
            }
            if(outPrice != NULL){
            fprintf(out_file," %s ,",outPrice);
            }
            if(outSpeed != NULL){
            fprintf(out_file," %s \n", outSpeed);
            }
            returnNode = returnNode->next;
        }
 	fclose(out_file);
        clrscr();
	printf("\nFile successfully Saved\n");                
        }
    }
}