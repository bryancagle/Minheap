/***************
Name: Bryan Cagle
Course: CSCE 3110.001
Assignment: Programming Assignment 4 - Minheaps
Due Date: April 9, 2016 11:59pm

Desciprtion: the purpose of this program is to implement
a minheap with functionality for a inserting data, deleting data,
changing data, as well as displaying the data in postorder.

Based on algorithm seen in class lecture
***************/

#include <iostream>

using namespace std;

//algorithm for adjusting the minheap when a node is added or any changes made
void adjust(int *array,int i,int n)
{
    int j, temp;
    temp = array[i];
    j = 2*i;
    while (j<=n)
    {
        if (j<n && array[j+1]<array[j])
            j = j + 1;
        if (temp<array[j])
            break;
        else if (temp>=array[j])
        {
            array[j/2]=array[j];
            j = 2*j;
        }
    }
    array[j/2] = temp;
    return;
}

//Heapify the minheap
void heapify(int *array, int n)
{
    int i;
    for(i=n/2; i>=1; i--)
    {
        adjust(array,i,n);
    }
}

//Takes the array and root and recursively calls the function using each child as a new root in the postorder manner
void Postorder(int *array, int i)
{
	
    if(array[i]!='\0')
    {
        Postorder(array,2*i);
        Postorder(array, 2*i+1);
        cout << array[i] << ", ";
    }
}

void remove(int *array, int n, int del)
{
	int index;
	
	for(int i=1;i<=n;i++){ //finds the index of the first occurence of the value to be deleted
		if(array[i]==del)
			index=i;
	}
	while(array[index+1]!='\0'){ //shifts all indexes after the deleted node over by one
				array[index] = array[index+1];
				index+=1;
			}
	array[n] = '\0';
}

//changes all occurrences to the value to be changed to
void change(int *array, int n, int from, int to)
{
		for(int i=1;i<=n;i++){
			if(array[i]==from)
				array[i]=to;
		}
}

//used by delete and change functions to see if the values are in the array to be changed
bool testExist(int *array, int n, int value)
{
	int test = -999;
	for(int i=1;i<=n;i++){
			if(array[i]==value)
			test=0;
		}
	if(test==0)
	return true;
	else
	return false;
}

int main()
{
	int array[500]={'\0'},value1,value2,counter; //initializes array, values, and a counter for deletion.
	char selection;
    int n=0, i=1; //initial values for size of minheap, and then the first available position.
	
	//shows initial menu
    cout << "\n*** Instructions ***" << endl;
	cout << "I #: Insert # into minheap" << endl;
	cout << "D #: Delete all occurrences of # from minheap" << endl;
	cout << "C #a #b: Change all occurrences of #a to #b in minheap" << endl;
	cout << "P: Print postorder traversal of minheap" << endl << endl;
	
	//forever loops the program
	while(1){
		cout << "Select a command: ";
		cin >> selection;
	
		switch(selection){
			case 'I': //insertion: simply inserts the valid value1 into the first open spot indicated by i
					if(cin >> value1){
						if(n==500){
							cout << "Maximum size of heap reached, cannot add anymore" << endl;
							break;
						}
						array[i]=value1;
						i++;
						n++;
						heapify(array, n);
						cout << "Value inserted into minheap: " << value1 << endl;
					}
					else{
					cout << "*** Error: Incompatible argument: " << value1 << "  ***" << endl;
					cin.clear();
					cin.ignore(256,'\n');
					}
				break;
			case 'D': //deletion: tests if value is in minheap, then counts how many occurences there are, and loops the deletion function that many times
					if(cin >> value1){
						if(testExist(array,n,value1)==false){
							cout << "Value not in minheap" << endl;
							break;
						}
						
						counter=0;
						for(int j=1;j<=n;j++){
							if(array[j]==value1){
								counter+=1;
							}							
						}
						
						for(int j=0;j<counter;j++){
							remove(array, n , value1);
							i--;
							n--;
							heapify(array, n);
						}
						
						cout << "All values of " << value1 << " removed from minheap" << endl;
					}
					else{
					cout << "*** Error: Incompatible argument: " << value1 << "  ***" << endl;
					cin.clear();
					cin.ignore(256,'\n');
					}
				break;
			case 'C': //change: tests if value to be changed exists, then takes both arguments into the change function
					if(cin >> value1){
						if(testExist(array,n,value1)==false){
							cout << "Value not in minheap" << endl;
							break;
						}
						if(cin >> value2){
							change(array,n,value1,value2);
							heapify(array, n);
							cout << "Values changed from: " << value1 << " to: " << value2 << endl;
						}
						else{
						cout << "*** Error: Incompatible argument: " << value1 << "  ***" << endl;
						cin.clear();
						cin.ignore(256,'\n');
					}
					}
					else{
					cout << "*** Error: Incompatible argument: " << value1 << "  ***" << endl;
					cin.clear();
					cin.ignore(256,'\n');
					}
				break;
			case 'P': //print: tests if minheap is empty, if not then it calls the post order function
					if(n==0)
						cout << "The minheap is empty" << endl;
					Postorder(array,1); //prints the post order of the tree starting at the "root" or 1
					cout << "\b\b " << endl; //removes the extra comma at the end
				break;
			default:
					cin.clear(); //clears the buffer of any extra inputs, as with all cases of clear and ignore in this code
					cin.ignore(256,'\n');
					cout << "*** Error: Invalid command ***" << endl;
				break;
		}
	}
}