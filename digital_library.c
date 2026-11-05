/*
 PROJECT TITLE: DIGITAL LIBRARY TEXTBOOK LOOKUP SYSTEM USING C
 Integrated menu-driven project covering all 13 Data Structure experiments.

 Compile: gcc digital_library.c -o digital_library
 Run:     ./digital_library       (Linux/macOS)
          digital_library.exe    (Windows)

 Note: Enter titles/authors without spaces (use underscores).
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_BOOKS 100
#define MAX 100
#define GRAPH_MAX 20
#define HASH_SIZE 11
#define EMPTY -1
#define DELETED -2
#define STATUS(x) ((x) > 0 ? "Available" : "Not Available")

/* ---------------- EXPERIMENT 1: STRUCTURES, ARRAYS, FUNCTIONS, POINTERS, MACROS ---------------- */

typedef struct {
    int id;
    char title[60];
    char author[50];
    char isbn[20];
    char category[40];
    int copies;
} Book;

Book catalogue[MAX_BOOKS];
int bookCount = 0;

void addBookRecord(void) {
    Book *b;
    int i;
    if (bookCount >= MAX_BOOKS) {
        printf("Catalogue is full.\n");
        return;
    }
    b = &catalogue[bookCount];
    printf("Enter Book ID: ");
    scanf("%d", &b->id);
    for (i = 0; i < bookCount; i++) {
        if (catalogue[i].id == b->id) {
            printf("Book ID already exists.\n");
            return;
        }
    }
    printf("Enter title (use_underscores): ");
    scanf("%59s", b->title);
    printf("Enter author (use_underscores): ");
    scanf("%49s", b->author);
    printf("Enter ISBN (digits only): ");
    scanf("%19s", b->isbn);
    printf("Enter category (use_underscores): ");
    scanf("%39s", b->category);
    printf("Enter available copies: ");
    scanf("%d", &b->copies);
    if (b->copies < 0) b->copies = 0;
    bookCount++;
    printf("Textbook added successfully.\n");
}

void displayBookRecords(void) {
    int i;
    if (bookCount == 0) {
        printf("Digital library catalogue is empty.\n");
        return;
    }
    printf("\n%-8s %-20s %-18s %-16s %-15s %-7s %s\n",
           "BOOK ID", "TITLE", "AUTHOR", "ISBN", "CATEGORY", "COPIES", "STATUS");
    for (i = 0; i < bookCount; i++) {
        Book *b = &catalogue[i];
        printf("%-8d %-20s %-18s %-16s %-15s %-7d %s\n",
               b->id, b->title, b->author, b->isbn, b->category,
               b->copies, STATUS(b->copies));
    }
}

void experiment1(void) {
    int choice;
    do {
        printf("\n--- EXPERIMENT 1: BOOK RECORDS USING STRUCTURES / ARRAYS / POINTERS ---\n");
        printf("1. Add textbook record\n2. Display all textbook records\n0. Back to main menu\nChoice: ");
        scanf("%d", &choice);
        if (choice == 1) addBookRecord();
        else if (choice == 2) displayBookRecords();
        else if (choice != 0) printf("Invalid choice.\n");
    } while (choice != 0);
}

/* ---------------- EXPERIMENT 2: LINEAR AND BINARY SEARCH ---------------- */

void experiment2(void) {
    int choice, key, i, pos = -1, low, high, mid;
    if (bookCount == 0) {
        printf("Add textbook records first using Experiment 1.\n");
        return;
    }
    printf("\n--- EXPERIMENT 2: SEARCH TEXTBOOK BY BOOK ID ---\n");
    printf("1. Linear Search\n2. Binary Search (sorts catalogue by ID first)\nChoice: ");
    scanf("%d", &choice);
    printf("Enter Book ID to search: ");
    scanf("%d", &key);

    if (choice == 1) {
        for (i = 0; i < bookCount; i++) {
            if (catalogue[i].id == key) { pos = i; break; }
        }
    } else if (choice == 2) {
        Book temp;
        for (i = 0; i < bookCount - 1; i++) {
            int j;
            for (j = 0; j < bookCount - i - 1; j++) {
                if (catalogue[j].id > catalogue[j + 1].id) {
                    temp = catalogue[j];
                    catalogue[j] = catalogue[j + 1];
                    catalogue[j + 1] = temp;
                }
            }
        }
        low = 0; high = bookCount - 1;
        while (low <= high) {
            mid = (low + high) / 2;
            if (catalogue[mid].id == key) { pos = mid; break; }
            if (catalogue[mid].id < key) low = mid + 1;
            else high = mid - 1;
        }
    } else {
        printf("Invalid choice.\n");
        return;
    }

    if (pos == -1) printf("Textbook not found in the digital library.\n");
    else {
        Book *b = &catalogue[pos];
        printf("Textbook found: ID=%d, Title=%s, Author=%s, ISBN=%s, Copies=%d\n",
               b->id, b->title, b->author, b->isbn, b->copies);
    }
}

