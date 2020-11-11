/*
  ==============================================================================

    SSHandle.cpp
    Created: 26 Mar 2017 6:52:37pm
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
#include "SSHandle.h"
#include "CurveView.h"
#include "../types/SSMultiCurve.h"

//==============================================================================
// these can be changed freely to adjust visual experience
//==============================================================================

float SSHandle::baseSize = 24.0f;

float SSHandle::indicatorSize = baseSize*0.35f;
float SSHandle::outlinePercent = 0.9f;

float SSHandle::animSpeed = 2.6;

//==============================================================================

SSHandle::SSHandle(void* p) : animProg(1.0), parent(p), animator(this)
{
    // In your constructor, you should add any child components, and
    // initialise any special settings that your component needs.
    addMouseListener(&mouse, false);
    setBounds((int)(0*CurveView::VIEW_WIDTH-baseSize/2+1), (int)(0*CurveView::VIEW_HEIGHT-baseSize/2+1), baseSize, baseSize);
    originalPos = getPosition();
}

SSHandle::SSHandle(void* p, float x, float y) : animProg(0.0), parent(p), animator(this)
{
    // In your constructor, you should add any child components, and
    // initialise any special settings that your component needs.
    addMouseListener(&mouse, false);
    setBounds((int)(x*CurveView::VIEW_WIDTH-baseSize/2), (int)((1-y)*CurveView::VIEW_HEIGHT-baseSize/2), baseSize, baseSize);
    originalPos = getPosition();
    animator.startTimerHz(60);
}

SSHandle::~SSHandle()
{
}

void SSHandle::paint (Graphics& g)
{
    /* This demo code just fills the component's background and
       draws some placeholder text to get you started.

       You should replace everything in this method with your own
       drawing code..
    */

    //g.setColour (Colours::grey);
    //g.drawRect (getLocalBounds(), 1);   // draw an outline around the component

    g.setColour (Colours::whitesmoke);
    if (isMouseOverOrDragging()) {
        g.fillEllipse(getWidth()/2 - indicatorSize/3, getHeight()/2 - indicatorSize/3, indicatorSize*2/3, indicatorSize*2/3);
        if (animProg < 1.0f) {
            g.drawEllipse(baseSize/2 - (ansz)/2, baseSize/2 - ansz/2, ansz, ansz, 1);
        }
        else
            g.drawEllipse(baseSize/2 - (ansz*outlinePercent)/2-1, baseSize/2 - (ansz*outlinePercent)/2-1, ansz*outlinePercent+fmod((ansz*outlinePercent), 2.0f), ansz*outlinePercent+fmod((ansz*outlinePercent), 2.0f), 1);
    } else {
        g.fillEllipse(getWidth()/2 - indicatorSize/2, getHeight()/2 - indicatorSize/2, indicatorSize, indicatorSize);
        if (animProg > 0.0f) {
            g.drawEllipse(baseSize/2 - (ansz)/2, baseSize/2 - ansz/2, ansz, ansz, 1);
        }
    }
}

void SSHandle::mouseEnter(const juce::MouseEvent &event) {
    animProg = 0;
    animator.startTimerHz(60);
}

void SSHandle::mouseExit(const juce::MouseEvent &event) {
    animator.startTimerHz(60);
}

void SSHandle::mouseMove(const juce::MouseEvent &event) {
    //do nothing, eventually this will move the coresponding point
}

void SSHandle::mouseDown(const juce::MouseEvent &event) {
    if (event.mods.isRightButtonDown() || (event.mods.isLeftButtonDown() && event.mods.isCommandDown()))
        ((SSMultiCurve*)parent)->remove(this);
    else if (event.mods.isLeftButtonDown() && event.mods.isAltDown()) {
        // set curve to straight line
    }
    else if (event.mods.isLeftButtonDown()) {
        setAlpha(0.5f);
        setMouseCursor(MouseCursor::NoCursor);
        Desktop::getInstance().getMainMouseSource().enableUnboundedMouseMovement(true, false);
        refreshParent();
    }
}

