#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h> 


//struct for node
typedef struct node{
	int value;
	int numofsucc;
	struct node **succ;
}node;

//struct for network
typedef struct network{
	int numofnodes;
	struct node **nodes;
}network;


//create a node
node *newNode() {
  node *p = (node *)malloc(sizeof(node));
  p -> numofsucc = 0;
  p -> succ = malloc(p -> numofsucc * sizeof(int));
  return p;
}

// create a network
network *newnetwork (int numofnodes){
	network *n = malloc(sizeof(network));
	n -> numofnodes = numofnodes;
	n -> nodes = malloc(sizeof(node) * numofnodes);
	for (int i = 0; i < numofnodes ; i ++){
		n -> nodes[i] = newNode();
	}
	return n;
}

//make link between nodes
void linknodes(network *n, int from, int to){
	node *p = n -> nodes[from];
	p -> succ = realloc(p -> succ, sizeof(node));
	p -> numofsucc += 1;
	p -> succ[p -> numofsucc -1] = n -> nodes[to];
}

//number of nodes
int numnodes(char args[]){
	int num = 1;
	for (int i = 1; i < strlen (args); i++){
		if ((args[i] != '-') && (args[i] != ',')){
			int j = 0;
			for (j = 0; j < i; j++){
				if ((args[j] != '-') && (args[j] != ',')  && (args[i] == args[j])) break;	
			}
			if (i == j) num ++;
		}
	}
	return num;	
}

//calculate the largestnode
int largest(char args[]){
	int strlength = strlen(args);
	int max = args[0] - 48;
	for (int i = 0; i < strlength; i++){
		if ((args[i] != '-') && (args[i] != ',')){
			int number = args[i] - 48;
			if (number > max) max = number;
		}
	}
	return max;
}

//calculate the total value from all nodes
int total(char args[]){
	int sum = args[0] - 48;
	for (int i = 1; i < strlen (args); i++){
		if ((args[i] != '-') && (args[i] != ',')){
			int j = 0;
			for (j = 0; j < i; j++){
				if ((args[j] != '-') && (args[j] != ',')  && (args[i] == args[j])) break;	
			}
			if (i == j) sum += args[i] - 48;
		}
	}
	return sum;	
}

//calculates the mean value of all nodes
double mean(int total, int numnodes){
	double av = (double)total/(double)numnodes;
	return av;
}

//print out the network
void printnetwork(char args[]){
	int desti, index = 0;
	while (index < strlen(args)){
		int data = args[index] - 48;
		printf("%d ", data);
		while (args[index+1] == '-'){
			desti = args[index + 2] - 48;
			printf("-> %d", desti);
			index += 2;

		}if (args[index + 1] == ',' || args[index+1] == '\0'){
			printf("\n");
			index += 2;
		}
	}
}

//print out the nodes
void printnodes(char args[]){
	printf("%d ", args[0]-48);
	for (int i = 1; i < strlen(args); i++){
		if ((args[i] != '-') && (args[i] != ',')){
			int j = 0;
			for (j = 0; j < i; j++){
				if ((args[j] != '-') && (args[j] != ',')  && (args[i] == args[j])) break;
		}
			if (i == j) printf("%d ", args[j]-48);
		
		}
	}
	printf("\n");
}

//free network
void freeing(network *n){
	if (n){
		for (int i = 0; i < n -> numofnodes; i++){
			node *m = n -> nodes[i];
			free(m -> succ);
			free (m);
		}
		free(n -> nodes);
	}
	free (n);
}

/*------------------------------------TESTS-------------------------------------------------------*/

//assert function
void assert(int line, bool b) {
  if (b) return;
  printf("The test on line %d fails.\n", line);
  exit(1);
}

void *build() {
	int num = 10;
	network *p = newnetwork(num);
	assert(__LINE__, p->numofnodes == num);
	freeing(p);
	return 0;
}


//test largest function
void testlargest(){
	assert(__LINE__, largest("1-2,3-4") == 4);
	assert(__LINE__, largest("1-2,3-4,5,9") == 9);
	assert(__LINE__, largest("1-2,7-6,3-4") == 7);
	assert(__LINE__, largest("1,2,3,4") == 4);
	assert(__LINE__, largest("1-2,3-4-5,4") == 5);
}

//test total function
void testtotal(){
	assert(__LINE__, total("1-2,3-4") == 10);
	assert(__LINE__, total("1-2,3-4,4-5") == 15);
	assert(__LINE__, total("1,2,3-4") == 10);
	assert(__LINE__, total("1-2,3-4-7") == 17);
	assert(__LINE__, total("1-2,3-4") == 10);
}

//test mean function
void testmean(){
	assert(__LINE__, mean(20,4) == 5.00);
	assert(__LINE__, mean(20,5) == 4.00);
	assert(__LINE__, mean(18, 4) == 4.50);
}

//test numnodes function
void testnumnodes(){
	assert(__LINE__, numnodes("1-2,3-4-8") == 5);
	assert(__LINE__, numnodes("1-2,3-4-4") == 4);
	assert(__LINE__, numnodes("1-2,6-8,9") == 5);
	assert(__LINE__, numnodes("1-2,3-3-3") == 3);


}

void test(){
	build();
	testlargest();
	testtotal();
	testmean();
	testnumnodes();
	printf("All tests passed!\n");
}



/*-------------------------------------User interface -----------------------------------------*/
int main(int n, char *args[n]) {
	if (n == 1) test();
	else if (n != 2 ){
		printf("Please input in this format:./network 1-2,1-3,2-4.\n");
		return 1;
	}
	else{
		// for (int i = 0; i < strlen(args[1]); i++){
		// 		if ((args[1][i] < 48 ) && (args[1][i] > 57) && (args[1][i] != 44) && (args[1][i] != 45)){
		// 			printf("Please input in this format:./network 1-2,1-3,2-4.\n");
		// 			return 1;
		// 		}
		// 	}
		int nodenum = numnodes(args[1]);
		network *m = newnetwork(nodenum);
		for (int i = 0; i < strlen(args[1] -1); i++){
			if (args[1][i] == '-'){
				int from = atoi(&args[1][i - 1]);
				int to = atoi(&args[1][i + 1]);
				linknodes(m, from, to);

			}
		}
		printf("This is the network you entered (where the preceeding values are linked to the first):\n");
		printnetwork(args[1]);
		printf("These are the nodes you entered: ");
		printnodes(args[1]);
		printf("Number of nodes: %d\n", nodenum);
		printf("The largest node is %d\n", largest(args[1]));
		int sum = total(args[1]);
		printf("The sum of all the nodes is %d\n", sum);
		printf("The mean of all the nodes is %.2f(to 2 d.p.)\n", mean(sum, nodenum));
		freeing(m);
		
	}
	return 0; 
} 

