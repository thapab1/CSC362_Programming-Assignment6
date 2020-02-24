/*Babita Thapa
  CSC 362
  Richard Fox
  Programming Assignment6
*/

/*This program is used to make linkedLists of Structs and to solve the Bin Packing Problem.There is also methods to insert items in the bins linkedLists in alphabetical order(if they fit into that bin), to traverse the binsand linkedLists, to print the linkedListsand binsand to destroy the binsand linkedLists.*/
#define _CRT_SECURE_NO_DEPRECATE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define SIZE 18

// bin struct with a capacity and a head pointer to the beginning of a linkedList
struct bin {
	double capacity;
	struct node* list; // struct node* front;
};


// struct to hold the datum and pointer to the next node in a linkedList
struct node {
	char* item;
	double weight;
	struct node* next;
};


//FUNCTION PROTOTYPES 
struct node* orderedInsert(struct node*, double, char*); // insert into linkedLists in alphabetical order
void printBin(int, double, struct node*); // print the current values inside the current bin
void traverse(struct bin[]); // traverse through the Array of bins
void destroy(struct node*); // destroy all the items in the linked list in the current bin

//main 
void main() {

	// an array of bin structs
	struct bin bins[20];

	//array of names and weights
	char* names[SIZE] = { "Computer Organization", "Internet_Infrastructure", "The_History_Of_The_Universe", "Linux_with_Operating_Systems_Concepts", "C_Programming", "Statistics", "English_For_Dummies", "American_History_2000-",
		"Computer_Architecture", "Hitchhiker's_Guide", "English-Minbari_Dictionary", "Zen_and_the_Art_of_Programming",
		"The_Joy_of_Cooking", "Heart_of_Darkness", "Cincinnati_Yellow_Pages", "Artificial_Intelligence",
		"Business_Programming:__Why?", "The_History_of_Ohio_State_Buckeyes" };
	double weights[] = { .75, .62, .27, .78, .21, .41, .55, .20, .90, .23, .42, .33, .56, .18, .98, .32, .12, .82 };

   /*
	char* names[SIZE] = { "Small_dog", "Moose_skull", "Squirrel", "Mouse", "Goldfish", "Snake", "Human_finger", "Pig_head",
		"Eagle_feather", "Shark_tooth", "Camel_hump", "Crocodile", "Elephant_tusk", "Cat", "Horse_manure", "Monkey_hand",
		"Octopus_eye", "Sheep_coat", "Bat", "Chicken_wing" };
	double weights[] = { .63, .25, .41, .15, .06, .52, .09, .39, .02, .11, .24, .94, .63, .28, .04, .21, .05, .33, .42, .12 };
	*/

	// int counter variables
	int i = 0, j = 0;


	// int variable that acts as a boolean variable on whether the item has been placed
	int isPlaced = 0;
	


	// for loop to initialize all the bins to have a capacity of 1.0 and a NULL linkedList
	for (i = 0; i < 20; i++) {
		bins[i].capacity = 1.0;
		bins[i].list = NULL;
	}


	// for loop to place the items inside the bins
	for (i = 0; i < SIZE; i++) {
		isPlaced = 0;
		j = 0;


		// while loop to loop through the bins to place the current item in the first bin it will fit in
		while (isPlaced == 0) {
			if (weights[i] < bins[j].capacity + .001) { // if the current item will fit
				bins[j].capacity -= weights[i]; // subtract the weight of the current item from the capacity of the current bin
				bins[j].list = orderedInsert(bins[j].list, weights[i], names[i]); // insert into current bin's linkedList in alphabetical order
				isPlaced = 1; // set "isPlaced" to 1 (true) to exit the while loop
			}
			else {
				j++; // move on to the next bin
			}
		}
	}


	// print all the bins with items in them
	traverse(bins);


	// destroy all the bins and set all their values back to their initial values
	for (int i = 0; i < 20; i++) {
		destroy(bins[i].list);
		bins[i].list = NULL;
		bins[i].capacity = 1.0;
	}


	// print the bins
	traverse(bins);
}




// insert the item into the current bin's linkedList in alphabetical order
struct node* orderedInsert(struct node* head, double itemWeight, char* itemName) {


