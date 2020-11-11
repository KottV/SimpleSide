/*
  ==============================================================================

    VintageKnob.cpp
    Created: 13 Mar 2017 8:35:48am
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

#include "../../JuceLibraryCode/JuceHeader.h"
#include "VintageKnob.h"

//==============================================================================
VintageKnob::VintageKnob()
{
    // In your constructor, you should add any child components, and
    // initialise any special settings that your component needs.

}

VintageKnob::~VintageKnob()
{
}

void VintageKnob::paint (juce::Graphics& g)
{
    /* This demo code just fills the component's background and
       draws some placeholder text to get you started.

       You should replace everything in this method with your own
       drawing code..
    */

    g.fillAll (juce::Colours::white);   // clear the background

    g.setColour (juce::Colours::grey);
    g.drawRect (getLocalBounds(), 1);   // draw an outline around the component

    g.setColour (juce::Colours::lightblue);
    g.setFont (14.0f);
    g.drawText ("VintageKnob", getLocalBounds(),
                juce::Justification::centred, true);   // draw some placeholder text
}

void VintageKnob::resized()
{
    // This method is where you should set the bounds of any child
    // components that your component contains..

}
