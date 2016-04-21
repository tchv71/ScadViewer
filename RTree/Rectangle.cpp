#include "Rectangle.h"
#include <cmath>

namespace RTree
{

	Rectangle::Rectangle()
	{
	}


	Rectangle::~Rectangle()
	{
	}

	Rectangle::Rectangle(float x1, float y1, float x2, float y2, float z1, float z2)
	{
		set(x1, y1, x2, y2, z1, z2);
	}

	Rectangle::Rectangle(float min[], float max[])
	{
		//if (min.Length != DIMENSIONS || max.Length != DIMENSIONS)
		//{
		//	throw new Exception("Error in Rectangle constructor: " +
		//		"min and max arrays must be of length " + DIMENSIONS);
		//}
		for (int i = 0; i < DIMENSIONS; i++)
		{
			this->min[i] = min[i];
			this->max[i] = max[i];
		}
		set(min, max);
	}

	void Rectangle::set(float x1, float y1, float x2, float y2, float z1, float z2)
	{
		min[0] = fmin(x1, x2);
		min[1] = fmin(y1, y2);
		min[2] = fmin(z1, z2);
		max[0] = fmax(x1, x2);
		max[1] = fmax(y1, y2);
		max[2] = fmax(z1, z2);
	}

	void Rectangle::set(float min[], float max[])
	{
		for (int i = 0; i < DIMENSIONS; i++)
		{
			this->min[i] = min[i];
			this->max[i] = max[i];
		}
	}

	Rectangle Rectangle::copy() const
	{
		return *this;
	}

	bool Rectangle::edgeOverlaps(Rectangle r) const
	{
		for (int i = 0; i < DIMENSIONS; i++)
		{
			if (fabs(min[i] - r.min[i]) < EPS || fabs(max[i] - r.max[i]) < EPS)
			{
				return true;
			}
		}
		return false;
	}

	bool Rectangle::intersects(Rectangle r) const
	{
		// Every dimension must intersect. If any dimension
		// does not intersect, return false immediately.
		for (int i = 0; i < DIMENSIONS; i++)
		{
			if (max[i] < r.min[i] || min[i] > r.max[i])
			{
				return false;
			}
		}
		return true;
	}

	bool Rectangle::contains(Rectangle r) const
	{
		for (int i = 0; i < DIMENSIONS; i++)
		{
			if (max[i] < r.max[i] || min[i] > r.min[i])
			{
				return false;
			}
		}
		return true;
	}

	bool Rectangle::containedBy(Rectangle r) const
	{
		for (int i = 0; i < DIMENSIONS; i++)
		{
			if (max[i] > r.max[i] || min[i] < r.min[i])
			{
				return false;
			}
		}
		return true;
	}

	float Rectangle::distance(Point p) const
	{
		float distanceSquared = 0;
		for (int i = 0; i < DIMENSIONS; i++)
		{
			float greatestMin = fmax(min[i], p.coordinates[i]);
			float leastMax = fmin(max[i], p.coordinates[i]);
			if (greatestMin > leastMax)
			{
				distanceSquared += ((greatestMin - leastMax) * (greatestMin - leastMax));
			}
		}
		return sqrt(distanceSquared);
	}

	float Rectangle::distance(Rectangle r)
	{
		float distanceSquared = 0;
		for (int i = 0; i < DIMENSIONS; i++)
		{
			float greatestMin = fmax(min[i], r.min[i]);
			float leastMax = fmin(max[i], r.max[i]);
			if (greatestMin > leastMax)
			{
				distanceSquared += ((greatestMin - leastMax) * (greatestMin - leastMax));
			}
		}
		return sqrt(distanceSquared);
	}

	float Rectangle::distanceSquared(int dimension, float point)
	{
		float distanceSquared = 0;
		float tempDistance = point - max[dimension];
		for (int i = 0; i < 2; i++)
		{
			if (tempDistance > 0)
			{
				distanceSquared = (tempDistance * tempDistance);
				break;
			}
			tempDistance = min[dimension] - point;
		}
		return distanceSquared;
	}

	float Rectangle::furthestDistance(Rectangle r) const
	{
		float distanceSquared = 0;

		for (int i = 0; i < DIMENSIONS; i++)
		{
			distanceSquared += fmax(r.min[i], r.max[i]);
//#warning possible didn't convert properly
			//distanceSquared += fmax(distanceSquared(i, r.min[i]), distanceSquared(i, r.max[i]));
		}

		return sqrt(distanceSquared);
	}

	float Rectangle::enlargement(Rectangle r)
	{
		float enlargedArea = (fmax(max[0], r.max[0]) - fmin(min[0], r.min[0])) *
			(fmax(max[1], r.max[1]) - fmin(min[1], r.min[1]));

		return enlargedArea - area();
	}

	float Rectangle::area()
	{
		return (max[0] - min[0]) * (max[1] - min[1]);
	}

	void Rectangle::add(Rectangle r)
	{
		for (int i = 0; i < DIMENSIONS; i++)
		{
			if (r.min[i] < min[i])
			{
				min[i] = r.min[i];
			}
			if (r.max[i] > max[i])
			{
				max[i] = r.max[i];
			}
		}
	}

	Rectangle Rectangle::Union(Rectangle r) const
	{
		Rectangle _union = copy();
		_union.add(r);
		return _union;
	}

	bool Rectangle::CompareArrays(const float a1[], const float a2[])
	{
		if ((a1 == nullptr) || (a2 == nullptr))
			return false;
		for (int i = 0; i < DIMENSIONS; i++)
			if (fabs(a1[i] - a2[i])>EPS)
				return false;
		return true;
	}

	bool Rectangle::operator==(const Rectangle& r) const
	{
		bool equals = false;
		if (CompareArrays(r.min, min) && CompareArrays(r.max, max))
		{
			equals = true;
		}
		return equals;
	}

	bool Rectangle::sameObject(const Rectangle& o) const
	{
		return *this == o;
	}
}
