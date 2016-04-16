//---------------------------------------------------------------------------

//#include <vcl.h>
#include "stdafx.h"
#pragma hdrstop

#include "Qsort.h"

//---------------------------------------------------------------------------

#pragma package(smart_init)
/*-----------------------------------------------------------------------*
 * filename - qsort.c
 *
 * function(s)
 *        Exchange  - exchanges two objects
 *        qSortHelp - performs the quicker sort
 *        qsort     - sorts using the quick sort routine
 *-----------------------------------------------------------------------*/

/*
 *      C/C++ Run Time Library - Version 10.0
 *
 *      Copyright (c) 1987, 2000 by Inprise Corporation
 *      All Rights Reserved.
 *
 */

/* $Revision:   9.1  $        */

#include <stdlib.h>
//e <_thread.h>

#if 0
#define _RTLTHREAD __declspec(thread)
#else
#define _RTLTHREAD
#endif
#if 0

static  _RTLTHREAD comparF    *Fcmp;
static  _RTLTHREAD unsigned    qWidth;

/*-----------------------------------------------------------------------*

Name            Exchange - exchanges two objects

Usage           static  void  Exchange (void  *leftP, void *rightP);

Description     exchanges the qWidth byte wide objects pointed to
                by leftP and rightP.

Return value    Nothing

*------------------------------------------------------------------------*/
typedef unsigned FT;

void __fastcall  Exchange (void  *leftP, void *rightP)
{
        FT  c;
        FT *lp = (FT *)leftP;
        FT *rp = (FT *)rightP;
        unsigned i=qWidth/sizeof(FT);
        do
        {
                c = *rp;
                *rp++ = *lp;
                *lp++ = c;
        } while (--i);
}

/*-----------------------------------------------------------------------*

Background

The Quicker Sort algorithm was first described by C.A.R.Hoare in the
Computer Journal, No. 5 (1962), pp.10..15, and in addition is frequently
described in computing literature, notably in D. Knuth's Sorting and
Searching.  The method used here includes a number of refinements:

- The median-of-three technique described by Singleton (Communications
  of the A.C.M., No 12 (1969) pp 185..187) is used, where the median
  operation is also the special case sort for 3 elements.  This slightly
  improves the average speed, especially when comparisons are slower
  than exchanges, but more importantly it prevents worst-case behavior
  on partly sorted files.  If a simplistic quicker-sort is run on a file
  which is only slightly disordered (a common need in some applications)
  then it is as slow as a bubble-sort.  The median technique prevents
  this.

  Another serious problem with the plain algorithm is that worst-case
  behavior causes very deep recursion (almost one level per table
  element !), so again it is best to use the median technique.

- The values of width and compar are copied to static storage and a help
  function with a minimum of parameters is used to reduce the recursion
  overheads.  Recursion is used both for simplicity and because there
  is no practical gain from conversion to loops: the extra housekeeping
  needed for loops needs registers for speed, but the 8086 family has not
  enough registers.  Juggling registers takes just as much time as calling
  subroutines.

*------------------------------------------------------------------------*/

/*
  Optimize pointer comparisons knowing segments are identical,
  except in HUGE model.
*/

#define _LT_(x,y)       (x < y)

/*-----------------------------------------------------------------------*

Name            qSortHelp - performs the quicker sort

Usage           static void  near pascal  qSortHelp (char *pivotP,
                                                     size_t nElem);

Description     performs the quicker sort on the nElem element array
                pointed to by pivotP.

Return value    Nothing

*------------------------------------------------------------------------*/

