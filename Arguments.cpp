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
#include "Arguments.h"
#include <QCoreApplication>
#include <QStringList>

Arguments::Arguments() :
	_decompress(
#ifndef UNLZS
		false
#else
		true
#endif
		), _help(false), _quiet(false),
    _validateHeader(true), _hasHeader(true)
{
	parse();
}

const QString &Arguments::path() const
{
	return _path;
}

QString Arguments::destPath() const
{
	if(_decompress) {
		return _path + ".dec";
	}
	return _path + ".lzs";
}

bool Arguments::decompress() const
{
	return _decompress;
}

bool Arguments::help() const
{
	return _help;
}

bool Arguments::quiet() const
{
	return _quiet;
}

bool Arguments::validateHeader() const
{
	return _validateHeader;
}

bool Arguments::hasHeader() const
{
	return _hasHeader;
}

void Arguments::parse()
{
	QStringList args = qApp->arguments();
	args.removeFirst(); // Application path

#ifndef UNLZS
	_decompress = false;
#else
	_decompress = true;
#endif
	_help = _quiet = false;

	foreach (const QString &arg, args) {
		if (arg == "-d" || arg == "--decompress" || arg == "--uncompress") {
			_decompress = true;
		} else if (arg == "-h" || arg == "--help") {
			_help = true;
		} else if (arg == "-q" || arg == "--quiet") {
			_quiet = true;
		} else if (arg == "--no-header-test") {
			_validateHeader = false;
		} else if (arg == "--no-header") {
			_hasHeader = false;
		} else {
			_path = arg;
		}
	}

	if (!_hasHeader && _validateHeader) {
		_validateHeader = false;
	}
}

QMap<QString, QString> Arguments::commands() const
{
	QMap<QString, QString> options;

#ifndef UNLZS
	options["-d --decompress --uncompress"] = "Decompress.";
#endif
	options["-h --help"] = "Show this help and quit.";
	options["--no-header"] = "The input file starts directly with compressed data.";
	options["--no-header-test"] = "Do not test the header integrity.";
	options["-q --quiet"] = "Suppress all outputs";

	return options;
}