/* ---------------- EXPERIMENT 3: INSERTION, QUICK, MERGE SORT ---------------- */

void displayIDs(int a[], int n) {
    int i;
    for (i = 0; i < n; i++) printf("%d ", a[i]);
    printf("\n");
}
void insertionSort(int a[], int n) {
    int i, j, key;
    for (i = 1; i < n; i++) {
        key = a[i]; j = i - 1;
        while (j >= 0 && a[j] > key) { a[j + 1] = a[j]; j--; }
        a[j + 1] = key;
    }
}
int partitionIDs(int a[], int low, int high) {
    int pivot = a[high], i = low - 1, j, t;
    for (j = low; j < high; j++) {
        if (a[j] <= pivot) {
            i++; t = a[i]; a[i] = a[j]; a[j] = t;
        }
    }
    t = a[i + 1]; a[i + 1] = a[high]; a[high] = t;
    return i + 1;
}
void quickSortIDs(int a[], int low, int high) {
    if (low < high) {
        int p = partitionIDs(a, low, high);
        quickSortIDs(a, low, p - 1);
        quickSortIDs(a, p + 1, high);
    }
}
void mergeIDs(int a[], int l, int m, int r) {
    int temp[MAX], i = l, j = m + 1, k = l, x;
    while (i <= m && j <= r) temp[k++] = (a[i] <= a[j]) ? a[i++] : a[j++];
    while (i <= m) temp[k++] = a[i++];
    while (j <= r) temp[k++] = a[j++];
    for (x = l; x <= r; x++) a[x] = temp[x];
}
void mergeSortIDs(int a[], int l, int r) {
    if (l < r) {
        int m = (l + r) / 2;
        mergeSortIDs(a, l, m);
        mergeSortIDs(a, m + 1, r);
        mergeIDs(a, l, m, r);
    }
}
void experiment3(void) {
    int a[MAX_BOOKS], i, choice;
    if (bookCount == 0) { printf("Add textbook records first.\n"); return; }
    for (i = 0; i < bookCount; i++) a[i] = catalogue[i].id;
    printf("\n--- EXPERIMENT 3: SORT TEXTBOOK CATALOGUE BY BOOK ID ---\n");
    printf("1. Insertion Sort\n2. Quick Sort\n3. Merge Sort\nChoice: ");
    scanf("%d", &choice);
    if (choice == 1) insertionSort(a, bookCount);
    else if (choice == 2) quickSortIDs(a, 0, bookCount - 1);
    else if (choice == 3) mergeSortIDs(a, 0, bookCount - 1);
    else { printf("Invalid choice.\n"); return; }
    printf("Sorted Book IDs: ");
    displayIDs(a, bookCount);
}

/* ---------------- EXPERIMENT 4: LINKED LIST BOOK CATALOGUE ---------------- */

typedef struct BookNode {
    int id;
    char title[60];
    struct BookNode *next;
} BookNode;
BookNode *listHead = NULL;

void listAdd(void) {
    BookNode *p, *t;
    p = (BookNode *)malloc(sizeof(BookNode));
    if (!p) { printf("Memory allocation failed.\n"); return; }
    printf("Enter Book ID: "); scanf("%d", &p->id);
    printf("Enter title (use_underscores): "); scanf("%59s", p->title);
    p->next = NULL;
    if (!listHead) listHead = p;
    else { t = listHead; while (t->next) t = t->next; t->next = p; }
    printf("Book added to linked catalogue.\n");
}
void listSearch(void) {
    int id;
    BookNode *t = listHead;
    printf("Enter Book ID: "); scanf("%d", &id);
    while (t) {
        if (t->id == id) { printf("Found: %d - %s\n", t->id, t->title); return; }
        t = t->next;
    }
    printf("Book not found.\n");
}
void listDisplay(void) {
    BookNode *t = listHead;
    if (!t) { printf("Linked catalogue is empty.\n"); return; }
    while (t) { printf("[%d] %s -> ", t->id, t->title); t = t->next; }
    printf("NULL\n");
}
void listDelete(void) {
    int id;
    BookNode *t = listHead, *prev = NULL;
    printf("Enter Book ID to delete: "); scanf("%d", &id);
    while (t && t->id != id) { prev = t; t = t->next; }
    if (!t) { printf("Book not found.\n"); return; }
    if (!prev) listHead = t->next;
    else prev->next = t->next;
    free(t);
    printf("Book deleted from linked catalogue.\n");
}
void experiment4(void) {
    int ch;
    do {
        printf("\n--- EXPERIMENT 4: LINKED LIST BOOK CATALOGUE ---\n");
        printf("1. Add book\n2. Search book\n3. Display books\n4. Delete book\n0. Back\nChoice: ");
        scanf("%d", &ch);
        if (ch == 1) listAdd();
        else if (ch == 2) listSearch();
        else if (ch == 3) listDisplay();
        else if (ch == 4) listDelete();
        else if (ch != 0) printf("Invalid choice.\n");
    } while (ch != 0);
}