static void __fastcall qSortHelp (char *pivotP, size_t nElem)
{
    char     *leftP, *rightP, *pivotEnd, *pivotTemp, *leftTemp;
    unsigned  lNum;
    int       retval;


tailRecursion:
    if (nElem <= 2)
        {
        if (nElem == 2)
            {
            if (Fcmp (pivotP, rightP = qWidth + pivotP) > 0)
                Exchange (pivotP, rightP);
            }
        return;
        }

    rightP = (nElem - 1) * qWidth + pivotP;
    leftP  = (nElem >> 1) * qWidth + pivotP;

/*  sort the pivot, left, and right elements for "median of 3" */

    if (Fcmp (leftP, rightP) > 0)
        Exchange (leftP, rightP);
    if (Fcmp (leftP, pivotP) > 0)
        Exchange (leftP, pivotP);
    else if (Fcmp (pivotP, rightP) > 0)
        Exchange (pivotP, rightP);

    if (nElem == 3)
        {
        Exchange (pivotP, leftP);
        return;
        }

/*  now for the classic Hoare algorithm */

    leftP = pivotEnd = pivotP + qWidth;

    do
        {
        while ((retval = Fcmp(leftP, pivotP)) <= 0)
            {
            if (retval == 0)
                {
                Exchange(leftP, pivotEnd);
                pivotEnd += qWidth;
                }
            if (_LT_ (leftP, rightP))
                leftP += qWidth;
            else
                goto qBreak;
            }

        while (_LT_(leftP, rightP))
            {
            if ((retval = Fcmp(pivotP, rightP)) < 0)
                rightP -= qWidth;
            else
                {
                Exchange (leftP, rightP);
                if (retval != 0)
                    {
                    leftP += qWidth;
                    rightP -= qWidth;
                    }
                break;
                }
            }
        }   while (_LT_(leftP, rightP));

qBreak:

    if (Fcmp(leftP, pivotP) <= 0)
        leftP = leftP + qWidth;

    leftTemp = leftP - qWidth;

    pivotTemp = pivotP;

    while ((pivotTemp < pivotEnd) && (leftTemp >= pivotEnd))
        {
        Exchange(pivotTemp, leftTemp);
        pivotTemp += qWidth;
        leftTemp -= qWidth;
        }

    lNum = (leftP - pivotEnd) / qWidth;
    nElem = ((nElem * qWidth + pivotP) - leftP)/qWidth;

    /* Sort smaller partition first to reduce stack usage */
    if (nElem < lNum)
        {
        qSortHelp (leftP, nElem);
        nElem = lNum;
        }
    else
        {
        qSortHelp (pivotP, lNum);
        pivotP = leftP;
        }

    goto tailRecursion;
}

/*-----------------------------------------------------------------------*

Name            qsort - sorts using the quick sort routine

Usage           void qsort(void *base, int nelem, int width, int (*fcmp)());

Prototype in    stdlib.h

Description     qsort is an implementation of the "median of three"
                variant of the quicksort algorithm. qsort sorts the entries
                in a table into order by repeatedly calling the user-defined
                comparison function pointed to by fcmp.

                base points to the base (0th element) of the table to be sorted.

                nelem is the number of entries in the table.

                width is the size of each entry in the table, in bytes.

                *fcmp, the comparison function, accepts two arguments, elem1
                and elem2, each a pointer to an entry in the table. The
                comparison function compares each of the pointed-to items
                (*elem1 and *elem2), and returns an integer based on the result
                of the comparison.

                        If the items            fcmp returns

                        *elem1 <  *elem2         an integer < 0
                        *elem1 == *elem2         0
                        *elem1 >  *elem2         an integer > 0

                In the comparison, the less than symbol (<) means that the left
                element should appear before the right element in the final,
                sorted sequence. Similarly, the greater than (>) symbol
                means that the left element should appear after the right
                element in the final, sorted sequence.

Return value    qsort does not return a value.

*------------------------------------------------------------------------*/

void _RTLENTRYF _EXPFUNC Mqsort(void *baseP, size_t nElem, size_t width,
                          comparF *compar)

/*
  The table *baseP containing a count of nElem records each of fixed width
  is to be converted from unknown order into ascending order, using the
  ordering provided by the comparison function compar.

  The comparison function compar (leftP, rightP) must return less than, equal,
  or greater than zero, according to whether it decides that (record) *leftP
  is less than, equal, or greater than (record) *rightP.

  The internal contents of the records are never inspected by qsort.  It
  depends entirely upon compar to decide the format and value of the records.
  This allows the content of the records to be of any fixed length type -
  formatted text, floating point, pointer to variable length record, etc. -
  so long as each record is understood by compar.

  The quicker sort algorithm will in general change the relative ordering
  of records which may compare as equal.  For example, if it is attempted
  to use two passes of quick sort on a order file, first by date and then
  by customer name, the result will be that the second sort pass randomly
  jumbles the dates.  It is necessary to design the compar() function to
  consider all the keys and sort in one pass.

*/

{
    if ((qWidth = width) == 0)
        return;

    Fcmp = compar;

    qSortHelp ((char *)baseP, nElem);
}
#else
/***
*qsort.c - quicksort algorithm; qsort() library function for sorting arrays
*
*       Copyright (c) 1985-1997, Microsoft Corporation. All rights reserved.
*
*Purpose:
*       To implement the qsort() routine for sorting arrays.
*
*******************************************************************************/

//#include <cruntime.h>
#include <stdlib.h>
#include <search.h>

