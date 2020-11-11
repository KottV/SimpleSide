/*
  ==============================================================================

    SSMixKnob.cpp
    Created: 30 Mar 2017 5:05:44pm
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
#include "SSMixKnob.h"

//==============================================================================
SSMixKnob::SSMixKnob()
{
    // In your constructor, you should add any child components, and
    // initialise any special settings that your component needs.
    frames = ImageCache::getFromMemory(BinaryData::MixKnobFilmstrip_png, BinaryData::MixKnobFilmstrip_pngSize);
    setBounds(627, 206, 156, 156);
    setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    setRange(0.0, 1.0, 0.0);
    setValue(1.0);
}

SSMixKnob::SSMixKnob(double initialValue)
{
    // In your constructor, you should add any child components, and
    // initialise any special settings that your component needs.
    frames = ImageCache::getFromMemory(BinaryData::MixKnobFilmstrip_png, BinaryData::MixKnobFilmstrip_pngSize);
    setBounds(627, 206, 156, 156);
    setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    setRange(0.0, 1.0, 0.0);
    setValue(initialValue);
}

SSMixKnob::~SSMixKnob()
{
}

void SSMixKnob::paint (Graphics& g)
{
    g.drawImageAt(frames, 0, (int)(-1.0*getValue()*255)*156);
}

void SSMixKnob::resized()
{
    // This method is where you should set the bounds of any child
    // components that your component contains..

}
