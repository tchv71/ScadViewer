#include "stdafx.h"
#include "Node.h"

namespace RTreeLib
{
	 Node::Node() : entryCount(0), bMbrInitialized(false)
	{
		this->nodeId = 0;
		this->level = 0;
	}

	Node::Node(int nodeId, int level, int maxNodeEntries): entryCount(0), bMbrInitialized(false)
	{
		this->nodeId = nodeId;
		this->level = level;
		//entries.resize(maxNodeEntries);
		//ids.resize(maxNodeEntries);
	}

	void Node::addEntry(Rectangle r, int id)
	{
		ids[entryCount] = id;
		entries[entryCount] = r.copy();
		entryCount++;
		if (!bMbrInitialized)
		{
			mbr = r.copy();
			bMbrInitialized = true;
		}
		else
		{
			mbr.add(r);
		}
	}

	void Node::addEntryNoCopy(Rectangle r, int id)
	{
		ids[entryCount] = id;
		entries[entryCount] = r;
		entryCount++;
		if (!bMbrInitialized)
		{
			mbr = r.copy();
			bMbrInitialized = true;
		}
		else
		{
			mbr.add(r);
		}
	}

	int Node::findEntry(Rectangle r, int id)
	{
		for (int i = 0; i < entryCount; i++)
		{
			if (id == ids[i] && r == entries[i])
			{
				return i;
			}
		}
		return -1;
	}

	void Node::deleteEntry(int i, int minNodeEntries)
	{
		int lastIndex = entryCount - 1;
		Rectangle deletedRectangle = entries[i];
		entries[i] = NullRect;
		if (i != lastIndex)
		{
			entries[i] = entries[lastIndex];
			ids[i] = ids[lastIndex];
			entries[lastIndex] = NullRect;
		}
		entryCount--;

		// if there are at least minNodeEntries, adjust the MBR.
		// otherwise, don't bother, as the Node<T> will be 
		// eliminated anyway.
		if (entryCount >= minNodeEntries)
		{
			recalculateMBR(deletedRectangle);
		}
	}

	void Node::recalculateMBR(Rectangle deletedRectangle)
	{
		if (mbr.edgeOverlaps(deletedRectangle))
		{
			mbr.set(entries[0].min, entries[0].max);

			for (int i = 1; i < entryCount; i++)
			{
				mbr.add(entries[i]);
			}
		}
	}

	int Node::getEntryCount() const
	{
		return entryCount;
	}

	Rectangle& Node::getEntry(int index)
	{
		if (index < entryCount)
		{
			return entries[index];
		}
		return entries[0];
	}

	int Node::getId(int index)
	{
		if (index < entryCount)
		{
			return ids[index];
		}
		return -1;
	}

	void Node::reorganize(int countdownIndex)
	{
		//int countdownIndex = rtree.maxNodeEntries - 1;
		for (int index = 0; index < entryCount; index++)
		{
			if (entries[index] == NullRect)
			{
				while (entries[countdownIndex] == NullRect && countdownIndex > index)
				{
					countdownIndex--;
				}
				entries[index] = entries[countdownIndex];
				ids[index] = ids[countdownIndex];
				entries[countdownIndex] = NullRect;
			}
		}
	}

	bool Node::isLeaf() const
	{
		return (level == 1);
	}

	int Node::getLevel() const
	{
		return level;
	}

	Rectangle Node::getMBR() const
	{
		return mbr;
	}

}