	struct node* temp, * current, * previous;		  // temp will point to new node, current and previous used to traverse list
	temp = (struct node*)malloc(sizeof(struct node)); // allocate a node from heap
	temp->weight = itemWeight;						  // assign the new node its value
	temp->item = itemName;
	temp->next = NULL;              // and it will be the current last node, so make next NULL
	if (head == NULL) return temp;  // special case of empty list, no list to traverse
	else if (strcmp(head->item, itemName) > 0) // special case 2:  if new node should be inserted at front
	{
		temp->next = head;      // let new node point at rest of list
		return temp;            // and return new node's pointer as new front of the list
	}
	else                         // have to traverse list until we have a pointer at the last node
	{
		current = head;              // initialize our two pointers to work down the list, current always
		previous = NULL;             // pointing at current node while previous points at its predecessor
		while (current != NULL && strcmp(head->item, itemName) < 0) {  // traverse list until we either reach the end of find the right location
			previous = current;            // previous always points at prior node
			current = current->next;       // current points at node we are inspecting
		}
		previous->next = temp;      // attach new node to list by having previous point at it
		temp->next = current;       // and reattach rest of list to temp's next field
		return head;               // return the front pointer so that we can reattach list in main
	}
}


// traverse through the Array of bins
void traverse(struct bin printBins[]) {
	// int counter variables
	int i = 0;
	int j = 0;


	// set "j" to the amount of bins with items inside them
	for (; i < 20; i++) {
		if (printBins[i].capacity < 1.0) {
			j++;
		}
	}


	// call print on only the bins with items inside them
	for (i = 0; i < j; i++) {
		printBin(i, printBins[i].capacity, printBins[i].list);
		printf("\n");
	}
}


// print the bin number, capacity and the items in the linkedList inside the bin
void printBin(int binNumber, double remainingCapacity, struct node* head) {
	printf("Bin %d (%.2f remaining): ", binNumber, remainingCapacity);


	// if there are items inside the linkedList, then print them
	if (head != NULL) {
		struct node* current = head;
		struct node* previous = NULL;


		// while loop to inchworm through the linkedList and print all the items inside it
		while (current != NULL) {
			printf("%s (%.2f), ", current->item, current->weight);
			previous = current;
			current = current->next;
		}
	}
}


void destroy(struct node* head) {         // deallocate all heap memory
	struct node* temp = head;            // need a temp pointer as one pointer will point to next


	while (head != NULL) {                // while we still have list nodes to deallocate
		head = head->next;               // f now points to the next node in the list
		free(temp);                      // so we can deallocate the current node
		temp = head;
	}
}


/*OUTPUT
Run 1:
Bin 0 (-0.00 remaining): Eagle_feather (0.02), Goldfish (0.06), Moose_skull (0.25), Small_dog (0.63), Horse_manure (0.04),
Bin 1 (0.00 remaining): Camel_hump (0.24), Human_finger (0.09), Mouse (0.15), Squirrel (0.41), Shark_tooth (0.11),
Bin 2 (0.04 remaining): Octopus_eye (0.05), Pig_head (0.39), Snake (0.52),
Bin 3 (0.06 remaining): Crocodile (0.94),
Bin 4 (0.09 remaining): Cat (0.28), Elephant_tusk (0.63),
Bin 5 (0.04 remaining): Bat (0.42), Monkey_hand (0.21), Sheep_coat (0.33),
Bin 6 (0.88 remaining): Chicken_wing (0.12),

Run 2:
Bin 0 (0.04 remaining): C_Programming (0.21), Computer Organization (0.75),
Bin 1 (0.11 remaining): Internet_Infrastructure (0.62), The_History_Of_The_Universe (0.27),
Bin 2 (0.02 remaining): American_History_2000- (0.20), Linux_with_Operating_Systems_Concepts (0.78),
Bin 3 (0.04 remaining): English_For_Dummies (0.55), Statistics (0.41),
Bin 4 (0.10 remaining): Computer_Architecture (0.90),
Bin 5 (0.02 remaining): English-Minbari_Dictionary (0.42), Hitchhiker's_Guide (0.23), Zen_and_the_Art_of_Programming (0.33),
Bin 6 (0.14 remaining): Business_Programming:__Why? (0.12), Heart_of_Darkness (0.18), The_Joy_of_Cooking (0.56),
Bin 7 (0.02 remaining): Cincinnati_Yellow_Pages (0.98),
Bin 8 (0.68 remaining): Artificial_Intelligence (0.32),
Bin 9 (0.18 remaining): The_History_of_Ohio_State_Buckeyes (0.82),
*/
