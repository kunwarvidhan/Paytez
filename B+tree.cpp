#include<bits/stdc++.h>
using namespace std;
#define MAX 50
struct details
{
    string password;
    string name;
    float balance;
    vector<float> history;
    FILE *f;
};
int numberOfPointers;
struct Block
{
    int tNodes;
    Block *parentBlock;
    int value[MAX];
    Block *childBlock[MAX];
    Block()
    {
        tNodes = 0;
        parentBlock = NULL;
        for(int i=0; i<MAX; i++)
        {
            value[i] = INT_MAX;
            childBlock[i] = NULL;
        }
    }
};
Block *rootBlock=new Block();
details cust[MAX];
bool validate(vector < Block* > Blocks,int no)
{
    vector < Block* > newBlocks;
    for(int i=0; i<Blocks.size(); i++)
    {
        Block *curBlock = Blocks[i];
        int j;
        for(j=0; j<curBlock->tNodes; j++)
        {
            if(curBlock->value[j]==no)
                return true;
            if(curBlock->childBlock[j]!=NULL)
            newBlocks.push_back(curBlock->childBlock[j]);
        }
        if(curBlock->value[j]==INT_MAX && curBlock->childBlock[j]!=NULL)
            newBlocks.push_back(curBlock->childBlock[j]);
    }

    if(newBlocks.size()==0)
    {
        puts("");
        puts("");
        Blocks.clear();
    }
    else
    {
        puts("");
        puts("");
        Blocks.clear();
        validate(newBlocks,no);
    }
    cout<<"User doesn't exist\n";
    return false;
}

bool add_account(vector<Block*>Blocks,int s)
{
    FILE *p,*file,*f2;
    int one=1,two=2,j1,j2;
    if(validate(Blocks,s)!=true)
    {
        char ar1[8],ar2[11];
        system("cls");
        int i=s/1000;
        p=fopen("input.txt", "a");
        fprintf(p,"\n%d %d\n%d",one,s,two);
        fclose(p);
        cout<<"Enter password,name in different lines"<<endl;
        cin>>cust[i].password>>cust[i].name;
        cust[i].balance=0.0;
        fflush(stdin);
        for(j1=0;j1<8;j1++)
        {
            ar1[j1]=cust[i].password[j1];
        }
        for(j2=0;j2<10;j2++)
        {
            ar2[j2]=cust[i].name[j2];
        }

        char buffer[32];
        snprintf(buffer, sizeof(char) * 32, "file%i.txt",i);
        file = fopen(buffer, "w");
        fclose(file);
        file = fopen(buffer, "a");
        f2=fopen("input1.txt","a");
        fprintf(f2,"%d %f %s %s\n",s,cust[i].balance,ar1,ar2);
        fclose(f2);
        /*while(fscanf(cust[i].f, "%d", &d)!=EOF)
        {
            cust[i].history.push_back(d);
        }*/
        return true;
    }
    else
    {
        cout<<"User already exists\nPlease login to proceed.\n\n\n";
        return false;
    }
}
void check_balance(vector<Block*> Blocks,int s)
{
    float bal=0.0;
    if(validate(Blocks,s)==true)
    {
        int i=s/1000,t;
        if(cust[i].history.size()>=1)
        {
            for(t=0;t<cust[i].history.size();t++)
            {
                bal+=cust[i].history[t];
            }
        }
        else
            cout<<"No recent transactions"<<endl;
        cout<<"Current Balance: "<<bal<<"\n";
        cout<<"Transaction History\n"<<endl;
        if(cust[i].history.size()>=1)
        {
            for(t=0;t<cust[i].history.size();t++)
            {
                cout<<cust[i].history[t]<<"\n";
            }
        }
        else
            cout<<"No recent transactions"<<endl;
    }
    else
    {
        system("cls");
        cout<<"error";
    }
}
bool login_validate(vector < Block* >Blocks,int no)
{
    int x=0,i;
    string p;
    if(validate(Blocks,no))
     {
        Y:cout<<"\tENTER PASSWORD:\n\t";
        cin>>p;
        i=no/1000;
        if(cust[i].password.compare(p)==0)
        {
            return true;
        }
        else
        {
            if(x<2)
            {
                cout<<"Wrong Password\nEnter password again"<<endl;
                x++;
                goto Y;
            }
            else
                return false;
        }
     }
    else
    {
        cout<<"Proceed to signup"<<endl;
    }
    return false;
}
void addBalance(int s,float transfer_amt)
{
    int i=s/1000;
    cust[i].balance+=transfer_amt;
    cust[i].history.push_back(transfer_amt);
    cout<<"Rs. "<<transfer_amt<<" added succesfully."<<endl;
}
void transaction(vector < Block* > Blocks,int s,int r,float transfer_amt)
{
    float transfer_amt1=-1*transfer_amt;
    if(validate(Blocks,r)==true)
    {
        int i=s/1000;
        int j=r/1000;
        if(cust[i].balance>transfer_amt)
        {
            cust[i].balance-=transfer_amt;
            cust[j].balance+=transfer_amt;
            cust[i].history.push_back(-1*transfer_amt);
            cust[j].history.push_back(transfer_amt);
            fprintf(cust[i].f,"\n%f",transfer_amt1);
            fprintf(cust[j].f,"\n%f",transfer_amt);
            cout<<"Paid Rs. "<<transfer_amt<<" succesfully"<<endl;
        }
        else
        {
            cout<<"Insufficient Balance"<<endl;
        }
    }
    else
        cout<<"Transaction Failed ";
}