/* ---------------- EXPERIMENT 5: STACK USING ARRAY AND LINKED LIST ---------------- */

int arrayStack[MAX], arrayTop = -1;
typedef struct StackNode { int id; struct StackNode *next; } StackNode;
StackNode *linkedTop = NULL;

void arrayStackPush(int id) {
    if (arrayTop == MAX - 1) printf("Recently viewed stack is full.\n");
    else { arrayStack[++arrayTop] = id; printf("Book added to recent history.\n"); }
}
void arrayStackPop(void) {
    if (arrayTop == -1) printf("Recent history is empty.\n");
    else printf("Removed recently viewed Book ID: %d\n", arrayStack[arrayTop--]);
}
void arrayStackDisplay(void) {
    int i;
    if (arrayTop == -1) { printf("Recent history is empty.\n"); return; }
    printf("Recently viewed (latest first): ");
    for (i = arrayTop; i >= 0; i--) printf("%d ", arrayStack[i]);
    printf("\n");
}
void linkedStackPush(int id) {
    StackNode *p = (StackNode *)malloc(sizeof(StackNode));
    if (!p) { printf("Memory allocation failed.\n"); return; }
    p->id = id; p->next = linkedTop; linkedTop = p;
    printf("Book added to linked recent history.\n");
}
void linkedStackPop(void) {
    StackNode *p;
    if (!linkedTop) { printf("Recent history is empty.\n"); return; }
    p = linkedTop;
    printf("Removed recently viewed Book ID: %d\n", p->id);
    linkedTop = p->next; free(p);
}
void linkedStackDisplay(void) {
    StackNode *p = linkedTop;
    if (!p) { printf("Recent history is empty.\n"); return; }
    printf("Recently viewed (latest first): ");
    while (p) { printf("%d ", p->id); p = p->next; }
    printf("\n");
}
void experiment5(void) {
    int type, op, id;
    do {
        printf("\n--- EXPERIMENT 5: RECENTLY VIEWED BOOK STACK ---\n");
        printf("1. Array Stack\n2. Linked List Stack\n0. Back\nImplementation: ");
        scanf("%d", &type);
        if (type == 0) break;
        if (type != 1 && type != 2) { printf("Invalid choice.\n"); continue; }
        printf("1. View book (Push)\n2. Remove latest (Pop)\n3. Display history\nOperation: ");
        scanf("%d", &op);
        if (op == 1) {
            printf("Enter Book ID: "); scanf("%d", &id);
            if (type == 1) arrayStackPush(id); else linkedStackPush(id);
        } else if (op == 2) {
            if (type == 1) arrayStackPop(); else linkedStackPop();
        } else if (op == 3) {
            if (type == 1) arrayStackDisplay(); else linkedStackDisplay();
        } else printf("Invalid operation.\n");
    } while (1);
}

/* ---------------- EXPERIMENT 6: QUEUE USING ARRAY AND LINKED LIST ---------------- */

typedef struct { int studentID, bookID; } IssueRequest;
IssueRequest requestArray[MAX];
int qFront = 0, qRear = -1;

typedef struct RequestNode {
    IssueRequest data;
    struct RequestNode *next;
} RequestNode;
RequestNode *linkedFront = NULL, *linkedRear = NULL;

