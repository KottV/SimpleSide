/*
  ==============================================================================

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

#ifndef PLUGINEDITOR_H_INCLUDED
#define PLUGINEDITOR_H_INCLUDED

#include "../JuceLibraryCode/JuceHeader.h"
#include "PluginProcessor.h"
#include "./ui/CurveView.h"
#include "./ui/SSMixKnob.h"
#include "./ui/SSRateReadout.h"

//==============================================================================
/**
*/
class SimpleSideAudioProcessorEditor  : public juce::AudioProcessorEditor
{
    SimpleSideAudioProcessor& processor;
    CurveView mainView;
    SSMixKnob mixKnob;
    SSRateReadout rateReadout;
    juce::Image background;
    juce::Image playhead;
    
    class redrawTimer : public juce::Timer
    {
    public:
        redrawTimer(juce::AudioProcessorEditor* e)
        {
            this->editor = e;
        }
        void timerCallback() override {
            editor->repaint();
            if (((SimpleSideAudioProcessorEditor*)editor)->mixKnob.isMouseButtonDown()) {
                ((SimpleSideAudioProcessorEditor*)editor)->processor.mixAutomationReference->beginChangeGesture();
                ((SimpleSideAudioProcessorEditor*)editor)->processor.mixValue = ((SimpleSideAudioProcessorEditor*)editor)->mixKnob.getValue();
                ((SimpleSideAudioProcessorEditor*)editor)->processor.mixAutomationReference->setValueNotifyingHost(((SimpleSideAudioProcessorEditor*)editor)->processor.mixValue);
                ((SimpleSideAudioProcessorEditor*)editor)->processor.mixAutomationReference->endChangeGesture();
            } else
                ((SimpleSideAudioProcessorEditor*)editor)->mixKnob.setValue(((SimpleSideAudioProcessorEditor*)editor)->processor.mixValue);
                
                if (((SimpleSideAudioProcessorEditor*)editor)->rateReadout.isMouseButtonDown()) {
                    ((SimpleSideAudioProcessorEditor*)editor)->processor.rateAutomationReference->beginChangeGesture();
                    ((SimpleSideAudioProcessorEditor*)editor)->processor.rateValue = ((SimpleSideAudioProcessorEditor*)editor)->rateReadout.getValue();
                    ((SimpleSideAudioProcessorEditor*)editor)->processor.rateAutomationReference->setValueNotifyingHost((((SimpleSideAudioProcessorEditor*)editor)->processor.rateValue + 3)/9);
                    ((SimpleSideAudioProcessorEditor*)editor)->processor.rateAutomationReference->endChangeGesture();
                } else
                ((SimpleSideAudioProcessorEditor*)editor)->rateReadout.setValue(((SimpleSideAudioProcessorEditor*)editor)->processor.rateValue);
        }
    private:
        juce::AudioProcessorEditor* editor;
    };
public:
    SimpleSideAudioProcessorEditor (SimpleSideAudioProcessor&);
    ~SimpleSideAudioProcessorEditor();

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;

private:
    //CurveView pluginBody;
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    redrawTimer graphicsUpdateTimer;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (SimpleSideAudioProcessorEditor)
};


#endif  // PLUGINEDITOR_H_INCLUDED
