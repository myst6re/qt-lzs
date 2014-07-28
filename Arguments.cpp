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
#include <QTextStream>

Arguments::Arguments() :
    _offset(0), _size(-1),
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

qint64 Arguments::offset() const
{
	return _offset;
}

qint64 Arguments::size() const
{
	return _size;
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

	while (!args.isEmpty()) {
		const QString &arg = args.takeFirst();
		bool ok;

		if (arg == "-d" || arg == "--decompress" || arg == "--uncompress") {
			_decompress = true;
		} else if (arg == "-h" || arg == "--help") {
			_help = true;
		} else if (arg == "-q" || arg == "--quiet") {
			_quiet = true;
		} else if (arg == "-p" || arg == "--offset") {
			_offset = args.takeFirst().toInt();
		} else if (arg == "-s" || arg == "--size") {
			_size = args.takeFirst().toInt(&ok);
			if(!ok) {
				_size = -1;
			}
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
	options["-p --offset"] = "Start offset in the source file.";
	options["-s --size"] = "Read at most size bytes (excluding lzs header) from the source file.";
	options["-q --quiet"] = "Suppress all outputs";

	return options;
}

void Arguments::showHelp(int exitCode)
{
	QTextStream out(stdout, QIODevice::WriteOnly);
#ifdef UNLZS
	out << "unlzs file\n";
#else
	out << "lzs [-d] file\n";
#endif
	out << "Options\n";

	QMapIterator<QString, QString> it(commands());
	while (it.hasNext()) {
		it.next();

		out << "\t" << qPrintable(it.key()) << "\n";
		out << "\t" << "\t" << qPrintable(it.value()) << "\n";
	}

	out.flush();

	::exit(exitCode);
}