void arrayEnqueue(void) {
    if (qRear == MAX - 1) { printf("Issue request queue is full.\n"); return; }
    qRear++;
    printf("Student ID: "); scanf("%d", &requestArray[qRear].studentID);
    printf("Requested Book ID: "); scanf("%d", &requestArray[qRear].bookID);
    printf("Issue request added to queue.\n");
}
void arrayDequeue(void) {
    if (qFront > qRear) { printf("No pending issue requests.\n"); qFront = 0; qRear = -1; return; }
    printf("Processing Student %d request for Book %d\n",
           requestArray[qFront].studentID, requestArray[qFront].bookID);
    qFront++;
    if (qFront > qRear) { qFront = 0; qRear = -1; }
}
void arrayQueueDisplay(void) {
    int i;
    if (qFront > qRear) { printf("Issue queue is empty.\n"); return; }
    for (i = qFront; i <= qRear; i++)
        printf("Student %d -> Book %d\n", requestArray[i].studentID, requestArray[i].bookID);
}
void linkedEnqueue(void) {
    RequestNode *p = (RequestNode *)malloc(sizeof(RequestNode));
    if (!p) { printf("Memory allocation failed.\n"); return; }
    printf("Student ID: "); scanf("%d", &p->data.studentID);
    printf("Requested Book ID: "); scanf("%d", &p->data.bookID);
    p->next = NULL;
    if (!linkedRear) linkedFront = linkedRear = p;
    else { linkedRear->next = p; linkedRear = p; }
    printf("Issue request added to linked queue.\n");
}
void linkedDequeue(void) {
    RequestNode *p;
    if (!linkedFront) { printf("No pending issue requests.\n"); return; }
    p = linkedFront;
    printf("Processing Student %d request for Book %d\n", p->data.studentID, p->data.bookID);
    linkedFront = linkedFront->next;
    if (!linkedFront) linkedRear = NULL;
    free(p);
}
void linkedQueueDisplay(void) {
    RequestNode *p = linkedFront;
    if (!p) { printf("Issue queue is empty.\n"); return; }
    while (p) {
        printf("Student %d -> Book %d\n", p->data.studentID, p->data.bookID);
        p = p->next;
    }
}
void experiment6(void) {
    int type, op;
    do {
        printf("\n--- EXPERIMENT 6: BOOK ISSUE REQUEST QUEUE ---\n");
        printf("1. Array Queue\n2. Linked List Queue\n0. Back\nImplementation: ");
        scanf("%d", &type);
        if (type == 0) break;
        if (type != 1 && type != 2) { printf("Invalid choice.\n"); continue; }
        printf("1. Add issue request (Enqueue)\n2. Process next request (Dequeue)\n3. Display pending requests\nOperation: ");
        scanf("%d", &op);
        if (op == 1) { if (type == 1) arrayEnqueue(); else linkedEnqueue(); }
        else if (op == 2) { if (type == 1) arrayDequeue(); else linkedDequeue(); }
        else if (op == 3) { if (type == 1) arrayQueueDisplay(); else linkedQueueDisplay(); }
        else printf("Invalid operation.\n");
    } while (1);
}

/* ---------------- EXPERIMENT 7: STACK APPLICATION - UNDO ISSUE ---------------- */

IssueRequest issueHistory[MAX];
int issueTop = -1;
void issueTextbook(void) {
    if (issueTop == MAX - 1) { printf("Issue history is full.\n"); return; }
    printf("Enter Student ID: "); scanf("%d", &issueHistory[issueTop + 1].studentID);
    printf("Enter Book ID to issue: "); scanf("%d", &issueHistory[issueTop + 1].bookID);
    issueTop++;
    printf("Book %d issued to Student %d.\n",
           issueHistory[issueTop].bookID, issueHistory[issueTop].studentID);
}
void undoIssue(void) {
    if (issueTop == -1) { printf("No issue transaction to undo.\n"); return; }
    printf("Undo completed: Book %d issue to Student %d has been cancelled.\n",
           issueHistory[issueTop].bookID, issueHistory[issueTop].studentID);
    issueTop--;
}
void showIssueHistory(void) {
    int i;
    if (issueTop == -1) { printf("No active issue records.\n"); return; }
    for (i = issueTop; i >= 0; i--)
        printf("Student %d - Book %d\n", issueHistory[i].studentID, issueHistory[i].bookID);
}
void experiment7(void) {
    int ch;
    do {
        printf("\n--- EXPERIMENT 7: UNDO LAST BOOK ISSUE USING STACK ---\n");
        printf("1. Issue textbook\n2. Undo last issue\n3. Display issue history\n0. Back\nChoice: ");
        scanf("%d", &ch);
        if (ch == 1) issueTextbook();
        else if (ch == 2) undoIssue();
        else if (ch == 3) showIssueHistory();
        else if (ch != 0) printf("Invalid choice.\n");
    } while (ch != 0);
}

/* ---------------- EXPERIMENT 8: BINARY SEARCH TREE ---------------- */

typedef struct TreeNode {
    int id;
    struct TreeNode *left, *right;
} TreeNode;
TreeNode *bookRoot = NULL;

