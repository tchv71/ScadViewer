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
	const int MAX_ENTRIES = 10;
	class Node
	{
	public:
		int nodeId;
		Rectangle mbr;
		Rectangle entries[MAX_ENTRIES];
		int ids[MAX_ENTRIES];
		//typedef RTreeLib::
		int level;
		int entryCount;
		bool bMbrInitialized;
		Node();

		Node(int nodeId, int level, int maxNodeEntries);

		void addEntry(const Rectangle& r, int id);

		void addEntryNoCopy(const Rectangle& r, int id);

		// Return the index of the found entry, or -1 if not found
		int findEntry(const Rectangle& r, int id);

		// delete entry. This is done by setting it to null and copying the last entry into its space.
		void deleteEntry(int i, int minNodeEntries);

		// oldRectangle is a rectangle that has just been deleted or made smaller.
		// Thus, the MBR is only recalculated if the OldRectangle influenced the old MBR
		void recalculateMBR(const Rectangle& deletedRectangle);

		int getEntryCount() const;

		Rectangle& getEntry(int index);

		int getId(int index);

		/**
		* eliminate null entries, move all entries to the start of the source node
		*/
		void reorganize(int countdownIndex);

		bool isLeaf() const;

		int getLevel() const;

		const Rectangle& getMBR() const;
	};

}
