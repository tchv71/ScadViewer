//   Rectangle.java
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
//  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307 USA

// Ported to C# By Dror Gluska, April 9th, 2009
// Ported to C++ By Dmitry Tsvetkov, April 21th, 2016
#pragma once
#include "Point.h"

namespace RTreeLib
{
	const float EPS = 1e-6f;
	class Rectangle
	{
	public:
		Rectangle();
		~Rectangle();
		/**
		* Currently hardcoded to 2 dimensions, but could be extended.
		*
		* @author  aled@sourceforge.net
		* @version 1.0b2p1
		*/
		/**
		* Number of dimensions in a rectangle. In theory this
		* could be exended to three or more dimensions.
		*/
	public:
		static const int DIMENSIONS = 3;

		/**
		* array containing the minimum value for each dimension; ie { min(x), min(y) }
		*/
		float max[DIMENSIONS];

		/**
		* array containing the maximum value for each dimension; ie { max(x), max(y) }
		*/
		float min[DIMENSIONS];

		/**
		* Constructor.
		*
		* @param x1 coordinate of any corner of the rectangle
		* @param y1 (see x1)
		* @param x2 coordinate of the opposite corner
		* @param y2 (see x2)
		*/
		Rectangle(float x1, float y1, float x2, float y2, float z1, float z2);

		/**
		* Constructor.
		*
		* @param min array containing the minimum value for each dimension; ie { min(x), min(y) }
		* @param max array containing the maximum value for each dimension; ie { max(x), max(y) }
		*/
		Rectangle(float min[], float max[]);

		/**
		* Sets the size of the rectangle.
		*
		* @param x1 coordinate of any corner of the rectangle
		* @param y1 (see x1)
		* @param x2 coordinate of the opposite corner
		* @param y2 (see x2)
		*/
		void set(float x1, float y1, float x2, float y2, float z1, float z2);

		/**
		* Sets the size of the rectangle.
		*
		* @param min array containing the minimum value for each dimension; ie { min(x), min(y) }
		* @param max array containing the maximum value for each dimension; ie { max(x), max(y) }
		*/
		void set(const float min[], const float max[]);

		/**
		* Make a copy of this rectangle
		*
		* @return copy of this rectangle
		*/
		Rectangle copy() const;

		/**
		* Determine whether an edge of this rectangle overlies the equivalent
		* edge of the passed rectangle
		*/
		bool edgeOverlaps(Rectangle r) const;

		/**
		* Determine whether this rectangle intersects the passed rectangle
		*
		* @param r The rectangle that might intersect this rectangle
		*
		* @return true if the rectangles intersect, false if they do not intersect
		*/
		bool intersects(Rectangle r) const;

		/**
		* Determine whether this rectangle contains the passed rectangle
		*
		* @param r The rectangle that might be contained by this rectangle
		*
		* @return true if this rectangle contains the passed rectangle, false if
		*         it does not
		*/
		bool contains(Rectangle r) const;

		/**
		* Determine whether this rectangle is contained by the passed rectangle
		*
		* @param r The rectangle that might contain this rectangle
		*
		* @return true if the passed rectangle contains this rectangle, false if
		*         it does not
		*/
		bool containedBy(Rectangle r) const;

		/**
		* Return the distance between this rectangle and the passed point.
		* If the rectangle contains the point, the distance is zero.
		*
		* @param p Point to find the distance to
		*
		* @return distance beween this rectangle and the passed point.
		*/
		float distance(Point p) const;

		/**
		* Return the distance between this rectangle and the passed rectangle.
		* If the rectangles overlap, the distance is zero.
		*
		* @param r Rectangle to find the distance to
		*
		* @return distance between this rectangle and the passed rectangle
		*/

		float distance(Rectangle r);

		/**
		* Return the squared distance from this rectangle to the passed point
		*/
		float distanceSquared(int dimension, float point);

		/**
		* Return the furthst possible distance between this rectangle and
		* the passed rectangle.
		*
		* Find the distance between this rectangle and each corner of the
		* passed rectangle, and use the maximum.
		*
		*/
		float furthestDistance(Rectangle r) const;

		/**
		* Calculate the area by which this rectangle would be enlarged if
		* added to the passed rectangle. Neither rectangle is altered.
		*
		* @param r Rectangle to union with this rectangle, in order to
		*          compute the difference in area of the union and the
		*          original rectangle
		*/
		float enlargement(Rectangle r);

		/**
		* Compute the area of this rectangle.
		*
		* @return The area of this rectangle
		*/
		float area();

		/**
		* Computes the union of this rectangle and the passed rectangle, storing
		* the result in this rectangle.
		*
		* @param r Rectangle to add to this rectangle
		*/
		void add(Rectangle r);

		/**
		* Find the the union of this rectangle and the passed rectangle.
		* Neither rectangle is altered
		*
		* @param r The rectangle to union with this rectangle
		*/
		Rectangle Union(Rectangle r) const;

		static bool CompareArrays(const float a1[], const float a2[]);

		/**
		* Determine whether this rectangle is equal to a given object.
		* Equality is determined by the bounds of the rectangle.
		*
		* @param o The object to compare with this rectangle
		*/
		bool operator ==(const Rectangle& r) const;

		/**
		* Determine whether this rectangle is the same as another object
		*
		* Note that two rectangles can be equal but not the same object,
		* if they both have the same bounds.
		*
		* @param o The object to compare with this rectangle.
		*/
		bool sameObject(const Rectangle& o) const;


	};
}

