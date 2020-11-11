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

#include "PluginProcessor.h"
#include "PluginEditor.h"
#include "./automation/MixAutomator.h"
#include "./automation/RateAutomator.h"


//==============================================================================
SimpleSideAudioProcessor::SimpleSideAudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
     : juce::AudioProcessor (BusesProperties()
                     #if ! JucePlugin_IsMidiEffect
                      #if ! JucePlugin_IsSynth
                       .withInput  ("Input",  juce::AudioChannelSet::stereo(), true)
                      #endif
                       .withOutput ("Output", juce::AudioChannelSet::stereo(), true)
                     #endif
                       )
#endif
{
    mixValue = 1.0;
    rateValue = 0.0;
    addParameter(mixAutomationReference = new MixAutomator(this));
    addParameter(rateAutomationReference = new RateAutomator(this));
}

SimpleSideAudioProcessor::~SimpleSideAudioProcessor()
{
}

//==============================================================================
const juce::String SimpleSideAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool SimpleSideAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool SimpleSideAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}


bool SimpleSideAudioProcessor::isParameterAutomatable (int parameterIndex) const {
    return getParameters()[parameterIndex]->isAutomatable();
};

double SimpleSideAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int SimpleSideAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int SimpleSideAudioProcessor::getCurrentProgram()
{
    return 0;
}

void SimpleSideAudioProcessor::setCurrentProgram (int index)
{
}

const juce::String SimpleSideAudioProcessor::getProgramName (int index)
{
    return juce::String("Default");
}

void SimpleSideAudioProcessor::changeProgramName (int index, const juce::String& newName)
{
}

//==============================================================================
void SimpleSideAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    // Use this method as the place to do any pre-playback
    // initialisation that you need..
    // senisble default sample rate
    samplesPerSec = getSampleRate();
    hostPlayHead = getPlayHead();
    hostPlayHead->getCurrentPosition(playHeadLoc);
    float hostBeatPerSec;
    if ((playHeadLoc.bpm > 1.0 && playHeadLoc.bpm < 450.0)) {
        hostSecPerBeat = 60.0/128.0;
        hostBeatPerSec = 128.0/60.0;
    } else {
        hostSecPerBeat = (60.0/playHeadLoc.bpm);
        hostBeatPerSec = (playHeadLoc.bpm/60.0);
    }
}

void SimpleSideAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool SimpleSideAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
  #if JucePlugin_IsMidiEffect
    ignoreUnused (layouts);
    return true;
  #else
    // This is the place where you check if the layout is supported.
    // In this template code we only support mono or stereo.
    if (layouts.getMainOutputChannelSet() != juce::AudioChannelSet::mono()
     && layouts.getMainOutputChannelSet() != juce::AudioChannelSet::stereo())
        return false;

    // This checks if the input layout matches the output layout
   #if ! JucePlugin_IsSynth
    if (layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet())
        return false;
   #endif

    return true;
  #endif
}
#endif

