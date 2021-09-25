#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

#include "BTREE.h"

void BTreeInit(int _t);
void traverse();
BTreeNode* search(int k);
BTreeNode* _createNode(bool _leaf);
void _traverse(BTreeNode* present);
BTreeNode* _search(BTreeNode* present, int k);
void insertElement(int k);

void _insert(BTreeNode* present, int k)
{
	// Initialize index as index of rightmost element
	int i = present->n;
	// If this is a leaf node
	if (present->leaf == true)
	{
		//-------------------------------------------------------------------------------------------------------
		//Write your code.
		int j = 0, m;
		while(j < present->n && k > present->keys[j])
			j++;
        int * tmp = (int*)malloc(sizeof(int)*(i-j+1));
		for(m = 0; m < i-j+1; m++)
			tmp[m] = present->keys[j+m];
		present->keys[j] = k;
		for(m = j+1; m < i+2; m++)
			present->keys[m] = tmp[m-j-1];
		present->n++;
		free(tmp);
		_balancing(present);
		//-------------------------------------------------------------------------------------------------------
	}
	else // If this node is not leaf
	{
		//-------------------------------------------------------------------------------------------------------
		//Write your code.
		int j=0;
		while (j < present->n && k > present->keys[j])
			j++;
		_insert(present->C[j], k);
		//-------------------------------------------------------------------------------------------------------
	}
}

void _balancing(BTreeNode* present);
BTreeNode * _splitChild(BTreeNode* present);
void removeElement(int k);

void _remove(BTreeNode* present, int k)
{
	//-------------------------------------------------------------------------------------------------------
	//Write your code.
	int i = 0;
	while (i < present->n && k > present->keys[i])
		i++;

    if(present->leaf ==true&&present->keys[i] == k)
    {
        int j, m;
        j = present->n;
        for(m = i; m < j-1; m++)
            present->keys[m] = present->keys[m+1];
            present->n--;
            _balancingAfterDel(present);
            return;
    }
    else if(present->keys[i] == k)
    {
            present->keys[i] = findReplaceKey(present->C[i]);
            _remove(present->C[i], present->keys[i]);
            return;
    }
    else
    {
            if(present->leaf==false)
                _remove(present->C[i], k);
            else{
                _balancingAfterDel(present);
                return;
            }
    }
	//-------------------------------------------------------------------------------------------------------
}

int findReplaceKey(BTreeNode* present);
void _balancingAfterDel(BTreeNode* present);
void _borrowFromRight(BTreeNode* present, int parentIdx);
void _borrowFromLeft(BTreeNode* present, int parentIdx);
BTreeNode* _merge(BTreeNode* present);
int _getLevel(BTreeNode* present);
void _getNumberOfNodes(BTreeNode* present, int* numNodes, int level);
void _mappingNodes(BTreeNode* present, BTreeNode ***nodePtr, int* numNodes, int level);
void printTree();
