/*
  ==============================================================================

    RateAutomator.h
    Created: 30 Mar 2017 7:31:04pm
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

#ifndef RATEAUTOMATOR_H_INCLUDED
#define RATEAUTOMATOR_H_INCLUDED

#include "../../JuceLibraryCode/JuceHeader.h"
#include <string>

class RateAutomator : public juce::AudioProcessorParameter
{
public:
    RateAutomator(juce::AudioProcessor* p);
    float getValue() const override;
    void setValue(float newValue) override;
    
    float getDefaultValue() const override { return 0.3f; }
    juce::String getName(int maximumStringLength) const override { return "Rate"; }
    juce::String getLabel() const override { return ""; }
    float getValueForText(const juce::String& text) const override { return std::stof(text.toStdString(), nullptr); }
private:
    juce::AudioProcessor* processor;
};



#endif  // RATEAUTOMATOR_H_INCLUDED
