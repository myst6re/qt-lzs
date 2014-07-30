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
#ifndef ARGUMENTS_H
#define ARGUMENTS_H

#include <QStringList>
#include <QMap>

class Arguments
{
public:
	Arguments();
	void showHelp(int exitCode = 0);
	const QStringList &paths() const;
	QString destination(const QString &path) const;
	qint64 offset() const;
	qint64 size() const;
	bool decompress() const;
	bool help() const;
	bool quiet() const;
	bool validateHeader() const;
	bool hasHeader() const;
	QMap<QString, QString> commands() const;
private:
	void parse();
	void wilcardParse();
	static QStringList searchFiles(const QString &path);
	QStringList _paths;
	QString _directory;
	qint64 _offset, _size;
	bool _decompress, _help, _quiet,
		_validateHeader, _hasHeader;

};

#endif // ARGUMENTS_H
