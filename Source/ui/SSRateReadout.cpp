/*
  ==============================================================================

    SSRateReadout.cpp
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

#include "../../JuceLibraryCode/JuceHeader.h"
#include "SSRateReadout.h"

//==============================================================================
SSRateReadout::SSRateReadout()
{
    // In your constructor, you should add any child components, and
    // initialise any special settings that your component needs.
    frames = juce::ImageCache::getFromMemory(BinaryData::ReadoutFilmstrip_png, BinaryData::ReadoutFilmstrip_pngSize);
    setBounds(636, 72, 141, 67);
    setSliderStyle(juce::Slider::SliderStyle::RotaryVerticalDrag);
    setRange(-3.0, 6.0, 1.0);
    setValue(0.3);
}

SSRateReadout::SSRateReadout(double initialValue)
{
    // In your constructor, you should add any child components, and
    // initialise any special settings that your component needs.
    frames = juce::ImageCache::getFromMemory(BinaryData::ReadoutFilmstrip_png, BinaryData::ReadoutFilmstrip_pngSize);
    setBounds(636, 72, 141, 67);
    setSliderStyle(juce::Slider::SliderStyle::RotaryVerticalDrag);
    setRange(-3.0, 6.0, 1.0);
    setValue(initialValue);
}

SSRateReadout::~SSRateReadout()
{
}

void SSRateReadout::paint (juce::Graphics& g)
{
    g.drawImageAt(frames, 0, (-1.0*(-getValue()+6.0))*67);
}

void SSRateReadout::resized()
{
    // This method is where you should set the bounds of any child
    // components that your component contains..

}