TreeNode *bstInsert(TreeNode *root, int id) {
    if (!root) {
        root = (TreeNode *)malloc(sizeof(TreeNode));
        if (!root) { printf("Memory allocation failed.\n"); return NULL; }
        root->id = id; root->left = root->right = NULL;
    } else if (id < root->id) root->left = bstInsert(root->left, id);
    else if (id > root->id) root->right = bstInsert(root->right, id);
    else printf("Book ID already exists in tree.\n");
    return root;
}
int bstSearch(TreeNode *root, int id) {
    if (!root) return 0;
    if (root->id == id) return 1;
    if (id < root->id) return bstSearch(root->left, id);
    return bstSearch(root->right, id);
}
void bstInorder(TreeNode *r) {
    if (r) { bstInorder(r->left); printf("%d ", r->id); bstInorder(r->right); }
}
void bstPreorder(TreeNode *r) {
    if (r) { printf("%d ", r->id); bstPreorder(r->left); bstPreorder(r->right); }
}
void bstPostorder(TreeNode *r) {
    if (r) { bstPostorder(r->left); bstPostorder(r->right); printf("%d ", r->id); }
}
void freeBST(TreeNode *r) {
    if (r) { freeBST(r->left); freeBST(r->right); free(r); }
}
void experiment8(void) {
    int ch, id;
    do {
        printf("\n--- EXPERIMENT 8: BOOK ID BINARY SEARCH TREE ---\n");
        printf("1. Insert Book ID\n2. Search Book ID\n3. Display tree traversals\n0. Back\nChoice: ");
        scanf("%d", &ch);
        if (ch == 1) { printf("Enter Book ID: "); scanf("%d", &id); bookRoot = bstInsert(bookRoot, id); }
        else if (ch == 2) {
            printf("Enter Book ID: "); scanf("%d", &id);
            if (bstSearch(bookRoot, id)) printf("Book ID exists in the tree.\n");
            else printf("Book ID not found.\n");
        } else if (ch == 3) {
            printf("Inorder (ascending IDs): "); bstInorder(bookRoot);
            printf("\nPreorder: "); bstPreorder(bookRoot);
            printf("\nPostorder: "); bstPostorder(bookRoot);
            printf("\n");
        } else if (ch != 0) printf("Invalid choice.\n");
    } while (ch != 0);
}

/* ---------------- EXPERIMENT 9: PRIORITY QUEUE AND HEAP SORT ---------------- */

typedef struct { int priority, bookID; } PriorityRequest;
PriorityRequest priorityHeap[MAX];
int heapSize = 0;
void swapPriority(PriorityRequest *a, PriorityRequest *b) {
    PriorityRequest t = *a; *a = *b; *b = t;
}
void addPriorityRequest(int priority, int id) {
    int i, p;
    if (heapSize == MAX) { printf("Priority queue is full.\n"); return; }
    i = heapSize++;
    priorityHeap[i].priority = priority;
    priorityHeap[i].bookID = id;
    while (i > 0) {
        p = (i - 1) / 2;
        if (priorityHeap[p].priority <= priorityHeap[i].priority) break;
        swapPriority(&priorityHeap[p], &priorityHeap[i]);
        i = p;
    }
    printf("Textbook request added to priority queue.\n");
}
void processPriorityRequest(void) {
    int i = 0, l, r, smallest;
    if (heapSize == 0) { printf("No pending priority requests.\n"); return; }
    printf("Processing urgent request: Book %d (priority %d)\n",
           priorityHeap[0].bookID, priorityHeap[0].priority);
    priorityHeap[0] = priorityHeap[--heapSize];
    while (1) {
        smallest = i; l = 2 * i + 1; r = 2 * i + 2;
        if (l < heapSize && priorityHeap[l].priority < priorityHeap[smallest].priority) smallest = l;
        if (r < heapSize && priorityHeap[r].priority < priorityHeap[smallest].priority) smallest = r;
        if (smallest == i) break;
        swapPriority(&priorityHeap[i], &priorityHeap[smallest]);
        i = smallest;
    }
}
void displayPriorityRequests(void) {
    int i;
    if (!heapSize) { printf("Priority queue is empty.\n"); return; }
    for (i = 0; i < heapSize; i++)
        printf("Book ID %d - Priority %d\n", priorityHeap[i].bookID, priorityHeap[i].priority);
}
void maxHeapify(int a[], int n, int i) {
    int largest = i, l = 2 * i + 1, r = 2 * i + 2, t;
    if (l < n && a[l] > a[largest]) largest = l;
    if (r < n && a[r] > a[largest]) largest = r;
    if (largest != i) {
        t = a[i]; a[i] = a[largest]; a[largest] = t;
        maxHeapify(a, n, largest);
    }
}
void heapSortCopies(int a[], int n) {
    int i, t;
    for (i = n / 2 - 1; i >= 0; i--) maxHeapify(a, n, i);
    for (i = n - 1; i > 0; i--) {
        t = a[0]; a[0] = a[i]; a[i] = t;
        maxHeapify(a, i, 0);
    }
}
void experiment9(void) {
    int ch, p, id, n, a[MAX], i;
    do {
        printf("\n--- EXPERIMENT 9: PRIORITY QUEUE AND HEAP SORT ---\n");
        printf("1. Add textbook request\n2. Process highest-priority request\n3. Display requests\n4. Heap Sort catalogue copy counts\n0. Back\nChoice: ");
        scanf("%d", &ch);
        if (ch == 1) {
            printf("Enter priority (1 is most urgent): "); scanf("%d", &p);
            printf("Enter Book ID: "); scanf("%d", &id);
            addPriorityRequest(p, id);
        } else if (ch == 2) processPriorityRequest();
        else if (ch == 3) displayPriorityRequests();
        else if (ch == 4) {
            printf("Enter number of textbook records: "); scanf("%d", &n);
            if (n < 1 || n > MAX) { printf("Invalid size.\n"); continue; }
            printf("Enter available copy counts: ");
            for (i = 0; i < n; i++) scanf("%d", &a[i]);
            heapSortCopies(a, n);
            printf("Copy counts in ascending order: ");
            displayIDs(a, n);
        } else if (ch != 0) printf("Invalid choice.\n");
    } while (ch != 0);
}

