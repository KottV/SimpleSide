/*
  ==============================================================================

    SSHandle.h
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

#ifndef SSHANDLE_H_INCLUDED
#define SSHANDLE_H_INCLUDED

#include "../../JuceLibraryCode/JuceHeader.h"

//==============================================================================
/*
*/
class SSHandle    : public Component
{
public:
    static float baseSize;
    static float indicatorSize;
    static float outlinePercent;
    static float animSpeed;
    
    SSHandle(void*);
    SSHandle(void*, float, float);
    ~SSHandle();

    void paint (Graphics&) override;
    void resized() override;
    
    void handleClick();         // Only call if we're already sure mouse event happened inside
    void center();              // Use to determine if an event is inside center+radius of baseSize
    void refreshParent();       // use to request a draw refresh from the parent CurveView
    
    void mouseEnter(const MouseEvent &event) override;
    void mouseExit(const MouseEvent &event) override;
    void mouseMove(const MouseEvent &event) override;
    void mouseDown(const MouseEvent &event) override;
    void mouseUp(const MouseEvent &event) override;
    void mouseDrag(const MouseEvent &event) override;
    
    
private:
    enum HandleType { HANDLE_ANCHOR, HANDLE_EXP, HANDLE_GUIDE, HANDLE_SIGMOID };
    HandleType type;
    float currSize;             // current draw size, with anim considered (getCurrTime(), abs difference)
    float animProg;             // progress of our animation, from 0 to 1 and back
    int ansz;                   // size of animated circle handle, so we can "bounce"
    Point<int> originalPos;   // used as an anchor for various movement tasks
    
    MouseListener mouse;
    
    void* parent;
    
    
    class AnimRedrawTimer : public Timer
    {
    private:
        SSHandle* p;
    public:
        AnimRedrawTimer(SSHandle* p) {
            this->p = p;
        }
        void timerCallback() override {
            p->refreshParent();
            if (p->isMouseOver()) {
                if (p->animProg < 1.0f) {
                    p->animProg += 0.1*animSpeed;
                    p->ansz = outlinePercent*baseSize*sqrtf(p->animProg);
                }
            } else {
                if (p->animProg > 0.0f) {
                    p->animProg -= 0.1*animSpeed;
                    p->ansz = outlinePercent*baseSize*sqrtf(p->animProg);
                }
            }
            
            if (p->animProg >= 1.0 || p->animProg <= 0) {
                stopTimer();
            }
        }
    };
    
    AnimRedrawTimer animator;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (SSHandle)
};

#endif  // SSHANDLE_H_INCLUDED
