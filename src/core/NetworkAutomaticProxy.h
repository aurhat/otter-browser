/**************************************************************************
* Otter Browser: Web browser controlled by the user, not vice-versa.
* Copyright (C) 2014 Jan Bajer aka bajasoft <jbajer@gmail.com>
* Copyright (C) 2014 - 2017 Michal Dutkiewicz aka Emdek <michal@emdek.pl>
*
* This program is free software: you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation, either version 3 of the License, or
* (at your option) any later version.
*
* This program is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
* GNU General Public License for more details.
*
* You should have received a copy of the GNU General Public License
* along with this program. If not, see <http://www.gnu.org/licenses/>.
*
**************************************************************************/

#ifndef OTTER_NETWORKAUTOMATICPROXY_H
#define OTTER_NETWORKAUTOMATICPROXY_H

#include <QtNetwork/QNetworkProxy>
#include <QtNetwork/QNetworkReply>
#include <QtQml/QJSEngine>

namespace Otter
{

class PacUtils final : public QObject
{
	Q_OBJECT

public:
	explicit PacUtils(QObject *parent = nullptr);

public slots:
	void alert(const QString &message) const;
	QString dnsResolve(const QString &host) const;
	QString myIpAddress() const;
	int dnsDomainLevels(const QString &host) const;
	bool isInNet(const QString &host, const QString &pattern, const QString &mask) const;
	bool isPlainHostName(const QString &host) const;
	bool isResolvable(const QString &host) const;
	bool localHostOrDomainIs(const QString &host, QString domain) const;
	bool dnsDomainIs(const QString &host, const QString &domain) const;
	bool shExpMatch(const QString &string, const QString &expression) const;
	bool weekdayRange(QString fromDay, QString toDay = QString(), const QString &gmt = QLatin1String("gmt")) const;
	bool dateRange(const QVariant &arg1, const QVariant &arg2 = QVariant(), const QVariant &arg3 = QVariant(), const QVariant &arg4 = QVariant(), const QVariant &arg5 = QVariant(), const QVariant &arg6 = QVariant(), const QString &gmt = QLatin1String("gmt")) const;
	bool timeRange(const QVariant &arg1, const QVariant &arg2, const QVariant &arg3, const QVariant &arg4, const QVariant &arg5, const QVariant &arg6, const QString &gmt = QLatin1String("gmt")) const;

protected:
	bool isInRange(const QVariant &valueOne, const QVariant &valueTwo, const QVariant &actualValue) const;

private:
	static QStringList m_months;
	static QStringList m_days;
};

class NetworkAutomaticProxy final : public QObject
{
	Q_OBJECT

public:
	explicit NetworkAutomaticProxy(const QString &path, QObject *parent = nullptr);

	void setPath(const QString &path);
	QString getPath() const;
	QVector<QNetworkProxy> getProxy(const QString &url, const QString &host);
	bool isValid() const;

protected:
	bool setup(const QString &script);

protected slots:
	void setup();

private:
	QNetworkReply *m_reply;
	QJSEngine m_engine;
	QJSValue m_findProxy;
	QString m_path;
	QHash<QString, QVector<QNetworkProxy> > m_proxies;
	bool m_isValid;
};

}

#endif