void SSHandle::mouseUp(const juce::MouseEvent &event) {
    if (event.mods.isRightButtonDown() || (event.mods.isLeftButtonDown() && event.mods.isCommandDown())) {
        // do nothing, exclude other options
    } else if (event.mods.isLeftButtonDown() && event.mods.isAltDown()) {
        // do nothing, exclude other options
    }
    else if (event.mods.isLeftButtonDown()) {
        setAlpha(1.0f);
        setMouseCursor(MouseCursor::NormalCursor);
        Desktop::getInstance().getMainMouseSource().enableUnboundedMouseMovement(false, false);
        Desktop::getInstance().getMainMouseSource().setScreenPosition(Point<float>(getScreenX()+baseSize/2, getScreenY()+baseSize/2));
        originalPos = getPosition();
        refreshParent();
    }
}

void SSHandle::mouseDrag(const juce::MouseEvent &event) {
    if (event.mods.isRightButtonDown() || (event.mods.isLeftButtonDown() && event.mods.isCommandDown())) {
        // do nothing
     } else if (event.mods.isLeftButtonDown() && event.mods.isAltDown()) {
        // do nothing
    }
    else if (event.mods.isLeftButtonDown()) {
        int i = ((SSMultiCurve*)parent)->getIndex(this);
        if (i == 0) {
            int newX = originalPos.x;
            int newY = originalPos.y + event.getDistanceFromDragStartY();
            if (newY > CurveView::VIEW_HEIGHT - baseSize/2)
                newY = CurveView::VIEW_HEIGHT - baseSize/2;
            else if (newY < 0 - baseSize/2)
                    newY = 0 - baseSize/2;
            setBounds(newX, newY, baseSize, baseSize);
            ((SSMultiCurve*)parent)->setNewPos(i, Point<float>((newX+baseSize/2)/(float)CurveView::VIEW_WIDTH, 1-(newY+baseSize/2)/(float)CurveView::VIEW_HEIGHT));
            
        } else {
            int newX = originalPos.x + event.getDistanceFromDragStartX();
            int newY = originalPos.y + event.getDistanceFromDragStartY();
            if (newY > CurveView::VIEW_HEIGHT - baseSize/1)
                newY = CurveView::VIEW_HEIGHT - baseSize/2;
            else if (newY < 0 - baseSize/2)
                newY = 0 - baseSize/2;
            if (newX > ((SSMultiCurve*)parent)->curveEnd(i)->getX()*CurveView::VIEW_WIDTH - baseSize/2-1)
                newX = ((SSMultiCurve*)parent)->curveEnd(i)->getX()*CurveView::VIEW_WIDTH-baseSize/2-1;
            else if (newX < ((SSMultiCurve*)parent)->handleStart(i-1)->getX()*CurveView::VIEW_WIDTH - baseSize/2 + 1)
                newX = ((SSMultiCurve*)parent)->handleStart(i-1)->getX()*CurveView::VIEW_WIDTH - baseSize/2 + 1;
            if (event.mods.isShiftDown()) {
                if (abs(event.getDistanceFromDragStartX()) > abs(event.getDistanceFromDragStartY())) {
                    newY = originalPos.y;
                } else {
                    newX = originalPos.x;
                }
            }
            setBounds(newX, newY, baseSize, baseSize);
            ((SSMultiCurve*)parent)->setNewPos(i, Point<float>((newX+baseSize/2)/(float)CurveView::VIEW_WIDTH, 1-(newY+baseSize/2)/(float)CurveView::VIEW_HEIGHT));
        }
        refreshParent();
    }
}

void SSHandle::refreshParent() {
    // depreciated, parent refreshes at constant rate, no need for additional draw calls.
    //((SSMultiCurve*)parent)->parent->repaint();
    
}

void SSHandle::resized()
{
    // This method is where you should set the bounds of any child
    // components that your component contains..

}