void splitLeaf(Block *curBlock,Block *rootBlock){
    int x, i, j;
    if(numberOfPointers%2)
        x = (numberOfPointers+1)/2;
    else x = numberOfPointers/2;
    Block *rightBlock = new Block();
    curBlock->tNodes = x;
    rightBlock->tNodes = numberOfPointers-x;
    rightBlock->parentBlock = curBlock->parentBlock;
    for(i=x, j=0; i<numberOfPointers; i++, j++)
    {
        rightBlock->value[j] = curBlock->value[i];
        curBlock->value[i] = INT_MAX;
    }
    int val = rightBlock->value[0];
    if(curBlock->parentBlock==NULL)
    {
        Block *parentBlock = new Block();
        parentBlock->parentBlock = NULL;
        parentBlock->tNodes=1;
        parentBlock->value[0] = val;
        parentBlock->childBlock[0] = curBlock;
        parentBlock->childBlock[1] = rightBlock;
        curBlock->parentBlock = rightBlock->parentBlock = parentBlock;
        rootBlock = parentBlock;
        return;
    }
    else
    {
        curBlock = curBlock->parentBlock;
        Block *newChildBlock = new Block();
        newChildBlock = rightBlock;
        for(i=0; i<=curBlock->tNodes; i++)
        {
            if(val < curBlock->value[i])
            {
                swap(curBlock->value[i], val);
            }
        }
        curBlock->tNodes++;
        for(i=0; i<curBlock->tNodes; i++)
        {
            if(newChildBlock->value[0] < curBlock->childBlock[i]->value[0])
            {
                swap(curBlock->childBlock[i], newChildBlock);
            }
        }
        curBlock->childBlock[i] = newChildBlock;
        for(i=0;curBlock->childBlock[i]!=NULL;i++)
        {
            curBlock->childBlock[i]->parentBlock = curBlock;
        }
    }
}

