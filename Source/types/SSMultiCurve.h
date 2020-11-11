/*
  ==============================================================================

    SSMultiCurve.h
    Created: 13 Mar 2017 9:28:16am
    Author:  Armando Montanez

	* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
	*  Copyright © 2017 Armando Montanez                                      *
	*                                                                         *
	*  This file is part of SimpleSide.                                       *
	*                                                                         *
	*  SimpleSide is free software: you can redistribute it and/or modify     *
	*  it under the terms of the GNU General Public License as published by   *
	*  the Free Software Foundation, either version 3 of the License, or      *
	*  (at your option) any later version.                                    *
	*                                                                         *
	*  SimpleSide is distributed in the hope that it will be useful,          *
	*  but WITHOUT ANY WARRANTY; without even the implied warranty of         *
	*  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the          *
	*  GNU General Public License for more details.                           *
	*                                                                         *
	*  You should have received a copy of the GNU General Public License      *
	*  along with SimpleSide.  If not, see <http://www.gnu.org/licenses/>.    *
	* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
  ==============================================================================
*/

#ifndef SSMULTICURVE_H_INCLUDED
#define SSMULTICURVE_H_INCLUDED

#include "../JuceLibraryCode/JuceHeader.h"
#include <deque>
#include "SSCurve.h"
#include "../ui/SSHandle.h"

class SSMultiCurve {
    std::deque <SSCurve*> curves;           // Curve deque, holds subcurves
    
public:
    std::deque <SSHandle*> handles;         // VARIOIUS DRAWABLE HANDLES, have no purpose other than directing mouse input and drawing
    Component* parent;                      // Pointer to parent
    float liveViewTime;
    
    SSMultiCurve();
    ~SSMultiCurve();
    int count();                            // returns number of curves
    double at(float);                       // returns y for a given x
    double smoothedAt(float);
    int curveAt(float);                     // returns index of curve for a given x
    const Point<float>* handleStart(int);   // returns beginning point of curve i
    const Point<float>* curveEnd(int);      // returns beginning point of curve i
    void splitAt(float, float, float=0.0f);     // splits at x and y of 0.0 to 1.0
    void rawSplitAt(float, float, float=0.0f);  // splits at x and y of 0.0 to 1.0
    void setParent(Component*);             // sets parent object for updating visual components
    void ensureWrap();                      // ensures the last point wraps around to first point to prevent clicking
    void remove(SSHandle*);                 // attempts to remove curve matching the passed handle
    int getIndex(SSHandle*);                // gets index from a handle reference
    void setNewPos(int, Point<float>);      // sets new position of curve beginning
    float getPow(int);                      // returns power of curve at index i
    void setPow(int, float);                // sets power of index i to pow
    void rawSetPow(int, float);             // sets power of index i to pow, ONLY USE FOR LOADING CURVES, DOESN'T SANITY CHECK/ADJUST!!!
    bool isRising(int);                     // returns true if curve is rising, false if falling
    void clearCurve();                      // clears all but the first point, which is instead reset.
};



#endif  // SSMULTICURVE_H_INCLUDED
