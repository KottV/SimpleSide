/*
  ==============================================================================

    CurveView.cpp
    Created: 13 Mar 2017 8:27:13am
    Author:  Armando Montanez

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

#include "../../JuceLibraryCode/JuceHeader.h"
#include "CurveView.h"
#include "SSHandle.h"

//==============================================================================

int CurveView::CV_HEIGHT = 478;                                 // view height, adjustable
int CurveView::CV_WIDTH = 598;                                  // view width,  adjustable

const int& CurveView::VIEW_HEIGHT = CurveView::CV_HEIGHT;       // static public width,  not editable
const int& CurveView::VIEW_WIDTH = CurveView::CV_WIDTH;         // static public height, not editable

//==============================================================================

CurveView::CurveView(SSMultiCurve* c) {
    // In your constructor, you should add any child components, and
    // initialise any special settings that your component needs.
    setBounds(12, 12, 598, 478);
    curves = c;
    for (int i = 0; i < curves->count(); i++)
        addAndMakeVisible(curves->handles[i]);
    highlightRegion = -1;
    
    playhead = juce::ImageCache::getFromMemory(BinaryData::Playhead_png, BinaryData::Playhead_pngSize);
}

CurveView::~CurveView()
{
}

void CurveView::addHandle(SSHandle* h) {
    addAndMakeVisible(h);
}

void CurveView::paint (juce::Graphics& g)
{
    /* This demo code just fills the component's background and
       draws some placeholder text to get you started.

       You should replace everything in this method with your own
       drawing code..
    */

    if (isMouseButtonDown())
        g.setColour(juce::Colour(0.5f, 0.2f, 0.3f, 0.35f));
    else
        g.setColour (juce::Colour(0.5f, 0.5f, 0.5f, 0.5f));
    if (highlightRegion >= 0) {
        g.fillRect((int)(curves->handleStart(highlightRegion)->getX()*CV_WIDTH), 0, (int)((curves->curveEnd(highlightRegion)->getX()-curves->handleStart(highlightRegion)->getX())*CV_WIDTH), CV_HEIGHT);
    }
    
    // draw curve
    g.setColour (juce::Colours::white);
    for (float i = 2.0/CV_WIDTH; i <= 1.0; i+=1.0/CV_WIDTH) {
        g.drawLine(CV_WIDTH*(i-1.0/CV_WIDTH), CV_HEIGHT*(1-curves->at(i-1.0/CV_WIDTH)), CV_WIDTH*i, CV_HEIGHT*(1-curves->at(i)), 2.0f);
    }
    
    g.drawImageAt(playhead, curves->liveViewTime*CurveView::VIEW_WIDTH-9, 0);
    
}
void CurveView::mouseEnter(const juce::MouseEvent &event) {
    mouseOver = true;
}
void CurveView::mouseExit(const juce::MouseEvent &event) {
    mouseOver = false;
    highlightRegion = -1;
}
void CurveView::mouseMove(const juce::MouseEvent &event) {
    if (isMouseOver()) {
        highlightRegion = curves->curveAt(event.getPosition().x/(float)CV_WIDTH);
        repaint();
    }
}

void CurveView::mouseDown(const juce::MouseEvent &event) {
    if (event.mods.isRightButtonDown() || (event.mods.isLeftButtonDown() && event.mods.isCommandDown())) {
        if (event.mods.isShiftDown()) {
            curves->splitAt(event.x/(float)CV_WIDTH, curves->at(event.x/(float)CV_WIDTH));
        } else {
            curves->splitAt(event.x/(float)CV_WIDTH, 1-event.y/(float)CV_HEIGHT);
        }
        repaint();
    } else if (event.mods.isLeftButtonDown() && highlightRegion != -1){
        if (event.mods.isAltDown())
            curves->setPow(highlightRegion, 0.0f);
        origPow = curves->getPow(highlightRegion);
        mouseLocSnap.x = event.getMouseDownScreenPosition().x;
        mouseLocSnap.y = event.getMouseDownScreenPosition().y;
        setMouseCursor(juce::MouseCursor::NoCursor);
        juce::Desktop::getInstance().getMainMouseSource().enableUnboundedMouseMovement(true, false);
    }
}

void CurveView::mouseDrag(const juce::MouseEvent &event) {
    if (event.mods.isLeftButtonDown() && highlightRegion != -1) {
        int dist = event.getDistanceFromDragStartY();
        if (event.mods.isShiftDown())
            curves->setPow(highlightRegion, origPow+dist*0.01);
        else
            curves->setPow(highlightRegion, origPow+dist*0.1f);
        repaint();
    }
}

void CurveView::mouseUp(const juce::MouseEvent &event) {
    if (event.mods.isLeftButtonDown() && highlightRegion != -1){
        juce::Desktop::getInstance().getMainMouseSource().enableUnboundedMouseMovement(false, false);
        juce::Desktop::getInstance().getMainMouseSource().setScreenPosition(mouseLocSnap);
        setMouseCursor(juce::MouseCursor::NormalCursor);
    }
}

void CurveView::resized()
{
    // This method is where you should set the bounds of any child
    // components that your component contains..

}
