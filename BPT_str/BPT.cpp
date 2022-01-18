#include "bpt_header.h"

#ifndef MAX
#define D 2
#define MAX 3
#endif

BPTree::BPTree() {
  root = NULL;
}

// Search operation
string BPTree::search(string x) {
	if (root == NULL)
		return "empty";
		
	else {
		Node *cursor = root;
		while (cursor->IS_LEAF == false)
		{
			for (int i = 0; i < cursor->size; i++)
			{
				if (x < cursor->key[i]) 
				{
					cursor = cursor->ptr[i];
					break;
				}
				if (i == cursor->size - 1) 
				{
					cursor = cursor->ptr[i + 1];
					break;
				}
			}
		}
		for (int i = 0; i < cursor->size; i++) 
		{
			if (cursor->key[i] == x) 
			{
				// cout << "Found\n";
				return cursor->meaning[i];
			}
		}
		return "not found";
		// cout << "Not found\n";
	}
	return "not found";
}

// Insert Operation
bool BPTree::insert(string x, string val) 
{
    if (root == NULL) 
    {
        root = new Node;
        root->key[0] = x;
		root->meaning[0]= val;
        root->IS_LEAF = true;
        root->size = 1;

		return 1;
    } 
    else 
	{
		Node *cursor = root;
		Node *parent;
		while (cursor->IS_LEAF == false) 
		{
			parent = cursor;
			for (int i = 0; i < cursor->size; i++) 
			{
				if (x < cursor->key[i]) 
				{
					cursor = cursor->ptr[i];
					break;
				}
				if (i == cursor->size - 1) 
				{
					cursor = cursor->ptr[i + 1];
					break;
				}
			}
		}
		if (cursor->size < MAX) 	//if no overflow
		{
			int i = 0;
			while (x > cursor->key[i] && i < cursor->size)
				i++;
			for (int j = cursor->size; j > i; j--)	// moving every element after inserted element to right
			{	
				cursor->key[j] = cursor->key[j - 1];
				cursor->meaning[j]= cursor->meaning[j-1];
			}

			cursor->key[i] = x;
			cursor->meaning[i]= val;
			cursor->size++;
			cursor->ptr[cursor->size] = cursor->ptr[cursor->size - 1];		//moving the previous last pointer
			cursor->ptr[cursor->size - 1] = NULL;
		} 

		else 		// in case of overflow
		{
			Node *newLeaf = new Node;
			// creating a container for new node
			string virtualNode[MAX + 1 + D];
			string virtualMeaning[MAX + 1 + D];
			for (int i = 0; i < MAX; i++)
			{
				virtualNode[i] = cursor->key[i];
				virtualMeaning[i] = cursor->meaning[i];
			}

			int i = 0, j;
			while (x > virtualNode[i] && i < MAX)
				i++;
			for (int j = MAX + 1; j > i; j--)
			{
				virtualNode[j] = virtualNode[j - 1];
				virtualMeaning[j] = virtualMeaning[j-1];
			}

			virtualNode[i] = x;
			virtualMeaning[i] = val;
			newLeaf->IS_LEAF = true;

			//after splitting size
			cursor->size = (MAX + 1) / 2;
			newLeaf->size = MAX + 1 - (MAX + 1) / 2;
			//linking leaf nodes
			cursor->ptr[cursor->size] = newLeaf;
			newLeaf->ptr[newLeaf->size] = cursor->ptr[MAX];
			cursor->ptr[MAX] = NULL;

			for (i = 0; i < cursor->size; i++)
			{
				cursor->key[i] = virtualNode[i];
				cursor->meaning[i] = virtualMeaning[i];
			}

			for (i = 0, j = cursor->size; i < newLeaf->size; i++, j++)
			{
				newLeaf->key[i] = virtualNode[j];
				newLeaf->meaning[i] = virtualMeaning[j];
			}

			if (cursor == root) 	//if cursor was root, create a new root
			{
				Node *newRoot = new Node;
				newRoot->key[0] = newLeaf->key[0];
				newLeaf->meaning[0] = newLeaf->meaning[0];
				newRoot->ptr[0] = cursor;
				newRoot->ptr[1] = newLeaf;
				newRoot->IS_LEAF = false;
				newRoot->size = 1;
				root = newRoot;
			} 
			else 
				insertInternal(newLeaf->key[0], newLeaf->meaning[0], parent, newLeaf);
		}
		return 1;
    }
	return 0;
}

