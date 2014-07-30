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

#include <QString>

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

class LZSObserverPercent : public LZSObserver
{
public:
	LZSObserverPercent();
	void setValue(int value);
	virtual void setPercent(int percent)=0;
private:
	int _lastPercent;
};

class LZSObserverStdOut : public LZSObserverPercent
{
public:
	LZSObserverStdOut();
	inline void setFilename(const QString &filename) {
		_filename = filename;
	}
	virtual void setPercent(int percent);
private:
	QString _filename;
};

#endif // LZSOBSERVER_H
