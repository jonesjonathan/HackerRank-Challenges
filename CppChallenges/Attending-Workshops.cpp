// https://www.hackerrank.com/challenges/attending-workshops

//Define the structs Workshops and Available_Workshops.
//Implement the functions initialize and CalculateMaxWorkshops

//HEURISTIC:
//Choose the workshops with the earliest end times first

struct Workshop {
    int start_time;
    int duration;
    int end_time;
};

struct Available_Workshops {
    int n;
    Workshop* workshops;
};

struct Node {
    Workshop workshop;
    Node* left;
    Node* right;
};

//Prototypes
Node* insert(Node*, Workshop); //Recursive function that inserts a node into a tree based on the duration of the workshop
Node* buildTree(Node*, Available_Workshops*);
void readTree(Node*, Available_Workshops*, int&);
Available_Workshops* initialize (int start_time[], int duration[], int n);
bool overlap(Workshop, Workshop);
int CalculateMaxWorkshops(Available_Workshops* ptr);

//Recursively inserts a node into the tree based on the end_time of the workshop
Node* insert(Node* node, Workshop workshop)
{
    if(node == NULL)
    {
        node = new Node();
        node->workshop = workshop;
        node->left = node->right = NULL;
    }
    else if(node->workshop.end_time >= workshop.end_time)
        node->left = insert(node->left, workshop);
    else
        node->right = insert(node->right, workshop);
    
    return node;
}

Node* buildTree(Node* root, Available_Workshops* aw)
{
    int size = aw->n;
    Workshop* ws = aw->workshops;
    for(int i = 0; i < size; i++)
        root = insert(root, ws[i]);
    return root;
}

//Does an in-order traversal of the tree and re-orders the workshop array to be in ascending order of duration
void readTree(Node* node, Available_Workshops* ws, int& pos)
{
    if(node == NULL)
        return;
    readTree(node->left, ws, pos);
    ws->workshops[pos++] = node->workshop;
    readTree(node->right, ws, pos);
}

/*
Creates an Available_Workshops object and initializes its elements using the elements in the start_time[] and duration[] parameters (both are of size n). Here, start_time[i] and duration[i] are the respective start time and duration for the ith workshop. This function must return a pointer to an Available_Workshops object.
*/
Available_Workshops* initialize (int start_time[], int duration[], int n)
{
    if(n < 1)
        return NULL;
    
    Available_Workshops* aws = new Available_Workshops();
    aws->n = n;
    Workshop* ws = new Workshop[n];
    for(int i = 0; i < n; i++)
    {
        int s_time = start_time[i];
        int d = duration[i];
        
        ws[i].start_time = s_time;
        ws[i].duration = d;
        ws[i].end_time = s_time + d;
    }
    
    aws->workshops = ws;
    
    return aws;
    
}

//Determines if two workshops overlap
bool overlap(Workshop x, Workshop y)
{
    return (x.end_time > y.start_time) && (y.end_time > x.start_time); 
}

/*
Returns the maximum number of workshops the student can attend—without overlap. The next workshop cannot be attended until the previous workshop ends. Uses a greedy algorithm with the earliest end_times as the focus
*/
int CalculateMaxWorkshops(Available_Workshops* ptr)
{
    int maxNum = 0, size = ptr->n, pos = 0;
    Workshop curr_ws;
    //Fill a tree of workshops based on end_times
    Node* ws_tree = NULL;
    ws_tree = buildTree(ws_tree, ptr);
    readTree(ws_tree, ptr, pos); //Sorts the available workshops based on end_times
    
    //Add first workshop
    maxNum++;
    curr_ws = ptr->workshops[0];
    for(int i = 1; i < size; i++)
    {
        if(!(overlap(curr_ws, ptr->workshops[i])))
        {
            curr_ws = ptr->workshops[i];
            maxNum++;
        }
    }
    
    return maxNum;
}
