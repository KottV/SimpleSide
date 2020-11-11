/*
  ==============================================================================

    SSRateReadout.h
    Created: 30 Mar 2017 5:06:02pm
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

#ifndef SSRATEREADOUT_H_INCLUDED
#define SSRATEREADOUT_H_INCLUDED

#include "../../JuceLibraryCode/JuceHeader.h"

//==============================================================================
/*
*/
class SSRateReadout    : public juce::Slider
{
public:
    SSRateReadout();
    SSRateReadout(double);
    ~SSRateReadout();

    void paint (juce::Graphics&) override;
    void resized() override;

private:
    juce::Image frames;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (SSRateReadout)
};


#endif  // SSRATEREADOUT_H_INCLUDED