/* ---------------- EXPERIMENT 10: GRAPH, DFS, BFS, TOPOLOGICAL SORT ---------------- */

int graph[GRAPH_MAX][GRAPH_MAX], graphN = 0;
void graphDFS(int v, int visited[]) {
    int i;
    visited[v] = 1; printf("%d ", v);
    for (i = 0; i < graphN; i++)
        if (graph[v][i] && !visited[i]) graphDFS(i, visited);
}
void graphBFS(int start) {
    int q[GRAPH_MAX], visited[GRAPH_MAX] = {0}, f = 0, r = 0, v, i;
    q[r++] = start; visited[start] = 1;
    while (f < r) {
        v = q[f++]; printf("%d ", v);
        for (i = 0; i < graphN; i++)
            if (graph[v][i] && !visited[i]) { visited[i] = 1; q[r++] = i; }
    }
}
void experiment10(void) {
    int i, j, ch, start, visited[GRAPH_MAX] = {0};
    int indegree[GRAPH_MAX] = {0}, q[GRAPH_MAX], f = 0, r = 0, count = 0, v;
    printf("\n--- EXPERIMENT 10: RELATED TEXTBOOK GRAPH ---\n");
    printf("Each vertex represents a textbook number from 0 to n-1.\n");
    printf("Enter number of textbooks/vertices (max %d): ", GRAPH_MAX);
    scanf("%d", &graphN);
    if (graphN < 1 || graphN > GRAPH_MAX) { printf("Invalid graph size.\n"); graphN = 0; return; }
    printf("Enter directed adjacency matrix (1=link/prerequisite, 0=no link):\n");
    for (i = 0; i < graphN; i++)
        for (j = 0; j < graphN; j++) scanf("%d", &graph[i][j]);
    printf("1. DFS related-book traversal\n2. BFS related-book traversal\n3. Topological reading order\nChoice: ");
    scanf("%d", &ch);
    if (ch == 1 || ch == 2) {
        printf("Enter starting textbook vertex: "); scanf("%d", &start);
        if (start < 0 || start >= graphN) { printf("Invalid vertex.\n"); return; }
        printf("Traversal order: ");
        if (ch == 1) graphDFS(start, visited); else graphBFS(start);
        printf("\n");
    } else if (ch == 3) {
        for (i = 0; i < graphN; i++)
            for (j = 0; j < graphN; j++) if (graph[i][j]) indegree[j]++;
        for (i = 0; i < graphN; i++) if (indegree[i] == 0) q[r++] = i;
        printf("Topological reading order: ");
        while (f < r) {
            v = q[f++]; printf("%d ", v); count++;
            for (j = 0; j < graphN; j++)
                if (graph[v][j] && --indegree[j] == 0) q[r++] = j;
        }
        if (count < graphN) printf("\nCycle detected; topological order is not possible.");
        printf("\n");
    } else printf("Invalid choice.\n");
}

/* ---------------- EXPERIMENT 11: DIJKSTRA SHORTEST ROUTE ---------------- */