/* prototypes for local routines */
static void __cdecl shortsort(char *lo, char *hi, unsigned width,
                int (__cdecl *comp)(const void *, const void *));
static void __fastcall swap(char *p, char *q, unsigned int width);

/* this parameter defines the cutoff between using quick sort and
   insertion sort for arrays; arrays with lengths shorter or equal to the
   below value use insertion sort */

#define CUTOFF 8            /* testing shows that this is good value */


/***
*qsort(base, num, wid, comp) - quicksort function for sorting arrays
*
*Purpose:
*       quicksort the array of elements
*       side effects:  sorts in place
*
*Entry:
*       char *base = pointer to base of array
*       unsigned num  = number of elements in the array
*       unsigned width = width in bytes of each array element
*       int (*comp)() = pointer to function returning analog of strcmp for
*               strings, but supplied by user for comparing the array elements.
*               it accepts 2 pointers to elements and returns neg if 1<2, 0 if
*               1=2, pos if 1>2.
*
*Exit:
*       returns void
*
*Exceptions:
*
*******************************************************************************/

/* sort the array between lo and hi (inclusive) */

void __cdecl Mqsort (
    void *base,
    unsigned num,
    unsigned width,
    int (__cdecl *comp)(const void *, const void *)
    )
{
    char *lo, *hi;              /* ends of sub-array currently sorting */
    char *mid;                  /* points to middle of subarray */
    char *loguy, *higuy;        /* traveling pointers for partition step */
    unsigned size;              /* size of the sub-array */
    char *lostk[30], *histk[30];
    int stkptr;                 /* stack for saving sub-array to be processed */

    /* Note: the number of stack entries required is no more than
       1 + log2(size), so 30 is sufficient for any array */

    if (num < 2 || width == 0)
        return;                 /* nothing to do */

    stkptr = 0;                 /* initialize stack */

    lo =(char *) base;
    hi = (char *)base + width * (num-1);        /* initialize limits */

    /* this entry point is for pseudo-recursion calling: setting
       lo and hi and jumping to here is like recursion, but stkptr is
       prserved, locals aren't, so we preserve stuff on the stack */
recurse:

    size = (hi - lo) / width + 1;        /* number of el's to sort */

    /* below a certain size, it is faster to use a O(n^2) sorting method */
    if (size <= CUTOFF) {
         shortsort(lo, hi, width, comp);
    }
    else {
        /* First we pick a partititioning element.  The efficiency of the
           algorithm demands that we find one that is approximately the
           median of the values, but also that we select one fast.  Using
           the first one produces bad performace if the array is already
           sorted, so we use the middle one, which would require a very
           wierdly arranged array for worst case performance.  Testing shows
           that a median-of-three algorithm does not, in general, increase
           performance. */

        mid = lo + (size / 2) * width;      /* find middle element */
        swap(mid, lo, width);               /* swap it to beginning of array */

        /* We now wish to partition the array into three pieces, one
           consisiting of elements <= partition element, one of elements
           equal to the parition element, and one of element >= to it.  This
           is done below; comments indicate conditions established at every
           step. */

        loguy = lo;
        higuy = hi + width;

        /* Note that higuy decreases and loguy increases on every iteration,
           so loop must terminate. */
        for (;;) {
            /* lo <= loguy < hi, lo < higuy <= hi + 1,
               A[i] <= A[lo] for lo <= i <= loguy,
               A[i] >= A[lo] for higuy <= i <= hi */

            do  {
                loguy += width;
            } while (loguy <= hi && comp(loguy, lo) <= 0);

            /* lo < loguy <= hi+1, A[i] <= A[lo] for lo <= i < loguy,
               either loguy > hi or A[loguy] > A[lo] */

            do  {
                higuy -= width;
            } while (higuy > lo && comp(higuy, lo) >= 0);

            /* lo-1 <= higuy <= hi, A[i] >= A[lo] for higuy < i <= hi,
               either higuy <= lo or A[higuy] < A[lo] */

            if (higuy < loguy)
                break;

            /* if loguy > hi or higuy <= lo, then we would have exited, so
               A[loguy] > A[lo], A[higuy] < A[lo],
               loguy < hi, highy > lo */

            swap(loguy, higuy, width);

            /* A[loguy] < A[lo], A[higuy] > A[lo]; so condition at top
               of loop is re-established */
        }

        /*     A[i] >= A[lo] for higuy < i <= hi,
               A[i] <= A[lo] for lo <= i < loguy,
               higuy < loguy, lo <= higuy <= hi
           implying:
               A[i] >= A[lo] for loguy <= i <= hi,
               A[i] <= A[lo] for lo <= i <= higuy,
               A[i] = A[lo] for higuy < i < loguy */

        swap(lo, higuy, width);     /* put partition element in place */

        /* OK, now we have the following:
              A[i] >= A[higuy] for loguy <= i <= hi,
              A[i] <= A[higuy] for lo <= i < higuy
              A[i] = A[lo] for higuy <= i < loguy    */

        /* We've finished the partition, now we want to sort the subarrays
           [lo, higuy-1] and [loguy, hi].
           We do the smaller one first to minimize stack usage.
           We only sort arrays of length 2 or more.*/

        if ( higuy - 1 - lo >= hi - loguy ) {
            if (lo + width < higuy) {
                lostk[stkptr] = lo;
                histk[stkptr] = higuy - width;
                ++stkptr;
            }                           /* save big recursion for later */

            if (loguy < hi) {
                lo = loguy;
                goto recurse;           /* do small recursion */
            }
        }
        else {
            if (loguy < hi) {
                lostk[stkptr] = loguy;
                histk[stkptr] = hi;
                ++stkptr;               /* save big recursion for later */
            }

            if (lo + width < higuy) {
                hi = higuy - width;
                goto recurse;           /* do small recursion */
            }
        }
    }

    /* We have sorted the array, except for any pending sorts on the stack.
       Check if there are any, and do them. */

    --stkptr;
    if (stkptr >= 0) {
        lo = lostk[stkptr];
        hi = histk[stkptr];
        goto recurse;           /* pop subarray from stack */
    }
    else
        return;                 /* all subarrays done */
}


