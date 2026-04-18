/*
 * ============================================================
 *  LINKED LISTS IN C — Complete Implementation
 *  Covers:
 *    1. Singly Linked List
 *    2. Doubly Linked List
 *    3. Circular Singly Linked List
 *  Operations: Insert (front/end/position),
 *              Delete (front/end/position),
 *              Search, Traverse, Reverse
 * ============================================================
 */

#include <stdio.h>
#include <stdlib.h>

/* ============================================================
 *  SECTION 1: SINGLY LINKED LIST
 * ============================================================ */

struct SNode {
    int data;
    struct SNode *next;
};

struct SNode *shead = NULL;

/* --- Create a new singly node --- */
struct SNode *screate(int val) {
    struct SNode *newNode = (struct SNode *)malloc(sizeof(struct SNode));
    if (!newNode) { printf("Memory allocation failed!\n"); exit(1); }
    newNode->data = val;
    newNode->next = NULL;
    return newNode;
}

/* --- Insert at front --- */
void sInsertFront(int val) {
    struct SNode *newNode = screate(val);
    newNode->next = shead;
    shead = newNode;
    printf("Inserted %d at front.\n", val);
}

/* --- Insert at end --- */
void sInsertEnd(int val) {
    struct SNode *newNode = screate(val);
    if (shead == NULL) { shead = newNode; }
    else {
        struct SNode *ptr = shead;
        while (ptr->next != NULL) ptr = ptr->next;
        ptr->next = newNode;
    }
    printf("Inserted %d at end.\n", val);
}

/* --- Insert at position (1-based) --- */
void sInsertPos(int val, int pos) {
    if (pos == 1) { sInsertFront(val); return; }
    struct SNode *newNode = screate(val);
    struct SNode *ptr = shead;
    for (int i = 1; i < pos - 1 && ptr != NULL; i++)
        ptr = ptr->next;
    if (ptr == NULL) { printf("Position out of range.\n"); free(newNode); return; }
    newNode->next = ptr->next;
    ptr->next = newNode;
    printf("Inserted %d at position %d.\n", val, pos);
}

/* --- Delete at front --- */
void sDeleteFront() {
    if (shead == NULL) { printf("List is empty.\n"); return; }
    struct SNode *ptr = shead;
    shead = shead->next;
    printf("Deleted %d from front.\n", ptr->data);
    free(ptr);
}

/* --- Delete at end --- */
void sDeleteEnd() {
    if (shead == NULL) { printf("List is empty.\n"); return; }
    if (shead->next == NULL) {
        printf("Deleted %d from end.\n", shead->data);
        free(shead); shead = NULL; return;
    }
    struct SNode *ptr = shead, *ptr1 = NULL;
    while (ptr->next != NULL) { ptr1 = ptr; ptr = ptr->next; }
    ptr1->next = NULL;
    printf("Deleted %d from end.\n", ptr->data);
    free(ptr);
}

/* --- Delete at position (1-based) --- */
void sDeletePos(int pos) {
    if (shead == NULL) { printf("List is empty.\n"); return; }
    if (pos == 1) { sDeleteFront(); return; }
    struct SNode *ptr = shead, *ptr1 = NULL;
    for (int i = 1; i < pos && ptr != NULL; i++) { ptr1 = ptr; ptr = ptr->next; }
    if (ptr == NULL) { printf("Position out of range.\n"); return; }
    ptr1->next = ptr->next;
    printf("Deleted %d from position %d.\n", ptr->data, pos);
    free(ptr);
}

/* --- Search --- */
void sSearch(int val) {
    struct SNode *ptr = shead;
    int pos = 1;
    while (ptr != NULL) {
        if (ptr->data == val) { printf("Found %d at position %d.\n", val, pos); return; }
        ptr = ptr->next; pos++;
    }
    printf("%d not found in list.\n", val);
}

/* --- Traverse --- */
void sTraverse() {
    if (shead == NULL) { printf("List is empty.\n"); return; }
    printf("List: ");
    struct SNode *ptr = shead;
    while (ptr != NULL) { printf("%d", ptr->data); if (ptr->next) printf(" -> "); ptr = ptr->next; }
    printf(" -> NULL\n");
}

/* --- Reverse --- */
void sReverse() {
    struct SNode *prev = NULL, *curr = shead, *next = NULL;
    while (curr != NULL) { next = curr->next; curr->next = prev; prev = curr; curr = next; }
    shead = prev;
    printf("Singly list reversed.\n");
}

