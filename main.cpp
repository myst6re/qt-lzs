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

	if (args.help() || args.paths().isEmpty()) {
		args.showHelp();
	} else {
		bool hasMultipleFiles = args.paths().count() > 1;

		foreach (const QString &path, args.paths()) {

			if (hasMultipleFiles) {
				stdObserver.setFilename(QDir::toNativeSeparators(path));
			}

			QFile f(path);
			if (f.open(QIODevice::ReadOnly)) {

				QFile dest(args.destination(path));
				bool destExistsBefore = dest.exists();
				if (dest.open(QIODevice::WriteOnly | QIODevice::Truncate)) {
					QByteArray data;
					bool needToRemoveDest = false;

					if (args.offset() > 0) {
						dest.seek(args.offset());
					}

					if (args.size() == 0) {
						qWarning() << "Please specify a size > 0.";
						needToRemoveDest = true;
					} else {
						if (args.decompress()) {
							if (args.hasHeader() && f.read((char *)&lzsSize, 4) != 4) {
								qWarning() << "Error when reading file." << QDir::toNativeSeparators(path);
								needToRemoveDest = true;
							} else {
								if (args.hasHeader() && args.validateHeader() && lzsSize != f.size() - 4) {
									qWarning() << "Invalid LZS header." << QDir::toNativeSeparators(path);
									needToRemoveDest = true;
								} else {
									if (args.size() < 0) {
										data = f.readAll();
									} else {
										data = f.read(args.size());
									}
									dest.write(LZS::decompressAll(data, observer));
								}
							}
						} else {
							if (args.size() < 0) {
								data = f.readAll();
							} else {
								data = f.read(args.size());
							}
							const QByteArray &lzsed = LZS::compress(data, observer);
							lzsSize = lzsed.size();
							dest.write((char *)&lzsSize, 4);
							dest.write(lzsed);
						}
					}

					if (!destExistsBefore && needToRemoveDest) {
						dest.remove();
					}

					dest.close();
				} else {
					qWarning() << "Error opening destination file." << dest.errorString();
				}

				f.close();
			} else {
				qWarning() << "Error opening source file." << QDir::toNativeSeparators(path) << f.errorString();
			}

			if (hasMultipleFiles) {
				printf("\n");
			}
		}
	}

	QTimer::singleShot(0, &a, SLOT(quit()));

	return a.exec();
}
