/*
 *  omnis.xcomp.widget
 *  ===================
 *
 *  oDLNode.h
 *  Header for our datalist node object
 *
 *  oDLNode is a support object for building our tree node
 *
 *  Bastiaan Olij
 */

#ifndef odlnodeh
#define odlnodeh

#include "omnis.xcomp.framework.h"

// Forward defines
class oDLNode;
typedef std::vector<oDLNode *>		oDLNodeArray;						// array of node pointers

typedef struct sDLRow {
	qlong	mLineNo;
	qdim	mTop;
	qdim	mBottom;
} sDLRow;

typedef std::vector<sDLRow>			sDLRowArray;						// array of datanode rows

//////////
class oDLNode {
private:
	bool			mTouched;											// if true this node is still part of our data list
	bool			mExpanded;											// if true our node is expanded
	qlong			mLineNo;											// line number in our data list this relates to, 0 if just grouping
	qlong			mSortOrder;											// numeric field to sort our node by
	qstring			mValue;												// our value, used to find related records
	qstring			mDescription;										// our description, only used if mLineNo=0
	
	// nodes
	oDLNodeArray	mChildNodes;										// child nodes
	sDLRowArray		mRowNodes;											// line nodes

public:
	// These are only set after we've drawn our tree so we can see where nodes are
	qdim			mTop;												// top position 
	qdim			mBottom;											// bottom position	
	qrect			mTreeIcon;											// Rectangle for our tree icon
	
	oDLNode(void);
	oDLNode(const qstring &pValue, const qstring &pDescription, qlong pLineNo=0);
	~oDLNode(void);
	
	// properties
	bool			touched(void);										// touched?
	void			setTouched(bool pTouched);							// set value of touched
	bool			expanded(void);										// expanded?
	void			setExpanded(bool pExpanded);						// set expanded
	qlong			lineNo(void);										// related line number
	void			setLineNo(qlong pLineNo);							// update the related line number
	qlong			sortOrder(void);									// our sort order
	void			setSortOrder(qlong pSortOrder);						// set our sort order 
	
	// read only
	const qstring &	value(void);										// value
	const qstring &	description(void);									// description
	bool			aboveTreeIcon(qpoint pAt);							// is this point within our tree icon?
	
	// methods
	void			clearChildNodes();									// Clear all the child nodes
	void			addNode(oDLNode * pNewNode);						// Add this node
	unsigned long	childNodeCount();									// Returns the number of child nodes
	oDLNode	*		findChildByValue(const qstring & pValue);			// Find a child node by value
	oDLNode	*		findChildByDescription(const qstring & pDesc, bool pNoValue=false);	// Find a child node by description
	oDLNode *		findChildByPoint(qpoint pAt);						// Find a child node by screen location
	oDLNode *		getChildByIndex(unsigned long pIndex);				// Get child at specific index
	
	void			addRow(sDLRow pRow);								// Add a row
	unsigned long	rowCount();											// Returns the number of rows
	sDLRow			getRowAtIndex(unsigned long pIndex);				// Get the row at this index
	void			setRowAtIndex(unsigned long pIndex, sDLRow pRow);	// Set the row at this index
	qlong			findRowAtPoint(qpoint pAt);							// Find row by screen location
	qdim			findTopForRow(qlong pLineNo);						// Find top position for specific line (will check child nodes if applicable)
	bool			hasRow(qlong pLineNo);								// Check if this row is part of our node?
	
	static bool		order(oDLNode * pA, oDLNode * pB);					// Static function that returns whether true if the sort order of A is smaller then B
	void			sortChildren(void);									// Sort our child nodes
	void			unTouchChildren(void);								// Marks all children as untouched and remove any line nodes
	void			removeUntouched(void);								// Removes children that are untouched	
};



#endif