void experiment11(void) {
    int n, g[GRAPH_MAX][GRAPH_MAX], dist[GRAPH_MAX], used[GRAPH_MAX] = {0};
    int parent[GRAPH_MAX], i, j, u, v, min, source;
    printf("\n--- EXPERIMENT 11: SHORTEST ROUTE BETWEEN LIBRARY SECTIONS ---\n");
    printf("Enter number of library sections (max %d): ", GRAPH_MAX); scanf("%d", &n);
    if (n < 1 || n > GRAPH_MAX) { printf("Invalid size.\n"); return; }
    printf("Enter distance matrix (0=no direct route; positive=distance):\n");
    for (i = 0; i < n; i++)
        for (j = 0; j < n; j++) scanf("%d", &g[i][j]);
    printf("Enter starting section (0 to %d): ", n - 1); scanf("%d", &source);
    if (source < 0 || source >= n) { printf("Invalid source section.\n"); return; }
    for (i = 0; i < n; i++) { dist[i] = 999999; parent[i] = -1; }
    dist[source] = 0;
    for (i = 0; i < n - 1; i++) {
        min = 999999; u = -1;
        for (j = 0; j < n; j++) if (!used[j] && dist[j] < min) { min = dist[j]; u = j; }
        if (u == -1) break;
        used[u] = 1;
        for (v = 0; v < n; v++)
            if (g[u][v] > 0 && !used[v] && dist[u] + g[u][v] < dist[v]) {
                dist[v] = dist[u] + g[u][v]; parent[v] = u;
            }
    }
    printf("Shortest routes from section %d:\n", source);
    for (i = 0; i < n; i++) {
        if (dist[i] == 999999) printf("Section %d: No route\n", i);
        else {
            int path[GRAPH_MAX], k = 0, x, z;
            x = i;
            while (x != -1 && k < GRAPH_MAX) { path[k++] = x; x = parent[x]; }
            printf("Section %d: Distance %d, Route ", i, dist[i]);
            for (z = k - 1; z >= 0; z--) printf("%d%s", path[z], z ? " -> " : "");
            printf("\n");
        }
    }
}

/* ---------------- EXPERIMENT 12: PRIM MINIMUM SPANNING TREE ---------------- */

void experiment12(void) {
    int n, g[GRAPH_MAX][GRAPH_MAX], key[GRAPH_MAX], parent[GRAPH_MAX];
    int chosen[GRAPH_MAX] = {0}, i, j, u, min, total = 0;
    printf("\n--- EXPERIMENT 12: MINIMUM-COST NETWORK FOR LIBRARY SECTIONS ---\n");
    printf("Enter number of library sections (max %d): ", GRAPH_MAX); scanf("%d", &n);
    if (n < 1 || n > GRAPH_MAX) { printf("Invalid size.\n"); return; }
    printf("Enter symmetric cable-cost matrix (0=no direct connection):\n");
    for (i = 0; i < n; i++)
        for (j = 0; j < n; j++) scanf("%d", &g[i][j]);
    for (i = 0; i < n; i++) { key[i] = 999999; parent[i] = -1; }
    key[0] = 0;
    for (i = 0; i < n; i++) {
        min = 999999; u = -1;
        for (j = 0; j < n; j++) if (!chosen[j] && key[j] < min) { min = key[j]; u = j; }
        if (u == -1) break;
        chosen[u] = 1;
        for (j = 0; j < n; j++)
            if (g[u][j] > 0 && !chosen[j] && g[u][j] < key[j]) {
                key[j] = g[u][j]; parent[j] = u;
            }
    }
    for (i = 1; i < n; i++) {
        if (parent[i] == -1) { printf("Sections are disconnected; spanning tree cannot be formed.\n"); return; }
    }
    printf("Minimum-cost connections:\n");
    for (i = 1; i < n; i++) {
        printf("Section %d - Section %d : Cost %d\n", parent[i], i, g[parent[i]][i]);
        total += g[parent[i]][i];
    }
    printf("Total minimum network cost = %d\n", total);
}

/* ---------------- EXPERIMENT 13: ISBN HASHING WITH OPEN ADDRESSING ---------------- */