void splitNonLeaf(Block *curBlock)
{
    int x, i, j;
    x = numberOfPointers/2;
    Block *rightBlock = new Block();
    curBlock->tNodes = x;
    rightBlock->tNodes = numberOfPointers-x-1;
    rightBlock->parentBlock = curBlock->parentBlock;
    for(i=x, j=0; i<=numberOfPointers; i++, j++)
    {
        rightBlock->value[j] = curBlock->value[i];
        rightBlock->childBlock[j] = curBlock->childBlock[i];
        curBlock->value[i] = INT_MAX;
        if(i!=x)curBlock->childBlock[i] = NULL;
    }
    int val = rightBlock->value[0];
    memcpy(&rightBlock->value, &rightBlock->value[1], sizeof(int)*(rightBlock->tNodes+1));
    memcpy(&rightBlock->childBlock, &rightBlock->childBlock[1], sizeof(rootBlock)*(rightBlock->tNodes+1));
    for(i=0;curBlock->childBlock[i]!=NULL;i++)
    {
        curBlock->childBlock[i]->parentBlock = curBlock;
    }
    for(i=0;rightBlock->childBlock[i]!=NULL;i++)
    {
        rightBlock->childBlock[i]->parentBlock = rightBlock;
    }
    if(curBlock->parentBlock==NULL)
    {
        Block *parentBlock = new Block();
        parentBlock->parentBlock = NULL;
        parentBlock->tNodes=1;
        parentBlock->value[0] = val;
        parentBlock->childBlock[0] = curBlock;
        parentBlock->childBlock[1] = rightBlock;
        curBlock->parentBlock = rightBlock->parentBlock = parentBlock;
        rootBlock = parentBlock;
        return;
    }
    else
    {
        curBlock = curBlock->parentBlock;
        Block *newChildBlock = new Block();
        newChildBlock = rightBlock;
        for(i=0; i<=curBlock->tNodes; i++)
        {
            if(val < curBlock->value[i])
            {
                swap(curBlock->value[i], val);
            }
        }
        curBlock->tNodes++;
        for(i=0; i<curBlock->tNodes; i++)
        {
            if(newChildBlock->value[0] < curBlock->childBlock[i]->value[0])
            {
                swap(curBlock->childBlock[i], newChildBlock);
            }
        }
        curBlock->childBlock[i] = newChildBlock;
        for(i=0;curBlock->childBlock[i]!=NULL;i++)
        {
            curBlock->childBlock[i]->parentBlock = curBlock;
        }
    }
}

void insertNode(Block *curBlock, int val)
{
    for(int i=0; i<=curBlock->tNodes; i++)
    {
        if(val < curBlock->value[i] && curBlock->childBlock[i]!=NULL)
        {
            insertNode(curBlock->childBlock[i], val);
            if(curBlock->tNodes==numberOfPointers)
                splitNonLeaf(curBlock);
            return;
        }
        else if(val < curBlock->value[i] && curBlock->childBlock[i]==NULL)
        {
            swap(curBlock->value[i], val);
            if(i==curBlock->tNodes)
            {
                    curBlock->tNodes++;
                    break;
            }
        }
    }
    if(curBlock->tNodes==numberOfPointers)
    {
        splitLeaf(curBlock,rootBlock);
    }
}

void redistributeBlock(Block *leftBlock, Block *rightBlock, bool isLeaf, int posOfLeftBlock, int whichOneisCurBlock )
{
    int PrevRightFirstVal = rightBlock->value[0];
    if(whichOneisCurBlock==0)
    {
        if(!isLeaf)
        {
            leftBlock->value[leftBlock->tNodes] = leftBlock->parentBlock->value[posOfLeftBlock];
            leftBlock->childBlock[leftBlock->tNodes+1] = rightBlock->childBlock[0];
            leftBlock->tNodes++;
            leftBlock->parentBlock->value[posOfLeftBlock] = rightBlock->value[0];
            memcpy(&rightBlock->value[0], &rightBlock->value[1], sizeof(int)*(rightBlock->tNodes+1));
            memcpy(&rightBlock->childBlock[0], &rightBlock->childBlock[1], sizeof(rootBlock)*(rightBlock->tNodes+1));
            rightBlock->tNodes--;
        }
        else
        {
            leftBlock->value[leftBlock->tNodes] = rightBlock->value[0];
            leftBlock->tNodes++;
            memcpy(&rightBlock->value[0], &rightBlock->value[1], sizeof(int)*(rightBlock->tNodes+1));
            rightBlock->tNodes--;
            leftBlock->parentBlock->value[posOfLeftBlock] = rightBlock->value[0];
        }
    }
    else
    {
        if(!isLeaf)
        {
            memcpy(&rightBlock->value[1], &rightBlock->value[0], sizeof(int)*(rightBlock->tNodes+1));
            memcpy(&rightBlock->childBlock[1], &rightBlock->childBlock[0], sizeof(rootBlock)*(rightBlock->tNodes+1));
            rightBlock->value[0] = leftBlock->parentBlock->value[posOfLeftBlock];
            rightBlock->childBlock[0] = leftBlock->childBlock[leftBlock->tNodes];
            rightBlock->tNodes++;
            leftBlock->parentBlock->value[posOfLeftBlock] = leftBlock->value[leftBlock->tNodes-1];
            leftBlock->value[leftBlock->tNodes-1] = INT_MAX;
            leftBlock->childBlock[leftBlock->tNodes] = NULL;
            leftBlock->tNodes--;
        }
        else
        {
            memcpy(&rightBlock->value[1], &rightBlock->value[0], sizeof(int)*(rightBlock->tNodes+1));
            rightBlock->value[0] = leftBlock->value[leftBlock->tNodes-1];
            rightBlock->tNodes++;
            leftBlock->value[leftBlock->tNodes-1] = INT_MAX;
            leftBlock->tNodes--;
            leftBlock->parentBlock->value[posOfLeftBlock] = rightBlock->value[0];
        }
    }
}

