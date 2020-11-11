/*
  ==============================================================================

  * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
  *  Copyright � 2017 Armando Montanez                                      *
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

#include "PluginProcessor.h"
#include "PluginEditor.h"


//==============================================================================
SimpleSideAudioProcessorEditor::SimpleSideAudioProcessorEditor (SimpleSideAudioProcessor& p)
    : AudioProcessorEditor (&p), processor (p), mainView(&(processor.primaryCurve)), mixKnob(processor.mixValue), rateReadout(processor.rateValue), graphicsUpdateTimer(this)
{
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    setSize (800, 500);
    background = ImageCache::getFromMemory(BinaryData::background_png, BinaryData::background_pngSize);
    addAndMakeVisible(&mainView);
    addAndMakeVisible(&mixKnob);
    addAndMakeVisible(&rateReadout);
    processor.primaryCurve.setParent(&mainView);
    graphicsUpdateTimer.startTimerHz(60);
}

SimpleSideAudioProcessorEditor::~SimpleSideAudioProcessorEditor()
{
    processor.primaryCurve.setParent(NULL);
}

//==============================================================================
void SimpleSideAudioProcessorEditor::paint (Graphics& g)
{
    g.drawImageAt(background, 0, 0);
    // debugging stuff
	/*
    if (false) {
        g.setColour(Colours::white);
        g.drawSingleLineText("this is some text", 0, 0);
        g.drawSingleLineText(std::to_string(processor.currentTime), 0, 10);
        g.drawSingleLineText(std::to_string(processor.numBeats), 0, 20);
        g.drawSingleLineText(std::to_string(processor.position), 0, 30);
        g.drawSingleLineText(std::to_string(processor.sizeOfSample), 0, 40);
        g.drawSingleLineText(std::to_string(processor.finalPosition), 0, 50);
        g.drawSingleLineText(std::to_string(processor.samplesPerSec), 0, 60);
        g.drawSingleLineText(std::to_string(processor.hostSecPerBeat), 0, 70);
        g.drawSingleLineText(std::to_string(processor.samplesPerSec*processor.hostSecPerBeat), 0, 80);
    }
	*/
}

void SimpleSideAudioProcessorEditor::resized()
{
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..
}