int isbnTable[HASH_SIZE];
int isbnHash(int isbn) { return ((isbn % HASH_SIZE) + HASH_SIZE) % HASH_SIZE; }
void insertISBN(int isbn) {
    int i = isbnHash(isbn), start = i, deletedSlot = -1;
    do {
        if (isbnTable[i] == isbn) { printf("ISBN already exists at slot %d.\n", i); return; }
        if (isbnTable[i] == DELETED && deletedSlot == -1) deletedSlot = i;
        if (isbnTable[i] == EMPTY) {
            if (deletedSlot != -1) i = deletedSlot;
            isbnTable[i] = isbn;
            printf("ISBN stored at hash slot %d.\n", i);
            return;
        }
        i = (i + 1) % HASH_SIZE;
    } while (i != start);
    if (deletedSlot != -1) {
        isbnTable[deletedSlot] = isbn;
        printf("ISBN stored in reused slot %d.\n", deletedSlot);
    } else printf("Hash table overflow: no empty slot available.\n");
}
void searchISBN(int isbn) {
    int i = isbnHash(isbn), start = i;
    do {
        if (isbnTable[i] == EMPTY) { printf("ISBN not found.\n"); return; }
        if (isbnTable[i] == isbn) { printf("ISBN found at hash slot %d.\n", i); return; }
        i = (i + 1) % HASH_SIZE;
    } while (i != start);
    printf("ISBN not found.\n");
}
void deleteISBN(int isbn) {
    int i = isbnHash(isbn), start = i;
    do {
        if (isbnTable[i] == EMPTY) break;
        if (isbnTable[i] == isbn) {
            isbnTable[i] = DELETED;
            printf("ISBN deleted from hash slot %d.\n", i);
            return;
        }
        i = (i + 1) % HASH_SIZE;
    } while (i != start);
    printf("ISBN not found; nothing deleted.\n");
}
void displayISBNTable(void) {
    int i;
    printf("HASH SLOT : ISBN\n");
    for (i = 0; i < HASH_SIZE; i++) {
        if (isbnTable[i] == EMPTY) printf("%9d : EMPTY\n", i);
        else if (isbnTable[i] == DELETED) printf("%9d : DELETED\n", i);
        else printf("%9d : %d\n", i, isbnTable[i]);
    }
}
void experiment13(void) {
    int ch, isbn;
    do {
        printf("\n--- EXPERIMENT 13: ISBN LOOKUP USING HASHING ---\n");
        printf("1. Insert ISBN\n2. Search ISBN\n3. Delete ISBN\n4. Display hash table\n0. Back\nChoice: ");
        scanf("%d", &ch);
        if (ch >= 1 && ch <= 3) {
            printf("Enter ISBN as an integer: "); scanf("%d", &isbn);
            if (ch == 1) insertISBN(isbn);
            else if (ch == 2) searchISBN(isbn);
            else deleteISBN(isbn);
        } else if (ch == 4) displayISBNTable();
        else if (ch != 0) printf("Invalid choice.\n");
    } while (ch != 0);
}

/* ---------------- MAIN MENU: ALL 13 EXPERIMENTS ---------------- */

void cleanupMemory(void) {
    BookNode *b;
    StackNode *s;
    RequestNode *q;
    while (listHead) { b = listHead; listHead = listHead->next; free(b); }
    while (linkedTop) { s = linkedTop; linkedTop = linkedTop->next; free(s); }
    while (linkedFront) { q = linkedFront; linkedFront = linkedFront->next; free(q); }
    freeBST(bookRoot);
}

int main(void) {
    int choice, i;
    for (i = 0; i < HASH_SIZE; i++) isbnTable[i] = EMPTY;

    do {
        printf("\n============================================================\n");
        printf("       DIGITAL LIBRARY TEXTBOOK LOOKUP SYSTEM\n");
        printf("============================================================\n");
        printf(" 1. Book Records - Structures, Arrays, Functions, Pointers\n");
        printf(" 2. Textbook Search - Linear Search and Binary Search\n");
        printf(" 3. Textbook Sorting - Insertion, Quick and Merge Sort\n");
        printf(" 4. Book Catalogue - Linked List ADT\n");
        printf(" 5. Recently Viewed Books - Stack using Array and Linked List\n");
        printf(" 6. Book Issue Requests - Queue using Array and Linked List\n");
        printf(" 7. Undo Last Book Issue - Stack Application\n");
        printf(" 8. Book ID Organisation - Binary Search Tree and Traversals\n");
        printf(" 9. Acquisition Requests - Priority Queue and Heap Sort\n");
        printf("10. Related Textbooks - Graph Traversals and Topological Sort\n");
        printf("11. Library Section Route - Dijkstra Shortest Path\n");
        printf("12. Library Network - Prim Minimum Spanning Tree\n");
        printf("13. ISBN Lookup - Hashing using Open Addressing\n");
        printf(" 0. Exit\n");
        printf("============================================================\n");
        printf("Enter your experiment choice: ");
        if (scanf("%d", &choice) != 1) {
            printf("Invalid input. Restart the program and enter numbers only.\n");
            cleanupMemory();
            return 0;
        }

        switch (choice) {
            case 1: experiment1(); break;
            case 2: experiment2(); break;
            case 3: experiment3(); break;
            case 4: experiment4(); break;
            case 5: experiment5(); break;
            case 6: experiment6(); break;
            case 7: experiment7(); break;
            case 8: experiment8(); break;
            case 9: experiment9(); break;
            case 10: experiment10(); break;
            case 11: experiment11(); break;
            case 12: experiment12(); break;
            case 13: experiment13(); break;
            case 0: printf("Thank you for using Digital Library Textbook Lookup System.\n"); break;
            default: printf("Invalid menu choice. Select 0 to 13.\n");
        }
    } while (choice != 0);

    cleanupMemory();
    return 0;
}