void mergeBlock(Block *leftBlock, Block *rightBlock, bool isLeaf, int posOfRightBlock)
{
    if(!isLeaf)
    {
        leftBlock->value[leftBlock->tNodes] = leftBlock->parentBlock->value[posOfRightBlock-1];
        leftBlock->tNodes++;
    }
    memcpy(&leftBlock->value[leftBlock->tNodes], &rightBlock->value[0], sizeof(int)*(rightBlock->tNodes+1));
    memcpy(&leftBlock->childBlock[leftBlock->tNodes], &rightBlock->childBlock[0], sizeof(rootBlock)*(rightBlock->tNodes+1));
    leftBlock->tNodes += rightBlock->tNodes;
    memcpy(&leftBlock->parentBlock->value[posOfRightBlock-1], &leftBlock->parentBlock->value[posOfRightBlock], sizeof(int)*(leftBlock->parentBlock->tNodes+1));
    memcpy(&leftBlock->parentBlock->childBlock[posOfRightBlock], &leftBlock->parentBlock->childBlock[posOfRightBlock+1], sizeof(rootBlock)*(leftBlock->parentBlock->tNodes+1));
    leftBlock->parentBlock->tNodes--;
    for(int i=0;leftBlock->childBlock[i]!=NULL;i++)
    {
        leftBlock->childBlock[i]->parentBlock = leftBlock;
    }
}
bool dataFound;
void deleteNode(Block *curBlock, int val, int curBlockPosition)
{
    bool isLeaf;
    if(curBlock->childBlock[0]==NULL)
        isLeaf = true;
    else
        isLeaf = false;
    int prevLeftMostVal = curBlock->value[0];
    for(int i=0;dataFound==false &&  i<=curBlock->tNodes; i++)
    {
        if(val < curBlock->value[i] && curBlock->childBlock[i] != NULL)
        {
            deleteNode(curBlock->childBlock[i], val, i);
        }
        else if(val == curBlock->value[i] && curBlock->childBlock[i] == NULL)
        {
            memcpy(&curBlock->value[i], &curBlock->value[i+1], sizeof(int)*(curBlock->tNodes+1));
            curBlock->tNodes--;
            dataFound = true;
            break;
        }
     }
     if(curBlock->parentBlock == NULL && curBlock->childBlock[0] == NULL)
     {
        return;
     }
    if(curBlock->parentBlock==NULL && curBlock->childBlock[0] != NULL && curBlock->tNodes == 0)
    {
        rootBlock = curBlock->childBlock[0];
        rootBlock->parentBlock = NULL;
        return;
    }
    if(isLeaf && curBlock->parentBlock!=NULL)
    {
        if(curBlockPosition==0)
        {
            Block *rightBlock = new Block();
            rightBlock = curBlock->parentBlock->childBlock[1];
            if(rightBlock!=NULL && rightBlock->tNodes > (numberOfPointers+1)/2)
            {
                redistributeBlock(curBlock, rightBlock, isLeaf, 0, 0);
            }
            else if (rightBlock!=NULL && curBlock->tNodes+rightBlock->tNodes < numberOfPointers)
            {
                mergeBlock(curBlock, rightBlock, isLeaf, 1);
            }
        }
        else
        {
            Block *leftBlock = new Block();
            Block *rightBlock = new Block();
            leftBlock = curBlock->parentBlock->childBlock[curBlockPosition-1];
            rightBlock = curBlock->parentBlock->childBlock[curBlockPosition+1];
            if(leftBlock!=NULL && leftBlock->tNodes > (numberOfPointers+1)/2)
            {
                 redistributeBlock(leftBlock, curBlock, isLeaf, curBlockPosition-1, 1);
            }
            else if(rightBlock!=NULL && rightBlock->tNodes > (numberOfPointers+1)/2)
            {
                redistributeBlock(curBlock, rightBlock, isLeaf, curBlockPosition, 0);
            }
            else if (leftBlock!=NULL && curBlock->tNodes+leftBlock->tNodes < numberOfPointers)
            {
                mergeBlock(leftBlock, curBlock, isLeaf, curBlockPosition);
            }
            else if (rightBlock!=NULL && curBlock->tNodes+rightBlock->tNodes < numberOfPointers)
            {
               mergeBlock(curBlock, rightBlock, isLeaf, curBlockPosition+1);
            }
        }
    }
    else if(!isLeaf && curBlock->parentBlock!=NULL)
    {
        if(curBlockPosition==0)
        {
            Block *rightBlock = new Block();
            rightBlock = curBlock->parentBlock->childBlock[1];
            if( rightBlock!=NULL && rightBlock->tNodes-1 >= ceil((numberOfPointers-1)/2) )
            {
                redistributeBlock(curBlock, rightBlock, isLeaf, 0, 0);
            }
            else if (rightBlock!=NULL && curBlock->tNodes+rightBlock->tNodes < numberOfPointers - 1)
            {
                mergeBlock(curBlock, rightBlock, isLeaf, 1);
            }
        }
        else
        {
            Block *leftBlock = new Block();
            Block *rightBlock = new Block();
            leftBlock = curBlock->parentBlock->childBlock[curBlockPosition-1];
            rightBlock = curBlock->parentBlock->childBlock[curBlockPosition+1];
            if( leftBlock!=NULL && leftBlock->tNodes-1 >= ceil((numberOfPointers-1)/2))
            {
                 redistributeBlock(leftBlock, curBlock, isLeaf, curBlockPosition-1, 1);
            }
            else if(rightBlock!=NULL && rightBlock->tNodes-1 >=  ceil((numberOfPointers-1)/2))
            {
                redistributeBlock(curBlock, rightBlock, isLeaf, curBlockPosition, 0);
            }
            else if ( leftBlock!=NULL && curBlock->tNodes+leftBlock->tNodes < numberOfPointers-1)
            {
                mergeBlock(leftBlock, curBlock, isLeaf, curBlockPosition);
            }
            else if ( rightBlock!=NULL && curBlock->tNodes+rightBlock->tNodes < numberOfPointers-1)
            {
               mergeBlock(curBlock, rightBlock, isLeaf, curBlockPosition+1);
            }
        }
    }
    Block *tempBlock = new Block();
    tempBlock = curBlock->parentBlock;
    while(tempBlock!=NULL)
    {
        for(int i=0; i<tempBlock->tNodes;i++)
        {
            if(tempBlock->value[i]==prevLeftMostVal)
            {
                tempBlock->value[i] = curBlock->value[0];
                break;
            }
        }
        tempBlock = tempBlock->parentBlock;
    }
}