/* --- Singly Menu --- */
void singlyMenu() {
    int choice, val, pos;
    do {
        printf("\n===== SINGLY LINKED LIST =====\n");
        printf("1. Insert at Front\n");
        printf("2. Insert at End\n");
        printf("3. Insert at Position\n");
        printf("4. Delete at Front\n");
        printf("5. Delete at End\n");
        printf("6. Delete at Position\n");
        printf("7. Search\n");
        printf("8. Traverse / Display\n");
        printf("9. Reverse\n");
        printf("0. Back to Main Menu\n");
        printf("Enter choice: ");
        scanf("%d", &choice);
        switch (choice) {
            case 1: printf("Enter value: "); scanf("%d", &val); sInsertFront(val); break;
            case 2: printf("Enter value: "); scanf("%d", &val); sInsertEnd(val); break;
            case 3: printf("Enter value and position: "); scanf("%d %d", &val, &pos); sInsertPos(val, pos); break;
            case 4: sDeleteFront(); break;
            case 5: sDeleteEnd(); break;
            case 6: printf("Enter position: "); scanf("%d", &pos); sDeletePos(pos); break;
            case 7: printf("Enter value to search: "); scanf("%d", &val); sSearch(val); break;
            case 8: sTraverse(); break;
            case 9: sReverse(); sTraverse(); break;
            case 0: break;
            default: printf("Invalid choice.\n");
        }
    } while (choice != 0);
}


/* ============================================================
 *  SECTION 2: DOUBLY LINKED LIST
 * ============================================================ */

struct DNode {
    int data;
    struct DNode *prev;
    struct DNode *next;
};

struct DNode *dhead = NULL;

/* --- Create a new doubly node --- */
struct DNode *dcreate(int val) {
    struct DNode *newNode = (struct DNode *)malloc(sizeof(struct DNode));
    if (!newNode) { printf("Memory allocation failed!\n"); exit(1); }
    newNode->data = val;
    newNode->prev = NULL;
    newNode->next = NULL;
    return newNode;
}

/* --- Insert at front --- */
void dInsertFront(int val) {
    struct DNode *newNode = dcreate(val);
    if (dhead == NULL) { dhead = newNode; }
    else {
        newNode->next = dhead;
        dhead->prev = newNode;
        dhead = newNode;
    }
    printf("Inserted %d at front.\n", val);
}

/* --- Insert at end --- */
void dInsertEnd(int val) {
    struct DNode *newNode = dcreate(val);
    if (dhead == NULL) { dhead = newNode; }
    else {
        struct DNode *ptr = dhead;
        while (ptr->next != NULL) ptr = ptr->next;
        ptr->next = newNode;
        newNode->prev = ptr;
    }
    printf("Inserted %d at end.\n", val);
}

/* --- Insert at position (1-based) --- */
void dInsertPos(int val, int pos) {
    if (pos == 1) { dInsertFront(val); return; }
    struct DNode *newNode = dcreate(val);
    struct DNode *ptr = dhead;
    for (int i = 1; i < pos - 1 && ptr != NULL; i++) ptr = ptr->next;
    if (ptr == NULL) { printf("Position out of range.\n"); free(newNode); return; }
    struct DNode *ptr1 = ptr->next;
    newNode->next = ptr1;
    if (ptr1) ptr1->prev = newNode;
    newNode->prev = ptr;
    ptr->next = newNode;
    printf("Inserted %d at position %d.\n", val, pos);
}

/* --- Delete at front --- */
void dDeleteFront() {
    if (dhead == NULL) { printf("List is empty.\n"); return; }
    struct DNode *ptr = dhead;
    dhead = dhead->next;
    if (dhead) dhead->prev = NULL;
    printf("Deleted %d from front.\n", ptr->data);
    free(ptr);
}

/* --- Delete at end --- */
void dDeleteEnd() {
    if (dhead == NULL) { printf("List is empty.\n"); return; }
    struct DNode *ptr = dhead;
    while (ptr->next != NULL) ptr = ptr->next;
    if (ptr->prev) ptr->prev->next = NULL;
    else dhead = NULL;
    printf("Deleted %d from end.\n", ptr->data);
    free(ptr);
}

/* --- Delete at position (1-based) --- */
void dDeletePos(int pos) {
    if (dhead == NULL) { printf("List is empty.\n"); return; }
    if (pos == 1) { dDeleteFront(); return; }
    struct DNode *ptr = dhead;
    for (int i = 1; i < pos && ptr != NULL; i++) ptr = ptr->next;
    if (ptr == NULL) { printf("Position out of range.\n"); return; }
    struct DNode *ptr1 = ptr->prev;
    struct DNode *ptr2 = ptr->next;
    if (ptr1) ptr1->next = ptr2;
    if (ptr2) ptr2->prev = ptr1;
    printf("Deleted %d from position %d.\n", ptr->data, pos);
    free(ptr);
}

/* --- Search --- */
void dSearch(int val) {
    struct DNode *ptr = dhead;
    int pos = 1;
    while (ptr != NULL) {
        if (ptr->data == val) { printf("Found %d at position %d.\n", val, pos); return; }
        ptr = ptr->next; pos++;
    }
    printf("%d not found in list.\n", val);
}

