#include<iostream>
#include<queue>
using namespace std;
class node{
    public:
    int data;
    node* left;
    node* right;
    node(int d)
    {
        data=d;
        left=NULL;
        right=NULL;
    }
};

node* buildtree()
{
    int data;
    cin>>data;
    if(data==-1)
    {
        return NULL;
    }
    node* root=new node(data);
    root->left=buildtree();
    root->right=buildtree();
    return root;
}

int height(node* root)
{
    if(root==NULL)
    {
        return 0;
    }
    int hl=height(root->left);
    int hr=height(root->right);
    return max(hl,hr) + 1;
}

void printkthlevel(node* root, int k)
{
    if(root==NULL)
    {
        return;
    }
    if(k==1)
    {
        cout<<root->data<<" ";
        return;
    }
    printkthlevel(root->left,k-1);
    printkthlevel(root->right,k-1);
    return;
}

void printlevelOrder(node * root)
{
    int h=height(root);
    for(int i=1;i<=h;i++)
    {
        printkthlevel(root,i);
        cout<<endl;
    }
}
void bfs(node* root)
{
    queue<node*> q;
    q.push(root);
    while(!q.empty())
    {
        node * f=q.front();
        q.pop();
        cout<<f->data<<" , ";
        if(f->left)
        {
            q.push(f->left);
        }
       if(f->right)
        {
            q.push(f->right);
        }
    }
    return;
}
void PreOrder(node* root)
{
    if(root==NULL)
    {
        return;
    }
    cout<<root->data<<" ";
    PreOrder(root->left);
    PreOrder(root->right);
}

void levelorder(node* root)
{
   queue<node*> q;
   if(root==NULL)
   {
       return;
   }
   q.push(root);
   while(q.empty()==false)
   {
        int numofnodes=q.size();
        while(numofnodes > 0)
        {
            node* f=q.front();
            cout<<f->data<<" ";
            q.pop();
            if(f->left)
            {
                q.push(f->left);
            }
            if(f->right)
            {
                q.push(f->right);
            }
            numofnodes--;
        }
        cout<<endl;
   }
}

int countnodes(node* root)
{
    if(root==NULL)
    {
     return 0;
    }
    return 1+countnodes(root->left)+countnodes(root->right);
}

int sumofnodes(node* root)
{
    if(root==NULL)
    {
        return 0;
    }
    int lsum=sumofnodes(root->left);
    int rsum=sumofnodes(root->right);
    return lsum+rsum+root->data;
}

int diameter(node* root)
{
    if(root==NULL)
    {
        return 0;
    }
    int h1=height(root->left);
    int h2=height(root->right);
    int op1=h1+h2;
    int op2=diameter(root->left);
    int op3=diameter(root->right);
    return max(op1,max(op2,op3));
}

void insertnode(node* &root,int key)
{
    queue<node*> q;
    q.push(root);
    while(q.empty()==false)
    {
        node* f=q.front();
        q.pop();
        if(!f->left)
        {
            f->left=new node(key);
            break;
        }
        else
        {
            q.push(f->left);
        }
        if(!f->right)
        {
            f->right=new node(key);
            break;
        }
        else
            q.push(f->right);
    }
}

void deletedeepright(node* root,node* nodetobedeleted)
{
   queue<node*> q;
   q.push(root);
   node* temp;
   while(!q.empty())
   {
       temp=q.front();
       if(temp==nodetobedeleted)
       {
           temp=NULL;
           delete(nodetobedeleted);
           return;
       }
       if(temp->left)
       {
           if(temp->left==nodetobedeleted)
           {
           temp=NULL;
           delete(nodetobedeleted);
           return;
           }
           else
           {
               q.push(temp->left);
           }
       }
       if(temp->right)
       {
           if(temp->right==nodetobedeleted)
           {
           temp=NULL;
           delete(nodetobedeleted);
           return;
           }
           else
           {
               q.push(temp->right);
           }
       }
   }
}

node* deletenode(node* &root,int key)
{
    if(root==NULL)
    {
        return NULL;
    }
    if(root->left==NULL && root->right==NULL)
    {
        if(root->data==key)
        {
            return NULL;
        }
        else
            return root;
    }
    node* temp;
    node* key_node=NULL;
    queue<node*> q;
    q.push(root);

    while(!q.empty())
    {
        temp=q.front();
        q.pop();
        if(temp->data==key)
        {
            key_node=temp;
        }
        if(temp->left)
        {
            q.push(temp->left);
        }
        if(temp->right)
        {
            q.push(temp->right);
        }
    }
    if(key_node!=NULL)
    {
        int x=temp->data;
        deletedeepright(root,temp);
        key_node->data=x;
    }
    return root;
}

class HBPair{
    public:
    int height;
    bool isBalance;
};

HBPair isBalanced(node* root)
{
    HBPair p;
    if(root==NULL)
    {
        p.height=0;
        p.isBalance=true;
        return p;
    }
    HBPair left=isBalanced(root->left);
    HBPair right=isBalanced(root->right);
    p.height=max(left.height,right.height)+1;
    if(abs(left.height-right.height)<=1 && left.isBalance && right.isBalance)
    {
        p.isBalance=true;
    }
    else
        p.isBalance=false;
    return p;
}
int l=0;
node* skewtree(int arr[],int n)     //Create a tree from an array
{
    int data=arr[l];
    if(l==n)
    {
        return NULL;
    }
    node* root=new node(data);
    l++;
    root->right=skewtree(arr,n);
    return root;
}

node* buildtreefromarray(int arr[],int start,int end)   //Height Balanced Tree from an Array
{
    if(start>end)
    {
        return NULL;
    }
    int mid=(start+end)/2;
    node* root=new node(arr[mid]);
    root->left=buildtreefromarray(arr,start,mid-1);
    root->right=buildtreefromarray(arr,mid+1,end);
    return root;
}

node* insertinBst(node* root,int data)
{
    if(root==NULL)      // B A S E   C A S E
    {
        return new node(data);
    }
    if(data < root->data)         // R E C   C A S E
    {
        root->left=insertinBst(root->left,data);
    }
    else
        root->right=insertinBst(root->right,data);
    return root;
}

node* buildBst()
{
    int data;
    cin>>data;
    node* root=NULL;
    while(data!=-1)
    {
        root=insertinBst(root,data);
        cin>>data;
    }
    return root;
}

node* deleteBSTnode(node* root,int data)
{
    if(root==NULL)
    {
        return NULL;
    }
    if(root->data==data)
    {
        // 0 CHILD
        if(!root->left && !root->right)
        {
            delete root;
            return NULL;

        }
        // 1 CHILD
        if(!root->left)
        {
            node* temp=root->right;
            delete root;
            return temp;
        }
        if(!root->right)
        {
            node* temp=root->left;
            delete root;
            return temp;
        }
        // 2 CHILD

    }
}
bool searchBst(node* root,int data)
{
    if(root==NULL)
    {
        return false;
    }
    if(root->data==data)
    {
        return true;
    }
    if(data<=root->data)
    {
        return searchBst(root->left,data);
    }
    else
        return searchBst(root->right,data);
}

int main()
{
    node* root = buildtree();
    levelorder(root);
    return 0;
}
