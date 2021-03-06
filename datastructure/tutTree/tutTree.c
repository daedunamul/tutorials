#include "tutTree.h"

void tutTree_travel( struct tutTreeNode *RootNode , void *Data , void ( *TravelFx )( struct tutTreeNode *ThisNode , void *Data ) )
{
	if( RootNode == NULL )
		return ;
	
	struct tutTreeNode *ThisNode = RootNode ;
	
	Visiting : 
	TravelFx( ThisNode , Data ) ;
	
	MovingToSub : 
	if( ThisNode->Sub != NULL )
	{
		ThisNode = ThisNode->Sub ;
		goto Visiting ;
	}
	
	MovingToRight : 
	if( ThisNode->Right != NULL )
	{
		ThisNode = ThisNode->Right ;
		goto Visiting ;
	}
	
	MovingToSuper : 
	if( ThisNode->Super != NULL )
	{
		ThisNode = ThisNode->Super ;
		goto MovingToRight ;
	}
	
	// no nodes to visit
}

void tutTree_push( struct tutTreeNode *ThisNode , struct tutTreeNodePool *NodePool , int Value )
{
	if( ThisNode == NULL || NodePool == NULL )
		return ;
	
	struct tutTreeNode *NewNode ;
	
	NewNode = tutTreeNodePool_allocate( NodePool ) ;
	if( NewNode == NULL )
		return ;
	NewNode->Value = Value ;
	NewNode->Degree = 0 ;
	NewNode->Super = ThisNode ;
	NewNode->Sub = NULL ;
	NewNode->Left = NULL ;
	NewNode->Right = ThisNode->Sub ;
	
	if( ThisNode->Sub != NULL )
		ThisNode->Sub->Left = NewNode ;
	ThisNode->Sub = NewNode ;
	ThisNode->Degree ++ ;
}
void tutTree_pop( struct tutTreeNode *ThisNode , struct tutTreeNodePool *NodePool )
{
	if( ThisNode == NULL || NodePool == NULL )
		return ;
	
	if( ThisNode->Super != NULL )
	{
		ThisNode->Super->Degree -- ;
		ThisNode->Super = NULL ;
	}
	tutTree_travel( ThisNode , NodePool , tutTree_flush ) ;
}
void tutTree_flush( struct tutTreeNode *ThisNode , void *Data )
{
	if( Data == NULL )
		return ;
	
	tutTreeNodePool_deallocate( ( struct tutTreeNodePool* )Data , ThisNode ) ;
}
