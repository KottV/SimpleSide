    _____ _                 __    _____ _     __   
   / ___//_/___ ___  ____  / /__ / ___//_/___/ /__ 
   \__ \/ / __ `__ \/ __ \/ / _ \\__ \/ / __  / _ \
  ___/ / / / / / / / /_/ / /  __/__/ / / /_/ /  __/
 /____/_/_/ /_/ /_/ .___/_/\___/____/_/\__,_/\___/ 
                 /_/                               
 
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 *  Copyright � 2017 Armando Montanez                                      *
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
 
 Description
 -------------------------
   SimpleSide is an audio plugin that uses a curve to change volume
 over a temp-synced period. Think of it like a drawable volume LFO.
 
 Features
 -------------------------
 - Adjustable rate that temp-syncs with host.
 - Adjustable ramp-up or ramp-down for each sub-curve.
 - Unlimited number of sub-curves.
 - Wet/dry mix knob to adjust the blend of the plugin with the original
   signal.
 - Sample-accurate automation of rate and blend.
 
 Usage
 -------------------------
 - Right click/cmd click a location to add a point.
 - Right click/cmd click a handle (dot) to remove the curve that lies
   to the right of the handle.
 - Click and drag a handle to move it.
 - Hold shift while dragging a handle to lock horizontal/vertical
   movement axis.
 - Drag up/down on a curve to adjust its ramp up/down.
 - Alt+click a curve to reset its ramp value to zero.
 - Hold shift while dragging a curve for more precise ramp adjustment.
 - Drag rate readout up/down to increase/decrease in multiples of two.
 - Drag blend knob horizontally or vertically to adjust wet/dry mix.
 
 Changelog
 -------------------------
 1.0.1 - 04/19/2016
 - Fixed sample delay between channels, FL studio use now transparent!
 - Resolved a few crashes in Logic Pro X
 
 1.0.0 - 04/07/2016
 - Initial release
 
 Todo/known bugs
 -------------------------
 - [bug]     Swapping two instances of SimpleSide cause erratic
             behavior/crashes. (Logic Pro X)
 - [optimize]Processing block calculates gain twice for each sample (L/R)
 - [feature] Add a few static presets for templates. (duck, trim, etc)
 
 About Me
 -------------------------
   Hey, my name is Armando Montanez! I'm currently studying at the
 University of California, Merced for Computer Science and Engineering.
 I first began audio production in 2012, and like every bedroom producer,
 was faced with the high cost of most audio software. As I've grown as a
 producer, mix engineer, and software developer I've decided to make
 it my mission to offer a few free/cheap plugins that I feel every
 producer/mix engineer should have in their toolkit.
 
   I'm still new to the plugin development scene, so if you find any
 bugs or have suggestions, please feel free to contact me! Donations
 are very appreciated as well; they help motivate me to continue investing
 my time into continued development and new plugins!
 
   Thank you for taking your time to read this, enjoy the plugin!
 
 Contact:
 + development@armandomontanez.com
 
 Donations:
 + http://paypal.me/ArmandoMontanez
 
 One person gives freely, yet gains even more;
  another withholds unduly, but comes to poverty.
   - Proverbs 11:24 (NIV)
   
 AKA more free plugins are on the way!
 
 Hope you enjoy! \(^.^)/