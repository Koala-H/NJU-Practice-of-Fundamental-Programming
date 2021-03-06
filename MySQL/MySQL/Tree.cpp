#include"Tree.h"
#include<iostream>
using namespace std;

void Tree::setUser(string name)
{
	father->user = name;
}

void Tree::treeRevoke(TNode *firstUser,vector<string> &list)
{
	if (firstUser == NULL)
		return;
	list.push_back(firstUser->user);
	if (firstUser->children.size() == 0)return;
	for (vector<TNode*>::iterator it = firstUser->children.begin(); it != firstUser->children.end(); it++)
		treeRevoke(*it,list);   //递归查找
}

void myInsert(TNode *node, string locate, string des)  //增加被授权人
{
	if (node->user == locate)
	{
		TNode *add = new TNode;
		add->user = des;
		node->children.push_back(add);
		return;
	}
	for (unsigned int i = 0; i < node->children.size(); ++i)
		myInsert(node->children[i], locate, des);
	return;
}

TNode *Tree::bfs2(TNode *node, string des)
{
	if (node == NULL)   //目标节点不存在
		return NULL;
	if (node->user == des)   //找到目标节点
		return node;
	for (unsigned int i = 0; i < node->children.size(); ++i)
		return bfs2(node->children[i], des);
}

TNode *Tree::bfs(TNode *node, string des) 
{
	if (node == NULL || node->children.size() == 0)   //目标节点不存在
		return node;
	if (node->user == des)   //找到目标节点
		return node;
	for (vector<TNode*>::iterator it = node->children.begin(); it != node->children.end(); it++)
		return bfs(*it, des);   //递归查找
}

void Tree::deleteMemory(TNode *&node)  
{
	if (node == NULL || node->children.size() == 0)  
		return;
	for (vector<TNode*>::iterator it = node->children.begin(); it != node->children.end(); it++)
		deleteMemory(*it);
	delete node;
}

void Tree::insertAfter(string locate, string des)
{
	myInsert(father, locate, des);
}

void Tree::deleteNode(string withdraw, string beWithdraw)
{
	TNode *tn1 = bfs(father, withdraw); //找到收回权限者
	if(tn1==NULL)   //收回权限者或被收回权限者不存在
		return;
	TNode *tn2 = bfs(tn1, beWithdraw); //找到被收回权限者
	if (tn2 == NULL)  //被收回权限者不存在
		return;
	TNode *tmp = tn2;
	for (vector<TNode*>::iterator it = tn1->children.begin(); it != tn1->children.end();++it)
		if (*it == tn2)
		{
			tn1->children.erase(it);
			break;
		}
	deleteMemory(tmp);  //释放被收回者空间
}