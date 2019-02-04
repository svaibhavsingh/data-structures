#include <stdio.h>
#include <string.h>
#include <stdlib.h>

//defining doubly linked list
struct list 
{
	struct list *prev;
	char data;
	struct list *next;
};

// defining transition table
struct transition
{
	char presentcharacter, nextcharacter, direction;
	int presentstate, nextstate;
};

//function to print tape content
void print_tape(struct list *, struct list *, int);

//function for adding elements in doubly linked list
void append(struct list **,char);

int main ()
{
	struct list *current, *head, *tape_header;//pointer to linked lists and other for printing it.
	head = NULL;
	char *input_sequence;
	int num_of_states, num_of_final_states, input_sequence_length = 0;
	int i,j;//temporary integers for looping
	int *states, *final_states, present_state = 0;//ps holds present state no.
	int count=0; //showing no. of transition table entries
	struct transition transition_table[100];

	// Reading stdin from file
	freopen("i.txt", "r", stdin);
	
	// Reading number of states
	scanf(" %d", &num_of_states);

	states=(int *) calloc(num_of_states, sizeof(int));
	printf("states are :\n");
	for(i = 0; i < num_of_states; i++) {
		states[i] = i;
		printf("q%d\n", states[i]);
	}
		
	// Reading number of final states
	scanf(" %d", &num_of_final_states);

	//printf("enter the state no. of the final state\n");
	final_states=(int *) calloc(num_of_final_states, sizeof(int));

	// Reading state number of final states
	for(i = 0; i < num_of_final_states; i++)
		scanf(" %d", &final_states[i]);

	//transition table entry and storing to structures
	char transition_end_symbol = ';';
	while(1)
	{
		// This is just for reading commas and newline character and ignoring it
		char unused_variables;
		if(transition_end_symbol == '.')
			break;
		scanf(" %c",&unused_variables);
		scanf(" %d",&transition_table[count].presentstate);
		scanf(" %c",&unused_variables);
		scanf(" %c",&transition_table[count].presentcharacter);
		scanf(" %c",&unused_variables);
		scanf(" %c",&unused_variables);
		scanf(" %d",&transition_table[count].nextstate);
		scanf(" %c",&unused_variables);
		scanf(" %c",&transition_table[count].nextcharacter);
		scanf(" %c",&unused_variables);
		scanf(" %c",&transition_table[count].direction);
		count++;
		scanf(" %c",&transition_end_symbol);
	}

	//getting input sequence
	input_sequence=(char *) calloc(1000,sizeof(char));
	scanf(" %s",input_sequence);

	// Traversing input sequence and adding to dll
	for(i=0; input_sequence[i]!='\0'; i++) {
		if(i == 0) {
			append(&head, input_sequence[0]);
			current = head;
			tape_header=head;
		} else {
			append(&head,input_sequence[i]);
			current=current->next;
		}
		input_sequence_length++;
	}

	print_tape(head, tape_header, present_state);
	//Making transition table work
	for(i=0; i<num_of_final_states; i++)
	{
		while(present_state != final_states[i])	
		{ 
			for(j = 0; j < count; j++)
			{
				if((transition_table[j].presentstate == present_state)
				&& (transition_table[j].presentcharacter == tape_header->data))
				{
					print_tape(head, tape_header, present_state);

					//doing the updation after according to transition table
					present_state=transition_table[j].nextstate;
					tape_header->data = transition_table[j].nextcharacter; 
					if(transition_table[j].direction == 'l'|| transition_table[j].direction == 'L')
					{
						if(tape_header->prev != NULL)
						{
							tape_header = tape_header->prev;
						}
						else
						{
							printf("\nincorrect entry. Left from start. Exiting\n");
							exit(0);
						}
					}
					else if(transition_table[j].direction == 'r' || transition_table[j].direction == 'R')
					{
						if(tape_header->next != NULL)
						{
							tape_header = tape_header->next;
						}
						// Since tape is infinite if we reach end and asked to moved right we add a blank
						else 
						{
							append(&head, 'b');
						}
					}
					// This is done to make sure that if a entry matched it doesn't go to below if condition
					j=0;
					printf("\n");
					i=0;
					break;
				}
			}
			// Completed the above loop and reached a stage with no matching transition in transition table
			if(j == count)
			{
				printf("\nReject and halting case.");
				exit(0);
			}
		}
	}
	print_tape(head, tape_header, present_state);
	printf("\nstring accepted\n");
	return 0;
}

void print_tape(struct list *current, struct list *tape_header, int present_state) {
	//printing before tape_header
	while(current != tape_header)
	{
		printf("%c",current->data);
		current = current->next;
	}

	//printing present state
	printf("*q%d*%c",present_state,tape_header->data); 
	
	//printing beyond tape_header
	while(current->next != NULL)
	{
		printf("%c",(current->next)->data);
		current = current->next;
	}
}
void append(struct list **head, char c)
{
	struct list *new_node, *current=*head;
	if(*head == NULL)
	{
		*head =( struct list *) malloc(sizeof(struct list));
		(*head)->next=NULL;
		(*head)->data=c;
		(*head)->prev=NULL;
	}
	else
	{
		while(current->next != NULL)
			current = current->next;
		new_node = (struct list *) malloc(sizeof(struct list));
		new_node->prev = current;
		new_node->data = c;
		new_node->next=NULL;
		current->next = new_node;
	}
}
