#ifndef LZSDEVICE_H
#define LZSDEVICE_H

#include <QIODevice>
#include <QFile>

class LZSDevice : public QIODevice
{
public:
	LZSDevice();
	LZSDevice(QObject *parent);
	virtual ~LZSDevice();

	virtual bool atEnd () const;
	//virtual qint64 bytesAvailable () const;
	//virtual qint64 bytesToWrite () const;
	//virtual bool canReadLine () const;
	virtual void close();
	inline bool isSequential() const {
		return false;
	}
	virtual bool open ( OpenMode mode );
	//virtual qint64 pos () const;
	//virtual bool reset ();
	virtual bool seek ( qint64 pos );
	virtual qint64 size() const;
protected:
	virtual qint64 readData(char *data, qint64 maxSize );
	//virtual qint64	readLineData ( char * data, qint64 maxSize );
	virtual qint64 writeData (const char *data, qint64 maxSize );
private:
	
};

#endif // LZSDEVICE_H
