#include <iostream>
#include <cstdlib>
#include <cmath>
#include <string.h>
#include "heap.h"

using namespace std;

    bool TreeNode::operator < (const TreeNode& anotherNode) 
	{
        return (this->key < anotherNode.key);
    }
    
    bool TreeNode::operator > (const TreeNode& anotherNode) 
	{
        return (this->key > anotherNode.key);;
    }
    bool TreeNode::operator == (const TreeNode& anotherNode) 
    {
        return (this->key == anotherNode.key);
    }   
    bool TreeNode::isLeaf()
    {
        return (leftChild == NULL && rightChild == NULL);
    }  
    void TreeNode::swapNodes(TreeNode * e)
    {
        if(e && this)
        {
            string temp1 = this->key;
            int temp2 = this->value;
            this->key = e->key;
            this->value = e->value;
            e->key = temp1;
            e->value = temp2;
        } 
        else
            cout << "swap called with NULL nodes" << endl;      
    }
    BinaryHeap::BinaryHeap(bool isMaxHeap) 
	{
        this->isMaxHeap = isMaxHeap;
        this->root = nullptr;
        this->heapSize = 0;
    }
    void BinaryHeap::heapify(int size, TreeNode * nodes) 
	{
        // implemented in main
    }
    int BinaryHeap::maxHeight(int n)
    {
        return log(n)/log(2);
    }
    char * BinaryHeap::bitString(int bitmap)
    {
        unsigned int q = bitmap;
        int r = 0;
        char * result = (char*)malloc(sizeof(char) * 50);
        int i = 0;
        while( q != 0)
        {
            r = q%2;
            q = q/2;
            *(result+i) = r + '0';
            i++;
        }
        *(result + i) = '\0';
        char * temp = strdup(result);
        int t = 0;
        int y = strlen(result) - 1;
        while( *(temp+t) != '\0')
            *(result+y--) = *(temp+t++);
        *(result+t) = '\0';
        return result;
    }
    bool BinaryHeap::insert(TreeNode * node) 
	{
        if (root == NULL)
        {
            root = node;
            heapSize++;
            return true;
        }
        int loc = ++heapSize;
        char * path = bitString(loc);
        //cout << "path = " << path<<endl;
        TreeNode * e = root;
        TreeNode * ep = NULL;
        for(int i = 1; i < strlen(path); i++)
        {
            ep = e;
            if(path[i] == '1')
                e = e->rightChild;
            else
                e = e->leftChild;
        }
        e = node;
        if(path[strlen(path)-1] == '0')
            ep->leftChild = node;
        else
            ep->rightChild = node;
        node->parent = ep;
        upheap(node);
    }
    void BinaryHeap::upheap(TreeNode * a)
    {
        TreeNode * p = a->parent;
        while( p && (isMaxHeap? *p < *a : *p > *a) )//max heap for now
        {
            p->swapNodes(a);
            a = p; 
            p = a->parent;
        }
    }
    void BinaryHeap::printTree(TreeNode * e)
    {
        //TreeNode * p = root;
        if (e->leftChild) 
            printTree(e->leftChild);
        std::cout << e->key << ' ' << endl;
        if (e->rightChild) 
            printTree(e->rightChild);
    }
    TreeNode * BinaryHeap::extract() 
	{
        TreeNode * last = root;
        char * path = bitString(heapSize--);
        for(int i = 1; i < strlen(path); i++)
        {
            if(path[i] == '1')
                last = last->rightChild;
            else
                last = last->leftChild;
        }
        last->swapNodes(root); //root and last node swapped
        TreeNode * result = last;
        if(last == root)
            root = NULL;
        else if(last == last->parent->leftChild)
            last->parent->leftChild = NULL;
        else
            last->parent->rightChild = NULL;
        downheap();
        return result;        
    }
    TreeNode * BinaryHeap::peek()
    {
        if(root)
            return new TreeNode(root->key, root->value);
        else
            return NULL;
    }
    void BinaryHeap::downheap()
    {
        TreeNode * e = root;
        while( e && !e->isLeaf() )
        {
            TreeNode * l = e->leftChild;
            TreeNode * r = e->rightChild;
            TreeNode * maxORmin;
            if( l && (isMaxHeap? *l > *e : *l < *e) )
                maxORmin = l;
            else
                maxORmin = e;
            if( r && ( isMaxHeap? *r > *maxORmin : *r < *maxORmin) )
                maxORmin = r;
            if( maxORmin == e )
                break;
            else
                e->swapNodes( maxORmin);
            e = maxORmin;
        }
    }
    int BinaryHeap::size() 
	{
        return heapSize;
    }
