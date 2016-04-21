//   Node.java
//   Java Spatial Index Library
//   Copyright (C) 2002 Infomatiq Limited
//  
//  This library is free software; you can redistribute it and/or
//  modify it under the terms of the GNU Lesser General Public
//  License as published by the Free Software Foundation; either
//  version 2.1 of the License, or (at your option) any later version.
//  
//  This library is distributed in the hope that it will be useful,
//  but WITHOUT ANY WARRANTY; without even the implied warranty of
//  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
//  Lesser General Public License for more details.
//  
//  You should have received a copy of the GNU Lesser General Public
//  License along with this library; if not, write to the Free Software
//  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA

// Ported to C# By Dror Gluska, April 9th, 2009
// Ported to C++ By Dmitry Tsvetkov, April 21th, 2016
#pragma once
#include "RTree.h"
#include "Rectangle.h"
#include <vector>

namespace RTreeLib
{

	//import com.infomatiq.jsi.Rectangle;

	/**
	* <p>Used by RTree. There are no public methods in this class.</p>
	*
	* @author aled@sourceforge.net
	* @version 1.0b2p1
	*/
	const Rectangle NullRect = Rectangle(0, 0, 0, 0, 0, 0);
	class Node
	{
	public:
		int nodeId;
		Rectangle mbr;
		std::vector<Rectangle> entries;
		std::vector<int> ids;
		//typedef RTreeLib::
		int level;
		int entryCount;
		bool bMbrInitialized;
		Node() : entryCount(0), bMbrInitialized(false)
		{
			this->nodeId = 0;
			this->level = 0;
		}

		Node(int nodeId, int level, int maxNodeEntries) : entryCount(0), bMbrInitialized(false)
		{
			this->nodeId = nodeId;
			this->level = level;
			entries.resize(maxNodeEntries);
			ids.resize(maxNodeEntries);
		}

		void addEntry(Rectangle r, int id)
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

		void addEntryNoCopy(Rectangle r, int id)
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

		// Return the index of the found entry, or -1 if not found
		int findEntry(Rectangle r, int id)
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

		// delete entry. This is done by setting it to null and copying the last entry into its space.
		void deleteEntry(int i, int minNodeEntries)
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

		// oldRectangle is a rectangle that has just been deleted or made smaller.
		// Thus, the MBR is only recalculated if the OldRectangle influenced the old MBR
		void recalculateMBR(Rectangle deletedRectangle)
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

		int getEntryCount() const
		{
			return entryCount;
		}

		Rectangle& getEntry(int index)
		{
			if (index < entryCount)
			{
				return entries[index];
			}
			return entries[0];
		}

		int getId(int index)
		{
			if (index < entryCount)
			{
				return ids[index];
			}
			return -1;
		}

		/**
		* eliminate null entries, move all entries to the start of the source node
		*/
		void reorganize(int countdownIndex)
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

		bool isLeaf() const
		{
			return (level == 1);
		}

		int getLevel() const
		{
			return level;
		}

		Rectangle getMBR() const
		{
			return mbr;
		}
	};
}
