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
#include <QCoreApplication>
#include "Arguments.h"
#include "lzs/LZS.h"

void showOptions(const QMap<QString, QString> &options)
{
	QMapIterator<QString, QString> it(options);
	while (it.hasNext()) {
		it.next();

		printf("\t%s\n", qPrintable(it.key()));
		printf("\t\t%s\n\n", qPrintable(it.value()));
	}
}

void help(const Arguments &args)
{
#ifdef UNLZS
	printf("unlzs file\n");
#else
	printf("lzs [-d] file\n");
#endif
	printf("Options\n");
	showOptions(args.commands());
}

int main(int argc, char *argv[])
{
	QCoreApplication a(argc, argv);
#ifdef Q_OS_WIN
	QTextCodec::setCodecForLocale(QTextCodec::codecForName("IBM 850"));
#endif

	Arguments args;
	quint32 lzsSize;
	LZSObserver *observer;
	LZSObserverStdOut stdObserver;

	if (args.quiet()) {
		observer = NULL;
	} else {
		observer = &stdObserver;
	}

	if (args.help() || args.path().isEmpty()) {
		help(args);
	} else {
		QFile f(args.path());
		if (f.open(QIODevice::ReadOnly)) {

			QFile dest(args.destPath());
			if (dest.open(QIODevice::WriteOnly | QIODevice::Truncate)) {
				if (args.decompress()) {
					if (args.hasHeader() && f.read((char *)&lzsSize, 4) != 4) {
						qWarning() << "Error when reading file.";
					} else {
						if (args.hasHeader() && args.validateHeader() && lzsSize != f.size() - 4) {
							qWarning() << "Invalid LZS header.";
						} else {
							dest.write(LZS::decompressAll(f.readAll(), observer));
						}
					}
				} else {
					const QByteArray &lzsed = LZS::compress(f.readAll(), observer);
					lzsSize = lzsed.size();
					dest.write((char *)&lzsSize, 4);
					dest.write(lzsed);
				}

				dest.close();
			} else {
				qWarning() << "Error opening destination file." << dest.errorString();
			}

			f.close();
		} else {
			qWarning() << "Error opening source file." << f.errorString();
		}
	}

	QTimer::singleShot(0, &a, SLOT(quit()));

	return a.exec();
}
