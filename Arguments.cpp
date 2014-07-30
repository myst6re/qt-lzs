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
#include <QDir>
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

const QStringList &Arguments::paths() const
{
	return _paths;
}

QString Arguments::destination(const QString &path) const
{
	QString destPath,
	        sourceFilename = path.mid(path.lastIndexOf('/') + 1);

	if (!_directory.isEmpty()) {
		destPath = QString("%1/%2").arg(_directory, sourceFilename);
	} else {
		destPath = sourceFilename;
	}

	if(_decompress) {
		return destPath + ".dec";
	}
	return destPath + ".lzs";
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
			_paths << arg;
		}
	}

	if (!_hasHeader && _validateHeader) {
		_validateHeader = false;
	}

	wilcardParse();
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
	out << "unlzs [files...] [output directory]\n";
#else
	out << "lzs [-d] [files...] [output directory]\n";
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

QStringList Arguments::searchFiles(const QString &path)
{
	int index = path.lastIndexOf('/');
	QString dirname, filename;

	if (index > 0) {
		dirname = path.left(index);
		filename = path.mid(index + 1);
	} else {
		filename = path;
	}

	QDir dir(dirname);
	QStringList entryList = dir.entryList(QStringList(filename), QDir::Files);
	int i=0;
	foreach (const QString &entry, entryList) {
		entryList.replace(i++, dir.filePath(entry));
	}
	return entryList;
}

void Arguments::wilcardParse()
{
	QStringList paths;

	foreach (const QString &path, _paths) {
		if (path.contains('*') || path.contains('?')) {
			paths << searchFiles(QDir::fromNativeSeparators(path));
		} else {
			paths << QDir::fromNativeSeparators(path);
		}
	}

	if (!paths.isEmpty()) {
		// Output directory
		if (QDir(paths.last()).exists()) {
			_directory = paths.takeLast();
		}

		_paths = paths;
	}
}
