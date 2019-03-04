/**

* Trevor Hansen & Zijian Liu

* CIS 22C, Lab 4

*/

#ifndef LIST_H_
#define LIST_H_

#include <iostream>
#include <cstddef> //for NULL
#include <assert.h>

using namespace std;

template <class listdata> //list stores generic listdata, not any specific C++ type
class List {

private:
    struct Node {
        listdata data;
        Node* next;
        Node* prev;

        Node(listdata newData){
            data = newData;
            next = NULL;
            prev = NULL;
        }
    };

    Node* first;
    Node* last;
    Node* iterator;
    int length;

    void reversePrint(Node* node) const;
    //Helper function for the public reversePrint() function.
    //Recursively prints the data in a List in reverse.

    bool isSorted(Node* node) const;
    //Helper function for the public isSorted() function.
    //Recursively determines whether a list is sorted in ascending order.

    int binarySearch(int low, int high, listdata data) const;
    //Recursively search the list by dividing the search space in half
    //Returns the index of the element, if it is found in the List
    //Returns -1 if the element is not in the List
    //Post: The iterator location has not been changed

public:

    /**Constructors and Destructors*/

    List();
    //Default constructor; initializes and empty list
    //Postcondition: A new list will be initialized with *first and *last set to null and length set to zero.

    List(const List &list);
    //Copy constructor; makes a copy of existing list
    //Postcondition: There will be a copy made of the list that was passed through.

    ~List();
    //Destructor. Frees memory allocated to the list
    //Postcondition: Deletes all the nodes from the list from first to last.

    /**Accessors*/

    listdata getFirst() const;
    //Returns the first data in the list
    //Precondition: List must not be empty

    listdata getLast() const;
    //Returns the last data in the list
    //Precondition: List can't be empty

    bool isEmpty() const;
    //Determines whether a list is empty.

    int getLength() const;
    //Returns the size of the list

    bool operator==(const List &list);
    //Tests two lists to determine whether their contents are equal
    //Postcondition: returns true if lists are equal and false otherwise

    bool isSorted() const;
    //Wrapper function that calls the isSorted helper function to determine whether
    //a list is sorted in ascending order.
    //We will consider that a list is trivially sorted if it is empty.
    //Therefore, no precondition is needed for this function

    int getIndex() const;
    //Indicates the index of the Node where the iterator is currently pointing
    //Nodes are numbered starting at 1 through the size of the list
    //Pre: !offEnd()

    int linearSearch(listdata data) const;
    //Searches the list, element by element, from the start of the List to the end of the List
    //Returns the index of the element, if it is found in the List
    //Does not call the indexing functions in the implementation
    //Returns -1 if the element is not in the List
    //Pre: length != 0
    //Post: The iterator location has not been changed

    int binarySearch(listdata data) const;
    //Returns the index where data is located in the List
    //Calls the private helper function binarySearch to perform the search
    //Pre: length != 0
    //Pre: List is sorted (must test on a sorted list)
    //Post: The iterator location has not been changed

    /**Manipulation Procedures*/

    void removeFirst();
    //Removes the value stored in first node in the list
    //Precondition: List can't be empty.
    //Postcondition: *first will be updated to second node while the first is deleted. If there is only one node, then the list will be empty and *first and last will be null.

    void removeLast();
    //Removes the value stored in the last node in the list
    //Precondition: List can't be empty.
    //Postcondition: *last will be updated to second last node while the last is deleted. If there is only one node, then the list will be empty and *first and last will be null.

    void insertFirst(listdata data);
    //Inserts a new data at the beginning of the list
    //If the list is empty, the new data becomes both first and last
    //Postcondition: *first will be updated to a new node and placed at beginning of list. If empty *first and *last will be pointing at the same new node.

    void insertLast(listdata data);
    //Inserts a new data at the end of the list
    //If the list is empty, the new data becomes both first and last
    //Postcondition: *last will be updated to a new node and placed at end of list. If empty *first and *last will be pointing at the same new node.

    void advanceToIndex(int index);
    //Moves the iterator to the node whose index number is specified in the parameter
    //Nodes are numbered starting at 1 through the size of the List
    //Pre: size != 0
    //Pre: index <= size

    /**Iterator Operations*/

    void startIterator();
    //Will set iterator to first.
    //Post: iterator = first;

    listdata getIterator() const;
    //Returns value for node iterator is pointing at.
    //Pre: !offEnd();

    void advanceIterator();
    //Moves iterator to next node in list
    //Pre: !offEnd();

