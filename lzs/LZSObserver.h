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
#ifndef LZSOBSERVER_H
#define LZSOBSERVER_H

class LZSObserver
{
public:
	LZSObserver();

	inline void setMaximum(int maximum) {
		_maximum = maximum;
	}

	inline int maximum() const {
		return _maximum;
	}

	virtual void setValue(int value)=0;
private:
	int _maximum;
};

class LZSObserverStdOut : public LZSObserver
{
public:
	LZSObserverStdOut();
	virtual void setValue(int value);
private:
	int _lastPercent;
};

#endif // LZSOBSERVER_H
