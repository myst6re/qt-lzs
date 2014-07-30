/****************************************************************************
 ** Copyright (C) 2009-2012 Arzel Jérôme <myst6re@gmail.com>
 **
 ** This program is free software: you can redistribute it and/or modify
 ** it under the terms of the GNU General Public License as published by
 ** the Free Software Foundation, either version 3 of the License, or
 ** (at your option) any later version.
 **
 ** This program is distributed in the hope that it will be useful,
 ** but WITHOUT ANY WARRANTY; without even the implied warranty of
 ** MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 ** GNU General Public License for more details.
 **
 ** You should have received a copy of the GNU General Public License
 ** along with this program.  If not, see <http://www.gnu.org/licenses/>.
 ****************************************************************************/
#include "LZSObserver.h"
#include <stdio.h>

LZSObserver::LZSObserver()
{
}

LZSObserverPercent::LZSObserverPercent()
{
}

void LZSObserverPercent::setValue(int value)
{
	int percent = value * 100.0 / (double)maximum();
	if (percent != _lastPercent) {
		_lastPercent = percent;
		setPercent(percent);
	}
}

LZSObserverStdOut::LZSObserverStdOut()
{
}

void LZSObserverStdOut::setPercent(int percent)
{
	printf("[%d%%] %s\r", percent, qPrintable(_filename));
}