// Insert Operation
void BPTree::insertInternal(string x, string val, Node *cursor, Node *child) 
{
	if (cursor->size < MAX) //if the non-leaf node doesn't overflow
	{
		int i = 0;
		while (x > cursor->key[i] && i < cursor->size)
			i++;
		for (int j = cursor->size; j > i; j--)
			cursor->key[j] = cursor->key[j - 1];

		for (int j = cursor->size + 1; j > i + 1; j--)
			cursor->ptr[j] = cursor->ptr[j - 1];

		cursor->key[i] = x;
		cursor->meaning[i]= val;
		cursor->size++;
		cursor->ptr[i + 1] = child;
	} 
	else 	//if the non-leaf node overflows
	{
		Node *newInternal = new Node;
		string virtualKey[MAX + 1 + D];
		string virtualMeaning[MAX+ 1 + D];
		Node *virtualPtr[MAX + 2 + D];

		for (int i = 0; i < MAX; i++)
		{
			virtualKey[i] = cursor->key[i];
			virtualMeaning[i] = cursor->meaning[i];
		}

		for (int i = 0; i < MAX + 1; i++)
			virtualPtr[i] = cursor->ptr[i];
		
		int i = 0, j;

		while (x > virtualKey[i] && i < MAX)
			i++;
		int ic= i;	
		for (int j = MAX + 1; j > i; j--)
		{
			virtualKey[j] = virtualKey[j - 1];
			virtualMeaning[j] = virtualMeaning[j-1];
		}

		virtualKey[i] = x;
		virtualMeaning[i] = val;

		newInternal->IS_LEAF = false;
		cursor->size = (MAX + 1) / 2;
		newInternal->size = MAX - (MAX + 1) / 2;

		for(int i=0; i<cursor->size+1; i++)
		{
			cursor->key[i]= virtualKey[i];
			cursor->meaning[i] = virtualMeaning[i];
		}
		for (i = 0, j = cursor->size + 1; i < newInternal->size; i++, j++)
		{
			newInternal->key[i] = virtualKey[j];
			newInternal->meaning[i] = virtualMeaning[j];
		}

		for (int j = MAX + 2; j > ic+1; j--)
			virtualPtr[j] = virtualPtr[j - 1];
		// Debug(child->key[0]);
		// Debug(i);
		virtualPtr[ic+1] = child;
		
		for(int i=0; i<cursor->size+1; i++)
			cursor->ptr[i]= virtualPtr[i];
		for (i = 0, j = cursor->size + 1; i < newInternal->size + 1; i++, j++)
			newInternal->ptr[i] = virtualPtr[j];

		if (cursor == root) //if overflown internal node was root u need new root
		{
			Node *newRoot = new Node;
			newRoot->key[0] = virtualKey[cursor->size];
			newRoot->meaning[0] = virtualMeaning[cursor->size];
			newRoot->ptr[0] = cursor;
			newRoot->ptr[1] = newInternal;
			newRoot->IS_LEAF = false;
			newRoot->size = 1;
			root = newRoot;
		} 
		else
			insertInternal(cursor->key[cursor->size], cursor->meaning[cursor->size], findParent(root, cursor), newInternal);

	}
}

// Find the parent
Node *BPTree::findParent(Node *cursor, Node *child) {
  Node *parent;
  if (cursor->IS_LEAF || (cursor->ptr[0])->IS_LEAF) {
    return NULL;
  }
  for (int i = 0; i < cursor->size + 1; i++) {
    if (cursor->ptr[i] == child) {
      parent = cursor;
      return parent;
    } else {
      parent = findParent(cursor->ptr[i], child);
      if (parent != NULL)
        return parent;
    }
  }
  return parent;
}

// Print the tree
void BPTree::display(Node *cursor) {
  if (cursor != NULL) {
    for (int i = 0; i < cursor->size; i++) {
      cout << cursor->key[i] << " ";
    }
    cout << "\n";
    if (cursor->IS_LEAF != true) {
      for (int i = 0; i < cursor->size + 1; i++) {
        display(cursor->ptr[i]);
      }
    }
  }
}

// Get the root
Node *BPTree::getRoot() {
  return root;
}