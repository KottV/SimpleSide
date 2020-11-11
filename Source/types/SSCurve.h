/*
  ==============================================================================

    SSCurve.h
    Created: 13 Mar 2017 8:41:14am
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

#ifndef SSCURVE_H_INCLUDED
#define SSCURVE_H_INCLUDED

#include "../JuceLibraryCode/JuceHeader.h"

class SSCurve {
private:
    juce::Point<float> entry;
    juce::Point<float> exit;
    float pwr;
    float rawExp;
public:
    SSCurve();
    SSCurve(juce::Point<float>, juce::Point<float>, float);
    SSCurve* splitAt(juce::Point<float>, float = 0.0f);
    SSCurve* rawSplitAt(juce::Point<float>, float = 0.0f); // use for loading curves
    double getY(double);
    bool isInRange(float);
    juce::Point<float>* getEntry();
    juce::Point<float>* getExit();
    void setExitY(float);
    void setEntryY(float);
    float getPow();
    void setPow(float);
    void rawSetPow(float); // only use when loading known valid save parameters!
    bool isRising();
};



#endif  // SSCURVE_H_INCLUDED