/* --- Traverse forward and backward --- */
void dTraverse() {
    if (dhead == NULL) { printf("List is empty.\n"); return; }
    struct DNode *ptr = dhead;
    printf("Forward : ");
    while (ptr->next != NULL) { printf("%d <-> ", ptr->data); ptr = ptr->next; }
    printf("%d\n", ptr->data);
    printf("Backward: ");
    while (ptr != NULL) { printf("%d", ptr->data); if (ptr->prev) printf(" <-> "); ptr = ptr->prev; }
    printf("\n");
}

/* --- Reverse --- */
void dReverse() {
    struct DNode *ptr = dhead, *temp = NULL;
    while (ptr != NULL) {
        temp = ptr->prev;
        ptr->prev = ptr->next;
        ptr->next = temp;
        ptr = ptr->prev;   /* move forward (was next) */
    }
    if (temp) dhead = temp->prev;
    printf("Doubly list reversed.\n");
}

/* --- Doubly Menu --- */
void doublyMenu() {
    int choice, val, pos;
    do {
        printf("\n===== DOUBLY LINKED LIST =====\n");
        printf("1. Insert at Front\n");
        printf("2. Insert at End\n");
        printf("3. Insert at Position\n");
        printf("4. Delete at Front\n");
        printf("5. Delete at End\n");
        printf("6. Delete at Position\n");
        printf("7. Search\n");
        printf("8. Traverse / Display\n");
        printf("9. Reverse\n");
        printf("0. Back to Main Menu\n");
        printf("Enter choice: ");
        scanf("%d", &choice);
        switch (choice) {
            case 1: printf("Enter value: "); scanf("%d", &val); dInsertFront(val); break;
            case 2: printf("Enter value: "); scanf("%d", &val); dInsertEnd(val); break;
            case 3: printf("Enter value and position: "); scanf("%d %d", &val, &pos); dInsertPos(val, pos); break;
            case 4: dDeleteFront(); break;
            case 5: dDeleteEnd(); break;
            case 6: printf("Enter position: "); scanf("%d", &pos); dDeletePos(pos); break;
            case 7: printf("Enter value to search: "); scanf("%d", &val); dSearch(val); break;
            case 8: dTraverse(); break;
            case 9: dReverse(); dTraverse(); break;
            case 0: break;
            default: printf("Invalid choice.\n");
        }
    } while (choice != 0);
}


/* ============================================================
 *  SECTION 3: CIRCULAR SINGLY LINKED LIST
 * ============================================================ */

struct CNode {
    int data;
    struct CNode *next;
};

struct CNode *chead = NULL;

/* --- Create a new circular node --- */
struct CNode *ccreate(int val) {
    struct CNode *newNode = (struct CNode *)malloc(sizeof(struct CNode));
    if (!newNode) { printf("Memory allocation failed!\n"); exit(1); }
    newNode->data = val;
    newNode->next = newNode;   /* points to itself initially */
    return newNode;
}

/* --- Insert at front --- */
void cInsertFront(int val) {
    struct CNode *newNode = ccreate(val);
    if (chead == NULL) { chead = newNode; return; }
    struct CNode *temp = chead;
    while (temp->next != chead) temp = temp->next;
    newNode->next = chead;
    temp->next = newNode;
    chead = newNode;
    printf("Inserted %d at front.\n", val);
}

/* --- Insert at end --- */
void cInsertEnd(int val) {
    struct CNode *newNode = ccreate(val);
    if (chead == NULL) { chead = newNode; printf("Inserted %d at end.\n", val); return; }
    struct CNode *temp = chead;
    while (temp->next != chead) temp = temp->next;
    temp->next = newNode;
    newNode->next = chead;
    printf("Inserted %d at end.\n", val);
}

/* --- Insert at position (1-based) --- */
void cInsertPos(int val, int pos) {
    if (pos == 1) { cInsertFront(val); return; }
    struct CNode *newNode = ccreate(val);
    struct CNode *ptr = chead;
    for (int i = 1; i < pos - 1; i++) {
        ptr = ptr->next;
        if (ptr == chead) { printf("Position out of range.\n"); free(newNode); return; }
    }
    newNode->next = ptr->next;
    ptr->next = newNode;
    printf("Inserted %d at position %d.\n", val, pos);
}

/* --- Delete at front --- */
void cDeleteFront() {
    if (chead == NULL) { printf("List is empty.\n"); return; }
    if (chead->next == chead) {
        printf("Deleted %d from front.\n", chead->data);
        free(chead); chead = NULL; return;
    }
    struct CNode *temp = chead;
    struct CNode *last = chead;
    while (last->next != chead) last = last->next;
    chead = chead->next;
    last->next = chead;
    printf("Deleted %d from front.\n", temp->data);
    free(temp);
}

