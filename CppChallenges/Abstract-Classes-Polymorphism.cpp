//Need to handle cases
//1 Empty list
//2 Is head
//3 Is tail
//4 not head or tail

class LRUCache:public Cache
{
    private:
        int numNodes;
    public:
        //Constructor
        LRUCache(int capacity)
        {
            this->cp = capacity;
            this->tail = NULL;
            this->head = NULL;
            this->numNodes = 0;
        }
        void set(int key, int value)
        {
            //Check if list is empty
            if(this->mp.empty())
            {
                //cout << "Empty!";
                //Fill head & tail
                this->head = new Node(key, value);
                this->tail = this->head;
                //Enter into map
                //this->mp.insert(pair<int,Node*>(key,this->head));
                this->mp[key] = this->head;
                numNodes++;
            }
            else
            {
                //Check for cache hit
                map<int,Node*>::iterator it;
                it = this->mp.find(key);
                //If we found a key match (cache hit)
                if(it != this->mp.end())
                {
                    //Insert new value
                    it->second->value = value;
                    //If key is not head
                    if(it->second != this->head)
                    {
                        this->head->prev = it->second;
                        it->second->prev->next = it->second->next;
                        //If not tail
                        if(it->second->next != NULL)
                        {
                            it->second->next->prev = it->second->prev;
                        }
                        else
                        {
                            it->second->prev->next = NULL;
                            this->tail = this->tail->prev;
                        }
                        it->second->prev = NULL;
                        it->second->next = this->head;
                        this->head = it->second;
                    }
                }
                //Cache miss
                else
                {
                    //Make new node
                    Node* N = new Node(NULL, this->head, key, value);
                    //this->mp.insert(pair<int,Node*>(key, N));
                    this->mp[key] = N;
                    //If full capacity
                    if(this->cp == this->numNodes)
                    {
                        this->tail = this->tail->prev;
                        this->mp.erase(this->tail->next->key);
                        delete this->tail->next;
                        this->tail->next = NULL;
                        this->head->prev = N;
                        this->head = N;
                    }
                    else
                    {
                        this->head->prev = N;
                        this->head = N;
                        this->numNodes++;
                    }
                }
            }
        }
        int get(int key)
        {
            map<int,Node*>::iterator it;
            it = this->mp.find(key);
            if(it != this->mp.end())
                return it->second->value;
            return -1;
        }
};
