/*
  ==============================================================================

    RateAutomator.cpp
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

#include "RateAutomator.h"
#include "../PluginProcessor.h"

RateAutomator::RateAutomator(AudioProcessor* p) {
    processor = p;
}

float RateAutomator::getValue() const {
    return (((SimpleSideAudioProcessor*)processor)->rateValue+3)/9;
}

void RateAutomator::setValue(float newValue) {
    ((SimpleSideAudioProcessor*)processor)->rateValue = ((int)(newValue*9) - 3);
}
