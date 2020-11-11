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

#ifndef PLUGINPROCESSOR_H_INCLUDED
#define PLUGINPROCESSOR_H_INCLUDED

#include "../JuceLibraryCode/JuceHeader.h"
#include "./types/SSMultiCurve.h"
#include "./automation/MixAutomator.h"
#include "./automation/RateAutomator.h"


//==============================================================================
/**
*/
class SimpleSideAudioProcessor  : public juce::AudioProcessor
{
public:
    //==============================================================================
    SimpleSideAudioProcessor();
    ~SimpleSideAudioProcessor();

    //==============================================================================
    void prepareToPlay (double sampleRate, int samplesPerBlock) override;
    void releaseResources() override;

   #ifndef JucePlugin_PreferredChannelConfigurations
    bool isBusesLayoutSupported (const BusesLayout& layouts) const override;
   #endif

    void processBlock (juce::AudioSampleBuffer&, juce::MidiBuffer&) override;

    //==============================================================================
    juce::AudioProcessorEditor* createEditor() override;
    bool hasEditor() const override;

    //==============================================================================
    const juce::String getName() const override;

    bool acceptsMidi() const override;
    bool producesMidi() const override;
    bool isParameterAutomatable (int parameterIndex) const override;
    double getTailLengthSeconds() const override;

    //==============================================================================
    int getNumPrograms() override;
    int getCurrentProgram() override;
    void setCurrentProgram (int index) override;
    const juce::String getProgramName (int index) override;
    void changeProgramName (int index, const juce::String& newName) override;

    //==============================================================================
    void getStateInformation (juce::MemoryBlock& destData) override;
    void setStateInformation (const void* data, int sizeInBytes) override;
    
    //==============================================================================
    SSMultiCurve primaryCurve;
    double currentTime;
    double numBeats;
    float position;
    float sizeOfSample;
    float finalPosition;
    double samplesPerSec;
    double hostSecPerBeat;
    
    double mixValue;
    double rateValue;
    
    MixAutomator* mixAutomationReference;
    RateAutomator* rateAutomationReference;

private:
    //==============================================================================
    juce::AudioPlayHead::CurrentPositionInfo playHeadLoc;
    juce::AudioPlayHead* hostPlayHead;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (SimpleSideAudioProcessor)
};


#endif  // PLUGINPROCESSOR_H_INCLUDED