/* --- Delete at end --- */
void cDeleteEnd() {
    if (chead == NULL) { printf("List is empty.\n"); return; }
    if (chead->next == chead) {
        printf("Deleted %d from end.\n", chead->data);
        free(chead); chead = NULL; return;
    }
    struct CNode *ptr = chead, *prev = NULL;
    while (ptr->next != chead) { prev = ptr; ptr = ptr->next; }
    prev->next = chead;
    printf("Deleted %d from end.\n", ptr->data);
    free(ptr);
}

/* --- Delete at position (1-based) --- */
void cDeletePos(int pos) {
    if (chead == NULL) { printf("List is empty.\n"); return; }
    if (pos == 1) { cDeleteFront(); return; }
    struct CNode *ptr = chead, *prev = NULL;
    for (int i = 1; i < pos; i++) {
        prev = ptr; ptr = ptr->next;
        if (ptr == chead) { printf("Position out of range.\n"); return; }
    }
    prev->next = ptr->next;
    printf("Deleted %d from position %d.\n", ptr->data, pos);
    free(ptr);
}

/* --- Search --- */
void cSearch(int val) {
    if (chead == NULL) { printf("List is empty.\n"); return; }
    struct CNode *ptr = chead;
    int pos = 1;
    do {
        if (ptr->data == val) { printf("Found %d at position %d.\n", val, pos); return; }
        ptr = ptr->next; pos++;
    } while (ptr != chead);
    printf("%d not found in list.\n", val);
}

/* --- Traverse --- */
void cTraverse() {
    if (chead == NULL) { printf("List is empty.\n"); return; }
    struct CNode *ptr = chead;
    printf("List (circular): ");
    do { printf("%d -> ", ptr->data); ptr = ptr->next; } while (ptr != chead);
    printf("(back to %d)\n", chead->data);
}

/* --- Reverse --- */
void cReverse() {
    if (chead == NULL || chead->next == chead) return;
    struct CNode *prev = NULL, *curr = chead, *next = NULL;
    struct CNode *last = chead;
    /* find last node */
    while (last->next != chead) last = last->next;
    do {
        next = curr->next;
        curr->next = prev;
        prev = curr;
        curr = next;
    } while (curr != chead);
    chead->next = prev;   /* old head's next = new head (last node) */
    chead = prev;
    /* fix last node to point back to new head */
    struct CNode *t = chead;
    while (t->next != NULL && t->next != chead) t = t->next;
    /* Actually redo: simpler approach — find the node with next==NULL after reversal */
    t = chead;
    while (t->next != NULL) t = t->next;
    t->next = chead;
    printf("Circular list reversed.\n");
}

/* --- Circular Menu --- */
void circularMenu() {
    int choice, val, pos;
    do {
        printf("\n===== CIRCULAR SINGLY LINKED LIST =====\n");
        printf("1. Insert at Front\n");
        printf("2. Insert at End\n");
        printf("3. Insert at Position\n");
        printf("4. Delete at Front\n");
        printf("5. Delete at End\n");
        printf("6. Delete at Position\n");
        printf("7. Search\n");
        printf("8. Traverse / Display\n");
        printf("9. Reverse\n");
        printf("0. Back to Main Menu\n");
        printf("Enter choice: ");
        scanf("%d", &choice);
        switch (choice) {
            case 1: printf("Enter value: "); scanf("%d", &val); cInsertFront(val); break;
            case 2: printf("Enter value: "); scanf("%d", &val); cInsertEnd(val); break;
            case 3: printf("Enter value and position: "); scanf("%d %d", &val, &pos); cInsertPos(val, pos); break;
            case 4: cDeleteFront(); break;
            case 5: cDeleteEnd(); break;
            case 6: printf("Enter position: "); scanf("%d", &pos); cDeletePos(pos); break;
            case 7: printf("Enter value to search: "); scanf("%d", &val); cSearch(val); break;
            case 8: cTraverse(); break;
            case 9: cReverse(); cTraverse(); break;
            case 0: break;
            default: printf("Invalid choice.\n");
        }
    } while (choice != 0);
}


/* ============================================================
 *  MAIN MENU
 * ============================================================ */

int main() {
    int choice;
    printf("================================================\n");
    printf("   LINKED LISTS IN C — Complete Implementation  \n");
    printf("================================================\n");
    do {
        printf("\n========== MAIN MENU ==========\n");
        printf("1. Singly Linked List\n");
        printf("2. Doubly Linked List\n");
        printf("3. Circular Singly Linked List\n");
        printf("0. Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);
        switch (choice) {
            case 1: singlyMenu();   break;
            case 2: doublyMenu();   break;
            case 3: circularMenu(); break;
            case 0: printf("Exiting. Goodbye!\n"); break;
            default: printf("Invalid choice. Try again.\n");
        }
    } while (choice != 0);
    return 0;
}