void print(vector < Block* > Blocks)
{
    vector < Block* > newBlocks;
    for(int i=0; i<Blocks.size(); i++)
    {
        Block *curBlock = Blocks[i];
        cout <<"[|";
        int j;
        for(j=0; j<curBlock->tNodes; j++)
        {
            cout << curBlock->value[j] << "|";
            if(curBlock->childBlock[j]!=NULL)
            newBlocks.push_back(curBlock->childBlock[j]);
        }
        if(curBlock->value[j]==INT_MAX && curBlock->childBlock[j]!=NULL)
            newBlocks.push_back(curBlock->childBlock[j]);

        cout << "]  ";
    }
    if(newBlocks.size()==0)
    {
        puts("");
        puts("");
        Blocks.clear();
    }
    else
    {
        puts("");
        puts("");
        Blocks.clear();
        print(newBlocks);
    }
}
void menu(vector<Block*>Blocks,int s)
{
    int c_t,r,t;
    char temp;
    system("cls");
    cout<<"\t\t\tPAYTEZZ"<<endl;
    cout<<"    Welcome "<<cust[s/1000].name;
    do
    {
        cout<<"\n\t1)Check Balance\n\t2)Pay\n\t3)Add Balance\n\t0)Exit\n\tEnter your choice: ";
        cin>>c_t;
        switch(c_t)
        {
            case 1:
                check_balance(Blocks,s);
                cout<<"Press any key to continue ";
                cin>>temp;
                break;
            case 2:
                cout<<"ENTER THE NUMBER OF RECIEVER:";
                cin>>r;
                cout<<"\nENTER AMOUNT:";
                cin>>t;
                transaction(Blocks,s,r,t);
                cout<<"Press any key to continue ";
                cin>>temp;
                break;
            case 3:
                cout<<"\nENTER AMOUNT:";
                cin>>t;
                addBalance(s,t);
                cout<<"Press any key to continue ";
                cin>>temp;
                break;
            case 0:
                break;
        }
    }while(c_t!=0);
}
void initialise()
{
    FILE *ptr;
    int d1;
    float f,f1;
    char s1[10],s2[10];
    cust[1].password="asdfgh";
    cust[1].balance=1000.0;
    cust[1].name="A";
    cust[1].f= fopen("A.txt", "r");
    while(fscanf(cust[1].f, "%f", &f)!=EOF)
    {
        cust[1].history.push_back(f);
    }
    fclose(cust[1].f);
    cust[1].f= fopen("A.txt", "a");

    cust[2].password="123456";
    cust[2].balance=2000.0;
    cust[2].name="B";
    cust[2].f= fopen("B.txt", "r");
    while(fscanf(cust[2].f, "%f", &f)!=EOF)
    {
        cust[2].history.push_back(f);
    }
    fclose(cust[2].f);
    cust[2].f= fopen("B.txt", "a");

    cust[4].password="qwerty";
    cust[4].balance=3000.0;
    cust[4].name="C";
    cust[4].f= fopen("C.txt", "r");
    while(fscanf(cust[4].f, "%f", &f)!=EOF)
    {
        cust[4].history.push_back(f);
    }
    fclose(cust[4].f);
    cust[4].f= fopen("C.txt", "a");

    cust[5].password="yuiop";
    cust[5].balance=900.0;
    cust[5].name="D";
    cust[5].f= fopen("D.txt", "r");
    while(fscanf(cust[5].f, "%f", &f)!=EOF)
    {
        cust[5].history.push_back(f);
    }
    fclose(cust[5].f);
    cust[5].f= fopen("D.txt", "a");

    cust[6].password="zxcvb";
    cust[6].balance=600.0;
    cust[6].name="E";
    cust[6].f= fopen("E.txt", "r");
    while(fscanf(cust[6].f, "%f", &f)!=EOF)
    {
        cust[6].history.push_back(f);
    }
    fclose(cust[6].f);
    cust[6].f= fopen("E.txt", "a");

    cust[10].password="aditi123";
    cust[10].balance=2500.0;
    cust[10].name="Aditi";
    cust[10].f= fopen("ADITI.txt", "r");
    while(fscanf(cust[10].f, "%f", &f)!=EOF)
    {
        cust[10].history.push_back(f);
    }
    fclose(cust[10].f);
    cust[10].f= fopen("ADITI.txt", "a");

    cust[16].password="kunwar123";
    cust[16].balance=2300.0;
    cust[16].name="Kunwar";
    cust[16].f= fopen("KUNWAR.txt", "r");
    while(fscanf(cust[16].f, "%f", &f)!=EOF)
    {
        cust[16].history.push_back(f);
    }
    fclose(cust[16].f);
    cust[16].f= fopen("KUNWAR.txt", "a");

    cust[21].password="sid123456";
    cust[21].balance=2510.0;
    cust[21].name="Siddarth";
    cust[21].f= fopen("SIDDHARTH.txt", "r");
    while(fscanf(cust[21].f, "%f", &f)!=EOF)
    {
        cust[21].history.push_back(f);
    }
    fclose(cust[21].f);
    cust[21].f= fopen("SIDDHARTH.txt", "a");

    cust[29].password="arpit123";
    cust[29].balance=2750.0;
    cust[29].name="Arpit";
    cust[29].f= fopen("ARPIT.txt", "r");
    while(fscanf(cust[29].f, "%f", &f)!=EOF)
    {
        cust[29].history.push_back(f);
    }
    fclose(cust[29].f);
    cust[29].f= fopen("ARPIT.txt", "a");

    cust[37].password="praveen123";
    cust[37].balance=2790.0;
    cust[37].name="Praveen";
    cust[37].f= fopen("PRAVEEN.txt", "r");
    while(fscanf(cust[37].f, "%f", &f)!=EOF)
    {
        cust[37].history.push_back(f);
    }
    fclose(cust[37].f);
    cust[37].f= fopen("PRAVEEN.txt", "a");

    cust[41].password="prateek123";
    cust[41].balance=1500.0;
    cust[41].name="Prateek";
    cust[41].f= fopen("PRATEEK.txt", "r");
    while(fscanf(cust[41].f, "%f", &f)!=EOF)
    {
        cust[41].history.push_back(f);
    }
    fclose(cust[41].f);
    cust[41].f= fopen("PRATEEK.txt", "a");

    cust[47].password="amogh1234";
    cust[47].balance=2580.0;
    cust[47].name="Amogh";
    cust[47].f= fopen("AMOGH.txt", "r");
    while(fscanf(cust[47].f, "%f", &f)!=EOF)
    {
        cust[47].history.push_back(f);
    }
    fclose(cust[47].f);
    cust[47].f= fopen("AMOGH.txt", "a");
    ptr=fopen("input1.txt","r");
    while(fscanf(ptr,"%d %f %s %s",&d1,&f,s1,s2)!=EOF)
    {
        int t=d1/1000;
        cust[t].balance=f;
        cust[t].password=s1;
        cust[t].name=s2;
        insertNode(rootBlock,d1);
    }
}
int main()
{
    initialise();
    int num[50];
    numberOfPointers=16;
    FILE *p;
    p = fopen("input.txt", "r");
    vector < Block* > Blocks;
    int ch;
    int i = 0;
    int totalValues = 0;
    while(fscanf(p, "%d", &ch)!=EOF)
    {
        if(ch==1){
            fscanf(p, "%d", &num[i]);
            printf("**** Insert %d ****\n\n", num[i]);
            insertNode(rootBlock, num[i]);
            i++;
            totalValues++;

        }else if(ch==2){
            Blocks.clear();
            Blocks.push_back(rootBlock);
            print(Blocks);
            puts("");

        }else if(ch==3) {
            int val;
            fscanf(p, "%d", &val);
            if(totalValues==0) {
                printf("Sorry! There is no more data to be deleted!!");
                continue;

            }
            printf("---- Delete %d ----\n\n", val);
            dataFound = false;
            deleteNode(rootBlock, val, 0);
            totalValues--;
        }
    }
int l_s;
int phno;
do
{
system("cls");
x:cout<<"\t\t\tPAYTEZZ"<<endl;
cout<<"\tMENU"<<endl;
cout<<"1)Login\n2)Signup\n0)Exit\nEnter your choice: ";
cin>>l_s;
switch(l_s)
{
    case 1:
        {system("cls");
        cout<<"\t\t\tPAYTEZZ"<<endl;
        string pass;
        cout<<"\tENTER PHONE:\n\t";
        cin>>phno;
        if(login_validate(Blocks,phno))
            menu(Blocks,phno);
        else
            goto x;
        break;
        }
    case 2:

            system("cls");
            cout<<"\t\t\tPAYTEZZ"<<endl;
            cout<<"\tENTER PHONE:\n\t";

            scanf("%d", &phno);
            add_account(Blocks,phno);
            insertNode(rootBlock, phno);
            Blocks.clear();
            Blocks.push_back(rootBlock);
            menu(Blocks,phno);
            break;
           }
}while(l_s!=0);
    return 0;

}
