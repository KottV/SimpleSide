/*
  ==============================================================================

    MixAutomator.cpp
    Created: 30 Mar 2017 7:30:44pm
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

#include "MixAutomator.h"
#include "../PluginProcessor.h"

MixAutomator::MixAutomator(juce::AudioProcessor* p) {
    processor = p;
}

float MixAutomator::getValue() const {
    return ((SimpleSideAudioProcessor*)processor)->mixValue;
}

void MixAutomator::setValue(float newValue) {
    ((SimpleSideAudioProcessor*)processor)->mixValue = newValue;
}