/***
*shortsort(hi, lo, width, comp) - insertion sort for sorting short arrays
*
*Purpose:
*       sorts the sub-array of elements between lo and hi (inclusive)
*       side effects:  sorts in place
*       assumes that lo < hi
*
*Entry:
*       char *lo = pointer to low element to sort
*       char *hi = pointer to high element to sort
*       unsigned width = width in bytes of each array element
*       int (*comp)() = pointer to function returning analog of strcmp for
*               strings, but supplied by user for comparing the array elements.
*               it accepts 2 pointers to elements and returns neg if 1<2, 0 if
*               1=2, pos if 1>2.
*
*Exit:
*       returns void
*
*Exceptions:
*
*******************************************************************************/

static void __cdecl shortsort (
    char *lo,
    char *hi,
    unsigned width,
    int (__cdecl *comp)(const void *, const void *)
    )
{
    char *p, *max;

    /* Note: in assertions below, i and j are alway inside original bound of
       array to sort. */

    while (hi > lo) {
        /* A[i] <= A[j] for i <= j, j > hi */
        max = lo;
        for (p = lo+width; p <= hi; p += width) {
            /* A[i] <= A[max] for lo <= i < p */
            if (comp(p, max) > 0) {
                max = p;
            }
            /* A[i] <= A[max] for lo <= i <= p */
        }

        /* A[i] <= A[max] for lo <= i <= hi */

        swap(max, hi, width);

        /* A[i] <= A[hi] for i <= hi, so A[i] <= A[j] for i <= j, j >= hi */

        hi -= width;

        /* A[i] <= A[j] for i <= j, j > hi, loop top condition established */
    }
    /* A[i] <= A[j] for i <= j, j > lo, which implies A[i] <= A[j] for i < j,
       so array is sorted */
}


/***
*swap(a, b, width) - swap two elements
*
*Purpose:
*       swaps the two array elements of size width
*
*Entry:
*       char *a, *b = pointer to two elements to swap
*       unsigned width = width in bytes of each array element
*
*Exit:
*       returns void
*
*Exceptions:
*
*******************************************************************************/

typedef unsigned FT;

#if 1
void __fastcall  swap(char *leftP, char *rightP,unsigned width)
{
        FT  c;
        FT *lp = (FT *)leftP;
        FT *rp = (FT *)rightP;
        unsigned i=width/sizeof(FT);
        do
        {
                c = *rp;
                *rp++ = *lp;
                *lp++ = c;
        } while (--i);
}
#else
static void __cdecl swap (
    char *a,
    char *b,
    unsigned width
    )
{
    char tmp;

    if ( a != b )
        /* Do the swap one character at a time to avoid potential alignment
           problems. */
        while ( width-- ) {
            tmp = *a;
            *a++ = *b;
            *b++ = tmp;
        }
}
#endif
#endif