    void reverseIterator();
    //Move iterator to previous node in list
    //Pre: !offEnd();

    bool offEnd() const;
    // Checks if iterator == NULL

    void insertIterator(listdata data);
    //Adds new data node after the node the iterator points at. If Iterator == first or last then calls insertFirst() or insertLast().
    //Pre: !offEnd();

    void removeIterator();
    //Removes data node the iterator points at. If Iterator == first or last then calls removeFirst() or removeLast().
    //Pre: !offEnd();


    /**Additional List Operations*/

    void printList() const;
    //Prints to the console the value of each data in the list sequentially
    //and separated by a blank space
    //Prints nothing if the list is empty
    //Prints a empty newline character if it's empty..

    void printNumberedList() const;
    //Prints to the console the value of each data in the list sequentially,
    //numbers them and puts a new line between each element.
    //If list empty it will print "There is nothing in the list!"

    void reversePrint() const;
    //Wrapper function that calls the reverse helper function to print a list in reverse
    //prints nothing if the List is empty
};

    template <class listdata>
	List<listdata>::List() {
	    first = NULL;
	    last = NULL;
	    iterator = NULL;
	    length = 0;
	}

	template <class listdata>
	List<listdata>::List(const List &list) {

        if(list.first == NULL) //If the original list is empty, make an empty list for this list
        {
            first = last = iterator = NULL;
        }
        else
        {
            first = new Node(list.first->data); //calling Node constructor
            Node* temp = list.first; //set a temporary node pointer to point at the first of the original list
            iterator = first; //set iterator to point to first node of the new list

            while(temp->next != NULL)
            {
                temp = temp->next; //advance up to the next node in the original list
                iterator->next = new Node(temp->data); //using node constructor to create new node w/ copy of data
                iterator->next->prev = iterator;
                iterator = iterator->next; //advance to this new node
            }
            last = iterator; //Why do I need this line of code?
            iterator = NULL;
        }
        length = list.length;
    }

    template <class listdata>
	List<listdata>::~List()
	{
	    Node* b = first;
	    Node* a = NULL; //a stands for "after" (i.e. after b)
	    while (b != NULL)
	    {
	        a = b->next; //move a to node after b
	        delete b; //remove b (you know it is not NULL from if)
	        b = a; //b "catches up" with a (both point to same place in list)
	    }
	}

    template <class listdata>
	void List<listdata>::insertFirst(listdata data)
	{
	    Node* N = new Node(data);
	    if (length == 0)
	    {
	        first = N;
	        last = N;
	    }
	    else
	    {
	        N->next = first;
	        first->prev = N;
	        first = N;
	    }
	    length++;
	}

    template <class listdata>
	void List<listdata>::removeFirst()
	{
    	assert(!isEmpty());
	    if(length == 1)
	    {
	        delete first;
	        first = last = NULL;
	        length = 0;
	    }
	    else
	    {
	        Node* temp = first;
	        first = first->next;
	        first->prev = NULL;
	        delete temp;
	        length--;
	    }
	}

    template <class listdata>
	void List<listdata>::insertLast(listdata data)
	{
		Node* N = new Node(data);
	    if (length == 0)
	    {
	        first = N;
	        last = N;
	    }
	    else
	    {
	    	last->next = N;
	    	N->prev = last;
	    	last = N;
	    }
	    length++;

	}


    template <class listdata>
	void List<listdata>::removeLast()
	{
    	assert(!isEmpty());
    	if (length == 1) {
	        delete first;
	        first = last = NULL;
	        length = 0;
	    } else {
	        Node* temp = last->prev;;
	        delete last;
	        last = temp; //set last to be the former second to last node stored in temp
	        last->next = NULL; //set pointer to point at NULL rather than deallocated memory
	        length--;
	    }
	}

    template <class listdata>
	bool List<listdata>::isEmpty() const
	{
	    return length == 0;
	}

    template <class listdata>
	listdata List<listdata>::getFirst() const
	{
    	assert(!isEmpty());
        return first->data;
	}

    template <class listdata>
	listdata List<listdata>::getLast() const
	{
    	assert(!isEmpty());
		return last->data;
	}

    template <class listdata>
	int List<listdata>::getLength() const
	{
		return length;
	}

    template <class listdata>
	void List<listdata>::startIterator()
    {
        iterator = first;
    }

    template <class listdata>
    listdata List<listdata>::getIterator() const
    {
    	assert(!offEnd());
        return iterator->data;
    }

    template <class listdata>
    void List<listdata>::advanceIterator()
    {
    	assert(!offEnd());
        iterator = iterator->next;
    }

    template <class listdata>
    void List<listdata>::reverseIterator()
    {
        assert(!offEnd());
        iterator = iterator->prev;
    }

    template <class listdata>
    bool List<listdata>::offEnd() const
    {
        return iterator == NULL;
    }

    template <class listdata>
    void List<listdata>::insertIterator(listdata data)
    {
    	assert(!offEnd());
    	if(iterator == last)
        {
            insertLast(data);
        } else
        {
            Node* N = new Node(data);
            N->next = iterator->next;
            N->prev = iterator;
            iterator->next = N;
            N->next->prev = N;
            length++;
        }
    }

    template <class listdata>
    void List<listdata>::removeIterator()
    {
        assert(!offEnd());
        if(iterator == last)
        {
            removeLast();
            iterator = NULL;
        } else if(iterator == first)
        {
            removeFirst();
            iterator = NULL;
        } else
        {
            iterator->prev->next = iterator->next;
            iterator->next->prev = iterator->prev;
            delete iterator;
            iterator = NULL;
            length--;
        }
    }

    template <class listdata>
    int List<listdata>::getIndex() const{
    	assert(!offEnd());
    	Node* temp = first;
    	int index = 1;
    	while(temp != iterator){
    		index++;
    		temp = temp->next;
    	}
    	return index;
    }

    template <class listdata>
    void List<listdata>::advanceToIndex(int index){
    	assert(length != 0);
    	assert(index <= length);
    	assert(index > 0);
    	startIterator();
    	for(int i = 1; i < index; i++){
    		iterator = iterator->next;
    	}
    }

    template <class listdata>
    bool List<listdata>::operator==(const List &list)
    {
        if(length != list.length)
        return false;
        Node* temp1 = first;
        Node* temp2 = list.first;
        while(temp1 != NULL)
        {
            if(temp1->data != temp2->data)
                return false;
            temp1 = temp1->next;
            temp2 = temp2->next;
        }
        return true;
    }

    template <class listdata>
    bool List<listdata>::isSorted(Node* node) const{
    	if (isEmpty() || node->next == NULL){ //if list is empty or on last pointer return true
    		return true;
    	}
    	if(node->data <= node->next->data){
    		return isSorted(node->next); // if two elements are in order call function again to test next
    	}else{
    		return false;
    	}
    }

    template <class listdata>
    bool List<listdata>::isSorted() const{
    	return isSorted(first);
    }

    template <class listdata>
    void List<listdata>::printNumberedList() const
    {
        Node* temp = first;
        int i = 1;
        while(temp != NULL)
            {
                cout << i << ".\t" << temp->data << endl;
                temp = temp->next;
                i++;
            }
        cout << endl;
    }

    template <class listdata>
    int List<listdata>::linearSearch(listdata data) const {
    	assert(length != 0);
    	Node* temp = first;
    	int index = 1;
    	while(temp != NULL){
    		if(temp->data == data)
    			return index;
    		else{
    			index++;
    			temp = temp->next;
    		}
    	}
    	return -1;
    }

    template <class listdata>
    int List<listdata>::binarySearch(listdata data) const{
    	assert(length != 0);
    	assert(isSorted());
    	return binarySearch(1, length, data);
    }

    template <class listdata>
    int List<listdata>::binarySearch(int low, int high, listdata data) const{
    	int mid;
    	Node* temp = first;
    	if(high < low)
    		return -1;
    	mid = low + (high-low)/2;
    	for(int i = 1; i < mid; i++){
    		temp = temp->next;
    	}
    	if(temp->data == data)
    		return mid;
    	else if(temp->data < data)
    		return binarySearch(mid+1, high, data);

    	else
    		return binarySearch(low, mid-1, data);
    }

    template <class listdata>
	void List<listdata>::printList() const
	{
	    Node* temp = first; //create a temporary iterator
	    while (temp != NULL) {
	    	cout << temp->data << " ";
	    	temp = temp->next;
	    }
	    cout << endl; //Prints empty line after list is printed.

	}

    template <class listdata>
	void List<listdata>::reversePrint(Node* node) const{
    	if(node == NULL){
    		return;
    	}else{
    		cout << node->data <<" ";
    		reversePrint(node->prev);
    	}
    }

    template <class listdata>
    void List<listdata>::reversePrint() const{

    	reversePrint(last);
    	cout << endl;
    }
    #endif /* LIST_H_ */
