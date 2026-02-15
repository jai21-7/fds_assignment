/*
================================================================================
CSC 1201 - Fundamental of Data Structures
Assignment-I Solutions (C Language)
B.Tech (First Year), Semester II
================================================================================
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// ============================================================================
// QUESTION 1: List Operations Using Arrays
// ============================================================================

void question1_demo() {
    printf("\n=== QUESTION 1: List Operations Using Arrays ===\n");
    
    int arr[100], n = 0;
    
    // Insert at end
    arr[n++] = 10;
    arr[n++] = 20;
    arr[n++] = 30;
    
    printf("After insertions: ");
    for(int i = 0; i < n; i++) printf("%d ", arr[i]);
    
    // Insert at position
    int pos = 1, value = 15;
    for(int i = n; i > pos; i--) arr[i] = arr[i-1];
    arr[pos] = value;
    n++;
    
    printf("\nAfter insert 15 at position 1: ");
    for(int i = 0; i < n; i++) printf("%d ", arr[i]);
    
    // Delete from position
    pos = 2;
    for(int i = pos; i < n-1; i++) arr[i] = arr[i+1];
    n--;
    
    printf("\nAfter delete at position 2: ");
    for(int i = 0; i < n; i++) printf("%d ", arr[i]);
    printf("\n");
}

// ============================================================================
// QUESTION 2: Largest and Smallest Number in Array
// ============================================================================

void question2_demo() {
    printf("\n=== QUESTION 2: Largest and Smallest Number ===\n");
    
    int arr[] = {45, 12, 78, 23, 89, 5, 67};
    int n = sizeof(arr)/sizeof(arr[0]);
    
    int largest = arr[0], smallest = arr[0];
    
    for(int i = 1; i < n; i++) {
        if(arr[i] > largest) largest = arr[i];
        if(arr[i] < smallest) smallest = arr[i];
    }
    
    printf("Array: ");
    for(int i = 0; i < n; i++) printf("%d ", arr[i]);
    printf("\nLargest: %d\n", largest);
    printf("Smallest: %d\n", smallest);
}

// ============================================================================
// QUESTION 3: Structure Members Sent to Function
// ============================================================================

struct Employee {
    char name[50];
    int id;
    float salary;
};

void displayEmployee(struct Employee emp) {
    printf("Name: %s\n", emp.name);
    printf("ID: %d\n", emp.id);
    printf("Salary: %.2f\n", emp.salary);
}

void question3_demo() {
    printf("\n=== QUESTION 3: Structure Members to Function ===\n");
    
    struct Employee emp1;
    strcpy(emp1.name, "John Doe");
    emp1.id = 101;
    emp1.salary = 50000.50;
    
    displayEmployee(emp1);
}

// ============================================================================
// QUESTION 4: Binary Search and Sum (Recursive)
// ============================================================================

int BinSearch(int *arr, int *n, int key, int low, int high) {
    if(low > high) return -1;
    
    int mid = (low + high) / 2;
    
    if(arr[mid] == key) return mid;
    else if(arr[mid] > key) return BinSearch(arr, n, key, low, mid-1);
    else return BinSearch(arr, n, key, mid+1, high);
}

int AddArray(int *arr, int n) {
    if(n <= 0) return 0;
    return arr[n-1] + AddArray(arr, n-1);
}

void question4_demo() {
    printf("\n=== QUESTION 4: Binary Search and Sum (Recursive) ===\n");
    
    int n = 7;
    int *arr = (int*)malloc(n * sizeof(int));
    
    // Sorted array for binary search
    int values[] = {10, 20, 30, 40, 50, 60, 70};
    for(int i = 0; i < n; i++) arr[i] = values[i];
    
    printf("Array: ");
    for(int i = 0; i < n; i++) printf("%d ", arr[i]);
    printf("\n");
    
    int key = 40;
    int result = BinSearch(arr, &n, key, 0, n-1);
    
    if(result != -1)
        printf("Element %d found at index %d\n", key, result);
    else
        printf("Element %d not found\n", key);
    
    int sum = AddArray(arr, n);
    printf("Sum of all elements: %d\n", sum);
    
    free(arr);
}

// ============================================================================
// QUESTION 5: Student Structure with Age Calculation
// ============================================================================

struct Date {
    int day;
    int month;
    int year;
};

struct Student {
    char name[50];
    float cgpa;
    struct Date *birthdate;
    struct Date *admission_date;
    char address[100];
};

void Age(struct Student *s) {
    int age_years = s->admission_date->year - s->birthdate->year;
    int age_months = s->admission_date->month - s->birthdate->month;
    
    if(age_months < 0) {
        age_years--;
        age_months += 12;
    }
    
    if(s->admission_date->day < s->birthdate->day) {
        age_months--;
    }
    
    printf("Age at admission: %d years %d months\n", age_years, age_months);
}

void question5_demo() {
    printf("\n=== QUESTION 5: Student Structure with Age ===\n");
    
    int n = 2;
    struct Student students[n];
    
    // Student 1
    strcpy(students[0].name, "Alice Smith");
    students[0].cgpa = 8.5;
    students[0].birthdate = (struct Date*)malloc(sizeof(struct Date));
    students[0].birthdate->day = 15;
    students[0].birthdate->month = 5;
    students[0].birthdate->year = 2005;
    students[0].admission_date = (struct Date*)malloc(sizeof(struct Date));
    students[0].admission_date->day = 1;
    students[0].admission_date->month = 8;
    students[0].admission_date->year = 2023;
    strcpy(students[0].address, "123 Main St");
    
    // Student 2
    strcpy(students[1].name, "Bob Johnson");
    students[1].cgpa = 9.0;
    students[1].birthdate = (struct Date*)malloc(sizeof(struct Date));
    students[1].birthdate->day = 20;
    students[1].birthdate->month = 10;
    students[1].birthdate->year = 2004;
    students[1].admission_date = (struct Date*)malloc(sizeof(struct Date));
    students[1].admission_date->day = 1;
    students[1].admission_date->month = 8;
    students[1].admission_date->year = 2023;
    strcpy(students[1].address, "456 Oak Ave");
    
    // Display and calculate age
    for(int i = 0; i < n; i++) {
        printf("\nStudent %d:\n", i+1);
        printf("Name: %s\n", students[i].name);
        printf("CGPA: %.2f\n", students[i].cgpa);
        printf("Birthdate: %02d/%02d/%d\n", students[i].birthdate->day, 
               students[i].birthdate->month, students[i].birthdate->year);
        printf("Admission: %02d/%02d/%d\n", students[i].admission_date->day,
               students[i].admission_date->month, students[i].admission_date->year);
        printf("Address: %s\n", students[i].address);
        Age(&students[i]);
        
        free(students[i].birthdate);
        free(students[i].admission_date);
    }
}

// ============================================================================
// QUESTION 6: Counting Sort for Election
// ============================================================================

void countingSort(int arr[], int n, int max_candidate) {
    int count[max_candidate];
    for(int i = 0; i < max_candidate; i++) count[i] = 0;
    
    // Count votes
    for(int i = 0; i < n; i++) {
        count[arr[i]-1]++;
    }
    
    printf("\nVote Count:\n");
    for(int i = 0; i < max_candidate; i++) {
        printf("Candidate %d: %d votes\n", i+1, count[i]);
    }
    
    // Reconstruct sorted array
    int idx = 0;
    for(int i = 0; i < max_candidate; i++) {
        for(int j = 0; j < count[i]; j++) {
            arr[idx++] = i+1;
        }
    }
}

void question6_demo() {
    printf("\n=== QUESTION 6: Counting Sort for Election ===\n");
    
    int votes[] = {1, 3, 2, 1, 4, 5, 2, 1, 3, 1, 2, 4, 1, 5, 3};
    int n = sizeof(votes)/sizeof(votes[0]);
    
    printf("Original votes: ");
    for(int i = 0; i < n; i++) printf("%d ", votes[i]);
    
    countingSort(votes, n, 5);
    
    printf("\nSorted votes: ");
    for(int i = 0; i < n; i++) printf("%d ", votes[i]);
    printf("\n");
}

// ============================================================================
// QUESTION 7: Radix Sort for User IDs
// ============================================================================

int getMax(int arr[], int n) {
    int max = arr[0];
    for(int i = 1; i < n; i++)
        if(arr[i] > max) max = arr[i];
    return max;
}

void countSort(int arr[], int n, int exp) {
    int output[n];
    int count[10] = {0};
    
    for(int i = 0; i < n; i++)
        count[(arr[i]/exp)%10]++;
    
    for(int i = 1; i < 10; i++)
        count[i] += count[i-1];
    
    for(int i = n-1; i >= 0; i--) {
        output[count[(arr[i]/exp)%10]-1] = arr[i];
        count[(arr[i]/exp)%10]--;
    }
    
    for(int i = 0; i < n; i++)
        arr[i] = output[i];
}

void radixSort(int arr[], int n) {
    int max = getMax(arr, n);
    
    for(int exp = 1; max/exp > 0; exp *= 10) {
        countSort(arr, n, exp);
        
        printf("After sorting by digit (exp=%d): ", exp);
        for(int i = 0; i < n; i++) printf("%03d ", arr[i]);
        printf("\n");
    }
}

void question7_demo() {
    printf("\n=== QUESTION 7: Radix Sort for User IDs ===\n");
    
    int userIDs[] = {170, 45, 75, 90, 802, 24, 2, 66};
    int n = sizeof(userIDs)/sizeof(userIDs[0]);
    
    printf("Original User IDs: ");
    for(int i = 0; i < n; i++) printf("%03d ", userIDs[i]);
    printf("\n\n");
    
    radixSort(userIDs, n);
    
    printf("\nFinal Sorted User IDs: ");
    for(int i = 0; i < n; i++) printf("%03d ", userIDs[i]);
    printf("\n");
}

// ============================================================================
// QUESTION 8: Array Insertion with Minimum Shifts
// ============================================================================

void insertWithMinShifts(int arr[], int *n, int pos, int element) {
    int size = *n;
    
    if(pos >= size) {
        arr[size] = element;
        (*n)++;
        printf("Inserted at end. No shifts needed.\n");
        return;
    }
    
    // Calculate shifts needed for left and right
    int left_shifts = pos;
    int right_shifts = size - pos;
    
    if(left_shifts < right_shifts) {
        // Shift left
        printf("Shifting left from position %d\n", pos);
        for(int i = 0; i < pos; i++) {
            arr[i-1] = arr[i];
        }
        arr[pos-1] = element;
    } else {
        // Shift right
        printf("Shifting right from position %d\n", pos);
        for(int i = size; i > pos; i--) {
            arr[i] = arr[i-1];
        }
        arr[pos] = element;
    }
    (*n)++;
}

void question8_demo() {
    printf("\n=== QUESTION 8: Insertion with Minimum Shifts ===\n");
    
    int arr[20] = {10, 20, 30, 40, 50, 60, 70};
    int n = 7;
    
    printf("Original array: ");
    for(int i = 0; i < n; i++) printf("%d ", arr[i]);
    printf("\n");
    
    insertWithMinShifts(arr, &n, 3, 35);
    
    printf("After insertion: ");
    for(int i = 0; i < n; i++) printf("%d ", arr[i]);
    printf("\n");
}

// ============================================================================
// QUESTION 9: Binary Search with Time Complexity Analysis
// ============================================================================

int binarySearch(int arr[], int n, int key) {
    int low = 0, high = n - 1;
    int iterations = 0;
    
    while(low <= high) {
        iterations++;
        int mid = (low + high) / 2;
        
        printf("Iteration %d: low=%d, mid=%d, high=%d, arr[mid]=%d\n", 
               iterations, low, mid, high, arr[mid]);
        
        if(arr[mid] == key) {
            printf("Found at index %d after %d iterations\n", mid, iterations);
            return mid;
        }
        else if(arr[mid] < key) low = mid + 1;
        else high = mid - 1;
    }
    
    printf("Not found after %d iterations\n", iterations);
    return -1;
}

void question9_demo() {
    printf("\n=== QUESTION 9: Binary Search Analysis ===\n");
    
    int arr[] = {5, 10, 12, 24, 34, 67};
    int n = sizeof(arr)/sizeof(arr[0]);
    int key = 24;
    
    printf("Array: ");
    for(int i = 0; i < n; i++) printf("%d ", arr[i]);
    printf("\nSearching for: %d\n\n", key);
    
    int result = binarySearch(arr, n, key);
    
    printf("\nWorst-case Time Complexity: O(log n)\n");
    printf("For n=%d elements, max iterations = %d\n", n, (int)(log(n)/log(2))+1);
}

// ============================================================================
// QUESTION 10: Singly Linked List Operations
// ============================================================================

struct Node {
    int data;
    struct Node* next;
};

struct Node* createNode(int data) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->data = data;
    newNode->next = NULL;
    return newNode;
}

void insertAtEnd(struct Node** head, int data) {
    struct Node* newNode = createNode(data);
    
    if(*head == NULL) {
        *head = newNode;
        return;
    }
    
    struct Node* temp = *head;
    while(temp->next != NULL) {
        temp = temp->next;
    }
    temp->next = newNode;
}

void insertAtBeginning(struct Node** head, int data) {
    struct Node* newNode = createNode(data);
    newNode->next = *head;
    *head = newNode;
}

void deleteNode(struct Node** head, int key) {
    struct Node* temp = *head;
    struct Node* prev = NULL;
    
    if(temp != NULL && temp->data == key) {
        *head = temp->next;
        free(temp);
        return;
    }
    
    while(temp != NULL && temp->data != key) {
        prev = temp;
        temp = temp->next;
    }
    
    if(temp == NULL) return;
    
    prev->next = temp->next;
    free(temp);
}

void displayList(struct Node* head) {
    struct Node* temp = head;
    while(temp != NULL) {
        printf("%d -> ", temp->data);
        temp = temp->next;
    }
    printf("NULL\n");
}

void question10_demo() {
    printf("\n=== QUESTION 10: Singly Linked List ===\n");
    
    struct Node* head = NULL;
    
    insertAtEnd(&head, 10);
    insertAtEnd(&head, 20);
    insertAtEnd(&head, 30);
    printf("After insertions at end: ");
    displayList(head);
    
    insertAtBeginning(&head, 5);
    printf("After insert at beginning: ");
    displayList(head);
    
    deleteNode(&head, 20);
    printf("After deleting 20: ");
    displayList(head);
}

// ============================================================================
// QUESTION 11: 2D Array Address Calculation (Row-Major)
// ============================================================================

void question11_demo() {
    printf("\n=== QUESTION 11: 2D Array Address Calculation ===\n");
    
    // Matrix M[-16 to 10][-15 to 10]
    int row_lower = -16, row_upper = 10;
    int col_lower = -15, col_upper = 10;
    int base_address = 2789;
    int element_size = 2;
    
    int target_row = 4, target_col = 2;
    
    int num_cols = col_upper - col_lower + 1;
    
    // Address = Base + [(i - row_lower) * num_cols + (j - col_lower)] * size
    int address = base_address + 
                  ((target_row - row_lower) * num_cols + 
                   (target_col - col_lower)) * element_size;
    
    printf("Matrix bounds: [%d to %d][%d to %d]\n", 
           row_lower, row_upper, col_lower, col_upper);
    printf("Base address: %d\n", base_address);
    printf("Element size: %d bytes\n", element_size);
    printf("Number of columns: %d\n", num_cols);
    printf("\nAddress of M[%d][%d] = %d + [(%d - (%d)) * %d + (%d - (%d))] * %d\n",
           target_row, target_col, base_address, 
           target_row, row_lower, num_cols, target_col, col_lower, element_size);
    printf("                       = %d + [%d * %d + %d] * %d\n",
           base_address, target_row - row_lower, num_cols, 
           target_col - col_lower, element_size);
    printf("                       = %d\n", address);
}

// ============================================================================
// QUESTION 12: Find Consecutive Pairs with Given Sum
// ============================================================================

void FIND_PAIR(struct Node* head, int sum) {
    if(head == NULL || head->next == NULL) {
        printf("Not enough elements in list\n");
        return;
    }
    
    struct Node* curr = head;
    int found = 0;
    
    printf("Pairs with sum = %d: ", sum);
    
    while(curr != NULL && curr->next != NULL) {
        if(curr->data + curr->next->data == sum) {
            printf("(%d, %d) ", curr->data, curr->next->data);
            found = 1;
        }
        curr = curr->next;
    }
    
    if(!found) printf("None");
    printf("\n");
}

void question12_demo() {
    printf("\n=== QUESTION 12: Find Consecutive Pairs ===\n");
    
    struct Node* head = NULL;
    int values[] = {1, 5, 4, 2, 6, 8, 1};
    int n = sizeof(values)/sizeof(values[0]);
    
    for(int i = 0; i < n; i++) {
        insertAtEnd(&head, values[i]);
    }
    
    printf("Linked List: ");
    displayList(head);
    
    FIND_PAIR(head, 9);
}

// ============================================================================
// QUESTION 13: Swap Node with Last Node
// ============================================================================

void swapWithLast(struct Node** head, int data) {
    if(*head == NULL || (*head)->next == NULL) return;
    
    struct Node *target = NULL, *target_prev = NULL;
    struct Node *last = *head, *last_prev = NULL;
    
    // Find target node and last node
    struct Node *temp = *head;
    
    while(temp != NULL) {
        if(temp->data == data) {
            target = temp;
        }
        if(temp->next != NULL) {
            if(temp->next->data == data) target_prev = temp;
            last_prev = temp;
            last = temp->next;
        }
        temp = temp->next;
    }
    
    if(target == NULL) {
        printf("Node not found\n");
        return;
    }
    
    if(target == last) {
        printf("Target is already last node\n");
        return;
    }
    
    // Case 1: Target is head
    if(target == *head) {
        *head = last;
        last_prev->next = target;
        struct Node* temp_next = target->next;
        target->next = last->next;
        last->next = temp_next;
    }
    // Case 2: Target and last are adjacent
    else if(target->next == last) {
        target_prev->next = last;
        target->next = last->next;
        last->next = target;
    }
    // Case 3: General case
    else {
        target_prev->next = last;
        last_prev->next = target;
        struct Node* temp = target->next;
        target->next = last->next;
        last->next = temp;
    }
}

void question13_demo() {
    printf("\n=== QUESTION 13: Swap with Last Node ===\n");
    
    struct Node* head = NULL;
    int values[] = {10, 20, 25, 30, 40, 50, 60};
    int n = sizeof(values)/sizeof(values[0]);
    
    for(int i = 0; i < n; i++) {
        insertAtEnd(&head, values[i]);
    }
    
    printf("Original list: ");
    displayList(head);
    
    swapWithLast(&head, 25);
    
    printf("After swapping 25 with last: ");
    displayList(head);
}

// ============================================================================
// QUESTION 14: Music Player Navigation
// ============================================================================

struct DNode {
    int bookID;
    struct DNode* prev;
    struct DNode* next;
};

struct DNode* createDNode(int id) {
    struct DNode* newNode = (struct DNode*)malloc(sizeof(struct DNode));
    newNode->bookID = id;
    newNode->prev = NULL;
    newNode->next = NULL;
    return newNode;
}

void insertSorted(struct DNode** head, int id) {
    struct DNode* newNode = createDNode(id);
    
    if(*head == NULL || (*head)->bookID >= id) {
        newNode->next = *head;
        if(*head != NULL) (*head)->prev = newNode;
        *head = newNode;
        return;
    }
    
    struct DNode* curr = *head;
    while(curr->next != NULL && curr->next->bookID < id) {
        curr = curr->next;
    }
    
    newNode->next = curr->next;
    if(curr->next != NULL) curr->next->prev = newNode;
    curr->next = newNode;
    newNode->prev = curr;
}

void displayReverse(struct DNode* head) {
    if(head == NULL) return;
    
    struct DNode* temp = head;
    while(temp->next != NULL) temp = temp->next;
    
    while(temp != NULL) {
        printf("%d ", temp->bookID);
        temp = temp->prev;
    }
    printf("\n");
}

void question14_demo() {
    printf("\n=== QUESTION 14: Music Player (Doubly Linked List) ===\n");
    printf("\nAnswer: Use DOUBLY LINKED LIST\n");
    printf("Reasons:\n");
    printf("1. Forward navigation: Using next pointer\n");
    printf("2. Backward navigation: Using prev pointer\n");
    printf("3. O(1) time for both directions\n");
    printf("4. Singly linked list only allows forward traversal\n");
    
    struct DNode* library = NULL;
    
    insertSorted(&library, 105);
    insertSorted(&library, 102);
    insertSorted(&library, 108);
    insertSorted(&library, 101);
    
    printf("\nLibrary (Forward): ");
    struct DNode* temp = library;
    while(temp != NULL) {
        printf("%d ", temp->bookID);
        temp = temp->next;
    }
    printf("\n");
    
    printf("Library (Reverse): ");
    displayReverse(library);
}

// ============================================================================
// QUESTION 15: Time Complexity Analysis
// ============================================================================

void question15_demo() {
    printf("\n=== QUESTION 15: Singly Linked List Complexity ===\n");
    
    printf("\n1. TRAVERSAL:\n");
    printf("   - Must visit each node once\n");
    printf("   - Time Complexity: O(n)\n");
    printf("   - Where n is number of nodes\n");
    
    printf("\n2. INSERTION:\n");
    printf("   a) At beginning: O(1)\n");
    printf("      - Just update head pointer\n");
    printf("   b) At end: O(n)\n");
    printf("      - Must traverse to find last node\n");
    printf("   c) At position k: O(k)\n");
    printf("      - Must traverse k nodes\n");
    printf("   WORST CASE: O(n) - insertion at end\n");
    
    printf("\n3. DELETION:\n");
    printf("   WORST CASE: O(n)\n");
    printf("   - May need to traverse entire list\n");
    
    printf("\n4. SEARCH:\n");
    printf("   WORST CASE: O(n)\n");
    printf("   - Element may be at end or not present\n");
}

// ============================================================================
// MAIN FUNCTION
// ============================================================================

int main() {
    printf("\n");
    printf("================================================================================\n");
    printf("       CSC 1201 - Fundamental of Data Structures Assignment Solutions\n");
    printf("                     B.Tech First Year, Semester II\n");
    printf("================================================================================\n");
    
    // Uncomment to run specific questions
    question1_demo();
    question2_demo();
    question3_demo();
    question4_demo();
    question5_demo();
    question6_demo();
    question7_demo();
    question8_demo();
    question9_demo();
    question10_demo();
    question11_demo();
    question12_demo();
    question13_demo();
    question14_demo();
    question15_demo();
    
    printf("\n");
    printf("================================================================================\n");
    printf("                           End of Solutions\n");
    printf("================================================================================\n");
    
    return 0;
}