void SimpleSideAudioProcessor::processBlock (juce::AudioSampleBuffer& buffer, juce::MidiBuffer& midiMessages)
{
    const int totalNumInputChannels  = getTotalNumInputChannels();
    const int totalNumOutputChannels = getTotalNumOutputChannels();
    double rate = pow(2.0, rateValue);

    // In case we have more outputs than inputs, this code clears any output
    // channels that didn't contain input data, (because these aren't
    // guaranteed to be empty - they may contain garbage).
    // This is here to avoid people getting screaming feedback
    // when they first compile a plugin, but obviously you don't need to keep
    // this code if your algorithm always overwrites all the output channels.
    for (int i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
        buffer.clear (i, 0, buffer.getNumSamples());
    
    // this is a mess, clean up!
    hostPlayHead->getCurrentPosition(playHeadLoc);
    hostSecPerBeat = (60.0/playHeadLoc.bpm);
    currentTime = playHeadLoc.editOriginTime + playHeadLoc.timeInSeconds;
    numBeats = (playHeadLoc.editOriginTime+playHeadLoc.timeInSeconds)/hostSecPerBeat;
    position = fmod(numBeats, rate);
    sizeOfSample = 1.0/(samplesPerSec*hostSecPerBeat*rate);
    finalPosition = position/rate;
    float positionBase = finalPosition;
    
    // This is the place where you'd normally do the guts of your plugin's
    // audio processing...
    for (int channel = 0; channel < buffer.getNumChannels(); ++channel)
    {
        float* channelData = buffer.getWritePointer(channel);
        finalPosition = positionBase; // restore base position so each channel starts at same time point
        
        for (int s = 0; s < buffer.getNumSamples(); s++) {
            finalPosition = fmodf(finalPosition, 1.0f);
            double lfoLevel = primaryCurve.at(finalPosition);
            double scale = (exp(lfoLevel)-1)/(1.7182818285); // logarithmically scale
            
            channelData[s] = channelData[s]*(scale)*mixValue+channelData[s]*(1.0-mixValue); // mix
            if (playHeadLoc.isPlaying)
                finalPosition += sizeOfSample;
            primaryCurve.liveViewTime = finalPosition;
        }
    }
}

//==============================================================================
bool SimpleSideAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

juce::AudioProcessorEditor* SimpleSideAudioProcessor::createEditor()
{
    return new SimpleSideAudioProcessorEditor (*this);
}

//==============================================================================
void SimpleSideAudioProcessor::getStateInformation (juce::MemoryBlock& destData)
{
    // Store parameters
    // add size of mix and rate parameters
    int size = sizeof(double)*2;
    // add size of curve (each curve needs three floats, start x, start y, and power)
    size += primaryCurve.count()*sizeof(float)*3;
    // set data size
    destData.setSize(size);
    // copy mix and rate parameters
    destData.copyFrom(&mixValue, 0, sizeof(double));
    destData.copyFrom(&rateValue, sizeof(double), sizeof(double));
    int offset = sizeof(double)*2;
    float data[3];
    for (int i = 0; i < primaryCurve.count(); i++) {
        data[0] = primaryCurve.handleStart(i)->getX();
        data[1] = primaryCurve.handleStart(i)->getY();
        data[2] = primaryCurve.getPow(i);
        destData.copyFrom(data, offset, sizeof(float)*3);
        offset += sizeof(float)*3;
    }
    
    
}

void SimpleSideAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // recall
    int offset = 0;
    std::memcpy(&mixValue, (unsigned char*)data+offset, sizeof(double));
    offset += sizeof(double);
    std::memcpy(&rateValue, (unsigned char*)data+offset, sizeof(double));
    offset += sizeof(double);
    
    // load first point, guarenteed to be present
    float tempData[3];
    std::memcpy(tempData, (unsigned char*)data+offset, sizeof(float));
    offset += sizeof(float);
    std::memcpy(tempData+1, (unsigned char*)data+offset, sizeof(float));
    offset += sizeof(float);
    std::memcpy(tempData+2, (unsigned char*)data+offset, sizeof(float));
    offset += sizeof(float);
    //primaryCurve.clearCurve();
    primaryCurve.setNewPos(0, juce::Point<float>(tempData[0], tempData[1])); // note, tempData[0] should always be 0.0f here!
    primaryCurve.setPow(0, tempData[2]);
    primaryCurve.handles[0]->setBounds((int)(1-SSHandle::baseSize/2), (int)((1-tempData[1])*CurveView::VIEW_HEIGHT-SSHandle::baseSize/2), SSHandle::baseSize, SSHandle::baseSize);
    int i = 1;
    while (offset < sizeInBytes) {
        std::memcpy(tempData, (unsigned char*)data+offset, sizeof(float));
        offset += sizeof(float);
        std::memcpy(tempData+1, (unsigned char*)data+offset, sizeof(float));
        offset += sizeof(float);
        std::memcpy(tempData+2, (unsigned char*)data+offset, sizeof(float));
        offset += sizeof(float);
        primaryCurve.rawSplitAt(tempData[0], tempData[1], tempData[2]);
        primaryCurve.setPow(i-1, primaryCurve.getPow(i-1)); // refresh power of previous curve now that we've added the following one
        i++;
    }
}

//==============================================================================
// This creates new instances of the plugin..
juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new SimpleSideAudioProcessor();
}
